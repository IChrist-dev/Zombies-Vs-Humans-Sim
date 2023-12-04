//
// Created by Ian on 11/26/2023.
//

#include <iostream>
#include <windows.h>
#include <random>
#include "City.h"
#include "GameSpecs.h"
#include "Organism.h"
#include "Human.h"
#include "Zombie.h"

using namespace std;

// Default constructor
City::City() {
    // Seed random number generator with current time
    random_device rd;
    mt19937 gen(rd());

    // Initialize the grid
    for (auto & i : grid) {
        for (auto & j : i) {
            j = nullptr; // Initialize all elements to nullptr
        }
    }

    // Set initial Zombie placement - similar to human logic but with quadrant distribution
    int quadrantSize = GRIDSIZE / 2;
    for (int quadX = 0; quadX < 2; quadX++) {
        for (int quadY = 0; quadY < 2;) {
            int x = uniform_int_distribution<int>(quadX * quadrantSize, (quadX + 1) * quadrantSize - 1)(gen);
            int y = uniform_int_distribution<int>(quadY * quadrantSize, (quadY + 1) * quadrantSize - 1)(gen);

            // Check if the cell is occupied
            if (grid[x][y] == nullptr) {
                grid[x][y] = new Zombie(this, x, y);

                quadY++;
            }
        }
    }

    // Last Zombie placement is fully random as first 4 were random within smaller grid-scope
    int zCount = 4;
    while (zCount < ZOMBIE_STARTCOUNT) {
        int x = uniform_int_distribution<int>(0, GRIDSIZE - 1)(gen);
        int y = uniform_int_distribution<int>(0, GRIDSIZE - 1)(gen);

        // Check if the cell is occupied
        if (grid[x][y] == nullptr) {
            grid[x][y] = new Zombie(this, x, y);

            zCount++;
        }
    }

    /*
    Add random placement of Humans
    While-loop only advanced to next human in 100 if it successfully placed someone in an empty space
    */
    int hCount = 0;
    while (hCount < HUMAN_STARTCOUNT) {
        int x = uniform_int_distribution<int>(0, GRIDSIZE - 1)(gen);
        int y = uniform_int_distribution<int>(0, GRIDSIZE - 1)(gen);

        // Check if the cell is occupied
        if (grid[x][y] == nullptr) {
            grid[x][y] = new Human(this, x, y);

            // Successful placement of a human; While-loop can move to next person in the 100
            hCount++;
        }
    }

    generation = 0;
}

// Destructor
City::~City() {
    // Delete organisms, one by one
    for (auto & i : grid) {
        for (auto & j : i) {
            delete j;
        }
    }
}

Organism *City::getOrganism(int x, int y) {
    return this->grid[x][y];
}

void City::setOrganism(Organism *organism, int x, int y) {
    this->grid[x][y] = organism;
}

// Defines top-level actions for a generation-tick
void City::step(City &city) {
    if (generation > 0) {
        // First pass - set new positions
        move(city);
    }

    // Second pass - print city to console
    cout << city << endl;

    // Third pass - reset moved flags
    for (auto & i : grid) {
        for (auto organism : i) {
            if (organism != nullptr) {
                organism->moved = false;
            }
        }
    }
}

// Method to call every organism's move method
void City::move(City &city) {
    for (auto & i : city.grid) {
        for (auto organism : i) {
            if (organism != nullptr) {
                if (organism->isTurn()) {
                    organism->move();
                }
            }
        }
    }
}

// Printing function for city
ostream &operator<<(ostream &output, City &city) {
    // Setup console color change ability
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i=0; i < GRIDSIZE; i++) {
        for (int j=0; j < GRIDSIZE; j++) {
            if (city.grid[i][j] != nullptr) {
                char orgChar = city.getOrganism(i, j)->getSpecies();
                // Set space without color; unnecessary but it feels more correct
                output << "  ";

                SetConsoleTextAttribute(hConsole, city.getOrganism(i, j)->getColor());
                // With console color set, append the organism character to output
                output << orgChar;
                // Reset to standard white text
                SetConsoleTextAttribute(hConsole, 7);
            }
            else {
                output << "  " << SPACE_CH;
            }
        }
        output << "\n";
    }
    // Generation increments
    city.generation++;

    return output;
}

int City::getGeneration() {
    return generation;
}

int City::countType(City &city, char organismCH) {
    int count = 0;

    for (auto & i : city.grid) {
        for (auto & j : i) {
            if (j != nullptr) {
                if (j->getSpecies() == organismCH) count++;
            }
        }
    }

    return count;
}

// Method will return true if at least one human and one zombie exist
bool City::hasDiversity(City &city) {
    bool hasHumans = false;
    bool hasZombies = false;

    // Traverse until a human is found
    for (auto & i : city.grid) {
        for (auto & j : i) {
            if (j != nullptr) {
                if (j->getSpecies() == HUMAN_CH) {
                    hasHumans = true;
                    break;
                }
            }
        }
    }

    // Traverse until a zombie is found
    for (auto & i : city.grid) {
        for (auto & j : i) {
            if (j != nullptr) {
                if (j->getSpecies() == ZOMBIE_CH) {
                    hasZombies = true;
                    break;
                }
            }
        }
    }

    if (hasZombies && hasHumans) return true;
    else return false;
}
