#include "Grid.h"

Grid::Grid(sf::Vector2f &position) :
	m_vertices(sf::Lines, 16)
{
	setPosition(position);

	m_vertices[0] = sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Color::Black);
	m_vertices[1] = sf::Vertex(sf::Vector2f(300.f, 0.f), sf::Color::Black);

	m_vertices[2] = sf::Vertex(sf::Vector2f(0.f, 100.f), sf::Color::Black);
	m_vertices[3] = sf::Vertex(sf::Vector2f(300.f, 100.f), sf::Color::Black);

	m_vertices[4] = sf::Vertex(sf::Vector2f(0.f, 200.f), sf::Color::Black);
	m_vertices[5] = sf::Vertex(sf::Vector2f(300.f, 200.f), sf::Color::Black);

	m_vertices[6] = sf::Vertex(sf::Vector2f(0.f, 300.f), sf::Color::Black);
	m_vertices[7] = sf::Vertex(sf::Vector2f(300.f, 300.f), sf::Color::Black);

	m_vertices[8] = sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Color::Black);
	m_vertices[9] = sf::Vertex(sf::Vector2f(0.f, 300.f), sf::Color::Black);

	m_vertices[10] = sf::Vertex(sf::Vector2f(100.f, 0.f), sf::Color::Black);
	m_vertices[11] = sf::Vertex(sf::Vector2f(100.f, 300.f), sf::Color::Black);

	m_vertices[12] = sf::Vertex(sf::Vector2f(200.f, 0.f), sf::Color::Black);
	m_vertices[13] = sf::Vertex(sf::Vector2f(200.f, 300.f), sf::Color::Black);

	m_vertices[14] = sf::Vertex(sf::Vector2f(300.f, 0.f), sf::Color::Black);
	m_vertices[15] = sf::Vertex(sf::Vector2f(300.f, 300.f), sf::Color::Black);
}

Grid::~Grid()
{

}

void Grid::play(Player player, int x, int y)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (getPosition().x + 100 * i <= x && x <= getPosition().x + 100 * (i + 1) &&
				getPosition().y + 100 * j <= y && y <= getPosition().y + 100 * (j + 1))
			{
				m_gridArray[i][j] = player;
			}
		}
	}
}

void Grid::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(m_vertices, states);
}
