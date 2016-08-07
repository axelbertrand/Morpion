#pragma once

#include "Defs.h"
#include "Grid.h"

enum Player
{
	NoPlayer,
	Player1,
	Player2,
	PlayerCount
};

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
		sf::Text m_textP1;
		sf::Text m_textP2;
		sf::Font m_font;
		Grid m_grid;
		Player m_currentPlayer;
		sf::RectangleShape m_selectedPlayer;
};

