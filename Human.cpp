//
// Created by Ian on 11/26/2023.
//

#include "Human.h"
#include "GameSpecs.h"

// Default constructor
Human::Human() {
}

Human::Human(City *city, int width, int height) : Organism(city, width, height) {
}

Human::~Human() {

}

void Human::move() {

}

int Human::getSpecies() {
    return HUMAN_CH;
}

int Human::getColor() {
    return HUMAN_COLOR;
}