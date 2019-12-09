#pragma once
#include "SFML\Graphics.hpp"

 class Block
{
public:
	
	Block(sf::RectangleShape &block) : m_cell(block) {}
	Block();
	void setOutline(sf::Color &color) { m_cell.setOutlineColor(color); }
	void drawblock(sf::RenderWindow &window);
	bool isFilled() { return m_blockContains; }
	void colorCell(sf::Color &color) { m_cell.setFillColor(color); m_BlockColor = color; }
	void fillCell() { m_blockContains = true; }
	void emptyCell() { m_blockContains = false; }
	void whitenCell() { if(!m_blockContains)m_cell.setFillColor(sf::Color::White); }
	

	// get color
	const sf::Color &getColor() { return m_BlockColor; }
	void setPosition(float x, float y);
	void setSize(sf::Vector2f &coords);
	
private:

	int BoardWidth = 600;
	int BoardHeight = 800;
	int WindowWidth = 1200;
	int WindowHeight = 880;
	int m_Cols = 10;
	int m_Rows = 20;
	int offset = 100;
	bool m_blockContains = false;
	sf::RectangleShape m_cell;
	sf::Color m_BlockColor;

};

