#pragma once


#include "Block.h"
#include <vector>
using std::vector;
class Tetronimoes
{
private:
	Block block{};
	sf::Color m_tetroColor;
	int pieceInfo[4][4];
	int m_currentRow = 3;
	int m_currentCol;	
	int BoardWidth = 600;
	int BoardHeight = 800;
	int WindowWidth = 1200;
	int WindowHeight = 880;
	int m_Cols = 10;
	int m_Rows = 20;
	int offset = 100;
	
	const sf::Color colorArray[7] = { sf::Color::Cyan, sf::Color::Blue, sf::Color::Green, sf::Color::Red, sf::Color::Yellow, sf::Color::Magenta, sf::Color::White };

	
public:
	// Rotate Matrix
	void rotatematrix(vector<vector<Block>> m_TetrisGrid);
	void cyclic_roll(int &a, int &b, int &c, int &d);
	// ShiftPiece
	bool shiftPiece(int direction, vector<vector<Block>> m_TetrisGrid);

	bool rowEmpty(int rowIndex);
	int getCurrentRow() { return m_currentRow; }
	int getCurrentCol() { return m_currentCol; }
	void increaseRow() { m_currentRow++; }
	void setRowIndex(int newIndex) { m_currentRow = newIndex; }
	void setColIndex(int newIndex) { m_currentCol = newIndex; }
	void increaseCol() { m_currentCol++; }
	void decreaseCol() { m_currentCol--; }
	void setBlock(int row, int col, int offset, sf::RenderWindow &window);
	

	sf::Color &getColor() { return m_tetroColor; }
	Tetronimoes(int *piece, int randy);
	bool containsMarker(int i, int j);
};

