#ifndef _Organism_H
#define _Organism_H

#include <iostream>

using namespace std;

class City;

class Organism
{
protected:
    int x;
    int y;
    int width;
    int height;
    City *city;
    enum direction { WEST, NORTH, EAST, SOUTH, NORTHWEST, NORTHEAST, SOUTHEAST, SOUTHWEST };

public:
    bool moved;

    Organism();
    Organism( City *city, int x, int y );
    virtual ~Organism();

    virtual void move() = 0; // Pure virtual (abstract) method
    //virtual void spawn() = 0;
    virtual int getSpecies() = 0; // Pure virtual (abstract) method
    virtual int getColor() = 0; // Pure virtual (abstract) method
    //virtual void getPosition() = 0;

    void setPosition( int x, int y );
    void endTurn();
    bool isTurn();

    friend ostream& operator<<( ostream &output, Organism *organism );
};

#endif
