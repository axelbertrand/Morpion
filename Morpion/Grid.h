#pragma once

#include "Defs.h"

class Grid : public sf::Drawable, public sf::Transformable
{
	public :
		Grid();
		~Grid();

	private :
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::RectangleShape m_rect;
};

