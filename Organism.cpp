//
// Created by Ian on 11/26/2023.
//

#include <windows.h>
#include "Organism.h"
#include "GameSpecs.h"

Organism::Organism() : x(0), y(0), width(0), height(0), moved(false), city(nullptr) {}

Organism::Organism(City *city, int x, int y) : city(city), x(x), y(y), width(GRIDSIZE), height(GRIDSIZE) {
    moved = false;
}

Organism::~Organism() {
    // Destructor implementation if needed
}

void Organism::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Organism::endTurn() {
    moved = true;
}

bool Organism::isTurn() {
    return !moved;
}

ostream &operator<<(ostream &output, Organism *organism) {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, organism->getColor());

    output << organism->getSpecies();
    return output;
}
