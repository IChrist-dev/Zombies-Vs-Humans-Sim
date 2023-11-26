//
// Created by Ian on 11/26/2023.
//

#include "Zombie.h"
#include "GameSpecs.h"

Zombie::Zombie() {
}

Zombie::Zombie(City *city, int width, int height) : Organism(city, width, height) {
}

Zombie::~Zombie() {

}

void Zombie::move() {

}

int Zombie::getSpecies() {
    return ZOMBIE_CH;
}

int Zombie::getColor() {
    return ZOMBIE_COLOR;
}