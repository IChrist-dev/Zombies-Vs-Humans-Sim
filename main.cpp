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

    while (City::hasDiversity(*city) && city->generation < ITERATIONS) { //while both humans and zombies exist
        this_thread::sleep_for(interval);

        ClearScreen();
        city->step(*city);
        cout << "GENERATION " << city->getGeneration() << endl;
        cout << "HUMANS: " << city->countType(*city, HUMAN_CH) << endl;
        cout << "ZOMBIES: " << city->countType(*city, ZOMBIE_CH) << endl;

    } // End while

    if (!city->hasDiversity(*city)) {
        ClearScreen();
        cout << EXTINCTION_MSG << endl;
        string consoleCommand = "start " + OFURTUNAFILE;
        system(consoleCommand.c_str());
    }
} // End main

