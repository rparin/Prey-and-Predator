#include "Grid.h"

Grid::Grid()
{
	_step = 1;
	_size = MAX - 1;
	_game_over = false;
	_winner = 0;

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			_board[i][j] = nullptr;
		}
	}

	fill_grid();
	gui_setup();
}

void Grid::step()
{
	move();
	breed();
	kill();

	//Increase Time Step
	_step++;
}

void Grid::move()
{
	moveAll();

	//Reset All Creatures Move
	resetMove();
}

void Grid::moveCreaType(int type)
{
	for (int i = 0; i < MAX; i++) {

		for (int j = 0; j < MAX; j++) {

			if (_board[i][j] != nullptr
				&& _board[i][j]->get_moved() == false
				&& _board[i][j]->get_type() == type)
				_board[i][j]->move(_board);

		}
	}
}

void Grid::resetMove()
{
	for (int i = 0; i < MAX; i++) {

		for (int j = 0; j < MAX; j++) {
			if (_board[i][j] != nullptr)
				_board[i][j]->set_moved(false);

		}
	}
}

void Grid::moveAll()
{
	for (int i = 0; i < MAX; i++) {

		for (int j = 0; j < MAX; j++) {
			if (_board[i][j] != nullptr)
				_board[i][j]->move(_board);

		}
	}
}

void Grid::breed()
{	
	for (int i = 0; i < MAX; i++) {

		for (int j = 0; j < MAX; j++) {
			if (_board[i][j] != nullptr)
				_board[i][j]->breed(_board);

		}
	}
}

void Grid::kill()
{
	//Check if game is Over
	bool prey = false;
	bool pred = false;

	for (int i = 0; i < MAX; i++) {

		for (int j = 0; j < MAX; j++) {
			if (_board[i][j] != nullptr) {

				if(_board[i][j]->get_type() != WALL_TYPE){

					if (_board[i][j]->get_type() != PRED_TYPE)
						prey = true;
					else
						pred = true;
				}

				_board[i][j]->kill(_board);
			}	
		}
	}

	if (prey) _winner = PREY_TYPE;
	else _winner = PRED_TYPE;
	
	if(prey && !pred || pred && !prey) 
		_game_over = true;
}

void Grid::fill_grid()
{
	//Set Walls
	createWalls();

	//Create Preys
	createCrea(PREY_AMOUNT);

	//Create Predators
	createCrea(PRED_AMOUNT, false);
}

void Grid::createWalls()
{
	//Left and Right
	for (int i = 0; i < MAX; i++) {
		_board[i][0] = new Wall(i, 0);
		_board[i][_size] = new Wall(i, _size); 
	}

	//Top and Bottom
	for (int i = 1; i < _size; i++) {
		_board[0][i] = new Wall(_size, 0);
		_board[_size][i] = new Wall(_size, 0);
	}
}

void Grid::createCrea(int crea_amount, bool prey)
{
	int amount = crea_amount;
	int i, j;
	while (amount > 0) {
		i = rand() % MAX;
		j = rand() % MAX;

		if (_board[i][j] == nullptr) {
			if(prey)
				_board[i][j] = new Prey(i, j);
			else
				_board[i][j] = new Predator(i, j);
			amount--;
		}
	}
}

int Grid::get_step() const
{
	return _step;
}

bool Grid::is_game_over() const
{
	return _game_over;
}

int Grid::get_winner() const
{
	return _winner;
}

ostream & operator<<(ostream & outs, const Grid & print_me)
{
	for (int i = 0; i < MAX; i++) {
		for (int i = 0; i < DASHES; i++)
			outs << DASH;
		outs << endl;
		for (int j = 0; j < MAX; j++) {
			if (print_me._board[i][j] == nullptr)
				outs << "| " << "  ";
			else
				outs << "| " << *print_me._board[i][j] << " ";

		}
		outs << "|" << endl;
	}
	for (int i = 0; i < DASHES; i++)
		outs << DASH;
	outs << endl;
	return outs;
}

//---------------[START OF GUI STUFF]------------------

void Grid::gui_setup()
{
	_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT)
		, "Prey and Predator");
	_window.setVerticalSyncEnabled(VSYNC);
	_start_pause = CLICK_TO_START;
	_window.display();
}

void Grid::draw_Board(Creature* _board[][MAX])
{

	//Values for Cordinates
	int vectorY;
	int vectorX;

	for (int row = 0; row < GRID_HEIGHT; row++) {
		for (int col = 0; col < GRID_WIDTH; col++) {

			//Get Creature Cordinates
			vectorY = row * (CELL_SIZE + BORDER);
			vectorX = col * (CELL_SIZE + BORDER);

			//Draw Null
			if (_board[row][col] == nullptr) {
				_BG.setPosition(sf::Vector2f(vectorX, vectorY));
				_window.draw(_BG);
			}

			//Draw Wall
			else if (_board[row][col]->get_type() == WALL_TYPE) {
				_wall.setPosition(sf::Vector2f(vectorX, vectorY));
				_window.draw(_wall);
			}

			//Draw Prey
			else if (_board[row][col]->get_type() == PREY_TYPE) {
				_prey.setPosition(sf::Vector2f(vectorX, vectorY));
				_window.draw(_prey);
			}

			//Draw Predator
			else {
				_pred.setPosition(sf::Vector2f(vectorX, vectorY));
				_window.draw(_pred);
			}
		}
	}
}

void Grid::set_Crea_Size()
{
	_BG.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	_wall.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	_prey.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	_pred.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
}

void Grid::set_Crea_Colors()
{
	_BG.setFillColor(sf::Color::Color(C_BG[0], C_BG[1], C_BG[2]));
	_wall.setFillColor(sf::Color::Color(C_WALL[0], C_WALL[1], C_WALL[2]));
	_prey.setFillColor(sf::Color::Color(C_PREY[0], C_PREY[1], C_PREY[2]));
	_pred.setFillColor(sf::Color::Color(C_PRED[0], C_PRED[1], C_PRED[2]));
}

void Grid::run()
{
	//Set Creature Size and Color
	set_Crea_Size();
	set_Crea_Colors();

	//Display and Update Board
	while (_window.isOpen()) {

		processEvents();

		if (!_start_pause) {
			update();
			step();
		}

	}
}

void Grid::processEvents()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		switch (event.type) {

		//Close Window
		case sf::Event::Closed:
			_window.close();
			break;

		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left) {
				if(_start_pause)
					_start_pause = false;
				else 
					_start_pause = true;
			}
			break;

		default:
			break;
		}
	}
}

void Grid::update()
{
	draw_Board(_board);
	_window.display();
	_window.clear();
}

//---------------[END OF GUI STUFF]------------------