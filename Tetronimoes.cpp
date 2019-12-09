#include "Tetronimoes.h"
#include <iostream>
#include <cstdlib>

bool Tetronimoes::rowEmpty(int rowIndex)
{
	for (size_t i = 0; i < 4; i++)
	{
		if (pieceInfo[rowIndex][i] == 1)
			return false;
	}
	return true;
}

// ** Function: Set Block
// ** Draws the blocks of the tetro piece given current row and column.  ** 
void Tetronimoes::setBlock(int row, int col, int offsetDist,sf::RenderWindow &window)
{
	sf::Color m_default(sf::Color::Black);
	sf::Color testcolor(sf::Color::Green);
	int startCol = col;
	int startRow = row;
	float x = BoardWidth / m_Cols;
	float y = BoardHeight / m_Rows;

	for (int index1 = 3; index1 >= 0 ; index1--)
	{
		startCol = col;
		for (int tempCol1 = 0; tempCol1 < 4; tempCol1++)
		{
			if (containsMarker(index1, tempCol1))
			{				
				if (col == m_Cols + 3) {
					block.colorCell(m_tetroColor);
				}
				else
				{
					block.colorCell(m_tetroColor);
				}
				
				block.setPosition(((float)startCol * x+60), ((float)startRow * y+40));
				block.drawblock(window);
				
			}
			else
			{
				
				if (col == m_Cols+3)
				{
					block.colorCell(m_default);
					block.setPosition(((float)startCol * x+60), ((float)startRow * y+40));
					block.setOutline(m_default);
					block.drawblock(window);
				}
			}
			startCol++;
		}
		startRow--;
	}
}

// Constructor
Tetronimoes::Tetronimoes(int  *piece, int randy) 
{
	// Seed random number
	srand(time(NULL));
	
	// Random column, random color
	int randomXstart = 0 + rand() % 7;
	int randomColor = 0 + rand() % 7;

	m_tetroColor = colorArray[randomColor];
	m_currentCol = randomXstart;
	int index = 0;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t k = 0; k < 4; k++)
		{
			if (piece[index] == 1)
				pieceInfo[i][k] = 1;
			else
				pieceInfo[i][k] = 0;
			index++;
		}
		
	}
}

// ******* Contains Marker Function ********
// -------- Returns true if 4x4 at [i][j] has a 1 - else, returns false
bool Tetronimoes::containsMarker(int i, int j)
{
	if (pieceInfo[i][j] == 1) 
	{ return true; 
	}
	else 
	{
		return false;
	}

}

// *********** Rotate 4x4 Matrix **************
void Tetronimoes::rotatematrix(vector<vector<Block>> m_TetrisGrid)
{
	int m = 4;
	int n = 4;
	int tempArray[4][4];
	std::move(&pieceInfo[0][0], &pieceInfo[0][0] + 16, &tempArray[0][0]);

	for (int i = 0; i<n / 2; i++)
		for (int j = 0; j<(n + 1) / 2; j++)
			cyclic_roll(pieceInfo[i][j], pieceInfo[n - 1 - j][i], pieceInfo[n - 1 - i][n - 1 - j], pieceInfo[j][n - 1 - i]);

	if(!shiftPiece(0, m_TetrisGrid))
		std::move(&tempArray[0][0], &tempArray[0][0] + 16, &pieceInfo[0][0]);
	

}
// Helper for rotate
void Tetronimoes::cyclic_roll(int &a, int &b, int &c, int &d)
{
	int temp = a;
	a = b;
	b = c;
	c = d;
	d = temp;
}

// Checks to see if the piece is with in boundaries given a direction(left, none, right)
// Returns true if we can, false if we can't
bool Tetronimoes::shiftPiece(int direction, vector<vector<Block>> m_TetrisGrid)
{
	// lets try right first
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (containsMarker(i, j))
			{
				if (getCurrentCol() + j + direction == m_Cols)
					return false;
				if (getCurrentCol() + j + direction == -1)
					return false;
				if (m_TetrisGrid[getCurrentRow() - 3 + i][getCurrentCol() + j+direction].isFilled())
					return false;
			}
		}
	}
	return true;
}