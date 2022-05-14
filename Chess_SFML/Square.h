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

		std::pair<int, int>  getPosition(); 
		void				 setPosition(int new_posX, int new_posY); 
		std::pair<char, int> getBoardPos();
		void				 setBoardPos(int new_posX, int new_posY);
		void				 setSquareColorToWhite();
		void				 setSquareColorToBlack();
		//initializes a piece from the FEN code
		void				 placePiece(Piece* piece);

		

		//draws the square on the screen
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

