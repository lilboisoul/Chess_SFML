#pragma once
#include "Square.h"
enum class PlayerColor {
	WHITE,
	BLACK
};

class GameLogic
{
private:

	PlayerColor CurrentPlayer;

public:
	GameLogic();
	
	void initVariables();
	PlayerColor getCurrentPlayer();
	void  setCurrentPlayer(PlayerColor _color);
	void  swapCurrentPlayer();
	bool  checkIfMoveIsLegal(Square& square, Square& square_to);

};

