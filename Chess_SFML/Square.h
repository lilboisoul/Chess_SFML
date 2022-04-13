#pragma once
#include <utility>

/*
	A class representing a square on a chessboard.
	A square can be occupied by a chess piece.

*/

class Square
{
private:
	//Private variables

	int posX, posY;
	//bool isOccupied

	//Private methods

	void initVariables(); //initializes the private variables 

public:
	//Constructors / Destructors

	Square();
	~Square();

	//Methods
	std::pair<int, int> getPosition(); //returns the position of the square as a pair: <posX, posY>
	void setPosition(int new_posX, int new_posY);
};

