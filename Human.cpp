//
// Created by Ian on 11/26/2023.
//

#include <random>
#include <chrono>
#include <algorithm>
#include "Human.h"
#include "GameSpecs.h"
#include "City.h"

// Default constructor
Human::Human() : Organism() {}

// Parameterized constructor
Human::Human(City *city, int x, int y) : Organism(city, x, y) {
}

Human::~Human() = default;

void Human::move() {
    vector<direction> directionOptions;

    int currentX = this->x;
    int currentY = this->y;

    // Check upper grid boundary
    if ((currentX - 1) >= 0) {
        // Check one cell north
        if (city->grid[currentX - 1][currentY] == nullptr) {
            directionOptions.push_back(NORTH);
        }
    }

    // Check right grid boundary
    if ((currentY + 1) > width) {
        // Check east cell
        if (city->grid[currentX][currentY + 1] == nullptr) {
            directionOptions.push_back(EAST);
        }
    }

    // Check lower grid boundary
    if ((currentX + 1) > height) {
        // Check one cell south
        if (city->grid[currentX + 1][currentY] == nullptr) {
            directionOptions.push_back(SOUTH);
        }
    }

    // Check left grid boundary
    if ((currentY - 1) >= 0) {
        // Check west cell
        if (city->grid[currentX][currentY - 1] == nullptr) {
            directionOptions.push_back(WEST);
        }
    }

    // Shuffle vector to eliminate bias of movement
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(directionOptions.begin(), directionOptions.end(), default_random_engine(seed));

    // Select first index of vector as direction of movement, if it exists
    if (!directionOptions.empty()) {
        // Clear current cell
        city->grid[currentX][currentY] = nullptr;

        int newX = currentX, newY = currentY;
        switch (directionOptions.front()) {
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
        }

        city->grid[newX][newY] = this;
        this->setPosition(newX, newY);
    }

    // Finished moving for this step
    this->endTurn();
}

int Human::getSpecies() {
    return HUMAN_CH;
}

int Human::getColor() {
    return HUMAN_COLOR;
}