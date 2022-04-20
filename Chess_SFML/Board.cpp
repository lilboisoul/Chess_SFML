#include "Board.h"

void Board::initBoard()
{
	/*this->test.sqr.setPosition({ 100, 50 });
	this->test.sqr.setSize(sf::Vector2f(100.0f, 100.0f));
	this->test.sqr.setFillColor(sf::Color::Black);*/




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
			//Square temp;
			//board[i][j] = temp;
			//this->array_of_squares[i][j].sqr.setSize({ 100, 100 });
			//this->array_of_squares[i][j].setCoordinates(i+1, j+1);
			//std::cout << "<" << board[i][j].getCoordinates().first << " " << board[i][j].getCoordinates().second << "> ";
			this->array_of_squares[i][j].setPosition(brd.getPosition().x + 100 * j, brd.getPosition().y + 100 * i);
			//std::cout << "{" << array_of_squares[i][j].getPosition().first << " " << array_of_squares[i][j].getPosition().second << "} ";
		}
		std::cout << "\n";
	}
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(brd);
	//target.draw(test);
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			target.draw(array_of_squares[i][j]);
		}
	}
}

Board::Board()
{
	this->initBoard();
}

Board::~Board()
{
}
