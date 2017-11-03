#pragma once

#include "Defs.h"
#include "Grid.h"
#include "Player.h"

class Application
{
	public :
		Application();
		~Application();

		void run();

	private :
		void processEvents();
		void render();
		bool playTurn(int xClic, int yClic);
		bool restartGame(const sf::Event & event);

		const sf::Time Application::TIME_PER_FRAME;

		sf::RenderWindow m_window;
		sf::Text m_textP1;
		sf::Text m_textP2;
		sf::Text m_endGameText;
		sf::Text m_restartText;
		sf::Font m_font;
		Grid m_grid;
		int m_currentPlayer;
		Player* m_players[2];
		sf::RectangleShape m_selectedPlayer;
		int m_turnNum = 0;
};

