#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include <iostream>
#include <vector>

/*
	A class representing a chess piece.
*/
class Game;
class Board;
class GameLogic;
enum class PieceColor {
	WHITE,
	BLACK
};

class Piece : public sf::Drawable
{
private:
	//Private variables

	//Private methods

	void initVariables();

public:
	Game* gamePtr;
	sf::RectangleShape pieceGameObject;
	std::string name;
	std::pair<char, int> boardPos;
	float posX, posY; //position on the screen [pixels]
	PieceColor pieceColor;
	//Constructors / Destructors

	Piece(Game* _game, PieceColor _color);
	Piece(const Piece& _piece);
	~Piece();
	Piece& operator=(const Piece& _piece);
	//Methods
		//returns the position of the piece as a pair: <posX, posY>
	std::pair<int, int> getPosition();
	virtual Piece* clone() const = 0;
	//sets the position of a piece
	void setPosition(float new_posX, float new_posY);
	void setTexture(sf::Texture* texture);
	void setBoardPos(std::string _boardPos);
	virtual void setBoardPos(std::pair<char, int> _boardPos);
	std::pair<char, int> getBoardPos();
	std::string getBoardPosAsString();
	std::pair<int, int> getBoardPosAsInt();
	void writeName();
	std::string getName();
	PieceColor getPieceColor();
	virtual std::vector<std::pair<int, int>> getPseudoLegalMoves(Board& board, GameLogic& logic) = 0;
	std::vector<std::pair<int, int>> getLegalMoves(std::vector<std::pair<int, int>> pseudoLegalMoves);
	//draws the piece on the screen
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

class Pawn : public Piece
{
private:

	void initVariables();
	bool hasMoved;
public:
	//Constructors / Destructors
	Pawn(Game* game, PieceColor _color);
	Piece* clone() const;
	void setBoardPos(std::pair<char, int> _boardPos);
	void setHasMoved();
	std::vector<std::pair<int, int>> getPseudoLegalMoves(Board& board, GameLogic& logic);

};

class Knight : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	Piece* clone() const;
	Knight(Game* game, PieceColor _color);
	std::vector<std::pair<int, int>> getPseudoLegalMoves(Board& board, GameLogic& logic);
};

class Bishop : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	Piece* clone() const;
	Bishop(Game* game, PieceColor _color);
	std::vector<std::pair<int, int>> getPseudoLegalMoves(Board& board, GameLogic& logic);
};

class Rook : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	Piece* clone() const;
	Rook(Game* game, PieceColor _color);
	std::vector<std::pair<int, int>> getPseudoLegalMoves(Board& board, GameLogic& logic);
};

class Queen : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	Piece* clone() const;
	Queen(Game* game, PieceColor _color);
	std::vector<std::pair<int, int>> getPseudoLegalMoves(Board& board, GameLogic& logic);
};

class King : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	Piece* clone() const;
	King(Game* game, PieceColor _color);
	std::vector<std::pair<int, int>> getPseudoLegalMoves(Board& board, GameLogic& logic);
};