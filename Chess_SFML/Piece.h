#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include <iostream>
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
		void writeName();
		std::string getName();
		virtual void getLegalMoves() = 0;
		//draws the piece on the screen
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

class Pawn : public Piece
{
private:

	void initVariables();
public:
	//Constructors / Destructors
	Pawn(PieceColor _color);
	~Pawn();

	void getLegalMoves() { std::cout << "legalmoves\n"; };
};

class Knight : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	Knight(PieceColor _color);
	~Knight();


	void getLegalMoves() { std::cout << "legalmoves\n"; };
};

class Bishop : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	Bishop(PieceColor _color);
	~Bishop();


	void getLegalMoves() { std::cout << "legalmoves\n"; };
};

class Rook : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	Rook(PieceColor _color);
	~Rook();


	void getLegalMoves() { std::cout << "legalmoves\n"; };
};

class Queen : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	Queen(PieceColor _color);
	~Queen();


	void getLegalMoves() { std::cout << "legalmoves\n"; };
};

class King : public Piece
{
private:

	void initVariables();

public:
	//Constructors / Destructors
	King(PieceColor _color);
	~King();


	void getLegalMoves() { std::cout << "legalmoves\n"; };
};