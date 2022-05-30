#include "Game.h"
#include <string>
#include <cstdlib>

Game::Game()
{
	this->loadFEN("defaultfen.txt");
	this->initVariables();
	this->initWindow();
	this->gameLoop();
}

Game::Game(std::string FEN_filename)
{
	this->currentGameLogic = new GameLogic();
	this->loadFEN(FEN_filename);
	this->initVariables();
	this->initWindow();
	this->gameLoop();
}

void Game::initVariables()
{
	this->window = nullptr;
	
	this->boardGameObject = new Board(this, FEN);
	this->boardGameObject->initBoard();
	this->defaultTime = 0.1f;
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

void Game::loadFEN(std::string FEN_filename)
{
	std::filesystem::path path = std::filesystem::current_path().append(FEN_filename);
	if (std::filesystem::exists(path)) {
		std::ifstream plik(path);
		std::getline(plik, FEN);
	}
	convertFEN(FEN);

}
void Game::convertFEN(std::string FEN)
{
	char tempChar = 'x';
	int tempIndex = 0;
	std::string FEN_pieces="";
	std::string FEN_who_moves="";
	std::string FEN_who_can_castle="";
	std::string FEN_possible_enpassant_moves = "";
	//extracting piece-portion of FEN
	
	for (size_t i = 0; i < FEN.length(); i++)
	{
		if (FEN[i] != ' ') FEN_pieces += FEN[i];
		else {
			tempIndex = i+1;
			break;
		}
	}
	//extracting which player moves on the next turn
	FEN_who_moves = FEN[tempIndex];
	tempIndex += 2;

	//extracting castling rights
	for (size_t i = tempIndex; i < FEN.length(); i++)
	{
		if (FEN[i] == 'k' || FEN[i] == 'q' || FEN[i] == 'K' || FEN[i] == 'Q') FEN_who_can_castle += FEN[i];
		else {
			tempIndex += 2;
			break;
		}
	}
	for (size_t i = tempIndex; i < FEN.length(); i++)
	{
		if (FEN[i] == '-') {
			tempIndex += 2;
			break;
		}
		else {
			FEN_possible_enpassant_moves += FEN[i];
			FEN_possible_enpassant_moves += FEN[i+1];
			tempIndex += 3;
			break;
		}
	}

	std::cout << "FEN pieces: " << FEN_pieces << "\nwho moves next: " << FEN_who_moves << "\nwho can castle: " << FEN_who_can_castle << "\npossible en passant moves: " << FEN_possible_enpassant_moves << "\n";
	if (FEN_who_moves == "w") this->currentGameLogic->setCurrentPlayer(PlayerColor::WHITE);
	else this->currentGameLogic->setCurrentPlayer(PlayerColor::BLACK);


}


void Game::waitingForMove(Board& board, GameLogic& logic)
{
	if (this->timer <= 0) {
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				Square* sqr = board.arrayOfSquares[i][j];
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
					sqr->getPiecePtr() != nullptr &&
					((logic.getCurrentPlayer() == PlayerColor::WHITE && sqr->getPiecePtr()->getPieceColor() == PieceColor::WHITE)
					|| (logic.getCurrentPlayer() == PlayerColor::BLACK && sqr->getPiecePtr()->getPieceColor() == PieceColor::BLACK))
					&& mousePosInWindow.x >= sqr->getPosition().first && mousePosInWindow.x <= sqr->getPosition().first + 100
					&& mousePosInWindow.y >= sqr->getPosition().second && mousePosInWindow.y <= sqr->getPosition().second + 100)
				{
					sqr->squareClicked();
					this->setTimeToMove(true);
					board.showLegalMoves(sqr->getPiecePtr()->getPossibleMoves());
					std::cout << "Clicked the " << sqr->getBoardPos().first << sqr->getBoardPos().second << " square\n";
					

					this->timer = defaultTime;
					break;
				}
			}
		}
	}
	
}

void Game::move(Board& board, GameLogic& logic)
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
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) 
					&& logic.checkIfMoveIsLegal(*sqr_from, *sqr_to) == true
					&& sqr_from->getBoardPos() != sqr_to->getBoardPos()
					&& mousePosInWindow.x >= sqr_to->getPosition().first && mousePosInWindow.x <= sqr_to->getPosition().first + 100
					&& mousePosInWindow.y >= sqr_to->getPosition().second && mousePosInWindow.y <= sqr_to->getPosition().second + 100)
				{
					if (sqr_to->getPiecePtr() != nullptr) {
						std::cout << sqr_from->getPiecePtr()->getName() << " from " << sqr_from->getBoardPos().first << sqr_from->getBoardPos().second
							  << " captured a " << sqr_to->getPiecePtr()->getName() << " on " << sqr_to->getBoardPos().first << sqr_to->getBoardPos().second << "\n";
					}
					else {
						std::cout << sqr_from->getPiecePtr()->getName() << " moved from " << sqr_from->getBoardPos().first << sqr_from->getBoardPos().second
							<< " to " << sqr_to->getBoardPos().first << sqr_to->getBoardPos().second << "\n";
					}
					sqr_from->move(sqr_to);
					sqr_from->squareUnclicked();
					sqr_to->squareUnclicked();
					board.unShowLegalMoves();
					this->setTimeToMove(false);
					logic.swapCurrentPlayer();

					this->timer = defaultTime;
					break;
				}
				//unclicking the square
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) 
					&& sqr_from->getBoardPos() == sqr_to->getBoardPos()
					&& mousePosInWindow.x >= sqr_to->getPosition().first && mousePosInWindow.x <= sqr_to->getPosition().first + 100
					&& mousePosInWindow.y >= sqr_to->getPosition().second && mousePosInWindow.y <= sqr_to->getPosition().second + 100)
				{
					
					sqr_from->squareUnclicked();
					this->setTimeToMove(false);
					board.unShowLegalMoves();
					std::cout << "Unclicked the " << sqr_from->getBoardPos().first << sqr_from->getBoardPos().second << " square\n";
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

Board* Game::getBoardPtr()
{
	return this->boardGameObject;
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

void Game::setTimeToMove(bool _move)
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
	if (this->timeToMove == false) this->waitingForMove(*this->boardGameObject, *this->currentGameLogic);
	else						   this->move(*this->boardGameObject, *this->currentGameLogic);

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
