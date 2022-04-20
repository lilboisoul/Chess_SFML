#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
/*
	A class representing a chess piece.

*/ 
class Piece
{
	private:
	//Private variables
	
	//Private methods

		void initVariables();

	public:

		sf::RectangleShape piece;

	//Constructors / Destructors
	
		Piece();
		~Piece();

	//Methods
};

