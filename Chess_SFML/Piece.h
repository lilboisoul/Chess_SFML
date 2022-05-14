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
		int posX, posY; //position on the screen [pixels]
		int coordinateX, coordinateY; //coordinates of the square in relation to the board itself [1-8][1-8]
		PieceColor pieceColor;
	//Constructors / Destructors
		
		Piece(PieceColor _color);
		~Piece();

	//Methods
		//returns the coordinates of the piece as a pair: <coordinateX, coordinateY>
		std::pair<int, int> getCoordinates() ;

		//sets the coordinates of a piece
		void setCoordinates(int new_coordinateX, int new_coordinateY);

		//returns the position of the piece as a pair: <posX, posY>
		std::pair<int, int> getPosition();

		//sets the position of a piece
		void setPosition(int new_posX, int new_posY);


		virtual void getName() = 0;
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

	//draw the pawn on the screen
	void getName() { std::cout << "pawn\n"; };
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

	//draw the pawn on the screen
	void getName() { std::cout << "knight\n"; };
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

	//draw the pawn on the screen
	void getName() { std::cout << "bishop\n"; };
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

	//draw the pawn on the screen
	void getName() { std::cout << "rook\n"; };
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

	//draw the pawn on the screen
	void getName() { std::cout << "queen\n"; };
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

	//draw the pawn on the screen
	void getName() { std::cout << "king\n"; };
	void getLegalMoves() { std::cout << "legalmoves\n"; };
};