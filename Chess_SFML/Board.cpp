#include "Board.h"

void Board::initBoard()
{
	//initializes the board
	this->brd.setPosition({ 100, 50 });
	this->brd.setSize(sf::Vector2f(800.0f, 800.0f));
	this->brd.setFillColor(sf::Color::Yellow);
	this->brd.setOutlineColor(sf::Color::Black);
	this->brd.setOutlineThickness(2.f);

	//initializes the squares
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			
			this->board[i][j].setCoordinates(i+1, j+1);
			//std::cout << "<" << board[i][j].getCoordinates().first << " " << board[i][j].getCoordinates().second << "> ";
			this->board[i][j].setPosition(brd.getPosition().x + 100 * j, brd.getPosition().y + 100 * i);
			std::cout << "{" << board[i][j].getPosition().first << " " << board[i][j].getPosition().second << "} ";
		}
		std::cout << "\n";
	}
}

void Board::draw()
{
	
	
	
}

Board::Board()
{
	this->initBoard();
}

Board::~Board()
{
}
