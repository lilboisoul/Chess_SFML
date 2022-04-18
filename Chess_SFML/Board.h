#pragma once
#include "Square.h"
#include <iostream>

/*
	A class representing a chessboard - it contains a two-dimensional, 8 by 8 array of Square objects.
	It is used as a background for Squares.
*/

class Board
{
private:

	//Private variables

		Square board[8][8];

public:

	//Constructors / Destructors

		Board();
		~Board();

	//Public methods

	//initializes the squares in the array
		void initBoard();

	//draws the board on the screen
		void draw();
	


};
