#ifndef _Zombie_H
#define _Zombie_H

#include "Organism.h"

class Zombie : public Organism
{
protected:
    int infectCount;
    int starveCount;
public:
    Zombie();
    Zombie( City *city, int x, int y );
    ~Zombie() override;

    void organismTurn() override;
    void move() override;
    bool breed();
    void starve();

    int getSpecies() override;

    int getColor() override;
};

#endif
