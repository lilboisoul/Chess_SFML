#include "Square.h"


Square::Square()
{
	this->initVariables();
}

Square::Square(SquareColor _color) : squareColor(_color)
{
	this->initVariables();
	if (SquareColor::WHITE == squareColor) {
		this->squareGameObject.setFillColor(sf::Color(239, 231, 219, 255));
	}
	if (SquareColor::BLACK == squareColor) {
		this->squareGameObject.setFillColor(sf::Color(155, 103, 60, 255));
	}
}

Square::~Square()
{
	delete piecePtr;
}

void Square::				 initVariables()
{
	//initializes render values
	this->squareGameObject.setSize(sf::Vector2f(100.0f, 100.0f));
	this->squareGameObject.setFillColor(sf::Color::White);
	this->squareGameObject.setOutlineColor(sf::Color::Black);
	this->squareGameObject.setOutlineThickness(1.f);

	//initializes private variables
	this->posX = 0;
	this->posY = 0;
	this->piecePtr = nullptr;
	this->isClicked = false;

}

std::pair<int, int> Square:: getPosition()
{
	return std::make_pair(posX, posY);
}
void Square::				 setPosition(int new_posX, int new_posY)
{
	this->posX = new_posX;
	this->posY = new_posY;
	squareGameObject.setPosition(posX, posY);
}

std::pair<char, int> Square::getBoardPos()
{
	return this->boardPos;
}
void Square::				 setBoardPos(int new_posX, int new_posY)
{
	this->boardPos.first = 'a' + static_cast<char>(new_posX);
	this->boardPos.second= new_posY;
}

void Square::setSquareColorToWhite()
{
	this->squareColor = SquareColor::WHITE;
	this->squareGameObject.setFillColor(sf::Color(239, 231, 219, 255));
}
void Square::setSquareColorToBlack()
{
	this->squareColor = SquareColor::BLACK;
	this->squareGameObject.setFillColor(sf::Color(155, 103, 60, 255));
}

SquareColor Square::getSquareColor()
{
	return this->squareColor;
}

bool Square::isSquareClicked()
{
	return this->isClicked;
}



void Square::squareClicked()
{
	this->isClicked = true;
	this->squareGameObject.setFillColor(sf::Color(250, 128, 114, 255)); // salmon color
}

void Square::squareUnclicked()
{
	this->isClicked = false;
	if (this->squareColor == SquareColor::WHITE) setSquareColorToWhite();
	else setSquareColorToBlack();
}

void Square::placePiece(Piece* piece)
{
	this->piecePtr = piece;
	piecePtr->setPosition(this->getPosition().first+25, this->getPosition().second+25);
}

void Square::move(Square* new_square)
{
	new_square->placePiece(this->piecePtr);
	this->piecePtr = nullptr;
}

void Square::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(squareGameObject);
	if (piecePtr != nullptr) {
		target.draw(piecePtr->pieceGameObject);
	}
}


