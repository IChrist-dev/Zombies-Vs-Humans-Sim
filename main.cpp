//
// Created by W0068332 on 11/21/2021.
//
//Example main.cpp
//This supposes that city->step() calls the move method of each organism in the city
//in a single pass causing each to perform all tasks that it can.

#include <iostream>
#include <chrono>
#include <thread>
#include "GameSpecs.h"
#include "Organism.h"
#include "City.h"

using namespace std;

void ClearScreen()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int main() {
    City *city = new City();
    int INTERVAL = (int) (PAUSE_SECONDS * 10000);
    chrono::milliseconds interval(INTERVAL);

    while (City::hasDiversity(*city)) { //while both humans and zombies exist
        this_thread::sleep_for(interval);
        ClearScreen();


// Alternate multi-pass version with each activity happening in its own
// pass through the array. Lends itself to prototyping and testing:
        //   city->humansMove();
        //   city->zombiesMoveEat();
        //   city->humansRecruit();
        //   city->zombiesRecruit();
        //   city->zombiesStarve();
        //   city->countOrganisms(Z or H goes here);

//        city->reset(); //resets moved flags
//        city->countOrganisms(Z or H goes here);// run once for each type
        city->step(*city);
        cout << "GENERATION " << city->getGeneration() << endl;
        cout << "HUMANS: " << city->countType(*city, HUMAN_CH) << endl;
        cout << "ZOMBIES: " << city->countType(*city, ZOMBIE_CH) << endl;
    } // End while

    if (!city->hasDiversity(*city)) {
        ClearScreen();
        cout << EXTINCTION_MSG << endl;
    }
} // End main

