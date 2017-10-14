#include "Grid.h"

Grid::Grid(sf::Vector2f &position) :
	m_vertices(sf::Lines, 16)
{
	setPosition(position);

	for (int i = 0; i < 9; ++i)
	{
		m_gridShapes[i / 3][i % 3] = nullptr;
	}

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
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (m_gridShapes[i][j] != nullptr)
			{
				delete m_gridShapes[i][j];
				m_gridShapes[i][j] = nullptr;
			}
		}
	}
}

void Grid::play(Player player, int x, int y)
{
	int clickedCell = getClickedCell(x, y);
	if (clickedCell < 0)
	{
		return;
	}

	int i = clickedCell / 3;
	int j = clickedCell % 3;

	m_gridArray[i][j] = player;

	if (player == 1)
	{
		drawCross(i, j);
	}
	else if (player == 2)
	{
		drawCircle(i, j);
	}
}

void Grid::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(m_vertices, states);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (m_gridShapes[i][j] != nullptr)
			{
				target.draw(*m_gridShapes[i][j], states);
			}
		}
	}
}

int Grid::getClickedCell(int x, int y) const
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (getPosition().x + 100 * j <= x && x <= getPosition().x + 100 * (j + 1) &&
				getPosition().y + 100 * i <= y && y <= getPosition().y + 100 * (i + 1))
			{
				return i + j;
			}
		}
	}

	return -1;
}

void Grid::drawCross(int i, int j)
{
	sf::VertexArray *cross = new sf::VertexArray(sf::Lines, 4);

	(*cross)[0] = sf::Vertex(sf::Vector2f(j*100 + 10.f, i*100 + 10.f), sf::Color::Black);
	(*cross)[1] = sf::Vertex(sf::Vector2f(j*100 + 80.f, i*100 + 80.f), sf::Color::Black);

	(*cross)[2] = sf::Vertex(sf::Vector2f(j*100 + 10.f, i*100 + 80.f), sf::Color::Black);
	(*cross)[3] = sf::Vertex(sf::Vector2f(j*100 + 80.f, i*100 + 10.f), sf::Color::Black);

	m_gridShapes[i][j] = cross;
}

void Grid::drawCircle(int i, int j)
{
	sf::CircleShape *circle = new sf::CircleShape(40.f);

	circle->setPosition(j * 100 + 50.f, i * 100 + 50.f);
	circle->setFillColor(sf::Color::White);
	circle->setOutlineThickness(1.f);
	circle->setOutlineColor(sf::Color::Black);

	m_gridShapes[i][j] = circle;
}
