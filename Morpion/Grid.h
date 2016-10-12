#pragma once

#include "Defs.h"

enum Player;

class Grid : public sf::Drawable, public sf::Transformable
{
	public :
		Grid(sf::Vector2f &position = sf::Vector2f(0.f, 0.f));
		~Grid();

		void play(Player player, int x, int y);

	private :
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::VertexArray m_vertices;
		Player m_gridArray[3][3];
};

