#include "Grid.h"

Grid::Grid() :
m_rect(sf::Vector2f(300, 300))
{
	m_rect.setPosition(150, 100);
	m_rect.setOutlineThickness(1);
	m_rect.setOutlineColor(sf::Color::Black);
}

Grid::~Grid()
{

}

void Grid::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= m_rect.getTransform();

	target.draw(m_rect, states);
}
