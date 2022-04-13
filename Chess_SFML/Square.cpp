#include "Square.h"

void Square::initVariables()
{
	this->posX = 0;
	this->posY = 0;
}

Square::Square()
{
	this->initVariables();
}

Square::~Square()
{
}

std::pair<int, int> Square::getPosition()
{
	return std::make_pair(posX, posY);
}

void Square::setPosition(int new_posX, int new_posY)
{
	this->posX = new_posX;
	this->posY = new_posY;
}
