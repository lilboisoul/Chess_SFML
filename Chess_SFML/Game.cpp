#include "Game.h"


Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->gameLoop();
}

void Game::initVariables()
{
	this->window = nullptr;
	this->board.initBoard();
}

void Game::initWindow()
{
	this->videomode.height = 768; //height of the game window
	this->videomode.width = 1024; //width of the game window
	this->window = new sf::RenderWindow (this->videomode, "Chess", sf::Style::Titlebar | sf::Style::Close);
}

void Game::gameLoop()
{
	while (this->running())
	{
		this->render();
		
		this->update();
	}
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->e))
	{
		switch (this->e.type)
		{
		//closes the app when the user clicks the "X" button in the upper right corner
		case sf::Event::Closed:
			this->window->close();
			break;
		//closes the app when 'Escape' is pressed
		case sf::Event::KeyPressed:
			if (this->e.key.code == sf::Keyboard::Escape) this->window->close();
			break;
		}
	}
}

void Game::update()
{
	this->pollEvents();
}

void Game::render()
{
	this->window->clear(sf::Color(255, 0, 0, 255));
	this->window->display();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}
