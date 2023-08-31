#ifndef WORKREPORT_H
#define WORKREPORT_H
/*
Features:
		Implemented: 
		Constants Header to easily modify Grid & Creature Behaviors
		-Modify GUI Variables such as GUI Size and frame rate
		-Modify Creature Colors
		
		Class Grid
			-Private variable of creature board pointer
			-Has step function:
			-Step calls move, breed, kill of all creatures on board
			-Print function to print the grid on the command prompt
		GUI private variables:
				-Wall Shape, Nullptr shape, Prey, and Predator Shape
		GUI functions:
			Set Shape sizes, and colors
			Draw board

		Struct Location
			-Takes in a Row and Column

		Class Creature
			-Private Variable called steps
				-Each creature has its own step tracker
			-Takes in a row and column and converts to Location
			-Has virtual move,breed,kill,get type and print functions
			-Virtual functions default to do nothing
			-Functions that use Queue class to return Locations
				-Get Blanks
				-Get not this creature
				-Get this creature

				--All Classes below has virtual get type & print--
				Class Prey Inherits Creature
					-Has its own virtual move, breed

				Class Predator Inherits Creature
					-Private Variable of eaten
						-Keeps track of when Predator has eaten
					-Has its own virtual move, breed, kill

				Class Wall Inherits Creature
					-Does nothing but occupy space
*/

#endif // WORKREPORT_H