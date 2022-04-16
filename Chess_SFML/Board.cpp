#include "Board.h"

void Board::initBoard()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			this->board[i][j].setCoordinates(i+1, j+1);
			//to do poprawy, chcialbym zeby bylo widac z perspektywy bialego
			//std::cout << "<" << board[i][j].getPosition().first << " " << board[i][j].getPosition().second << "> ";
		}
		std::cout << "\n";
	}
}

Board::Board()
{
	this->initBoard();
}

Board::~Board()
{
}
