#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

#include "Board.h"
#include "Square.h"
#include "Piece.h"

/*
	A class acting as a game manager/game engine.

*/
class Game
{
private:
	//Private
	sf::VideoMode videomode;
	sf::RenderWindow* window;
	sf::Event e;
	
	Board board;
	
	//Private methods
	void initVariables();
	void initWindow();
	void gameLoop();
public:
	//Constructors / Destructors
	Game();
	~Game();
	//Getters / Setters
	const bool running() const;
	//Methods
	void pollEvents();
	void update();
	void render(); 
	//void initBoard();
	//void initInterface();
};

