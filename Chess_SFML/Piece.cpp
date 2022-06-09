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
	if (!isInBounds(x2, y2))
		return false;
	if (isEmpty(board, x2, y2))
		return false;
	if (board.arrayOfSquares[x1 - 1][y1 - 1]->getPiecePtr()->getPieceColor() != board.arrayOfSquares[x2 - 1][y2 - 1]->getPiecePtr()->getPieceColor())
		return false;

	return true;
}
bool isMyKingChecked(GameLogic logic, Board board, PieceColor pieceColor, int x1, int y1, int x2, int y2)
{
	PlayerColor color;
	if (pieceColor == PieceColor::WHITE)
	{
		color = PlayerColor::WHITE;
	}
	else 
	{
		color = PlayerColor::BLACK;
	}
	board.arrayOfSquares[x1 - 1][y1 - 1]->move(board.arrayOfSquares[x2 - 1][y2 - 1]);
	if (logic.isMyKingChecked(board, color))
	{
		return true;
	}
	return false;
}
std::vector<std::pair<int, int>> checkForAvailableSquares(Board& board, int x, int y, int offsetX, int offsetY)
{
	std::vector <std::pair<int, int>> availableSquares;
	int tempOffsetX = offsetX;
	int tempOffsetY = offsetY;
	while (isInBounds(x + offsetX, y + offsetY))
	{
		if (isEmpty(board, x + offsetX, y + offsetY)) {
			availableSquares.push_back({ x + offsetX, y + offsetY });
			offsetX += tempOffsetX;
			offsetY += tempOffsetY;
		}
		else if (!isSameColor(board, x, y, x + offsetX, y + offsetY))
		{
			availableSquares.push_back({ x + offsetX, y + offsetY });
			break;
		}
		else break;
	}
	return availableSquares;
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

Piece::Piece(const Piece& _piece)
{
	*this = _piece;

}

Piece::~Piece()
{

}

Piece& Piece::operator=(const Piece& _piece)
{
	this->initVariables();
	this->gamePtr = _piece.gamePtr;
	this->pieceGameObject = _piece.pieceGameObject;
	this->name = _piece.name;
	this->boardPos = _piece.boardPos;
	this->posX = _piece.posX;
	this->posY = _piece.posY;
	this->pieceColor = _piece.pieceColor;
	return *this;
}

std::pair<int, int> Piece::getPosition()
{
	return std::make_pair(posX, posY);
}

void Piece::setPosition(float new_posX, float new_posY)
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
	temp += boardPos.second + 48;
	return temp;
}
std::pair<int, int> Piece::getBoardPosAsInt()
{
	return std::make_pair(boardPos.first - 96, boardPos.second);
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
std::vector<std::pair<int, int>> Piece::getLegalMoves(std::vector<std::pair<int, int>> pseudoLegalMoves)
{
	int x = getBoardPos().first - 96;
	int y = getBoardPos().second;
	Board* board = this->gamePtr->getBoardPtr();
	GameLogic* logic = this->gamePtr->getLogicPtr();
	
	std::vector<std::pair<int, int>> legalMoves;
	for (auto [moveX, moveY] : pseudoLegalMoves)
	{
		if (!isMyKingChecked(*logic, *board, pieceColor, x, y, moveX, moveY))
			legalMoves.push_back({ moveX, moveY });
	}
	return legalMoves;
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
Piece* Pawn::clone() const
{
	return new Pawn(*this);
}
Piece* Knight::clone() const
{
	return new Knight(*this);
}
Piece* Bishop::clone() const
{
	return new Bishop(*this);
}
Piece* Rook::clone() const
{
	return new Rook(*this);
}
Piece* Queen::clone() const
{
	return new Queen(*this);
}
Piece* King::clone() const
{
	return new King(*this);
}
Pawn::Pawn(Game* game, PieceColor _color) : Piece(game, _color)
{
	initVariables();

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

std::vector<std::pair<int, int>> Pawn::getPseudoLegalMoves(Board& board, GameLogic& logic)
{
	int x = getBoardPos().first - 96;
	int y = getBoardPos().second;
	int one;
	//Board* board = this->gamePtr->getBoardPtr();
	//GameLogic* logic = this->gamePtr->getLogicPtr();
	pieceColor == PieceColor::WHITE ? one = 1 : one = -1;
	std::vector<std::pair<int, int>> possibleMoves;
	std::vector<std::pair<int, int>> legalMoves;
	if (hasMoved == false)
		if (isEmpty(board, x, y + one))
			if (isEmpty(board, x, y + one * 2)) 
			{
				possibleMoves.push_back({ x , y + one * 2 });
				possibleMoves.push_back({ x , y + one });
			}
	if (hasMoved == true)
		if (isEmpty(board, x, y + one))// && !isCheck(*logic, *board, x, y, x, y + one))
		{
			possibleMoves.push_back({ x , y + one });
		}
	if (isInBounds(x - 1, y + one))
		if (!isEmpty(board, x - 1, y + one))
			if (!isSameColor(board, x, y, x - 1, y + one))
				//if(!isCheck(*logic, *board, x, y, x - 1, y + one))
			{
				possibleMoves.push_back({ x - 1, y + one });
			}
	if (isInBounds(x + 1, y + one))
		if (!isEmpty(board, x + 1, y + one))
			if (!isSameColor(board, x, y, x + 1, y + one))
				//if (!isCheck(*logic, *board, x, y, x + 1, y + one))
			{
				possibleMoves.push_back({ x + 1, y + one });
			}


	return possibleMoves;
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



std::vector<std::pair<int, int>> Knight::getPseudoLegalMoves(Board& board, GameLogic& logic)
{
	int x = getBoardPos().first - 96;
	int y = getBoardPos().second;
	int one;
	//Board* board = this->gamePtr->getBoardPtr();
	pieceColor == PieceColor::WHITE ? one = 1 : one = -1;
	std::vector<std::pair<int, int>> possibleMoves = { {x - 1, y + one * 2}, { x - 1, y - one * 2 },{x + 1, y + one * 2},{x + 1, y - one * 2}, {x - 2, y + one}, {x - 2, y - one}, {x + 2, y + one}, {x + 2, y - one} };
	std::vector<std::pair<int, int>> legalMoves;

	for (auto& [moveX, moveY] : possibleMoves) {
		if (isInBounds(moveX, moveY))
			if (isEmpty(board, moveX, moveY) || !isSameColor(board, x, y, moveX, moveY))
				legalMoves.push_back({ moveX, moveY });
	}
	return legalMoves;
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


std::vector<std::pair<int, int>> Bishop::getPseudoLegalMoves(Board& board, GameLogic& logic)
{
	int x = getBoardPos().first - 96;
	int y = getBoardPos().second;
	//Board* board = this->gamePtr->getBoardPtr();
	std::vector<std::pair<int, int>> legalMoves;
	//checks up-right diagonal
	for (auto i : checkForAvailableSquares(board, x, y, 1, 1))
		legalMoves.push_back(i);
	//checks down-right diagonal
	for (auto i : checkForAvailableSquares(board, x, y, 1, -1))
		legalMoves.push_back(i);
	//checks down-left diagonal
	for (auto i : checkForAvailableSquares(board, x, y, -1, -1))
		legalMoves.push_back(i);
	//checks up-left diagonal
	for (auto i : checkForAvailableSquares(board, x, y, -1, 1))
		legalMoves.push_back(i);

	return legalMoves;
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


std::vector<std::pair<int, int>> Rook::getPseudoLegalMoves(Board& board, GameLogic& logic)
{
	int x = getBoardPos().first - 96;
	int y = getBoardPos().second;
	//Board* board = this->gamePtr->getBoardPtr();
	std::vector<std::pair<int, int>> legalMoves;

	//checks to the right
	for (auto i : checkForAvailableSquares(board, x, y, 1, 0))
		legalMoves.push_back(i);
	//checks to the left
	for (auto i : checkForAvailableSquares(board, x, y, -1, 0))
		legalMoves.push_back(i);
	//checks down
	for (auto i : checkForAvailableSquares(board, x, y, 0, -1))
		legalMoves.push_back(i);
	//checks up
	for (auto i : checkForAvailableSquares(board, x, y, 0, 1))
		legalMoves.push_back(i);
	return legalMoves;
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


std::vector<std::pair<int, int>> Queen::getPseudoLegalMoves(Board& board, GameLogic& logic)
{
	int x = getBoardPos().first - 96;
	int y = getBoardPos().second;
	//Board* board = this->gamePtr->getBoardPtr();
	std::vector<std::pair<int, int>> legalMoves;

	//checks to the right
	for (auto i : checkForAvailableSquares(board, x, y, 1, 0))
		legalMoves.push_back(i);
	//checks to the left
	for (auto i : checkForAvailableSquares(board, x, y, -1, 0))
		legalMoves.push_back(i);
	//checks down
	for (auto i : checkForAvailableSquares(board, x, y, 0, -1))
		legalMoves.push_back(i);
	//checks up
	for (auto i : checkForAvailableSquares(board, x, y, 0, 1))
		legalMoves.push_back(i);
	//checks up-right diagonal
	for (auto i : checkForAvailableSquares(board, x, y, 1, 1))
		legalMoves.push_back(i);
	//checks down-right diagonal
	for (auto i : checkForAvailableSquares(board, x, y, 1, -1))
		legalMoves.push_back(i);
	//checks down-left diagonal
	for (auto i : checkForAvailableSquares(board, x, y, -1, -1))
		legalMoves.push_back(i);
	//checks up-left diagonal
	for (auto i : checkForAvailableSquares(board, x, y, -1, 1))
		legalMoves.push_back(i);

	return legalMoves;
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


std::vector<std::pair<int, int>> King::getPseudoLegalMoves(Board& board, GameLogic& logic)
{
	int x = getBoardPos().first - 96;
	int y = getBoardPos().second;
	int one;
	pieceColor == PieceColor::WHITE ? one = 1 : one = -1;
	//Board* board = this->gamePtr->getBoardPtr();
	std::vector<std::pair<int, int>> possibleMoves{ {x + one, y + one}, {x + one, y }, {x + one, y - one}, {x, y + one},
													 {x, y - one}, {x - one, y + one}, {x - one, y}, {x - one, y - one} };
	std::vector<std::pair<int, int>> legalMoves;
	for (auto& [moveX, moveY] : possibleMoves) {
		if (isInBounds(moveX, moveY))
			if (isEmpty(board, moveX, moveY) || !isSameColor(board, x, y, moveX, moveY))
				legalMoves.push_back({ moveX, moveY });
	}
	return legalMoves;
}
