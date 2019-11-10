#include "Application.h"
#include <sstream>

Application::Application() :
	TIME_PER_FRAME(sf::seconds(1.f / 60.f)),
	mWindow(sf::VideoMode(800u, 600u), "Morpion"),
	mTextP1(),
	mTextP2(),
	mEndGameText(),
	mRestartText(),
	mFont(),
	mGrid(sf::Vector2f(200.f, 200.f)),
	mCurrentPlayer(0),
	mStarterPlayer(0),
	mSelectedPlayer(),
	mTurnNum(0),
	mIsFinished(false)
{
	mWindow.setKeyRepeatEnabled(false);

	if (!mFont.loadFromFile("arial.ttf"))
		std::cerr << "erreur de chargement de la police" << std::endl;

	mEndGameText.setFont(mFont);
	mEndGameText.setFillColor(sf::Color::Black);
	mEndGameText.setPosition(sf::Vector2f(300.f, 50.f));

	mRestartText.setFont(mFont);
	mRestartText.setFillColor(sf::Color::Black);
	mRestartText.setPosition(sf::Vector2f(70.f, 520.f));

	mTextP1.setString("Joueur 1 : 0");
	mTextP1.setFont(mFont);
	mTextP1.setFillColor(sf::Color::Black);
	mTextP1.setPosition(sf::Vector2f(100.f, 100.f));

	mTextP2.setString("Joueur 2 : 0");
	mTextP2.setFont(mFont);
	mTextP2.setFillColor(sf::Color::Black);
	mTextP2.setPosition(sf::Vector2f(500.f, 100.f));

	sf::FloatRect bounds(mTextP1.getGlobalBounds());

	mSelectedPlayer.setOutlineThickness(3);
	mSelectedPlayer.setOutlineColor(sf::Color::Black);
	mSelectedPlayer.setFillColor(sf::Color::Transparent);
	mSelectedPlayer.setOrigin(sf::Vector2f(bounds.width / 2.f, bounds.width / 2.f));
	mSelectedPlayer.setPosition(sf::Vector2f(bounds.left - 10 + bounds.width / 2.f, bounds.top - 10 + bounds.width / 2.f));
	mSelectedPlayer.setSize(sf::Vector2f(bounds.width + 20, bounds.height + 20));

	mPlayers[0] = new Player(1);
	mPlayers[1] = new Player(2);
}

Application::~Application()
{
	delete mPlayers[0];
	delete mPlayers[1];
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate(sf::Time::Zero);

	while (mWindow.isOpen())
	{
		sf::Time elapsedTime(clock.restart());
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents();
		}
		
		render();
	}
}

void Application::processEvents()
{
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::MouseButtonPressed :
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (playTurn(event.mouseButton.x, event.mouseButton.y))
					{
						mIsFinished = true;
						mRestartText.setString("Voulez-vous recommencer ? (o = Oui / n = Non)");
					}
				}
				break;
			case sf::Event::KeyPressed :
				if (mIsFinished)
				{
					if(!restartGame(event))
						mWindow.close();
				}
				break;
			case sf::Event::Closed :
				mWindow.close();
				break;
		}
	}
}

void Application::render()
{
	mWindow.clear(sf::Color::White);
	mWindow.draw(mTextP1);
	mWindow.draw(mTextP2);
	mWindow.draw(mGrid);
	mWindow.draw(mSelectedPlayer);
	mWindow.draw(mEndGameText);
	mWindow.draw(mRestartText);
	mWindow.display();
}

bool Application::playTurn(int xClic, int yClic)
{
	if (mPlayers[mCurrentPlayer]->play(mGrid, xClic, yClic))
	{
		++mTurnNum;
		int winner = mPlayers[mCurrentPlayer]->checkWin(mGrid, mTurnNum);
		if (winner != 0)
		{
			std::stringstream s;
			switch (winner)
			{
				case 1 :
				case 2 :
					mPlayers[winner - 1]->incrementScore();

					s << "Le joueur " << winner << " a gagné !";
					mEndGameText.setString(s.str());

					s.str("");
					s << "Joueur 1 : " << mPlayers[0]->getScore();
					mTextP1.setString(s.str());

					s.str("");
					s << "Joueur 2 : " << mPlayers[1]->getScore();
					mTextP2.setString(s.str());
					break;
				case 3 :
					mEndGameText.setString("Egalité");
					break;
			}
			return true;
		}

		mCurrentPlayer = (mCurrentPlayer + 1) % 2;
		mSelectedPlayer.move(mCurrentPlayer ? sf::Vector2f(400.f, 0.f) : sf::Vector2f(-400.f, 0.f));
	}

	return false;
}

bool Application::restartGame(const sf::Event & event)
{
	switch (event.key.code)
	{
		case sf::Keyboard::Escape :
		case sf::Keyboard::N :
			return false;
		case sf::Keyboard::O :

			/* Réinitialisation du score et de la grille */
			mTurnNum = 0;
			mGrid.emptyGrid();
			mIsFinished = false;
			mStarterPlayer = (mStarterPlayer + 1) % 2;
			if (mCurrentPlayer != mStarterPlayer)
			{
				mCurrentPlayer = mStarterPlayer;
				mSelectedPlayer.move(mCurrentPlayer ? sf::Vector2f(400.f, 0.f) : sf::Vector2f(-400.f, 0.f));
			}

			mEndGameText.setString("");
			mRestartText.setString("");

			return true;
		default:
			return false;
	}
}
