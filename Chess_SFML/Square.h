#pragma once
#include <utility>
#include "Piece.h"

/*
	A class representing a square on a chessboard.
	A square can be occupied by a chess piece.
*/

class Square
{
	private:

	//Private variables

		int posX, posY; //position on the screen [pixels]
		int coordinateX, coordinateY; //coordinates of the square in relation to the board itself [1-8][1-8]
		bool isOccupied; //determines whether a square is occupied by a chess piece
		bool isWhite; 
		Piece piece;

	//Private methods

		void initVariables(); //initializes the private variables 

	public:
		sf::RectangleShape sqr;
	//Constructors / Destructors

		Square();
		~Square();

	//Methods
	
		//returns the coordinates of the square as a pair: <coordinateX, coordinateY>
		std::pair<int, int> getCoordinates();

		//sets the coordinates of a square
		void setCoordinates(int new_coordinateX, int new_coordinateY); 

		//returns the position of the square as a pair: <posX, posY>
		std::pair<int, int> getPosition(); 

		//sets the position of a square
		void setPosition(int new_posX, int new_posY); 

		//sets the square color to white or black
		void setSquareColorToWhite();
		void setSquareColorToBlack();

		//draws the square on the screen
		void draw();

};

