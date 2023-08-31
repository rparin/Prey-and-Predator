/*
 * Author: Ralph Parin
 * Project: Prey - Predator
 */
#include "Grid.h"
#include <time.h>
#include <iostream>
using namespace std;

void game();

int main() {

	//Random Comiple Runs
	srand(time(0));

	//GUI
	game();

	return 0;
}

void game()
{
	Grid g;
	g.run();
}