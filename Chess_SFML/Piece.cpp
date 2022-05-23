#include "Piece.h"
void Piece::initVariables()
{
	this->pieceGameObject.setSize({ 100, 100 });
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

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(pieceGameObject);
}

//---------------------------------------------------------------------
void Pawn::initVariables()
{
	
	
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
	
}

King::King(PieceColor _color) : Piece(_color)
{
	initVariables();
}

King::~King()
{

}