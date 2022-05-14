#include "Board.h"

void Board::initBoard()
{
	//initializes the board 
	this->boardGameObject.setPosition({ 100, 50 });
	this->boardGameObject.setSize(sf::Vector2f(800.0f, 800.0f));
	this->boardGameObject.setFillColor(sf::Color::Yellow);
	this->boardGameObject.setOutlineColor(sf::Color::Black);
	this->boardGameObject.setOutlineThickness(2.f);

	
}

void Board::initArrayOfSquares()
{
	//sets the position and the color of squares in the array
	int temporaryNumber = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			// if/else statement determining whether the square should be black or white
			if (temporaryNumber % 2 == 1)
			{
				this->arrayOfSquares[i][j].setSquareColorToBlack();
			}
			else {
				this->arrayOfSquares[i][j].setSquareColorToWhite();
			}
			temporaryNumber++;

			
			//sets the position of squares on the board in pixels
			this->arrayOfSquares[i][j].setPosition(boardGameObject.getPosition().x + 100 * j, boardGameObject.getPosition().y + 100 * i);
			this->arrayOfSquares[i][j].setBoardPos(j, 8-i);
			//std::cout << "" << arrayOfSquares[i][j].getBoardPos().first << arrayOfSquares[i][j].getBoardPos().second << " ";
			//std::cout << "{" << array_of_squares[i][j].getPosition().first << " " << array_of_squares[i][j].getPosition().second << "} ";
		}
		temporaryNumber++;
		std::cout << "\n";
	}
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(boardGameObject);
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			target.draw(arrayOfSquares[i][j]);
		}
	}
}

void Board::convertFENIntoPieces()
{
	//converts a FEN notation from a file into a two-dimensional character array
	std::filesystem::path path = std::filesystem::current_path().append("fen.txt");

	//temporary variables
	char temporaryCharacter;
	int row = 7, column = 0;

	//initializes the array
	char fenPosition[8][8];
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			fenPosition[i][j] = '-';
		}
	}

	//if FEN file exists, convert
	if (std::filesystem::exists(path)) {
		std::ifstream plik(path);
		while (plik >> temporaryCharacter)
		{

			if (temporaryCharacter >= 'a' && temporaryCharacter <= 'z'|| temporaryCharacter >= 'A' && temporaryCharacter <= 'Z')
			{
				fenPosition[row][column] = temporaryCharacter;
				
				column++;
			}
			else if (temporaryCharacter == '/')
			{
				row--;
				column = 0;
			}
			else {
				column += static_cast<int>(temporaryCharacter - 48);
			}
			if (row == 0 && column == 8) break; //checks for the end of piece placement section of the FEN code
		}
	}
	//if FEN file doesn't exist, load the default position
	else {
		const char* defaultFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
		for(int i = 0; i < 42; i++)
		{
			temporaryCharacter = defaultFEN[i];
			if (temporaryCharacter >= 'a' && temporaryCharacter <= 'z' || temporaryCharacter >= 'A' && temporaryCharacter <= 'Z')
			{
				fenPosition[row][column] = temporaryCharacter;

				column++;
			}
			else if (temporaryCharacter == '/')
			{
				row--;
				column = 0;
			}
			else {
				column += static_cast<int>(temporaryCharacter - 48);
			}
			if (row == 0 && column == 8) break; //checks for the end of piece placement section of the FEN code
		}
	}

	//displays the board in the console
	/*for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			std::cout << fenPosition[i][j] << " ";
		}
		std::cout << "\n";
	}*/

	//converts array into Piece pointers
	for (int i = 8; i > 0; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			switch (fenPosition[i-1][j])
			{
			case 'p':
				arrayOfSquares[i - 1][j].placePiece(new Pawn(PieceColor::WHITE));
				break;

			case 'P':
				arrayOfSquares[i - 1][j].placePiece(new Pawn(PieceColor::BLACK));
				break;

			case 'r':
				arrayOfSquares[i - 1][j].placePiece(new Rook(PieceColor::WHITE));
				break;

			case 'R':
				arrayOfSquares[i - 1][j].placePiece(new Rook(PieceColor::BLACK));
				break;

			case 'n':
				arrayOfSquares[i - 1][j].placePiece(new Knight(PieceColor::WHITE));
				break;

			case 'N':
				arrayOfSquares[i - 1][j].placePiece(new Knight(PieceColor::BLACK));
				break;

			case 'b':
				arrayOfSquares[i - 1][j].placePiece(new Bishop(PieceColor::WHITE));
				break;

			case 'B':
				arrayOfSquares[i - 1][j].placePiece(new Bishop(PieceColor::BLACK));
				break;

			case 'q':
				arrayOfSquares[i - 1][j].placePiece(new Queen(PieceColor::WHITE));
				break;

			case 'Q':
				arrayOfSquares[i - 1][j].placePiece(new Queen(PieceColor::BLACK));
				break;

			case 'k':
				arrayOfSquares[i - 1][j].placePiece(new King(PieceColor::WHITE));
				break;

			case 'K':
				arrayOfSquares[i - 1][j].placePiece(new King(PieceColor::BLACK));
				break;
			}

		}
		
	}


}

Board::Board()
{
	this->initBoard();
	this->initArrayOfSquares();
	this->convertFENIntoPieces();
}


Board::~Board()
{
}
