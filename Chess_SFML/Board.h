#pragma once
#include "Square.h"
#include <iostream>
#include "SFML\Graphics.hpp"
/*
	A class representing a chessboard - it contains a two-dimensional, 8 by 8 array of Square objects.
	It is used as a background for Squares.
*/

class Board
{		
public:
	//Public variables 

		Square board[8][8];
		sf::RectangleShape brd;

	//Constructors / Destructors

		Board();
		~Board();

	//Public methods

	//initializes the squares in the array
		void initBoard();

	//draws the board on the screen
		void draw();
	


};
