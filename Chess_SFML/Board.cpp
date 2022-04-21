#include "Board.h"

void Board::initBoard()
{
	//initializes the board 
	this->boardGameObject.setPosition({ 100, 50 });
	this->boardGameObject.setSize(sf::Vector2f(800.0f, 800.0f));
	this->boardGameObject.setFillColor(sf::Color::Yellow);
	this->boardGameObject.setOutlineColor(sf::Color::Black);
	this->boardGameObject.setOutlineThickness(2.f);

	
}

void Board::initArrayOfSquares()
{
	//sets the position and the color of squares in the array
	int temporaryNumber = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			// if/else statement determining whether the square should be black or white
			if (temporaryNumber % 2 == 1)
			{
				this->arrayOfSquares[i][j].setSquareColorToBlack();
			}
			temporaryNumber++;

			//std::cout << "<" << board[i][j].getCoordinates().first << " " << board[i][j].getCoordinates().second << "> ";
			
			//sets the position of squares on the board in pixels
			this->arrayOfSquares[i][j].setPosition(boardGameObject.getPosition().x + 100 * j, boardGameObject.getPosition().y + 100 * i);
			
			//std::cout << "{" << array_of_squares[i][j].getPosition().first << " " << array_of_squares[i][j].getPosition().second << "} ";
		}
		temporaryNumber++;
		std::cout << "\n";
	}
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(boardGameObject);
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			target.draw(arrayOfSquares[i][j]);
		}
	}
}

Board::Board()
{
	this->initBoard();
	this->initArrayOfSquares();
}

Board::~Board()
{
}
