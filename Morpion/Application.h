#pragma once

#include "Defs.h"

class Application
{
	public:
		Application();
		~Application();

		void run();

	private :
		sf::RenderWindow m_window;
		void processEvents();
		void render();
};

