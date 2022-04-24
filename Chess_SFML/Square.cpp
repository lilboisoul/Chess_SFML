#include "Square.h"

void Square::initVariables()
{
	//initializes render values
	this->squareGameObject.setSize(sf::Vector2f(100.0f, 100.0f));
	this->squareGameObject.setFillColor(sf::Color::White);
	this->squareGameObject.setOutlineColor(sf::Color::Black);
	this->squareGameObject.setOutlineThickness(1.f);

	//initializes private variables
	this->posX = 0;
	this->posY = 0;
	this->coordinateX = 0;
	this->coordinateY = 0;
	this->isWhite = false;
	this->isOccupied = false;
	this->piecePtr = nullptr;
}

Square::Square()
{
	this->initVariables();
}

Square::~Square()
{
	delete piecePtr;
}

std::pair<int, int> Square::getCoordinates()
{
	return std::make_pair(coordinateX, coordinateY);
}

void Square::setCoordinates(int new_coordinateX, int new_coordinateY)
{
	this->coordinateX = new_coordinateX;
	this->coordinateY = new_coordinateY;
}

std::pair<int, int> Square::getPosition()
{
	return std::make_pair(posX, posY);
}

void Square::setPosition(int new_posX, int new_posY)
{
	this->posX = new_posX;
	this->posY = new_posY;
	squareGameObject.setPosition(posX, posY);
}

void Square::setSquareColorToWhite()
{
	this->isWhite = true;
	squareGameObject.setFillColor(sf::Color(239, 231, 219, 255));
}

void Square::setSquareColorToBlack()
{
	this->isWhite = false;
	squareGameObject.setFillColor(sf::Color(155, 103, 60, 255));
}

void Square::placePiece(Piece* piece)
{
	this->piecePtr = piece;
	piecePtr->setCoordinates(this->getCoordinates().first, this->getCoordinates().second);
	piecePtr->setPosition(this->getPosition().first+25, this->getPosition().second+25);
}

void Square::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(squareGameObject);
	if (piecePtr != nullptr) {
		target.draw(piecePtr->pieceGameObject);
	}
}


