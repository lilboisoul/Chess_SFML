#include "Board.h"
#include "Game.h"
Board::Board(Game* _game): gamePtr(_game)
{
	this->initTextures();
	this->initBoard();
	this->initArrayOfSquares();
	this->convertFENIntoPieces();
}


Board::~Board()
{
	delete gamePtr;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete arrayOfSquares[i][j];
		}
	}
}

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
			arrayOfSquares[i][j] = new Square(gamePtr);
			// if/else statement determining whether the square should be black or white
			if (temporaryNumber % 2 == 1)
			{
				this->arrayOfSquares[i][j]->setSquareColorToBlack();
			}
			else {
				this->arrayOfSquares[i][j]->setSquareColorToWhite();
			}
			temporaryNumber++;

			
			//sets the position of squares on the board in pixels
			this->arrayOfSquares[i][j]->setPosition(boardGameObject.getPosition().x + 100 * j, boardGameObject.getPosition().y + 100 * i);
			this->arrayOfSquares[i][j]->setBoardPos(j, 8-i);
			//std::cout << "" << arrayOfSquares[i][j].getBoardPos().first << arrayOfSquares[i][j].getBoardPos().second << " ";
			//std::cout << "{" << array_of_squares[i][j].getPosition().first << " " << array_of_squares[i][j].getPosition().second << "} ";
		}
		temporaryNumber++;
		std::cout << "\n";
	}
}

inline void Board::update()
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			arrayOfSquares[i][j]->update();
		}
	}
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(boardGameObject);
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			target.draw(*arrayOfSquares[i][j]);
		}
	}
}
void Board::initTextures()
{
	sf::Texture texture;
	texture.loadFromFile("PieceTextures/bP.png");
	textures.insert(std::make_pair("black_pawn", texture));
	texture.loadFromFile("PieceTextures/wP.png");
	textures.insert(std::make_pair("white_pawn", texture));
	texture.loadFromFile("PieceTextures/bB.png");
	textures.insert(std::make_pair("black_bishop", texture));
	texture.loadFromFile("PieceTextures/wB.png");
	textures.insert(std::make_pair("white_bishop", texture));
	texture.loadFromFile("PieceTextures/bR.png");
	textures.insert(std::make_pair("black_rook", texture));
	texture.loadFromFile("PieceTextures/wR.png");
	textures.insert(std::make_pair("white_rook", texture));
	texture.loadFromFile("PieceTextures/bK.png");
	textures.insert(std::make_pair("black_king", texture));
	texture.loadFromFile("PieceTextures/wK.png");
	textures.insert(std::make_pair("white_king", texture));
	texture.loadFromFile("PieceTextures/bQ.png");
	textures.insert(std::make_pair("black_queen", texture));
	texture.loadFromFile("PieceTextures/wQ.png");
	textures.insert(std::make_pair("white_queen", texture));
	texture.loadFromFile("PieceTextures/bN.png");
	textures.insert(std::make_pair("black_knight", texture));
	texture.loadFromFile("PieceTextures/wN.png");
	textures.insert(std::make_pair("white_knight", texture));
	

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
				arrayOfSquares[i - 1][j]->placePiece(new Pawn(PieceColor::WHITE));
				arrayOfSquares[i - 1][j]->getPiecePtr()->setTexture(&textures.at("white_pawn"));
				break;

			case 'P':
				arrayOfSquares[i - 1][j]->placePiece(new Pawn(PieceColor::BLACK));
				arrayOfSquares[i - 1][j]->getPiecePtr()->setTexture(&textures.at("black_pawn"));
				break;

			case 'r':
				arrayOfSquares[i - 1][j]->placePiece(new Rook(PieceColor::WHITE));
				arrayOfSquares[i - 1][j]->getPiecePtr()->setTexture(&textures.at("white_rook"));
				break;

			case 'R':
				arrayOfSquares[i - 1][j]->placePiece(new Rook(PieceColor::BLACK));
				arrayOfSquares[i - 1][j]->getPiecePtr()->setTexture(&textures.at("black_rook"));
				break;

			case 'n':
				arrayOfSquares[i - 1][j]->placePiece(new Knight(PieceColor::WHITE));
				arrayOfSquares[i - 1][j]->getPiecePtr()->setTexture(&textures.at("white_knight"));
				break;

			case 'N':
				arrayOfSquares[i - 1][j]->placePiece(new Knight(PieceColor::BLACK));
				arrayOfSquares[i - 1][j]->getPiecePtr()->setTexture(&textures.at("black_knight"));
				break;

			case 'b':
				arrayOfSquares[i - 1][j]->placePiece(new Bishop(PieceColor::WHITE));
				arrayOfSquares[i - 1][j]->getPiecePtr()->setTexture(&textures.at("white_bishop"));
				break;

			case 'B':
				arrayOfSquares[i - 1][j]->placePiece(new Bishop(PieceColor::BLACK));
				arrayOfSquares[i - 1][j]->getPiecePtr()->setTexture(&textures.at("black_bishop"));
				break;

			case 'q':
				arrayOfSquares[i - 1][j]->placePiece(new Queen(PieceColor::WHITE));
				arrayOfSquares[i - 1][j]->getPiecePtr()->setTexture(&textures.at("white_queen"));
				break;

			case 'Q':
				arrayOfSquares[i - 1][j]->placePiece(new Queen(PieceColor::BLACK));
				arrayOfSquares[i - 1][j]->getPiecePtr()->setTexture(&textures.at("black_queen"));
				break;

			case 'k':
				arrayOfSquares[i - 1][j]->placePiece(new King(PieceColor::WHITE));
				arrayOfSquares[i - 1][j]->getPiecePtr()->setTexture(&textures.at("white_king"));
				break;

			case 'K':
				arrayOfSquares[i - 1][j]->placePiece(new King(PieceColor::BLACK));
				arrayOfSquares[i - 1][j]->getPiecePtr()->setTexture(&textures.at("black_king"));
				break;
			}

		}
		
	}


}

