#pragma once
enum class PlayerColor {
	WHITE,
	BLACK
};
class GameLogic
{
private:

	PlayerColor CurrentPlayer;

public:
	GameLogic();
	
	void initVariables();
	PlayerColor getCurrentPlayer();
	void  setCurrentPlayer(PlayerColor _color);
	void  swapCurrentPlayer();

};

