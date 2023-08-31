#ifndef CONST_VARIABLES_H
#define CONST_VARIABLES_H

//Board Size including Boarders
const int MAX = 100;
const char DASH = '-';
const int DASHES = (MAX*MAX) * .18 + 2;

//Grid GUI Constants
const int GRID_WIDTH = MAX;
const int GRID_HEIGHT = MAX;
const int CELL_SIZE = 5;
const int BORDER = 0;
const int BORDER_MULTIPLIER = (CELL_SIZE * (MAX / CELL_SIZE)) * BORDER;
const int SCREEN_WIDTH = (CELL_SIZE * GRID_WIDTH) + BORDER_MULTIPLIER;
const int SCREEN_HEIGHT = (CELL_SIZE * GRID_HEIGHT) + BORDER_MULTIPLIER;
const int FRAME = 60;
const bool VSYNC = true;
const bool CLICK_TO_START = false;

//Colors for Creatures GUI
const int C_BG[3] = { 21, 5, 15 };
const int C_WALL[3] = { 1, 38, 56 };
const int C_PRED[3] = { 136, 13, 44 };
const int C_PREY[3] = { 61, 4, 72 };

//Amount of Creatures
const int PREY_AMOUNT = ((MAX*MAX) * .21) -1; //21% of the grid
const int PRED_AMOUNT = ((MAX*MAX) * .01) +1; //1% of the grid

//Creature Icons
const char CRE_ICO =  'C';
const char WALL_ICO = 'Z';
const char PREY_ICO = 'o';
const char PRED_ICO = 'X';

//Creature Types
const int CRE_TYPE  = 0;
const int PREY_TYPE = 1;
const int PRED_TYPE = 2;
const int WALL_TYPE = 3;

//Breed Steps
const int PREY_BREED = 3;
const int PRED_BREED = 8;

//Prey Starve
const int STARVE = 3;

//During x turn all Predators move before Preys
const int PRED_TURN = 5;

#endif //CONST_VARIABLES_H