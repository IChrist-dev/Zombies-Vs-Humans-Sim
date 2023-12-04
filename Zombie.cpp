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
Zombie::Zombie(City *city, int x, int y) : Organism(city, x, y) {
}

Zombie::~Zombie() = default;

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
        delete city->getOrganism(newX, newY);

        // Set Zombie's new location
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

    // TODO: Zombie turn method overriding from organism
    // TODO: Zombie infect method
    // TODO: Zombie starve

    // Finished moving for this step
    this->endTurn();
}

int Zombie::getSpecies() {
    return ZOMBIE_CH;
}

int Zombie::getColor() {
    return ZOMBIE_COLOR;
}