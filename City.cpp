//
// Created by Ian on 11/26/2023.
//

#include <windows.h>
#include "City.h"
#include "GameSpecs.h"
#include "Organism.h"
#include "Human.h"
#include "Zombie.h"

// Default constructor
City::City() {
    // Initialize the grid
    for (int i = 0; i < GRIDSIZE; ++i) {
        for (int j = 0; j < GRIDSIZE; ++j) {
            grid[i][j] = nullptr; // Initialize all elements to nullptr
        }
    }

    // Add random placement of Humans
    for (int hCount = 0; hCount < HUMAN_STARTCOUNT; hCount++) {
        int x = rand() % GRIDSIZE;
        int y = rand() % GRIDSIZE;

        // Check if the cell has an organism yet
        if (grid[x][y] == nullptr) {
            grid[x][y] = new Human(this, x, y);
        }
    }

    // Add distributed placement of Zombies
    // TODO: Stubbed even distribution for now
    for (int zCount = 0; zCount < ZOMBIE_STARTCOUNT; zCount++) {
        int x = rand() % GRIDSIZE;
        int y = rand() % GRIDSIZE;

        // Check if the cell has an organism yet
        if (grid[x][y] == nullptr) {
            grid[x][y] = new Zombie(this, x, y);
        }
    }
}

City::~City() {
    // Delete organisms, one by one
    for (int i=0; i < GRIDSIZE; i++) {
        for (int j=0; j < GRIDSIZE; j++) {
            delete grid[i][j];
        }
    }
}

Organism *City::getOrganism(int x, int y) {
    return this->grid[x][y];
}

void City::setOrganism(Organism *organism, int x, int y) {
    this->grid[x][y] = organism;
}

void City::move() {

}

// Printing function for city
ostream &operator<<(ostream &output, City &city) {
    for (int i=0; i < GRIDSIZE; i++) {
        for (int j=0; j < GRIDSIZE; j++) {
            if (city.grid[i][j] != nullptr) {
                char orgChar = city.getOrganism(i, j)->getSpecies();

                output << ' ' << orgChar;
            }
            else {
                output << ' ' << '_';
            }
        }
        output << "\n";
    }

    return output;
}

int City::getGeneration() {
    // TODO: Stubbed generation until I begin iterating
    return 1;
}

int City::countType(City &city, char organismCH) {
    int count = 0;

    for (int i=0; i < GRIDSIZE; i++) {
        for (int j=0; j < GRIDSIZE; j++) {
            if (city.grid[i][j] != nullptr) {
                if (city.grid[i][j]->getSpecies() == organismCH) count++;
            }
        }
    }

    return count;
}
