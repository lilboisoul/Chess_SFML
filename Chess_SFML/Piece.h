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
enum class PieceColor{
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
		int posX, posY; //position on the screen [pixels]
		PieceColor pieceColor;
	//Constructors / Destructors
		
		Piece(Game* _game, PieceColor _color);
		~Piece();

	//Methods
		//returns the position of the piece as a pair: <posX, posY>
		std::pair<int, int> getPosition();

		//sets the position of a piece
		void setPosition(int new_posX, int new_posY);
		void setTexture(sf::Texture* texture);
		void setBoardPos(std::string _boardPos);
		virtual void setBoardPos(std::pair<char, int> _boardPos);
		std::pair<char, int> getBoardPos();
		std::string getBoardPosAsString();
		void writeName();
		std::string getName();
		PieceColor getPieceColor();
		virtual std::vector<std::pair<int, int>> getLegalMoves() = 0;
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
	~Pawn();
	void setBoardPos(std::pair<char, int> _boardPos);
	void setHasMoved();
	std::vector<std::pair<int, int>> getLegalMoves();
	
};

class Knight : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	Knight(Game* game, PieceColor _color);
	~Knight();


	std::vector<std::pair<int, int>> getLegalMoves();
	
};

class Bishop : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	Bishop(Game* game, PieceColor _color);
	~Bishop();


	std::vector<std::pair<int, int>> getLegalMoves();
	
};

class Rook : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	Rook(Game* game, PieceColor _color);
	~Rook();


	std::vector<std::pair<int, int>> getLegalMoves();
	
};

class Queen : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	Queen(Game* game, PieceColor _color);
	~Queen();


	std::vector<std::pair<int, int>> getLegalMoves();
};

class King : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	King(Game* game, PieceColor _color);
	~King();


	std::vector<std::pair<int, int>> getLegalMoves();

};