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
