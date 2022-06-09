#pragma once
#include <utility>
#include "Piece.h"
#include <iostream>

enum class SquareColor {
	WHITE,
	BLACK
};


class Game;
/*
	A class representing a square on a chessboard.
	A square can be occupied by a chess piece.
*/

class Square : public sf::Drawable
{
	private:

	//Private variables

		float posX, posY; //position on the screen [pixels]
		std::pair<char, int> boardPos;
		SquareColor squareColor;
		Piece* piecePtr;
		bool isClicked;
		Game* gamePtr;
	//Private methods

		//Initializes private variables 
		void initVariables();

	public:

	//Visual representation of the square
		sf::RectangleShape squareGameObject;

	//Constructors / Destructors
		Square(Game* _game);
		Square(const Square& _square);
		Square(SquareColor _color);
		~Square();
		Square& operator=(const Square& _square);
		Square* clone() const;

	//Methods

		std::pair<int, int>  getPosition();
		void setPosition(float new_posX, float new_posY); 
		std::pair<char, int> getBoardPos();
		std::pair<int, int>getBoardPosAsInt();
		std::string getBoardPosAsString();
		void setBoardPos(int new_posX, int new_posY);
		void setSquareColorToWhite();
		void setSquareColorToBlack();
		SquareColor getSquareColor();
		bool isSquareClicked();
		void squareClicked();
		void squareUnclicked();
		//initializes a piece from the FEN code
		void placePiece(Piece* piece);
		Piece* getPiecePtr();
		void move(Square* new_square);

		//draws the square on the screen
		virtual inline void update();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

