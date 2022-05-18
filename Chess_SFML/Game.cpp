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
	this->boardGameObject.initBoard();
	this->timeToMove = false;
}

void Game::initWindow()
{
	this->videomode.width = 1024; //width of the game window
	this->videomode.height = 900; //height of the game window
	//this->window->setFramerateLimit(120);
	this->window = new sf::RenderWindow (this->videomode, "Chess", sf::Style::Titlebar | sf::Style::Close);
}

void Game::waitingForMove()
{
	for (auto sqr : boardGameObject.arrayOfSquares)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
			&& mousePosInWindow.x >= sqr->getPosition().first && mousePosInWindow.x <= sqr->getPosition().first + 100
			&& mousePosInWindow.y >= sqr->getPosition().second && mousePosInWindow.y <= sqr->getPosition().second + 100)
		{
			sqr->squareClicked();
			this->setMove(true);
			std::cout << "clicked\n";
			break;
		}

	}

}

void Game::move()
{
	for (auto sqr1 : boardGameObject.arrayOfSquares)
	{
		if (sqr1->isSquareClicked() == true)
		{
			for (auto sqr2 : boardGameObject.arrayOfSquares)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sqr2 != sqr1 && this->getTimeToMove() == true
					&& mousePosInWindow.x >= sqr2->getPosition().first && mousePosInWindow.x <= sqr2->getPosition().first + 100
					&& mousePosInWindow.y >= sqr2->getPosition().second && mousePosInWindow.y <= sqr2->getPosition().second + 100)
				{
					sqr1->move(sqr2);
					sqr1->squareUnclicked();
					sqr2->squareUnclicked();
					this->setMove(false);
					std::cout << "moved from " << sqr1->getBoardPos().first << sqr1->getBoardPos().second << " to " << sqr2->getBoardPos().first << sqr2->getBoardPos().second << "\n";
					break;
				}

			}
		}

	}
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
	while (this->window->pollEvent(this->sfevent))
	{
		switch (this->sfevent.type)
		{
		//closes the app when the user clicks the "X" button in the upper right corner
		case sf::Event::Closed:
			this->window->close();
			break;
		//closes the app when 'Escape' is pressed
		case sf::Event::KeyPressed:
			if (this->sfevent.key.code == sf::Keyboard::Escape) this->window->close();
			break;
		}
	}
}

void Game::updateMousePositions()
{
	this->mousePosInWindow = sf::Mouse::getPosition(*this->window);
	//std::cout << "Mouse pos: " << mousePosInWindow.x << " " << mousePosInWindow.y << "\n";
}

void Game::setMove(bool _move)
{
	this->timeToMove = _move;
}
bool Game::getTimeToMove()
{
	return this->timeToMove;
}

void Game::update()
{
	this->pollEvents();
	this->updateMousePositions();
	this->waitingForMove();
	this->move();
}

void Game::render()
{
	this->window->clear(sf::Color(255,255, 255, 255));
	this->window->draw(this->boardGameObject);
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
