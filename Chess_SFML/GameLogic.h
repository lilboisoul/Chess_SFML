#pragma once
#include "Square.h"
#include "Board.h"

class Game;
enum class PlayerColor {
	WHITE,
	BLACK
};

class GameLogic
{
private:
	Game* gamePtr;
	PlayerColor currentPlayer;
	bool canWhiteKingCastleShort;
	bool canWhiteKingCastleLong;
	bool canBlackKingCastleShort;
	bool canBlackKingCastleLong;
public:
	GameLogic(Game* game);
	~GameLogic();
	void initVariables();

	//player turn
	PlayerColor getCurrentPlayer();
	void setCurrentPlayer(PlayerColor _color);
	void swapCurrentPlayer();
	void setCurrentPlayerFromFEN(std::string FEN);

	//castling
	void setCastlingRights(std::string FEN_who_can_castle);

	bool checkIfMoveIsLegal(Square& square_from, Square& square_to);

};

