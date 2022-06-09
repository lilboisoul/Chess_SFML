#include "GameLogic.h"
#include "Game.h"
void GameLogic::areKingsChecked(Board& board)
{
	isWhiteKingChecked = false;
	isBlackKingChecked = false;
	std::pair<int, int> whiteKingBoardPos = board.getKingPtr(PieceColor::WHITE)->getBoardPosAsInt();
	//std::cout << "White king position: " << whiteKingBoardPos.first << whiteKingBoardPos.second << "\n";
	std::vector<std::pair<int, int>> allPseudoLegalMoves = getPlayerAllPseudoLegalMoves(board, PlayerColor::BLACK);
	for (auto [x, y] : allPseudoLegalMoves)
	{
		if (x == whiteKingBoardPos.first && y == whiteKingBoardPos.second) {
			board.arrayOfSquares[x - 1][y - 1]->getPiecePtr()->writeName();
			std::cout << " is checked\n";
			isWhiteKingChecked = true;
			
		}
	}
	

	std::pair<int, int> blackKingBoardPos = board.getKingPtr(PieceColor::BLACK)->getBoardPosAsInt();
	//std::cout << "Black king position: " << blackKingBoardPos.first << blackKingBoardPos.second << "\n";
	allPseudoLegalMoves = getPlayerAllPseudoLegalMoves(board, PlayerColor::WHITE);
	for (auto [x, y] : allPseudoLegalMoves)
	{
		if (x == blackKingBoardPos.first && y == blackKingBoardPos.second) {
			board.arrayOfSquares[x - 1][y - 1]->getPiecePtr()->writeName();
			std::cout << " is checked\n";
			isBlackKingChecked = true;

		}
	}
	

}
bool GameLogic::isCheckMate(Board& board)
{
	//swapCurrentPlayer();
	//for (int i = 0; i < 8; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//	{
	//		if ((board.arrayOfSquares[i][j]->getPiecePtr()->getPieceColor() == PieceColor::WHITE && getCurrentPlayer() == PlayerColor::WHITE) ||
	//			(board.arrayOfSquares[i][j]->getPiecePtr()->getPieceColor() == PieceColor::BLACK && getCurrentPlayer() == PlayerColor::BLACK))
	//		{
	//			Piece* currentPiece = board.arrayOfSquares[i][j]->getPiecePtr();
	//			std::vector<std::pair<int, int>> moves = currentPiece->getPseudoLegalMoves();
	//			for (auto [x, y] : moves)
	//			{
	//				board.arrayOfSquares[i][j]->move(board.arrayOfSquares[x][y]);
	//				if (!isCheck(board)) {
	//					board.arrayOfSquares[x][y]->move(board.arrayOfSquares[i][j]);
	//					swapCurrentPlayer();
	//					return false;
	//				}
	//				board.arrayOfSquares[x][y]->move(board.arrayOfSquares[i][j]);
	//			}
	//		}
	//	}
	//}
	//swapCurrentPlayer();
	//return true;
	return false;
}
bool GameLogic::isStalemate(Board& board)
{
	if (getPlayerAllPseudoLegalMoves(board, PlayerColor::WHITE).size() == 0 || getPlayerAllPseudoLegalMoves(board, PlayerColor::BLACK).size() == 0) {
		return true;
	}
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

GameLogic::GameLogic(const GameLogic& _logic)
{
	this->initVariables();
	this->gamePtr = _logic.gamePtr;
	this->currentGameState = _logic.currentGameState;
	this->currentPlayer = _logic.currentPlayer;
	//this->isBlackKingChecked = _logic.isBlackKingChecked;
	//this->isWhiteKingChecked = _logic.isWhiteKingChecked;
}


GameLogic::~GameLogic()
{

}

void GameLogic::initVariables()
{
	this->currentPlayer = PlayerColor::WHITE;
	this->currentGameState = GameState::NORMAL;
	this->isWhiteKingChecked = false;
	this->isBlackKingChecked = false;
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
	areKingsChecked(board);
	if (isWhiteKingChecked == true || isBlackKingChecked == true) {
		/*if (isCheckMate(board)) {
			std::cout << "checkmate\n"; return GameState::CHECKMATE;
		}*/
		std::cout << "check\n";
		return GameState::CHECK;
	}
	else if (isStalemate(board)) {
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

std::vector<std::pair<int, int>> GameLogic::getPlayerAllPseudoLegalMoves(Board& board, PlayerColor player)
{

	std::vector<std::pair<int, int>> pieceLegalMoves;
	std::vector<std::pair<int, int>> allLegalMoves;
	Piece* piece;
	switch (player)
	{
	case PlayerColor::WHITE:
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				pieceLegalMoves.resize(0);
				if (board.arrayOfSquares[i][j]->getPiecePtr() != nullptr) {
					piece = board.arrayOfSquares[i][j]->getPiecePtr();
					if (piece->getPieceColor() == PieceColor::WHITE) {
						pieceLegalMoves = piece->getPseudoLegalMoves(board, *this);
						for (auto i : pieceLegalMoves) allLegalMoves.push_back(i);
					}
					
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
				if (board.arrayOfSquares[i][j]->getPiecePtr() != nullptr) {
					piece = board.arrayOfSquares[i][j]->getPiecePtr();
					if (piece->getPieceColor() == PieceColor::BLACK) {
						pieceLegalMoves = piece->getPseudoLegalMoves(board, *this);
						for (auto i : pieceLegalMoves) allLegalMoves.push_back(i);
					}
					
				}


			}
		}
		break;

	}

	return allLegalMoves;
}

bool GameLogic::checkIfMoveIsLegal(Board& board, GameLogic& logic, Square& square_from, Square& square_to)
{
	bool isMoveLegal = false;
	if (square_from.getPiecePtr() != nullptr) {
		//std::vector<std::pair<int, int>> legalmoves = square_from.getPiecePtr()->getPseudoLegalMoves(); 
		std::vector<std::pair<int, int>> legalmoves = square_from.getPiecePtr()->getLegalMoves(square_from.getPiecePtr()->getPseudoLegalMoves(board, logic));

		for (int i = 0; i < legalmoves.size(); i++) {
			if (square_to.getBoardPosAsInt() == legalmoves[i]) {
				isMoveLegal = true;
				break;
			}
		}
	}
	return isMoveLegal;
}

bool GameLogic::isMyKingChecked(Board& board, PlayerColor color)
{
	if (color == PlayerColor::WHITE) {
		std::pair<int, int> kingBoardPos = board.getKingPtr(PieceColor::WHITE)->getBoardPosAsInt();
		std::vector<std::pair<int, int>> allPseudoLegalMoves = getPlayerAllPseudoLegalMoves(board,PlayerColor::BLACK);
		
		for (auto [x, y] : allPseudoLegalMoves)
		{
			if (x == kingBoardPos.first && y == kingBoardPos.second) {
				return true;
			}
		}
	}

	if (color == PlayerColor::BLACK) {
		std::pair<int, int> kingBoardPos = board.getKingPtr(PieceColor::BLACK)->getBoardPosAsInt();
		std::vector<std::pair<int, int>> allPseudoLegalMoves = getPlayerAllPseudoLegalMoves(board, PlayerColor::WHITE);
		for (auto [x, y] : allPseudoLegalMoves)
		{
			if (x == kingBoardPos.first && y == kingBoardPos.second) {
				return true;
			}
		}
	}
	return false;
}


std::pair<int, int> GameLogic::getEnemyKingPos(Board& board)
{
	std::pair<int, int> boardPos = { 0, 0 };
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			Square* sqr = board.arrayOfSquares[i][j];
			if (sqr->getPiecePtr() != nullptr) {
				if ((sqr->getPiecePtr()->getName() == "White king" && getCurrentPlayer() != PlayerColor::WHITE)
					|| (sqr->getPiecePtr()->getName() == "Black king" && getCurrentPlayer() != PlayerColor::BLACK)) {
					boardPos = sqr->getPiecePtr()->getBoardPosAsInt();
					return boardPos;
				}
			}
		}
	}
	return boardPos;
}