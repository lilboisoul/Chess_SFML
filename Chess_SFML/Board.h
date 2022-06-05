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

class Game;
class Board : public sf::Drawable
{		
private:
	//FEN -> pieces
	void convertFENIntoPieces(std::string FEN);

	//Handling textures
	std::map <std::string, sf::Texture> textures;
	void initTextures();
public: 
		Game* gamePtr;
	//An array containing 64 squares in 8 rows and 8 columns
		Square* arrayOfSquares[8][8];
		
		
	//Visual representation of the board
		sf::RectangleShape boardGameObject;

	//Constructors / Destructors

		Board(Game* _game, std::string FEN_filename);
		~Board();

	//Public methods

		void initBoardVisualProperties();
		void initArrayOfSquares();
		void showLegalMoves(std::vector<std::pair<int,int>> legalMoves);
		void unShowLegalMoves();
	//draws the board on the screen
		virtual inline void update();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	


};
