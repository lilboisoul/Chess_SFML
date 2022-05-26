#include "GameLogic.h"

GameLogic::GameLogic()
{
    initVariables();
}

void GameLogic::initVariables()
{
    this->CurrentPlayer = PlayerColor::WHITE;
}

PlayerColor GameLogic::getCurrentPlayer()
{
    return this->CurrentPlayer;
}

void GameLogic::setCurrentPlayer(PlayerColor _color)
{
    this->CurrentPlayer = _color;
}

void GameLogic::swapCurrentPlayer()
{
    if (getCurrentPlayer() == PlayerColor::WHITE) setCurrentPlayer(PlayerColor::BLACK);
    else setCurrentPlayer(PlayerColor::WHITE);
}

bool GameLogic::checkIfMoveIsLegal(Square& square_from, Square& square_to)
{
	bool isMoveLegal = false;
	if (square_from.getPiecePtr() != nullptr) {
		std::vector<std::string> legalmoves = square_from.getPiecePtr()->getLegalMoves();

		for (int i = 0; i < legalmoves.size(); i++) {
			if (square_to.getBoardPosAsString() == legalmoves[i]) {

				isMoveLegal = true;
				break;
			}
		}
	}
	return isMoveLegal;
}
