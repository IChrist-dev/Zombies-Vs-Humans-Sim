#ifndef _Human_H
#define _Human_H

#include "Organism.h"

class Human : public Organism
{
public:
    Human();
    Human( City *city, int x, int y );
    ~Human() override;

    void move() override;

    int getSpecies() override;

    int getColor() override;
};

#endif
