#include "Square.h"

void Square::initVariables()
{
	//initializes render values
	this->sqr.setSize(sf::Vector2f(100.0f, 100.0f));
	this->sqr.setFillColor(sf::Color::Magenta);
	this->sqr.setOutlineColor(sf::Color::Black);
	this->sqr.setOutlineThickness(1.f);

	//initializes private variables
	this->posX = 0;
	this->posY = 0;
	this->coordinateX = 0;
	this->coordinateY = 0;
	this->isWhite = false;
	this->isOccupied = false;
}

Square::Square()
{
	this->initVariables();
}

Square::~Square()
{

}

std::pair<int, int> Square::getCoordinates()
{
	return std::make_pair(coordinateX, coordinateY);
}

void Square::setCoordinates(int new_posX, int new_posY)
{
	this->posX = new_posX;
	this->posY = new_posY;
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

void Square::setSquareColorToWhite()
{
	this->isWhite = true;
}

void Square::setSquareColorToBlack()
{
	this->isWhite = false;
}


