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
		void emptyGrid();

	private :
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::VertexArray mVertices;
		int mGridArray[3][3];
		sf::Drawable* mGridShapes[3][3];
};

