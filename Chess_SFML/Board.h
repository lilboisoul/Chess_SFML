#pragma once
#include "Square.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include "SFML\Graphics.hpp"
/*
	A class representing a chessboard - it contains a two-dimensional, 8 by 8 array of Square objects.
	It is used as a background for Squares.
*/

class Board : public sf::Drawable
{		
private:

	void convertFENIntoPieces();

public: 

	//An array containing 64 squares in 8 rows and 8 columns
		Square arrayOfSquares[8][8];
		
	//Visual representation of the board
		sf::RectangleShape boardGameObject;

	//Constructors / Destructors

		Board();
		~Board();

	//Public methods

		//initializes the board
			void initBoard();
			void initArrayOfSquares();
		

		//draws the board on the screen

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	


};
