#include "GameLogic.h"
#include "Game.h"
bool GameLogic::isCheck(Board& board)
{
	swapCurrentPlayer();
	std::pair<int, int> enemyKingBoardPosition = getKingPos(board);
	swapCurrentPlayer();
	std::vector<std::pair<int, int>> allLegalMoves = getCurrentPlayerAllLegalMoves();
	for (auto [x, y] : allLegalMoves)
	{
		if (x == enemyKingBoardPosition.first && y == enemyKingBoardPosition.second)
			return true;
	}

	return false;
}
bool GameLogic::isCheckMate(Board& board)
{
	swapCurrentPlayer();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((board.arrayOfSquares[i][j]->getPiecePtr()->getPieceColor() == PieceColor::WHITE && getCurrentPlayer() == PlayerColor::WHITE) ||
				(board.arrayOfSquares[i][j]->getPiecePtr()->getPieceColor() == PieceColor::BLACK && getCurrentPlayer() == PlayerColor::BLACK))
			{
				Piece* currentPiece = board.arrayOfSquares[i][j]->getPiecePtr();
				std::vector<std::pair<int, int>> moves = currentPiece->getLegalMoves();
				for (auto [x, y] : moves)
				{
					board.arrayOfSquares[i][j]->move(board.arrayOfSquares[x][y]);
					if (!isCheck(board)) {
						board.arrayOfSquares[x][y]->move(board.arrayOfSquares[i][j]);
						swapCurrentPlayer();
						return false;
					}
					board.arrayOfSquares[x][y]->move(board.arrayOfSquares[i][j]);
				}
			}
		}
	}
	swapCurrentPlayer();
	return true;
}
bool GameLogic::isStalemate()
{
	swapCurrentPlayer();
	if (getCurrentPlayerAllLegalMoves().size() == 0) {
		swapCurrentPlayer();
		return true;
	}
	swapCurrentPlayer();
	return false;
}
bool GameLogic::isDraw()
{
	//to-do
	return false;
}
GameLogic::GameLogic(Game* game) : gamePtr(game)
{
	initVariables();
}


GameLogic::~GameLogic()
{

}

void GameLogic::initVariables()
{
	this->currentPlayer = PlayerColor::WHITE;
	this->currentGameState = GameState::NORMAL;
	this->canWhiteKingCastleShort = false;
	this->canWhiteKingCastleLong = false;
	this->canBlackKingCastleShort = false;
	this->canBlackKingCastleLong = false;
}

PlayerColor GameLogic::getCurrentPlayer()
{
	return this->currentPlayer;
}

void GameLogic::setCurrentPlayer(PlayerColor _color)
{
	this->currentPlayer = _color;
}

void GameLogic::swapCurrentPlayer()
{
	if (getCurrentPlayer() == PlayerColor::WHITE) setCurrentPlayer(PlayerColor::BLACK);
	else setCurrentPlayer(PlayerColor::WHITE);
}

void GameLogic::setCurrentPlayerFromFEN(std::string FEN)
{

	if (FEN == "w") this->setCurrentPlayer(PlayerColor::WHITE);
	else this->setCurrentPlayer(PlayerColor::BLACK);
}

void GameLogic::setCastlingRights(std::string FEN_who_can_castle)
{
	for (int i = 0; i < FEN_who_can_castle.length(); i++)
	{
		if (FEN_who_can_castle[i] == 'K') this->canBlackKingCastleShort = true;
		if (FEN_who_can_castle[i] == 'Q') this->canBlackKingCastleLong = true;
		if (FEN_who_can_castle[i] == 'k') this->canWhiteKingCastleShort = true;
		if (FEN_who_can_castle[i] == 'q') this->canWhiteKingCastleLong = true;
	}
}

GameState GameLogic::checkBoardGameState(Board& board)
{
	//is there a check on the board
	if (isCheck(board)) {
		/*if (isCheckMate(board)) {
			std::cout << "checkmate\n"; return GameState::CHECKMATE;
		}*/
		std::cout << "check\n";
		return GameState::CHECK;
	}
	else if (isStalemate()) {
		std::cout << "stalemate\n";
		return GameState::STALEMATE;
	}
	else if (isDraw())
	{
		std::cout << "draw\n";
		return GameState::DRAW;
	}
	std::cout << "normal\n";
	return GameState::NORMAL;
}

void GameLogic::setGameState(GameState _gamestate)
{
	this->currentGameState = _gamestate;
}

GameState GameLogic::getGameState()
{
	return this->currentGameState;
}

std::vector<std::pair<int, int>> GameLogic::getCurrentPlayerAllLegalMoves()
{

	std::vector<std::pair<int, int>> pieceLegalMoves;
	std::vector<std::pair<int, int>> allLegalMoves;
	Piece* piece;
	switch (getCurrentPlayer())
	{
	case PlayerColor::WHITE:
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				pieceLegalMoves.resize(0);
				if (gamePtr->getBoardPtr()->arrayOfSquares[i][j]->getPiecePtr() != nullptr) {
					piece = gamePtr->getBoardPtr()->arrayOfSquares[i][j]->getPiecePtr();
					if (piece->getPieceColor() == PieceColor::WHITE) {
						pieceLegalMoves = gamePtr->getBoardPtr()->arrayOfSquares[i][j]->getPiecePtr()->getLegalMoves();
					}
					for (auto i : pieceLegalMoves) allLegalMoves.push_back(i);
				}
			}
		}
		break;
	case PlayerColor::BLACK:
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				pieceLegalMoves.resize(0);
				if (gamePtr->getBoardPtr()->arrayOfSquares[i][j]->getPiecePtr() != nullptr) {
					piece = gamePtr->getBoardPtr()->arrayOfSquares[i][j]->getPiecePtr();
					if (piece->getPieceColor() == PieceColor::BLACK) {
						pieceLegalMoves = gamePtr->getBoardPtr()->arrayOfSquares[i][j]->getPiecePtr()->getLegalMoves();
					}
					for (auto i : pieceLegalMoves) allLegalMoves.push_back(i);
				}

			}
		}
		break;

	}

	return allLegalMoves;
}

bool GameLogic::checkIfMoveIsLegal(Square& square_from, Square& square_to)
{
	bool isMoveLegal = false;
	if (square_from.getPiecePtr() != nullptr) {
		std::vector<std::pair<int, int>> legalmoves = square_from.getPiecePtr()->getLegalMoves();

		for (int i = 0; i < legalmoves.size(); i++) {
			if (square_to.getBoardPosAsInt() == legalmoves[i]) {
				isMoveLegal = true;
				break;
			}
		}
	}
	return isMoveLegal;
}


std::pair<int, int> GameLogic::getKingPos(Board& board)
{
	std::pair<int, int> boardPos = { 0, 0 };
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			Square* sqr = board.arrayOfSquares[i][j];
			if (sqr->getPiecePtr() != nullptr) {
				if ((sqr->getPiecePtr()->getName() == "White king" && getCurrentPlayer() == PlayerColor::WHITE)
					|| (sqr->getPiecePtr()->getName() == "Black king" && getCurrentPlayer() == PlayerColor::BLACK)) {
					boardPos = sqr->getPiecePtr()->getBoardPosAsInt();
					return boardPos;
				}
			}
		}
	}
	return boardPos;
}