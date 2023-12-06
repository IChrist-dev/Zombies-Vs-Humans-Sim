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
Human::Human(City *city, int x, int y) : Organism(city, x, y), recruitCount(1) {
}

Human::~Human() = default;

// Driver for human-specific turn behaviour
void Human::organismTurn() {
    // Human move method occurs every turn, without conditionals
    this->move();

    if (this->recruitCount >= HUMAN_BREED) {
        // Human can recruit another out of the rubble
        this->recruit();

        // Reset counter
        this->recruitCount = 1;
    }

    // Increment human-specific counter(s) for special behaviour
    this->recruitCount++;
    this->endTurn();
}

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
    if ((currentY + 1) < width) {
        // Check east cell
        if (city->grid[currentX][currentY + 1] == nullptr) {
            directionOptions.push_back(EAST);
        }
    }

    // Check lower grid boundary
    if ((currentX + 1) < height) {
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

        city->setOrganism(this, newX, newY);
        this->setPosition(newX, newY);
    }
}

// Function to add a new, adjacent human if possible
void Human::recruit() {
    vector<direction> recruitOptions;

    int currentX = this->x;
    int currentY = this->y;

    // Check upper grid boundary
    if ((currentX - 1) >= 0) {
        // Check one cell north
        if (city->grid[currentX - 1][currentY] == nullptr) {
            recruitOptions.push_back(NORTH);
        }
    }

    // Check right grid boundary
    if ((currentY + 1) < width) {
        // Check east cell
        if (city->grid[currentX][currentY + 1] == nullptr) {
            recruitOptions.push_back(EAST);
        }
    }

    // Check lower grid boundary
    if ((currentX + 1) < height) {
        // Check one cell south
        if (city->grid[currentX + 1][currentY] == nullptr) {
            recruitOptions.push_back(SOUTH);
        }
    }

    // Check left grid boundary
    if ((currentY - 1) >= 0) {
        // Check west cell
        if (city->grid[currentX][currentY - 1] == nullptr) {
            recruitOptions.push_back(WEST);
        }
    }

    // Shuffle vector to eliminate bias of movement
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(recruitOptions.begin(), recruitOptions.end(), default_random_engine(seed));

    // Select first index of vector as direction of movement, if it exists
    if (!recruitOptions.empty()) {
        // New human will be adjacent to current human's position
        int newX = currentX, newY = currentY;
        switch (recruitOptions.front()) {
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

        // Send command up to city-controller to add a new human at the location specified
        city->setOrganism(new Human(city, newX, newY), newX, newY);
    }
}


int Human::getSpecies() {
    return HUMAN_CH;
}

int Human::getColor() {
    return HUMAN_COLOR;
}