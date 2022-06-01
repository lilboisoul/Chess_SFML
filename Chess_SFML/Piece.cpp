#include "Piece.h"
#include "Game.h"

bool isInBounds(int x, int y)
{
	if (x > 0 && x <= 8 && y > 0 && y <= 8) return true;
	return false;
}
bool isEmpty(Board& board, int x, int y)
{
	if (isInBounds(x, y))
	{
		//board.arrayOfSquares[x - 1][y - 1]->squareGameObject.setFillColor(sf::Color::Black);
		if (board.arrayOfSquares[x - 1][y - 1]->getPiecePtr() == nullptr) return true;
	}
	return false;
}
bool isSameColor(Board& board, int x1, int y1, int x2, int y2)
{	
	if (isInBounds(x2, y2))
		if(!isEmpty(board, x2, y2))
			if (board.arrayOfSquares[x1 - 1][y1 - 1]->getPiecePtr()->getPieceColor() == board.arrayOfSquares[x2 - 1][y2 - 1]->getPiecePtr()->getPieceColor()) return true;
	
	return false;
}
void Piece::initVariables()
{
	this->pieceGameObject.setSize({ 100, 100 });
	this->name = "";
}

Piece::Piece(Game* game, PieceColor _color) : pieceColor(_color), gamePtr(game)
{
	this->initVariables();
}

Piece::~Piece()
{
	delete gamePtr;
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

Pawn::Pawn(Game* game, PieceColor _color): Piece(game, _color)
{
	initVariables();
	
}

Pawn::~Pawn()
{
	delete gamePtr;
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
	Board* board = this->gamePtr->getBoardPtr();
	pieceColor == PieceColor::WHITE ? one = 1 : one = -1;
	std::vector<std::pair<int, int>> possibleMoves;
	std::vector<std::pair<int, int>> legalMoves;
	if (hasMoved == false)
		if(isEmpty(*board, x, y + one))
			if(isEmpty(*board, x, y + one * 2)) {
				possibleMoves.push_back({x , y + one * 2});
				possibleMoves.push_back({x , y + one });
	}
	if (hasMoved == true)
		if(isEmpty(*board, x, y + one))
		{
			possibleMoves.push_back({ x , y + one });
		}
	if (isInBounds(x - 1, y + one))
		if(!isEmpty(*board, x - 1, y + one))
			if(!isSameColor(*board, x, y, x - 1, y + one)){
				possibleMoves.push_back({ x - 1, y + one });
				}
	if (isInBounds(x - 1, y + one))
		if(!isEmpty(*board, x + 1, y + one))
			if(!isSameColor(*board, x, y, x + 1, y + one)) {
				possibleMoves.push_back({ x + 1, y + one });
			}
	
	
	return possibleMoves;
}

std::vector<std::pair<int, int>> Pawn::getLegalMoves(std::vector<std::pair<int, int>>)
{
	int x = getBoardPos().first - 96;
	int y = getBoardPos().second;
	int one;
	pieceColor == PieceColor::WHITE ? one = 1 : one = -1;
	return std::vector<std::pair<int, int>>();
}



//---------------------------------------------------------------------
void Knight::initVariables()
{
	if (this->pieceColor == PieceColor::WHITE) this->name = "White knight";
	else this->name = "Black knight";
}

Knight::Knight(Game* game, PieceColor _color) : Piece(game, _color)
{
	initVariables();
}

Knight::~Knight()
{
	delete gamePtr;
}

std::vector<std::pair<int, int>> Knight::getPossibleMoves()
{
	int x = getBoardPos().first - 96;
	int y = getBoardPos().second;
	int one;
	pieceColor == PieceColor::WHITE ? one = 1 : one = -1;
	std::vector<std::pair<int, int>> possibleMoves = { {x - 1, y + one * 2}, { x - 1, y - one * 2 },{x + 1, y + one * 2},{x + 1, y - one * 2}, {x - 2, y + one}, {x - 2, y - one}, {x + 2, y + one}, {x + 2, y - one} };
	std::vector<std::pair<int, int>> legalMoves;

	for (auto& [moveX, moveY] : possibleMoves) {
		if (moveX > 0 && moveX <= 8 && moveY > 0 && moveY <= 8) {
			legalMoves.push_back({ moveX, moveY });
		}
	}
	return legalMoves;
}


std::vector<std::pair<int, int>> Knight::getLegalMoves(std::vector<std::pair<int, int>>)
{
	return std::vector<std::pair<int, int>>();
}

//---------------------------------------------------------------------
void Bishop::initVariables()
{
	if (this->pieceColor == PieceColor::WHITE) this->name = "White bishop";
	else this->name = "Black bishop";
}

Bishop::Bishop(Game* game, PieceColor _color) : Piece(game, _color)
{

	initVariables();
}

Bishop::~Bishop()
{
	delete gamePtr;
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
std::vector<std::pair<int, int>> Bishop::getLegalMoves(std::vector<std::pair<int, int>>)
{
	return std::vector<std::pair<int, int>>();
}
//---------------------------------------------------------------------
void Rook::initVariables()
{
	if (this->pieceColor == PieceColor::WHITE) this->name = "White rook";
	else this->name = "Black rook";
}

Rook::Rook(Game* game, PieceColor _color) : Piece(game, _color)
{
	initVariables();
}

Rook::~Rook()
{
	delete gamePtr;
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
std::vector<std::pair<int, int>> Rook::getLegalMoves(std::vector<std::pair<int, int>>)
{
	return std::vector<std::pair<int, int>>();
}
//---------------------------------------------------------------------
void Queen::initVariables()
{
	if (this->pieceColor == PieceColor::WHITE) this->name = "White queen";
	else this->name = "Black queen";
}

Queen::Queen(Game* game, PieceColor _color) : Piece(game, _color)
{
	initVariables();
}

Queen::~Queen()
{
	delete gamePtr;
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
std::vector<std::pair<int, int>> Queen::getLegalMoves(std::vector<std::pair<int, int>>)
{
	return std::vector<std::pair<int, int>>();
}
//---------------------------------------------------------------------
void King::initVariables()
{
	if (this->pieceColor == PieceColor::WHITE) this->name = "White king";
	else this->name = "Black king";
}

King::King(Game* game, PieceColor _color) : Piece(game, _color)
{
	initVariables();
}

King::~King()
{
	delete gamePtr;
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

std::vector<std::pair<int, int>> King::getLegalMoves(std::vector<std::pair<int, int>>)
{
	return std::vector<std::pair<int, int>>();
}
