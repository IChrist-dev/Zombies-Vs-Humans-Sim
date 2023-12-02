#ifndef _CITY_H
#define _CITY_H

#include <iostream>
#include "GameSpecs.h"

using namespace std;

class Organism;

class City
{

public:
    // Handle to the array itself
    Organism *grid[GRIDSIZE][GRIDSIZE];

    int generation;

    City();
    virtual ~City();

    Organism *getOrganism( int x, int y );
    void setOrganism( Organism *organism, int x, int y );

    void step(City &city);

    static void move(City &city);

    friend ostream& operator<<( ostream &output, City &city );

    int getGeneration();

    int countType(City &city, char organismCH);

    static bool hasDiversity(City &city);
};

#endif

