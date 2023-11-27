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
    for (int i = 0; i < GRIDSIZE; ++i) {
        for (int j = 0; j < GRIDSIZE; ++j) {
            grid[i][j] = nullptr; // Initialize all elements to nullptr
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
}

// Destructor
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
