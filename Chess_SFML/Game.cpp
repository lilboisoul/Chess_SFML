#include "Game.h"

Game::Game()
{
	this->initWindow();
}

void Game::initWindow()
{
	this->videomode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow (this->videomode, "Chess");

	//window->setFramerateLimit(144);
	sf::Event e;
	while (window->isOpen())
	{
		window->clear(sf::Color::Blue);
		while (window->pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window->close();
			}
		}
		window->display();
	}
}

Game::~Game()
{
	delete window;
}
