#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "Block.h"
#include "Tetronimoes.h"
#include "SFML\Audio.hpp"


using std::vector;
class Board
{

private:
	

	int shit;
	
	int BoardWidth = 600;
	int BoardHeight = 800;
	int WindowWidth = 1200;
	int WindowHeight = 880;
	int m_Cols = 10;
	int m_Rows = 20;
	int offset = 100;


	// Vector of rectangles to draw the grid
	vector<vector<Block>> m_TetrisGrid;
	vector<Tetronimoes> m_Tetros;
	vector<Block> m_Frame;
	// The window where to draw the board
	sf::RenderWindow &m_window;

	
	
	bool m_Grid[10][20];
	// 7 Blocks, each one is 4 by 4 spaces
	//static int blockInfo[10][4 * 4];
	// Colors for the blocks
	static int blockInfoColor[7];
	int m_score = 0;
	sf::Text scoreText;
	sf::Text levelText;
	sf::Text nextPieceText;
	sf::Font font;
	sf::Texture texture;
	std::string nextpiece = "Next piece";
	std::string level = "Level : ";
	std::string score= "Your score = ";
	sf::Music music;
	int m_currentLevel = 1;
	float m_fallSpeed = 0.8;
	void increaseTime(float &time) { time = time - 0.2; }

public:
	
	void drawFrame();
	// Initiate frame
	void initiateFrame();

	// Smash row - accepts the row, and smashes the shit out of it
	void smashRow(int row);

	// Initiate smashing - start smashing row process
	bool initiateSmashing(int colRow);

	// Check if row is completed( every cell is filled )
	bool rowCompleted(vector<Block> vec);

	void drawTetroPiece(Tetronimoes &piece);
	// Constructor
	Board(sf::RenderWindow &tetris_window);
	// Draw Tetroes
	// Whites out cell
	void whiteOutCell(int row, int col) { m_TetrisGrid[row][col].whitenCell(); }
	// Fill cell with color
	void fillCell(int row, int col, sf::Color color) { m_TetrisGrid[row][col].colorCell(color); }

	void drawTetroe(Tetronimoes &TetroPiece_Current);
	// Move tetro piece
	bool moveTetro(Tetronimoes &TetroPiece_Current, int direction);
	// Start the game

	void startGame();

	//game over- when the board if full
	void gameOver();

	////////////////Lock Tetro Function//////////////////////
	bool lockPiece(Tetronimoes &tetro);

	
	void drawStackPiece(Tetronimoes &stack_piece);

	// Initiate Grid and Tetris pieces
	void initiateGrid();
	int getBoardHeight();
	int getBoardWidth();
	int getRows();
	int getColumns();
	void draw(Tetronimoes &tetro, Tetronimoes &stack_piece);
	bool checkBoundries(Tetronimoes &TetroPiece_Current);
	int blockInfo[7][4 * 4] =
	{ {
			// Line
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
		},
		{
			// Box
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		},
		{ // L
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		},
		{ // L Backwards
			0, 0, 1, 0,
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		},
		{ // Crossed
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0,
		},
		{ // Squiggle left
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0,
		},
		{ //Squiggle right
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0,
		} };
	
};


