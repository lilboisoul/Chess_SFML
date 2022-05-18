#include "Piece.h"
void Piece::initVariables()
{
	this->pieceGameObject.setFillColor(sf::Color::Green);
	this->pieceGameObject.setSize({ 50, 50 });
	this->pieceGameObject.setOutlineColor(sf::Color::Black);
	this->pieceGameObject.setOutlineThickness(5.f);
}

Piece::Piece(PieceColor _color) : pieceColor(_color)
{
	this->initVariables();
	if (PieceColor::WHITE == pieceColor) {
		this->pieceGameObject.setOutlineColor(sf::Color::White);
	}
	if (PieceColor::BLACK == pieceColor) {
		this->pieceGameObject.setOutlineColor(sf::Color::Black);
	}
}

Piece::~Piece()
{
	
}

std::pair<int, int> Piece::getPosition()
{
	return std::make_pair(posX, posY);
}
void Piece::setPosition(int new_posX, int new_posY)
{
	this->posX = new_posX;
	this->posY = new_posY;
	pieceGameObject.setPosition(posX, posY);
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(pieceGameObject);
}

//---------------------------------------------------------------------
void Pawn::initVariables()
{
	this->pieceGameObject.setFillColor(sf::Color::Magenta);
}

Pawn::Pawn(PieceColor _color): Piece(_color)
{
	initVariables();
}

Pawn::~Pawn()
{
}

//---------------------------------------------------------------------
void Knight::initVariables()
{
	this->pieceGameObject.setFillColor(sf::Color::Yellow);
}

Knight::Knight(PieceColor _color) : Piece(_color)
{
	initVariables();
}

Knight::~Knight()
{

}

//---------------------------------------------------------------------
void Bishop::initVariables()
{
	this->pieceGameObject.setFillColor(sf::Color::Cyan);
}

Bishop::Bishop(PieceColor _color) : Piece(_color)
{
	initVariables();
}

Bishop::~Bishop()
{

}
//---------------------------------------------------------------------
void Rook::initVariables()
{
	this->pieceGameObject.setFillColor(sf::Color::Blue);
}

Rook::Rook(PieceColor _color) : Piece(_color)
{
	initVariables();
}

Rook::~Rook()
{

}
//---------------------------------------------------------------------
void Queen::initVariables()
{
	this->pieceGameObject.setFillColor(sf::Color::Red);
}

Queen::Queen(PieceColor _color) : Piece(_color)
{
	initVariables();
}

Queen::~Queen()
{

}
//---------------------------------------------------------------------
void King::initVariables()
{
	this->pieceGameObject.setFillColor(sf::Color(255, 128, 128, 255));
}

King::King(PieceColor _color) : Piece(_color)
{
	initVariables();
}

King::~King()
{

}