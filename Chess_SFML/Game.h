#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

#include <vector>
#include "Board.h"
#include "Square.h"
#include "Piece.h"
#include "GameLogic.h"





/*
	A class acting as a game manager/game engine.
*/

class Game
{

private:
	//SFML variables
	sf::VideoMode     videomode;
	sf::Event		  sfevent;
	sf::Vector2i      mousePosInWindow;

	//Game logic management
	GameLogic* currentGameLogic;
	bool			  timeToMove;
	std::string		  FEN;
	//Game objects
	Board*			  boardGameObject;
	
	//Private methods
	void gameLoop();
	void initVariables();
	void initWindow();
	void loadFEN(std::string FEN_filename);
	void convertFEN(std::string FEN);
	void waitingForMove(Board& board, GameLogic& logic);
	void move(Board& board, GameLogic& logic);

	//Delta time management
	float	  defaultTime;
	sf::Clock clock;
	void	  calculateDeltaTime();
	float	  timer;
	float	  deltatime;

	


public:
	sf::RenderWindow* window;
	//Constructors / Destructors
	Game();
	Game(std::string FEN_filename);
	~Game();
	//Getters / Setters
	//Methods
	void pollEvents();
	void updateMousePositions();
	void setTimeToMove(bool _move);
	bool getTimeToMove();
	void update();
	void render(); 
	const bool running() const;
	//void initInterface();



};

