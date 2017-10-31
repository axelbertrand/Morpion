#pragma once

#include "Defs.h"

class Grid : public sf::Drawable, public sf::Transformable
{
	public :
		Grid(sf::Vector2f &position = sf::Vector2f(0.f, 0.f));
		~Grid();

		int getClickedCell(int x, int y) const;
		void drawCross(int i, int j);
		void drawCircle(int i, int j);
		void setGrid(int i, int j, int player);
		int getGrid(int i, int j) const;

	private :
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::VertexArray m_vertices;
		int m_gridArray[3][3];
		sf::Drawable* m_gridShapes[3][3];
};

