#include "GameLogic.h"
#include "Game.h"

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


