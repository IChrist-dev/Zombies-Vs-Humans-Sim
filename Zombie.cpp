//
// Created by Ian on 11/26/2023.
//

#include <random>
#include <chrono>
#include <algorithm>
#include "Zombie.h"
#include "GameSpecs.h"
#include "City.h"

Zombie::Zombie() = default;

// Parameterized constructor
Zombie::Zombie(City *city, int x, int y) : Organism(city, x, y), infectCount(1), starveCount(1) {
}

Zombie::~Zombie() = default;

// Driver for zombie-specific turn behaviour
void Zombie::organismTurn() {
    // Zombie move method occurs every turn, without conditionals
    this->move();

    if (this->infectCount >= ZOMBIE_BREED) {
        // Zombie has been around for a while, can now multiply
        bool breedResult = this->breed();

        // Reset counter if they did infect someone
        if (breedResult) {
            this->infectCount = 1;
        }
    }

    if (this->starveCount >= ZOMBIE_STARVE) {
        // Zombie will revert to human form
        this->starve();
    }

    // Increment zombie-specific counter(s) for special behaviour
    this->infectCount++;
    this->starveCount++;

    this->endTurn();
}

void Zombie::move() {
    vector<direction> eatOptions;
    vector<direction> emptyOptions; // Only accessed if there are no Humans to eat

    int currentX = this->x;
    int currentY = this->y;

    // Check upper grid boundary
    if ((currentX - 1) >= 0) {
        // Check one cell north
        if (city->grid[currentX - 1][currentY] != nullptr) {
            // Check if occupied cell has a Human
            if (city->grid[currentX - 1][currentY]->getSpecies() == HUMAN_CH) {
                eatOptions.push_back(NORTH);
            }
        } else emptyOptions.push_back(NORTH);
    }

    // Check right grid boundary
    if ((currentY + 1) < width) {
        // Check east cell
        if (city->grid[currentX][currentY + 1] != nullptr) {
            if (city->grid[currentX][currentY + 1]->getSpecies() == HUMAN_CH) {
                eatOptions.push_back(EAST);
            }
        } else emptyOptions.push_back(EAST);
    }

    // Check lower grid boundary
    if ((currentX + 1) < height) {
        // Check one cell south
        if (city->grid[currentX + 1][currentY] != nullptr) {
            if (city->grid[currentX + 1][currentY]->getSpecies() == HUMAN_CH) {
                eatOptions.push_back(SOUTH);
            }
        } else emptyOptions.push_back(SOUTH);
    }

    // Check left grid boundary
    if ((currentY - 1) >= 0) {
        // Check west cell
        if (city->grid[currentX][currentY - 1] != nullptr) {
            if (city->grid[currentX][currentY - 1]->getSpecies() == HUMAN_CH) {
                eatOptions.push_back(WEST);
            }
        } else emptyOptions.push_back(WEST);
    }

    // Diagonal checks
    // Check North-East
    if ((currentX - 1) >= 0 && (currentY + 1) < width) {
        if (city->grid[currentX - 1][currentY + 1] != nullptr) {
            if (city->getOrganism(x - 1, y + 1)->getSpecies() == HUMAN_CH) {
                eatOptions.push_back(NORTHEAST);
            }
        } else emptyOptions.push_back(NORTHEAST);
    }

    // Check South-East
    if ((currentX + 1) > height && (currentY + 1) < width) {
        if (city->grid[currentX + 1][currentY + 1] != nullptr) {
            if (city->getOrganism(x + 1, y + 1)->getSpecies() == HUMAN_CH) {
                eatOptions.push_back(SOUTHEAST);
            }
        } else emptyOptions.push_back(SOUTHEAST);
    }

    // Check South-West
    if ((currentX + 1) > height && (currentY - 1) <= 0) {
        if (city->grid[currentX + 1][currentY - 1] != nullptr) {
            if (city->getOrganism(x + 1, y - 1)->getSpecies() == HUMAN_CH) {
                eatOptions.push_back(SOUTHWEST);
            }
        } else emptyOptions.push_back(SOUTHWEST);
    }

    // Check North-West
    if ((currentX - 1) >= 0 && (currentY - 1) >= 0) {
        if (city->grid[currentX - 1][currentY - 1] != nullptr) {
            if (city->getOrganism(x - 1, y - 1)->getSpecies() == HUMAN_CH) {
                eatOptions.push_back(NORTHWEST);
            }
        } else emptyOptions.push_back(NORTHWEST);
    }

    // Shuffle both lists
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    unsigned secondSeed = seed + 1;
    shuffle(eatOptions.begin(), eatOptions.end(), default_random_engine(seed));
    shuffle(emptyOptions.begin(), emptyOptions.end(), default_random_engine(secondSeed));

    if (!eatOptions.empty()) {
        // Select a Human to eat - Clear current cell
        city->grid[currentX][currentY] = nullptr;

        int newX = currentX, newY = currentY;
        switch (eatOptions.front()) {
            case NORTH:
                newX--;
                break;
            case EAST:
                newY++;
                break;
            case SOUTH:
                newX++;
                break;
            case WEST:
                newY--;
                break;
            case NORTHWEST:
                newX--; newY--;
                break;
            case NORTHEAST:
                newX--; newY++;
                break;
            case SOUTHWEST:
                newX++; newY--;
                break;
            case SOUTHEAST:
                newX++; newY++;
                break;
        }

        // "Eat" human at new location
        City::removeOrganism(*city, newX, newY);

        // Move Zombie to new location
        city->setOrganism(this, newX, newY);
        this->setPosition(newX, newY);
    } else if (!emptyOptions.empty()) {
        // Moving to empty cell - Clear current cell
        city->grid[currentX][currentY] = nullptr;

        int newX = currentX, newY = currentY;
        switch (emptyOptions.front()) {
            case NORTH:
                newX--;
                break;
            case EAST:
                newY++;
                break;
            case SOUTH:
                newX++;
                break;
            case WEST:
                newY--;
                break;
            case NORTHWEST:
                newX--; newY--;
                break;
            case NORTHEAST:
                newX--; newY++;
                break;
            case SOUTHWEST:
                newX++; newY--;
                break;
            case SOUTHEAST:
                newX++; newY++;
                break;
        }

        // Set new location
        city->setOrganism(this, newX, newY);
        this->setPosition(newX, newY);
    }
}

// Function to find a nearby human and convert them to a zombie
bool Zombie::breed() {
    vector<direction> infectOptions;

    int currentX = this->x;
    int currentY = this->y;

    // Check upper grid boundary
    if ((currentX - 1) >= 0) {
        // Check one cell north
        if (city->grid[currentX - 1][currentY] != nullptr) {
            // Check if occupied cell has a Human
            if (city->grid[currentX - 1][currentY]->getSpecies() == HUMAN_CH) {
                infectOptions.push_back(NORTH);
            }
        }
    }

    // Check right grid boundary
    if ((currentY + 1) < width) {
        // Check east cell
        if (city->grid[currentX][currentY + 1] != nullptr) {
            if (city->grid[currentX][currentY + 1]->getSpecies() == HUMAN_CH) {
                infectOptions.push_back(EAST);
            }
        }
    }

    // Check lower grid boundary
    if ((currentX + 1) < height) {
        // Check one cell south
        if (city->grid[currentX + 1][currentY] != nullptr) {
            if (city->grid[currentX + 1][currentY]->getSpecies() == HUMAN_CH) {
                infectOptions.push_back(SOUTH);
            }
        }
    }

    // Check left grid boundary
    if ((currentY - 1) >= 0) {
        // Check west cell
        if (city->grid[currentX][currentY - 1] != nullptr) {
            if (city->grid[currentX][currentY - 1]->getSpecies() == HUMAN_CH) {
                infectOptions.push_back(WEST);
            }
        }
    }

    // Diagonal checks
    // Check North-East
    if ((currentX - 1) >= 0 && (currentY + 1) < width) {
        if (city->grid[currentX - 1][currentY + 1] != nullptr) {
            if (city->getOrganism(x - 1, y + 1)->getSpecies() == HUMAN_CH) {
                infectOptions.push_back(NORTHEAST);
            }
        }
    }

    // Check South-East
    if ((currentX + 1) > height && (currentY + 1) < width) {
        if (city->grid[currentX + 1][currentY + 1] != nullptr) {
            if (city->getOrganism(x + 1, y + 1)->getSpecies() == HUMAN_CH) {
                infectOptions.push_back(SOUTHEAST);
            }
        }
    }

    // Check South-West
    if ((currentX + 1) > height && (currentY - 1) <= 0) {
        if (city->grid[currentX + 1][currentY - 1] != nullptr) {
            if (city->getOrganism(x + 1, y - 1)->getSpecies() == HUMAN_CH) {
                infectOptions.push_back(SOUTHWEST);
            }
        }
    }

    // Check North-West
    if ((currentX - 1) >= 0 && (currentY - 1) >= 0) {
        if (city->grid[currentX - 1][currentY - 1] != nullptr) {
            if (city->getOrganism(x - 1, y - 1)->getSpecies() == HUMAN_CH) {
                infectOptions.push_back(NORTHWEST);
            }
        }
    }

    // Shuffle list
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(infectOptions.begin(), infectOptions.end(), default_random_engine(seed));

    if (!infectOptions.empty()) {
        // Select a Human to infect
        int newX = currentX, newY = currentY;
        switch (infectOptions.front()) {
            case NORTH:
                newX--;
                break;
            case EAST:
                newY++;
                break;
            case SOUTH:
                newX++;
                break;
            case WEST:
                newY--;
                break;
            case NORTHWEST:
                newX--; newY--;
                break;
            case NORTHEAST:
                newX--; newY++;
                break;
            case SOUTHWEST:
                newX++; newY--;
                break;
            case SOUTHEAST:
                newX++; newY++;
                break;
        }

        // Replace human with zombie at same location
        city->removeOrganism(*city, newX, newY);
        city->setOrganism(new Zombie(city, newX, newY), newX, newY);

        return true;
    } else return false; // Did not find a human to infect
}

// Function to convert this zombie back to human
void Zombie::starve() {
    city->convertOrganism(this->x, this->y);
}

int Zombie::getSpecies() {
    return ZOMBIE_CH;
}

int Zombie::getColor() {
    return ZOMBIE_COLOR;
}