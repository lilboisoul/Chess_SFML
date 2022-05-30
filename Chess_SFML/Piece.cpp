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


}

Pawn::Pawn(PieceColor _color): Piece(_color)
{
	initVariables();
	
}

Pawn::~Pawn()
{
}

void Pawn::setBoardPos(std::pair<char, int> _boardPos)
{
	this->boardPos = _boardPos;
	setHasMoved();
}

void Pawn::setHasMoved()
{
	if (this->boardPos.second != 7 && this->pieceColor == PieceColor::BLACK) this->hasMoved = true;
	else if (this->boardPos.second != 2 && this->pieceColor == PieceColor::WHITE) this->hasMoved = true;
	else this->hasMoved = false;
}

std::vector<std::pair<int, int>> Pawn::getPossibleMoves()
{
	int x = getBoardPos().first - 96;
	int y = getBoardPos().second;
	int one;
	pieceColor == PieceColor::WHITE ? one = 1 : one = -1;
	std::vector<std::pair<int, int>> possibleMoves = { {x-1, y + one}, {x + 1, y + one}, {x, y + one}};
	std::vector<std::pair<int, int>> legalMoves;
	if (hasMoved == false) {
		possibleMoves.push_back({x , y + one*2});
	}
	for (auto& [moveX, moveY] : possibleMoves) {
		if (moveX > 0 && moveX <= 8 && moveY > 0 && moveY <= 8) {
			legalMoves.push_back({ moveX, moveY });
		}
	}
	return legalMoves;
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

std::vector<std::pair<int, int>> Knight::getPossibleMoves()
{
	int x = getBoardPos().first - 96;
	int y = getBoardPos().second;
	int one;
	////
	//std::cout << "Position of the piece: " << x << y << "\n";
	////
	pieceColor == PieceColor::WHITE ? one = 1 : one = -1;
	std::vector<std::pair<int, int>> possibleMoves = { {x - 1, y + one * 2}, {x - 1, y - one * 2},
		 {x + 1, y + one * 2},{x + 1, y - one * 2}, {x - 2, y + one}, {x - 2, y - one}, {x + 2, y + one}, {x + 2, y - one} };
	////debug
	//std::cout << "Possible moves: ";
	//for (auto [i, j] : possibleMoves) std::cout << i << j << " ";
	////
	std::vector<std::pair<int, int>> legalMoves;

	for (auto& [moveX, moveY] : possibleMoves) {
		if (moveX > 0 && moveX <= 8 && moveY > 0 && moveY <= 8) {
			legalMoves.push_back({ moveX, moveY });
		}
	}
	////debug
	//std::cout << "\nLegal moves: ";
	//for (auto [i, j] : legalMoves) std::cout << i << j << " ";
	////
	return legalMoves;
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
std::vector<std::pair<int, int>> Bishop::getPossibleMoves()
{
	int x = getBoardPos().first - 96;
	int y = getBoardPos().second;
	int one;
	pieceColor == PieceColor::WHITE ? one = 1 : one = -1;

	std::vector<std::pair<int, int>> possibleMoves;
	std::vector<std::pair<int, int>> legalMoves;

	for (int i = 0; i < 8; i++)
	{
		possibleMoves.push_back({ x + i, y + one * i });
		possibleMoves.push_back({ x - i, y + one * i });
		possibleMoves.push_back({ x + i, y - one * i });
		possibleMoves.push_back({ x - i, y - one * i });
	}

	for (auto& [moveX, moveY] : possibleMoves) {
		if (moveX > 0 && moveX <= 8 && moveY > 0 && moveY <= 8) {
			legalMoves.push_back({ moveX, moveY });
		}
	}
	return legalMoves;
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
std::vector<std::pair<int, int>> Rook::getPossibleMoves()
{
	int x = getBoardPos().first - 96;
	int y = getBoardPos().second;
	int one;
	pieceColor == PieceColor::WHITE ? one = 1 : one = -1;

	std::vector<std::pair<int, int>> possibleMoves;
	std::vector<std::pair<int, int>> legalMoves;

	for (int i = 0; i < 8; i++)
	{
		possibleMoves.push_back({ x, y + one * i });
		possibleMoves.push_back({ x, y - one * i });
		possibleMoves.push_back({ x + i, y });
		possibleMoves.push_back({ x - i, y });

	}
	for (auto& [moveX, moveY] : possibleMoves) {
		if (moveX > 0 && moveX <= 8 && moveY > 0 && moveY <= 8) {
			legalMoves.push_back({ moveX, moveY });
		}
	}
	return legalMoves;
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
std::vector<std::pair<int, int>> Queen::getPossibleMoves()
{
	int x = getBoardPos().first - 96;
	int y = getBoardPos().second;
	int one;
	pieceColor == PieceColor::WHITE ? one = 1 : one = -1;

	std::vector<std::pair<int, int>> possibleMoves;
	std::vector<std::pair<int, int>> legalMoves;

	for (int i = 0; i < 8; i++)
	{
		possibleMoves.push_back({ x, y + one * i });
		possibleMoves.push_back({ x, y - one * i });
		possibleMoves.push_back({ x + i, y });
		possibleMoves.push_back({ x - i, y });
		possibleMoves.push_back({ x + i, y + one * i });
		possibleMoves.push_back({ x - i, y + one * i });
		possibleMoves.push_back({ x + i, y - one * i });
		possibleMoves.push_back({ x - i, y - one * i });
	}
	for (auto& [moveX, moveY] : possibleMoves) {
		if (moveX > 0 && moveX <= 8 && moveY > 0 && moveY <= 8) {
			legalMoves.push_back({ moveX, moveY });
		}
	}
	return legalMoves;
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

std::vector<std::pair<int, int>> King::getPossibleMoves()
{
	int x = getBoardPos().first - 96;
	int y = getBoardPos().second;
	int one;
	pieceColor == PieceColor::WHITE ? one = 1 : one = -1;

	std::vector<std::pair<int, int>> possibleMoves { {x + one, y + one}, {x + one, y }, {x + one, y - one}, {x, y + one},
													 {x, y - one}, {x - one, y + one}, {x - one, y}, {x - one, y - one} };
	std::vector<std::pair<int, int>> legalMoves;

	for (auto& [moveX, moveY] : possibleMoves) {
		if (moveX > 0 && moveX <= 8 && moveY > 0 && moveY <= 8) {
			legalMoves.push_back({ moveX, moveY });
		}
	}
	return legalMoves;
}