#ifndef _Human_H
#define _Human_H

#include "Organism.h"

class Human : public Organism
{
protected:
    int recruitCount;
public:
    Human();
    Human( City *city, int x, int y );
    ~Human() override;

    void organismTurn() override;
    void move() override;
    void recruit();

    int getSpecies() override;

    int getColor() override;
};

#endif
