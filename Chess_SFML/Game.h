#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

#include <vector>
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
	sf::VideoMode     videomode;
	sf::RenderWindow* window;
	sf::Event		  sfevent;
	sf::Vector2i      mousePosWindow;

	//Game objects
	Board boardGameObject;
	
	//Private methods
	void gameLoop();
	void initVariables();
	void initWindow();

public:

	//Constructors / Destructors
	Game();
	~Game();
	//Getters / Setters
	//Methods
	void pollEvents();
	void updateMousePositions();
	void update();
	void render(); 
	const bool running() const;
	//void initInterface();



};

