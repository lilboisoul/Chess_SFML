#include "Game.h"


Game::Game()
{
	this->initVariables();
	this->initWindow();
	while (this->running()) {
		this->update();
		this->render();
	}
}

void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videomode.height = 600;
	this->videomode.width = 800;
	this->window = new sf::RenderWindow (this->videomode, "Chess", sf::Style::Titlebar | sf::Style::Close);
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->e))
	{
		switch (this->e.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
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
