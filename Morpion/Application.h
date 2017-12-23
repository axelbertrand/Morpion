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

		sf::RenderWindow mWindow;
		sf::Text mTextP1;
		sf::Text mTextP2;
		sf::Text mEndGameText;
		sf::Text mRestartText;
		sf::Font mFont;
		Grid mGrid;
		int mCurrentPlayer;
		int mStarterPlayer;
		Player* mPlayers[2];
		sf::RectangleShape mSelectedPlayer;
		int mTurnNum;
		bool mIsFinished;
};

