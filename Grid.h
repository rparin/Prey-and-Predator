#ifndef GRID_H
#define GRID_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Creature.h"

//2D Array of creature pointers
class Grid {
public:

	//Constructor
	Grid();

	//calls functions move, breed, kill
	void step();
	void move();
	void breed();
	void kill();

	//Functions for Step
	void moveCreaType(int type);
	void resetMove();
	void moveAll();

	//Creating the Board
	void fill_grid();
	void createWalls();
	void createCrea(int crea_amount, bool prey = true);

	int get_step() const;

	bool is_game_over() const;
	int get_winner() const;

	//Prints the grid
	friend ostream& operator << (ostream& outs, const Grid& print_me);

private:
	int _size;
	int _step; //Time Step
	bool _game_over;
	int _winner;
	Creature* _board[MAX][MAX];

//Gui Stuff
public:
	//Draw Board
	void gui_setup();

	void set_Crea_Size();
	void set_Crea_Colors();

	void draw_Board(Creature* _board[][MAX]);

	void run();				//call process, update, and render
	void processEvents();	//handle keyboard and mouse events
	void update();			//Display Next Frame

private:
	bool _start_pause;
	sf::RenderWindow _window;
	sf::RectangleShape _BG;
	sf::RectangleShape _wall;
	sf::RectangleShape _prey;
	sf::RectangleShape _pred;
};

#endif //GRID_H