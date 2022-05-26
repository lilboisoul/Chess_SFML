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

void Piece::setBoardPos(std::string _boardPos)
{
	this->boardPos.first = _boardPos[0];
	this->boardPos.second = _boardPos[1];
}
void Piece::setBoardPos(std::pair<char, int> _boardPos)
{
	this->boardPos = _boardPos;
}
std::pair<char, int> Piece::getBoardPos()
{
	return this->boardPos;
}

std::string Piece::getBoardPosAsString()
{
	std::string temp = "";
	temp += boardPos.first;
	temp += boardPos.second+48;
	return temp;
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
	this->hasMoved = false;
}

Pawn::Pawn(PieceColor _color): Piece(_color)
{
	initVariables();
}

Pawn::~Pawn()
{
}

std::vector<std::string> Pawn::getLegalMoves()
{
	std::vector<std::string> moves;
	std::string temp="";
	int one;
	if (pieceColor == PieceColor::WHITE) one = 1;
	else one = -1;
	if (hasMoved == false) {
		temp += getBoardPos().first;
		temp += getBoardPos().second + 48 + one*2;
		moves.push_back(temp);
		temp = "";
		temp += getBoardPos().first;
		temp += getBoardPos().second + 48 + one * 1;
		moves.push_back(temp);
		temp = "";
	}
	if (hasMoved == true) {
		temp += getBoardPos().first;
		temp += getBoardPos().second + 48 + one;
		moves.push_back(temp);
		temp = "";
	}
	temp += getBoardPos().first + 1;
	temp += getBoardPos().second + 48 + one;
	moves.push_back(temp);
	temp = "";
	temp += getBoardPos().first - 1;
	temp += getBoardPos().second + 48 + one;
	moves.push_back(temp);
	temp = "";
	return moves;
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

std::vector<std::string> Knight::getLegalMoves()
{
	std::vector<std::string> moves;
	return moves;
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
std::vector<std::string> Bishop::getLegalMoves()
{
	std::vector<std::string> moves;
	return moves;
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
std::vector<std::string> Rook::getLegalMoves()
{
	std::vector<std::string> moves;
	return moves;
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
std::vector<std::string> Queen::getLegalMoves()
{
	std::vector<std::string> moves;
	return moves;
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

std::vector<std::string> King::getLegalMoves()
{
	std::vector<std::string> moves;
	return moves;
}
