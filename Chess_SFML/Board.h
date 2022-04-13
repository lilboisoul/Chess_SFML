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

	//Private methods

	void initBoard(); //initializes the squares in the array

public:

	//Constructors / Destructors

	Board();
	~Board();


};
