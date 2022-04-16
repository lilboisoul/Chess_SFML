#include "Piece.h"
void Piece::initVariables()
{
	this->piece.setFillColor(sf::Color(0, 0, 0, 255));
}

Piece::Piece()
{
	this->initVariables();
}

Piece::~Piece()
{
	
}
