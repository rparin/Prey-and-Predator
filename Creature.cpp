#include "Creature.h"

//---------------[START OF CREATURE CLASS]------------------
Creature::Creature(int row, int col) :
	_loc(row, col)
{
	_moved = false;
	_step = 0;
}

void Creature::print(ostream& outs) const
{
	outs << CRE_ICO;
}

ostream& operator << (ostream& outs, const Creature& c)
{
	c.print(outs);
	return outs;
}

void Creature::set_moved(bool new_moved)
{
	_moved = new_moved;
}

bool Creature::get_moved()
{
	return _moved;
}

int Creature::get_step()
{
	return _step;
}

void Creature::kill_this_creature(Creature* _board[][MAX])
{
	_board[_loc._r][_loc._c] = nullptr;
	delete this;
}

int Creature::get_type()
{
	return CRE_TYPE;
}

void Creature::move(Creature*_board[][MAX])
{
	//Default: Do Nothing
}

void Creature::breed(Creature* _board[][MAX])
{
	//Default: Do Nothing
}

void Creature::kill(Creature* _board[][MAX])
{
	//Default: Do Nothing
}

void Creature::move_to
(Creature* _board[][MAX], Location loc)
{
	//New Location
	_board[loc._r][loc._c] = this;

	//Old location
	_board[this->_loc._r][this->_loc._c] = nullptr;

	//Update Object
	this->_loc = loc;
	this->set_moved(true);
	this->_step++;
}

Queue<Location> Creature::find_blank(Creature* _board[][MAX])
{
	Queue<Location> blanks;
	int startI = _loc._r - 1;
	int startJ = _loc._c - 1;
	int stopI = _loc._r + 1;
	int stopJ = _loc._c + 1;

	for (int i = startI; i <= stopI; i++) {
		for (int j = startJ; j <= stopJ; j++) {
			if (_board[i][j] == nullptr) {
				blanks.push(Location(i, j));
			}
				
		}
	}

	return blanks;
}

Queue<Location> Creature::find_creature
(Creature* _board[][MAX], int cType)
{
	Queue<Location> blanks;
	int startI = _loc._r - 1;
	int startJ = _loc._c - 1;
	int stopI = _loc._r + 1;
	int stopJ = _loc._c + 1;

	for (int i = startI; i <= stopI; i++) {
		for (int j = startJ; j <= stopJ; j++) {
			if (_board[i][j] != nullptr && 
				_board[i][j]->get_type() == cType) {
				blanks.push(Location(i, j));
			}

		}
	}

	return blanks;
}

Queue<Location> Creature::find_not_creature
(Creature* _board[][MAX], int cType)
{
	Queue<Location> blanks;
	int startI = _loc._r - 1;
	int startJ = _loc._c - 1;
	int stopI = _loc._r + 1;
	int stopJ = _loc._c + 1;

	for (int i = startI; i <= stopI; i++) {
		for (int j = startJ; j <= stopJ; j++) {

			if (_board[i][j] == nullptr)
				blanks.push(Location(i, j));

			else if (_board[i][j]->get_type() != cType
				&& _board[i][j]->get_type() != WALL_TYPE)
				blanks.push(Location(i, j));

		}
	}

	return blanks;
}
//---------------[END OF CREATURE CLASS]------------------


//---------------[START OF WALL CLASS]--------------------

int Wall::get_type()
{
	return WALL_TYPE;
}

void Wall::print(ostream& outs) const
{
	outs << WALL_ICO;
}

//---------------[END OF WALL CLASS]--------------------

//---------------[START OF PREY CLASS]--------------------

int Prey::get_type()
{
	return PREY_TYPE;
}

void Prey::move(Creature* _board[][MAX])
{
	Queue<Location> blanks = find_blank(_board);

	//Move Prey if there is a valid location to move
	if (!blanks.is_empty()) {

		//Get Random Location near Prey
		int rand_num = rand() % blanks.size();
		rand_num = blanks.size() - rand_num;

		for (int i = 0; i < rand_num - 1; i++)
			blanks.pop();

		move_to(_board, blanks.pop());
	}
}

void Prey::breed(Creature* _board[][MAX])
{
	if (get_step() % PREY_BREED == 0) {
		Queue<Location> blanks = find_blank(_board);

		//Breed if space available
		if (!blanks.is_empty()) {
			//Get Random Location near Prey
			int rand_num = rand() % blanks.size();
			rand_num = blanks.size() - rand_num;

			for (int i = 0; i < rand_num - 1; i++)
				blanks.pop();

			Location loc = blanks.pop();

			_board[loc._r][loc._c] = new Prey(loc._r, loc._c);
		}
	}
}

void Prey::print(ostream& outs) const
{
	outs << PREY_ICO;
}

//---------------[END OF PREY CLASS]----------------------

//---------------[START OF PRED CLASS]--------------------
int Predator::get_type()
{
	return PRED_TYPE;
}

void Predator::move(Creature* _board[][MAX])
{
	Queue<Location> food = find_creature(_board, PREY_TYPE);
	//Move Pred to empty location if there is a spot available
	if (food.is_empty()) {
		Queue<Location> blanks = find_blank(_board);
		if (!blanks.is_empty()) {
			//Get Random Location near Predator
			int rand_num = rand() % blanks.size();
			rand_num = blanks.size() - rand_num;

			for (int i = 0; i < rand_num - 1; i++)
				blanks.pop();

			move_to(_board, blanks.pop());
		}
	}
	else {
		//Get Random Food near Predator
		int rand_num = rand() % food.size();
		rand_num = food.size() - rand_num;

		for (int i = 0; i < rand_num - 1; i++)
			food.pop();

		Location loc = food.pop();

		delete _board[loc._r][loc._c];

		move_to(_board, loc);

		_eaten++;
	}
}

void Predator::breed(Creature* _board[][MAX])
{
	if (get_step() % PRED_BREED == 0) {
		Queue<Location> blanks = find_blank(_board);

		//Breed if space available
		if (!blanks.is_empty()) {

			//Get Random Location near Predator
			int rand_num = rand() % blanks.size();

			for (int i = 0; i < rand_num - 1; i++)
				blanks.pop();

			Location loc = blanks.pop();

			_board[loc._r][loc._c] = new Predator(loc._r, loc._c);
		}
	}

}

void Predator::kill(Creature* _board[][MAX])
{
	if (get_step() % STARVE == 0 && get_step() != 0) {

		if (_eaten == 0) {
			kill_this_creature(_board);
		}
		_eaten = 0;

	}
		
}

void Predator::print(ostream& outs) const
{
	outs << PRED_ICO;
}

//---------------[END OF PRED CLASS]--------------------