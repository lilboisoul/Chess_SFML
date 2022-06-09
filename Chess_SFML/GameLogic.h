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
public:
	bool isWhiteKingChecked;
	bool isBlackKingChecked;
	bool canWhiteKingCastleShort;
	bool canWhiteKingCastleLong;
	bool canBlackKingCastleShort;
	bool canBlackKingCastleLong;
	GameLogic(Game* game);
	GameLogic(const GameLogic& _logic);
	~GameLogic();
	void initVariables();

	//player turn
	PlayerColor getCurrentPlayer();
	void setCurrentPlayer(PlayerColor _color);
	void swapCurrentPlayer();
	void setCurrentPlayerFromFEN(std::string FEN);

	//castling
	void setCastlingRights(std::string FEN_who_can_castle);

	//check, check-mate, stalemate, draw
	GameState checkBoardGameState(Board& board);
	void setGameState(GameState _gamestate);
	GameState getGameState();

	std::vector<std::pair<int, int>> getPlayerAllPseudoLegalMoves(Board& board, PlayerColor player);
	bool checkIfMoveIsLegal(Board& board, GameLogic& logic, Square& square_from, Square& square_to);
	bool isMyKingChecked(Board& board, PlayerColor color);
	void areKingsChecked(Board& board);
	bool isCheckMate(Board& board);
	bool isStalemate(Board& board);
	bool isDraw();

	std::pair<int, int> getEnemyKingPos(Board& board);

};