#ifndef _Zombie_H
#define _Zombie_H

#include "Organism.h"

class Zombie : public Organism
{
public:
    Zombie();
    Zombie( City *city, int x, int y );
    ~Zombie() override;

    void move() override;

    int getSpecies() override;

    int getColor() override;
};

#endif
