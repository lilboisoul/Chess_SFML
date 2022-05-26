#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include <iostream>
#include <vector>

/*
	A class representing a chess piece.

*/ 

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
		sf::RectangleShape pieceGameObject;
		std::string name;
		std::pair<char, int> boardPos;
		int posX, posY; //position on the screen [pixels]
		PieceColor pieceColor;
	//Constructors / Destructors
		
		Piece(PieceColor _color);
		~Piece();

	//Methods
		//returns the position of the piece as a pair: <posX, posY>
		std::pair<int, int> getPosition();

		//sets the position of a piece
		void setPosition(int new_posX, int new_posY);
		void setTexture(sf::Texture* texture);
		void setBoardPos(std::string _boardPos);
		void setBoardPos(std::pair<char, int> _boardPos);
		std::pair<char, int> getBoardPos();
		std::string getBoardPosAsString();
		void writeName();
		std::string getName();
		PieceColor getPieceColor();
		virtual std::vector<std::string> getLegalMoves() = 0;
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
	Pawn(PieceColor _color);
	~Pawn();

	std::vector<std::string> getLegalMoves();
};

class Knight : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	Knight(PieceColor _color);
	~Knight();


	std::vector<std::string> getLegalMoves() ;
};

class Bishop : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	Bishop(PieceColor _color);
	~Bishop();


	std::vector<std::string> getLegalMoves() ;
};

class Rook : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	Rook(PieceColor _color);
	~Rook();


	std::vector<std::string> getLegalMoves() ;
};

class Queen : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	Queen(PieceColor _color);
	~Queen();


	std::vector<std::string> getLegalMoves();
};

class King : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	King(PieceColor _color);
	~King();


	std::vector<std::string> getLegalMoves() ;
};