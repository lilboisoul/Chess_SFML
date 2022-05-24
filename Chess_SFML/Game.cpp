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
	this->boardGameObject = new Board(this);
	this->boardGameObject->initBoard();
	this->defaultTime = 0.5f;
	this->timer = defaultTime;
	this->timeToMove = false;
}

void Game::initWindow()
{
	this->videomode.width = 1024; //width of the game window
	this->videomode.height = 900; //height of the game window
	this->window = new sf::RenderWindow (this->videomode, "Chess", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}


void Game::waitingForMove(Board& board)
{
	if (this->timer <= 0) {
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				Square* sqr = board.arrayOfSquares[i][j];
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sqr->getPiecePtr() != nullptr
					&& mousePosInWindow.x >= sqr->getPosition().first && mousePosInWindow.x <= sqr->getPosition().first + 100
					&& mousePosInWindow.y >= sqr->getPosition().second && mousePosInWindow.y <= sqr->getPosition().second + 100)
				{
					sqr->squareClicked();
					this->setMove(true);
					std::cout << "clicked " << sqr->getBoardPos().first << sqr->getBoardPos().second << "\n";
					this->timer = 0.5f;
					break;
				}
			}
		}
	}
	
}

void Game::move(Board& board)
{
	if (this->timer <= 0) {
		//looking for a clicked square
		Square* sqr_from = nullptr;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board.arrayOfSquares[i][j]->isSquareClicked() == true) {
					sqr_from = board.arrayOfSquares[i][j];
					break;
				}
			}
		}
		//looking for a clicked square other than the first one
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				Square* sqr_to = board.arrayOfSquares[i][j];
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sqr_from->getBoardPos() != sqr_to->getBoardPos()
				&& mousePosInWindow.x >= sqr_to->getPosition().first && mousePosInWindow.x <= sqr_to->getPosition().first + 100
				&& mousePosInWindow.y >= sqr_to->getPosition().second && mousePosInWindow.y <= sqr_to->getPosition().second + 100)
				{
					sqr_from->move(sqr_to);
					sqr_from->squareUnclicked();
					sqr_from->squareUnclicked();
					this->setMove(false);
					std::cout << "moved from " << sqr_from->getBoardPos().first << sqr_from->getBoardPos().second << " to " << sqr_to->getBoardPos().first << sqr_to->getBoardPos().second << "\n";
					this->timer = 0.5f;
					break;
				}
				//unclicking the square
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sqr_from->getBoardPos() == sqr_to->getBoardPos()
					&& mousePosInWindow.x >= sqr_to->getPosition().first && mousePosInWindow.x <= sqr_to->getPosition().first + 100
					&& mousePosInWindow.y >= sqr_to->getPosition().second && mousePosInWindow.y <= sqr_to->getPosition().second + 100)
				{
					
					sqr_from->squareUnclicked();
					this->setMove(false);
					std::cout << "unclicked " << sqr_from->getBoardPos().first << sqr_from->getBoardPos().second << "\n";
					this->timer = 0.5f;
					break;
				}
			}
		}
	}
	
	
}

void Game::calculateDeltaTime()
{
	this->deltatime = clock.restart().asSeconds();
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
	calculateDeltaTime();
	this->timer -= deltatime;
	//std::cout << timer << "\n";
	this->pollEvents();
	this->updateMousePositions();

	//checking for the square movement
	if (this->timeToMove == false) this->waitingForMove(*this->boardGameObject);
	else						   this->move(*this->boardGameObject);

	boardGameObject->update();
}

void Game::render()
{
	this->window->clear(sf::Color(255,255, 255, 255));
	this->window->draw(*this->boardGameObject);
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
