#include "Piece.h"
void Piece::initVariables()
{
	this->pieceGameObject.setSize({ 100, 100 });
	this->name = "";
}

Piece::Piece(PieceColor _color) : pieceColor(_color)
{
	this->initVariables();
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

void Piece::setTexture(sf::Texture* texture)
{
	this->pieceGameObject.setTexture(texture);
}

void Piece::writeName()
{
	std::cout << name;
}

std::string Piece::getName()
{
	return this->name;
}

PieceColor Piece::getPieceColor()
{
	return this->pieceColor;
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(pieceGameObject);
}

//---------------------------------------------------------------------
void Pawn::initVariables()
{
	if (this->pieceColor == PieceColor::WHITE) this->name = "White pawn";
	else this->name = "Black pawn";
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
	if (this->pieceColor == PieceColor::WHITE) this->name = "White knight";
	else this->name = "Black knight";
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
	if (this->pieceColor == PieceColor::WHITE) this->name = "White bishop";
	else this->name = "Black bishop";
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
	if (this->pieceColor == PieceColor::WHITE) this->name = "White rook";
	else this->name = "Black rook";
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
	if (this->pieceColor == PieceColor::WHITE) this->name = "White queen";
	else this->name = "Black queen";
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
	if (this->pieceColor == PieceColor::WHITE) this->name = "White king";
	else this->name = "Black king";
}

King::King(PieceColor _color) : Piece(_color)
{
	initVariables();
}

King::~King()
{

}