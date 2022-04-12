#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

/*
	<co robi klasa>

*/
class Game
{
private:
	//Private
	sf::VideoMode videomode;
	sf::RenderWindow* window;
	sf::Event e;
	//Private methods
	void initVariables();
	void initWindow();
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

