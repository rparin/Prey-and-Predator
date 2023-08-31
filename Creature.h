#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <cassert>
#include <cstdlib>
#include "../../!includes/myQueue.h"
#include "Const_Variables.h"
using namespace std;

struct Location {
	Location(int row = 0, int col = 0) :
		_r(row), _c(col) { }

	friend ostream& operator << (ostream& outs, const Location& l) {
		outs << l._r << "," << l._c;
		return outs;
	}

	int _r;
	int _c;
};

//The base class for all other creature classes
class Creature {
public:

	//Default Constructor
	Creature(int row, int col);

	//Creature type = 0
	virtual int get_type();

	virtual void move(Creature* _board[][MAX]);

	virtual void breed(Creature* _board[][MAX]);

	virtual void kill(Creature* _board[][MAX]);

	virtual void print(ostream& outs = cout) const;

	//Given grid & Location, moves creature to location 
	//Child Classes call this to move 
	void move_to(Creature* _board[][MAX], Location loc);

	//Given Grid, returns/creates array containing 
	//location of empty spaces around this creature
	Queue<Location> find_blank(Creature* _board[][MAX]);

	//Given grid and Creature type 
	//Returns array of locations of 
	//given creature type next to this creature
	Queue<Location> find_creature(Creature* _board[][MAX],
		int cType);

	//Given grid and Creature type
	//Returns array of locations of the 
	//not given creature type next to this creature
	Queue<Location> find_not_creature(Creature* _board[][MAX],
		int cType);

	//Kills the creature
	void kill_this_creature(Creature* _board[][MAX]);

	//Setter for the _moved private var
	void set_moved(bool new_moved);

	//Getter for the _moved private var
	bool get_moved();

	//Step Tracker
	int get_step();

	//Prints the creature
	friend ostream& operator << (ostream& outs, const Creature& c);

private:
	Location _loc;
	bool _moved;
	int _step;
};

//Prey inheriting Creature
class Prey : public Creature
{
public:

	//Default Constructor
	Prey(int row = 0, int col = 0)
		: Creature(row, col) {
	}

	virtual int get_type();

	virtual void move(Creature* _board[][MAX]);

	virtual void breed(Creature*_board[][MAX]);

	virtual void print(ostream& outs = cout) const;

private:

};

//Predator inheriting Creature
class Predator : public Creature
{
public:

	//Default Constructor
	Predator(int row = 0 , int col = 0)
		: Creature(row,col){
		_eaten = 0;
	}
  
	virtual int get_type();

	virtual void move(Creature* _board[][MAX]);

	virtual void breed(Creature*_board[][MAX]);

	virtual void kill(Creature* _board[][MAX]);

	virtual void print(ostream& outs = cout) const;

private:
	int _eaten;
};

//Wall inheriting Creature
class Wall : public Creature
{
public:

	//Default Constructor
	Wall(int row = 0, int col = 0)
		: Creature(row, col) {
	}

	virtual int get_type();

	virtual void print(ostream& outs = cout) const;
};

#endif //PREY_PREDATOR_H