#pragma once

#include "Defs.h"
#include "Grid.h"

class Application
{
	public :
		Application();
		~Application();

		void run();

	private :
		void processEvents();
		void render();

		const sf::Time Application::TIME_PER_FRAME;

		sf::RenderWindow m_window;
		sf::Text m_textJ1;
		sf::Text m_textJ2;
		sf::Font m_font;
		Grid m_grid;
};

