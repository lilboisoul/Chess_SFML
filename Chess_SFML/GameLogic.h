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

	//player turn
	PlayerColor getCurrentPlayer();
	void setCurrentPlayer(PlayerColor _color);
	void swapCurrentPlayer();
	
	//castling
	void setCastlingRights(std::string FEN_who_can_castle);

	//check, check-mate, stalemate, draw
	GameState checkBoardGameState(Board& board);
	void setGameState(GameState _gamestate);
	GameState getGameState();

	std::vector<std::pair<int, int>> getCurrentPlayerAllLegalMoves();
	bool checkIfMoveIsLegal(Square& square_from, Square& square_to);
	
	void simulateNextMove(Board board, Square& square_from, Square& square_to);

};

