#include "Board.h"
#include <iostream>
#include <cstdlib>
#include<sstream>


// *****************************************************
//					Initiate Grid
// *****************************************************
void Board::initiateGrid()
{

	//Size of each rectangle is boardsize/rows, boardsize/cols
	float x = (BoardWidth / m_Cols);
	float y = (BoardHeight / m_Rows);

	vector<Block> m_blockRow;

	for (int i = 0; i < m_Rows; i++)
	{
		for (int k = 0; k < m_Cols; k++)
		{

			sf::RectangleShape rect{ sf::Vector2f{ x,y } };
			std::cout << x << " " << y << std::endl;
			rect.setPosition((k * x)+60, i  * y+40);
			//rect.setFillColor(sf::Color::White);
			rect.setOutlineColor(sf::Color::White);
			//rect.setFillColor(sf::Color::Green);
			rect.setFillColor(sf::Color::Black);
			rect.setOutlineThickness(1.5f);

			//rect.setSize(sf::Vector2f((float)BoardWidth/m_Cols, (float)BoardHeight/m_Rows));
			Block block{ rect };

			//m_window.draw(rect);
			m_blockRow.push_back(block);

		}
		m_TetrisGrid.push_back(m_blockRow);
		m_blockRow.clear();

	}
}

// *****************************************************
//					Accessors
// *****************************************************
int Board::getBoardHeight()
{
	return BoardHeight;
}
int Board::getBoardWidth()
{
	return BoardWidth;
}
int Board::getRows()
{
	return m_Cols;
}
int Board::getColumns()
{
	return m_Rows;
}

// *****************************************************
//					Draw Board Function
// *****************************************************
void Board::draw(Tetronimoes &tetro, Tetronimoes &stack_piece)
{

	// First display board
	std::for_each(m_TetrisGrid.begin(), m_TetrisGrid.end(), [&](auto & row)
	{
		std::for_each(row.begin(), row.end(), [&](auto & block) {block.drawblock(m_window); });
	});
	drawFrame();
	drawTetroPiece(tetro);
	drawStackPiece(stack_piece);
	
	//drawText();	
	m_window.display();

}

// *****************************************************
//					Check Boundaries
// *****************************************************
bool Board::checkBoundries(Tetronimoes & TetroPiece_Current)
{

	if (TetroPiece_Current.getCurrentRow() < 0)
	{
		TetroPiece_Current.increaseRow();
		return false;
	}
	if (TetroPiece_Current.getCurrentCol() < 0)
	{
		TetroPiece_Current.increaseCol();
		return false;
	}
	if (TetroPiece_Current.getCurrentCol() > m_Cols - 4)
	{
		TetroPiece_Current.decreaseCol();
		return false;
	}

}

// *****************************************************
//					Draw Tetro piece
// *****************************************************
void Board::drawTetroPiece(Tetronimoes &tetropiece)
{
	int tempRows = tetropiece.getCurrentRow();
	int offsetDif = 0;
	if (tempRows >= m_Rows - 1)
	{
		offsetDif = tempRows - m_Rows - 1;


	}

	tetropiece.setBlock(tempRows, tetropiece.getCurrentCol(), offsetDif, m_window);
}
// *****************************************************
//					Constructor
// *****************************************************
Board::Board(sf::RenderWindow & tetris_window) : m_window(tetris_window)
{

	//chack downloads
	if (!music.openFromFile("tetrismusic.wav"))
	{
		std::cerr << "can't open music" << std::endl;
	}
	if (!texture.loadFromFile("whatever.png"))
	{
		std::cerr << "Error loading texture";
	}
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cerr << "Error!";

	}	
	// select the font
	
	nextPieceText.setFont(font); // font is a sf::Fon
	nextPieceText.setPosition(800, 50);				// set the string to display
	nextPieceText.setString(nextpiece);
	nextPieceText.setCharacterSize(44); // in pixels, not points!					   // set the color
	nextPieceText.setFillColor(sf::Color::Blue);
	nextPieceText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	scoreText.setFont(font);
	scoreText.setPosition(800, 400);
	scoreText.setString(score);
	scoreText.setCharacterSize(44);
	scoreText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	scoreText.setFillColor(sf::Color::Red);
	levelText.setFont(font);
	levelText.setPosition(800, 650);				
	// set the string to display
	levelText.setString(level);
	levelText.setCharacterSize(44); // in pixels, not points!					  
	levelText.setFillColor(sf::Color::White);
	levelText.setStyle(sf::Text::Bold | sf::Text::Underlined);


	m_window.create(sf::VideoMode(WindowWidth, WindowHeight), "Tetris");
	m_window.display();

}

void Board::drawTetroe(Tetronimoes & TetroPiece_Current)
{
	if (TetroPiece_Current.getCurrentRow() < 0)
	{
		return;
	}
}
// *****************************************************
//					Move Tetro Function
// *****************************************************
bool Board::moveTetro(Tetronimoes & TetroPiece_Current, int direction)
{
	// 4x4 grid scan index
	int rowScanIndex = 0;

	// Iterate through the 4 by 4 matrix starting from bottom left corner
	for (int rowIndex = 3; rowIndex >= 0; rowIndex--)
	{

		for (int colIndex = 0; colIndex < 4; colIndex++)
		{
			// Does the current 4x4 contain a '1'?
			if (TetroPiece_Current.containsMarker(rowIndex, colIndex))
			{
				// Check to see if next row is last row. If it is, lock 
				// the piece.
				if (TetroPiece_Current.getCurrentRow() - rowScanIndex + 1 == m_Rows)
				{
					// LOCK THE PIECE
					std::cout << "Locking piece";
					lockPiece(TetroPiece_Current);
					return true;
				}
				//if (TetroPiece_Current.getCurrentRow() - rowScanIndex + 1 < m_Rows - 1)
				if (m_TetrisGrid[TetroPiece_Current.getCurrentRow() - rowScanIndex + 1][TetroPiece_Current.getCurrentCol() + colIndex].isFilled())
				{
					lockPiece(TetroPiece_Current);
					return true;
				}

			}
		}
		rowScanIndex++;
	}

	//std::cout << "Breakpoint";
	if (!direction)
	{
		//std::cout << "Going down a row." << std::endl;
		TetroPiece_Current.increaseRow();
	}
	return false;
}

// *****************************************************
// **************	 Start game	   *********************
// *****************************************************
void Board::startGame()
{
	
	music.play();
	music.setLoop(true);
	
	std::string num;
	num = std::to_string(m_score);
	score.append(num);
	std::string lev;
	lev = std::to_string(m_currentLevel);
	level.append(num);
	
	std::vector<Tetronimoes> m_Current;
	std::vector<Tetronimoes> m_onStack;
	sf::Clock gameClock;
	sf::Time deltaTime;
	sf::Time zeroTime = sf::seconds(0);
	srand(time(NULL));
	int random = rand() % 6;
	m_window.setFramerateLimit(33);

	Tetronimoes TetroShape(blockInfo[random],random);
	m_Current.push_back(TetroShape);
	//Next shape
	random = rand() % 6;
	Tetronimoes StackShape1(blockInfo[random],random);
	m_onStack.push_back(StackShape1);
	
	//TetroPiece_Current = TetroShape;

	float m_time = 0;
	bool flag = true;
	while (1)
	{
		while (m_window.isOpen())
		{

			
			sf::Event event;
			while (m_window.pollEvent(event))
			{

				switch (event.type)
				{
				case sf::Event::Closed:
					m_window.close();
					break;
				case sf::Event::KeyPressed:

					if (event.key.code == sf::Keyboard::Right)
					{

						if (m_Current[0].shiftPiece(1, m_TetrisGrid))
							m_Current[0].increaseCol();

					}
					if (event.key.code == sf::Keyboard::Left)
					{

						if (m_Current[0].shiftPiece(-1, m_TetrisGrid))
							m_Current[0].decreaseCol();
					}
					if (event.key.code == sf::Keyboard::Up)
					{
						m_Current[0].rotatematrix(m_TetrisGrid);
					}
					if (event.key.code == sf::Keyboard::Down)
					{
						if (moveTetro(m_Current[0], 0))
						{
							std::cout << "Piece locked";
							m_Current.pop_back();
							m_Current.push_back(m_onStack.at(0));
							random = 0 + rand() % 6;							
							m_onStack.pop_back();
							Tetronimoes StackShape(blockInfo[random], random);
							m_onStack.push_back(StackShape);
						}
					}
				
				}
			}
			// Create random Tetro
			// Pass it to moving
			deltaTime += gameClock.restart();
			if (deltaTime.asSeconds() > m_fallSpeed)
			{

				if (moveTetro(m_Current[0], 0)) {
					std::cout << "Piece locked";
					m_Current.pop_back();
					m_Current.push_back(m_onStack.at(0));
					m_onStack.pop_back();
					random = 0 + rand() % 6;
					Tetronimoes StackShape(blockInfo[random],random);
					m_onStack.push_back(StackShape);


				}
				deltaTime = zeroTime;
				
			}

			m_window.clear(); 
			levelText.setString(level);
			scoreText.setString(score);
			m_window.draw(nextPieceText);
			m_window.draw(levelText);
			m_window.draw(scoreText);
			draw(m_Current[0], m_onStack[0]);

			
		}
	}
	
}


// ************** Lock Tetro piece to board *********************
// Returns true if we succesfully lock into grid
// Returns false if we can't lock in. 
// If we can't lock, game over bro. 
bool Board::lockPiece(Tetronimoes & tetro)
{
	int RowMarkerIndex = -1;
	int holdColIndex = tetro.getCurrentCol();
	int holdRowIndex = tetro.getCurrentRow();
	sf::Color tempColor{ sf::Color::Yellow };
	holdRowIndex = holdRowIndex - 3;
	for (size_t i = 0; i < 4 && holdRowIndex < m_Rows; i++)
	{
		tetro.setColIndex(holdColIndex);
		for (size_t j = 0; j < 4; j++)
		{
			if (tetro.containsMarker(i, j))
			{
				if (holdRowIndex -1 < 0)
					gameOver();

				RowMarkerIndex = holdRowIndex;
				std::cout << "Hold Row Index " << holdRowIndex << std::endl;
				m_TetrisGrid[holdRowIndex][tetro.getCurrentCol()].colorCell(tetro.getColor());
				m_TetrisGrid[holdRowIndex][tetro.getCurrentCol()].fillCell();


			}
			tetro.increaseCol();
		}
		holdRowIndex++;
	}

	int m_whichRow;
	if (tetro.getCurrentRow() > m_Rows - 1)
	{
		
		RowMarkerIndex = m_Rows - 1;
	}
	std::for_each(m_TetrisGrid.begin(), m_TetrisGrid.end(), [&](auto & row)
	{
		if (rowCompleted(row))
			initiateSmashing(RowMarkerIndex);
	});
	return false;
}
// *****************************************************
//					Draw Board Function
// *****************************************************
void Board::drawStackPiece(Tetronimoes & stack_piece)
{
	stack_piece.setBlock(5, m_Cols + 3, 0, m_window);
}

void Board::drawFrame()
{
	for (size_t i = 0; i < m_Frame.size(); i++)
	{
		m_Frame.at(i).drawblock(m_window);
	}
}
void Board::initiateFrame()
{
	
	//Size of each rectangle is boardsize/rows, boardsize/cols
	float x = (BoardWidth / m_Cols);
	float y = (BoardHeight / m_Rows);
	for (size_t i = 0; i < m_Rows+2; i++)
	{
		for (size_t k = 0; k < m_Cols + 2; k++)
		{
			if (i != 0 || i!=m_Rows+1)
			{
				if (k == 0 || k == m_Cols + 1)
				{
					sf::RectangleShape rect{ sf::Vector2f{ x,y } };
					std::cout << x << "aasa " << y << std::endl;
					rect.setPosition((k * x), i  * y);
					rect.setOutlineColor(sf::Color::White);
					rect.setOutlineThickness(1.5f);
					rect.setTexture(&texture);
					Block block{ rect };
					m_Frame.push_back(block);
				}
			}
			if (i == 0 || i == m_Rows + 1)
			{
				sf::RectangleShape rect{ sf::Vector2f{ x,y } };
				std::cout << x << "aasa " << y << std::endl;
				rect.setPosition((k * x), i  * y);
				rect.setOutlineColor(sf::Color::White);
				rect.setTexture(&texture);
				rect.setOutlineThickness(1.5f);
				Block block{ rect };
				m_Frame.push_back(block);
			}
			

		}
	}
}

// *****************************************************
//					Smash Row Function
// *****************************************************
void Board::smashRow(int row)
{
	sf::Color m_color(sf::Color::Black);
	std::for_each(m_TetrisGrid[row].begin(), m_TetrisGrid[row].end(),
		[&m_color](auto & block) {block.emptyCell();block.colorCell(m_color); });

	m_score++;
	std::string Score;
	Score = std::to_string(m_score);
	score = "Your Score = ";
	score.append(Score);
	if (m_score % 5 == 0)
	{
		increaseTime(m_fallSpeed);
		m_currentLevel++;
		std::string num;
		num = std::to_string(m_currentLevel);
		level = "Level : ";
		level.append(num);
	}
		
}

// *****************************************************
//					Initiate Smashing of Rows
// *****************************************************
bool Board::initiateSmashing(int colRow)
{
	smashRow(colRow);

	//Update the grid.
	//Block temp;

	sf::Color testing(m_TetrisGrid[1][1].getColor());

	sf::Color temp(sf::Color::Black);
	sf::Color temp1(sf::Color::White);

	bool flag = false;
	


		for (int k = colRow ; k > 0; k--)
		{
			for (int i = 0; i < m_Cols; i++)
			{

				if (m_TetrisGrid[k - 1][i].isFilled())
				{
					flag = true;
					sf::Color testing(m_TetrisGrid[k - 1][i].getColor());
					m_TetrisGrid[k][i].fillCell();
					m_TetrisGrid[k][i].colorCell(testing);

					m_TetrisGrid[k - 1][i].emptyCell();
					m_TetrisGrid[k - 1][i].colorCell(temp);
				}


			}
			if (!flag)//empty row
				return false;
		}
		

	return false;
}


// *****************************************************
//			 Check if row completed(All cell full)
// *****************************************************
bool Board::rowCompleted(vector<Block> vec)
{
	bool check = true;
	std::for_each(vec.begin(), vec.end(), [&check](auto &block)
	{ if (!block.isFilled()) check = false; });
	return check;
}

// *****************************************************
//			       Game over !!!!
// *****************************************************
void Board::gameOver()
{
	sf::Text gameOver("Game Over!!!", font, 120);
	sf::Text myScore (score,font,120);
	gameOver.setFillColor(sf::Color::Red);
	gameOver.setPosition(sf::Vector2f(270, 200));
	myScore.setFillColor(sf::Color::Blue);
	myScore.setPosition(sf::Vector2f(70, 350));
	m_window.draw(gameOver);
	m_window.draw(myScore);
	m_window.display();
	sf::Time time(sf::seconds(5));
	sf::sleep(time);
	exit(1);
}
