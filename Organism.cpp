//
// Created by Ian on 11/26/2023.
//

#include <windows.h>
#include "Organism.h"

#include "Organism.h"

Organism::Organism() {
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    moved = false;
    city = nullptr;
}

Organism::Organism(City *city, int width, int height) : city(city), width(width), height(height) {
    x = 0;
    y = 0;
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
    moved = false;
}

bool Organism::isTurn() {
    return !moved;
}

ostream &operator<<(ostream &output, Organism *organism) {
    Organism::addColor(organism->getColor());

    output << organism->getSpecies();
    return output;
}

void Organism::addColor(int c) {
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);
}

