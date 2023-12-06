#ifndef _GAMESPECS_H
#define _GAMESPECS_H

#include <string>

const int GRIDSIZE = 20; // size of the square grid
const int HUMAN_STARTCOUNT = 100; // initial Humans
const int ZOMBIE_STARTCOUNT = 5; //initial Zombie count
const int HUMAN_BREED = 5; // steps until a Human breeds
const int ZOMBIE_BREED = 3; // steps until an Zombie breeds
const int ZOMBIE_STARVE = 5; // steps until a Zombie starves and converts back
const char HUMAN_CH = 72;// "H"// ascii for Human
const char SPACE_CH = 45; // "-" ascii dash for empty elements
const char ZOMBIE_CH = 90;//90 "Z"// ascii for zombie
const double PAUSE_SECONDS = .02; // pause between steps
const int ITERATIONS = 1000; // max number of steps
const std::string EXTINCTION_MSG = "EXTINCTION!!!";
const std::string OFURTUNAFILE = "../O_Fortuna-Carmina_Burana.mp3";

//Colors
//0  = black				//9  = bright blue
//1  = blue					//10 = bright green
//2  = green				//11 = bright turquoise
//3  = turquoise			//12 = bright red
//4  = red					//13 = bright pink
//5  = pink					//14 = bright yellow
//6  = yellow				//15 = bright white
//7  = white regular		//16+ = solid blocks
//8  = white pale

const int HUMAN_COLOR = 3; // turquoise
const int ZOMBIE_COLOR = 12; // bright red

#endif