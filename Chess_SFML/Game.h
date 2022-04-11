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
	sf::RectangleShape fsodakg;
	sf::VideoMode videomode;
	sf::RenderWindow* window;
public:
	//Constructors / Destructors
	Game();
	~Game();
	//Methods
	void initWindow();
	void update();
	void render(); 
	//void initBoard();
	//void initInterface();
};

