#pragma once
#include "Square.h"
#include "Board.h"

class Game;
enum class PlayerColor {
	WHITE,
	BLACK
};
enum class GameState {
	NORMAL,
	CHECK,
	CHECKMATE,
	STALEMATE,
	DRAW
};

class GameLogic
{
private:
	Game* gamePtr;
	PlayerColor currentPlayer;
	GameState currentGameState;
	bool canWhiteKingCastleShort;
	bool canWhiteKingCastleLong;
	bool canBlackKingCastleShort;
	bool canBlackKingCastleLong;
public:
	GameLogic(Game* game);
	~GameLogic();
	void initVariables();
	PlayerColor getCurrentPlayer();
	void setCurrentPlayer(PlayerColor _color);
	void swapCurrentPlayer();
	
	void setCastlingRights(std::string FEN_who_can_castle);
	void checkCurrentGameState(Board& board);

	void setGameState(GameState _gamestate);
	GameState getGameState();

	bool checkIfMoveIsLegal(Square& square, Square& square_to);

};

