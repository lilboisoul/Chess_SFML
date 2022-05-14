#pragma once
#include <utility>
#include "Piece.h"

/*
	A class representing a square on a chessboard.
	A square can be occupied by a chess piece.
*/
enum class SquareColor {
	WHITE,
	BLACK
};
class Square : public sf::Drawable
{
	private:

	//Private variables

		int posX, posY; //position on the screen [pixels]
		std::pair<char, int> boardPos;
		SquareColor squareColor;
		Piece* piecePtr;

	//Private methods

		//Initializes private variables 
		void initVariables();

	public:

	//Visual representation of the square
		sf::RectangleShape squareGameObject;

	//Constructors / Destructors
		Square();
		Square(SquareColor _color);
		~Square();

	//Methods

		//returns the position of the square as a pair: <posX, posY>
		std::pair<int, int> getPosition(); 

		//sets the position of a square
		void setPosition(int new_posX, int new_posY); 

		//sets the square color to white or black
		void setSquareColorToWhite();
		void setSquareColorToBlack();

		//initializes a piece from the FEN code
		void placePiece(Piece* piece);

		//draws the square on the screen
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

