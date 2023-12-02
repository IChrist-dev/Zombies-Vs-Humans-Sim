//
// Created by Ian on 11/26/2023.
//

#include "Zombie.h"
#include "GameSpecs.h"

Zombie::Zombie() = default;

// Parameterized constructor
Zombie::Zombie(City *city, int x, int y) : Organism(city, x, y) {
}

Zombie::~Zombie() = default;

void Zombie::move() {

    // Finished moving for this step
    this->endTurn();
}

int Zombie::getSpecies() {
    return ZOMBIE_CH;
}

int Zombie::getColor() {
    return ZOMBIE_COLOR;
}