#include "Application.h"
#include <sstream>

Application::Application() :
	TIME_PER_FRAME(sf::seconds(1.f / 60.f)),
	m_window(sf::VideoMode(800u, 600u), "Morpion"),
	m_textP1(),
	m_textP2(),
	m_font(),
	m_grid(sf::Vector2f(200.f, 200.f)),
	m_currentPlayer(0),
	m_selectedPlayer()
{
	m_window.setKeyRepeatEnabled(false);

	if (!m_font.loadFromFile("arial.ttf"))
		std::cerr << "erreur de chargement de la police" << std::endl;

	m_endGameText.setFont(m_font);
	m_endGameText.setColor(sf::Color::Black);
	m_endGameText.setPosition(sf::Vector2f(300.f, 50.f));

	m_restartText.setFont(m_font);
	m_restartText.setColor(sf::Color::Black);
	m_restartText.setPosition(sf::Vector2f(300.f, 500.f));

	m_textP1.setString("Joueur 1 : 0");
	m_textP1.setFont(m_font);
	m_textP1.setColor(sf::Color::Black);
	m_textP1.setPosition(sf::Vector2f(100.f, 100.f));

	m_textP2.setString("Joueur 2 : 0");
	m_textP2.setFont(m_font);
	m_textP2.setColor(sf::Color::Black);
	m_textP2.setPosition(sf::Vector2f(500.f, 100.f));

	sf::FloatRect bounds(m_textP1.getGlobalBounds());

	m_selectedPlayer.setOutlineThickness(3);
	m_selectedPlayer.setOutlineColor(sf::Color::Black);
	m_selectedPlayer.setFillColor(sf::Color::Transparent);
	m_selectedPlayer.setOrigin(sf::Vector2f(bounds.width / 2.f, bounds.width / 2.f));
	m_selectedPlayer.setPosition(sf::Vector2f(bounds.left - 10 + bounds.width / 2.f, bounds.top - 10 + bounds.width / 2.f));
	m_selectedPlayer.setSize(sf::Vector2f(bounds.width + 20, bounds.height + 20));

	m_players[0] = new Player(1);
	m_players[1] = new Player(2);
}

Application::~Application()
{
	delete m_players[0];
	delete m_players[1];
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate(sf::Time::Zero);

	while (m_window.isOpen())
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

	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				playTurn(event.mouseButton.x, event.mouseButton.y);
			}
		}
		else if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void Application::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_textP1);
	m_window.draw(m_textP2);
	m_window.draw(m_grid);
	m_window.draw(m_selectedPlayer);
	m_window.draw(m_endGameText);
	m_window.draw(m_restartText);
	m_window.display();
}

bool Application::playTurn(int xClic, int yClic)
{
	if (m_players[m_currentPlayer]->play(m_grid, xClic, yClic))
	{
		++m_turnNum;
		int winner = m_players[m_currentPlayer]->checkWin(m_grid, m_turnNum);
		if (winner != 0)
		{
			std::stringstream s;
			switch (winner)
			{
				case 1 :
				case 2 :
					m_players[winner - 1]->incrementScore();

					s << "Le joueur " << winner << " a gagné !";
					m_endGameText.setString(s.str());

					s.str("");
					s << "Joueur 1 : " << m_players[0]->getScore();
					m_textP1.setString(s.str());

					s.str("");
					s << "Joueur 2 : " << m_players[1]->getScore();
					m_textP1.setString(s.str());
					break;
				case 3:
					m_endGameText.setString("Egalité");
					break;
			}
			return restartGame();
		}

		m_currentPlayer = (m_currentPlayer + 1) % 2;
	}

	return true;
}

bool Application::restartGame()
{
	int continuer = true;
	sf::Event event;

	m_restartText.setString("Voulez - vous recommencer ? (o = Oui / n = Non)");

	while (continuer)
	{
		m_window.waitEvent(event);
		switch (event.type)
		{
			case sf::Event::KeyPressed :
				switch (event.key.code)
				{
					case sf::Keyboard::Escape :
					case sf::Keyboard::N :
						continuer = false;
						break;
					case sf::Keyboard::O :

						/* Réinitialisation du score et de la grille */
						m_turnNum = 0;
						m_grid.emptyGrid();

						m_endGameText.setString("");
						m_restartText.setString("");

						return true;
				}
				break;
			case sf::Event::Closed :
				continuer = false;
				m_window.close();
				break;
		}
	}

	return false;
}
