#include "Block.h"
#include <iostream>


void Block::setPosition(float x, float y)
{
	m_cell.setPosition(x, y);
}

void Block::setSize(sf::Vector2f &coords)
{
	m_cell.setSize(coords);
}

Block::Block() 
{

	float x = BoardWidth / m_Cols;
	float y = BoardHeight / m_Rows;
	m_cell.setSize(sf::Vector2f{ x,y } );
	
	m_cell.setOutlineColor(sf::Color::Red);
	m_cell.setOutlineThickness(1.5f);	
	std::cout << x << " " << y << std::endl;
	
}


void Block::drawblock(sf::RenderWindow & window)
{
	window.draw(m_cell);
}
