#pragma once
#ifdef _DEBUG
#pragma comment ( lib , "sfml-main-d.lib" )
#elif defined (NDEBUG)
#pragma comment ( lib , "sfml-main.lib" )
#else
 
#endif

#include "Game.h"
#include "Board.h"

int main()
{
	
	// Initiate game board.
	sf::RenderWindow app;
	Board board(app);
	board.initiateGrid();
	board.initiateFrame();
	board.startGame();
	
	
	return 0;
}


Game::Game()
{
}


Game::~Game()
{
}
