#include "GameLogic.h"
#include "Game.h"
bool isCheck()
{
	return true;
}
bool isCheckMate()
{
	return true;
}
bool isStalemate()
{
	return true;
}
bool isDraw()
{
	return true;
}
GameLogic::GameLogic(Game* game): gamePtr(game)
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
	if (isCheck()) {
		if (isCheckMate()) return GameState::CHECKMATE;
		return GameState::CHECK;
	}
	else if (isStalemate()) return GameState::STALEMATE;
	else if (isDraw()) return GameState::DRAW;
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
		std::vector<std::pair<int,int>> legalmoves = square_from.getPiecePtr()->getLegalMoves();

		for (int i = 0; i < legalmoves.size(); i++) {
			if (square_to.getBoardPosAsInt() == legalmoves[i]) {
				isMoveLegal = true;
				break;
			}
		}
	}
	return isMoveLegal;
}
