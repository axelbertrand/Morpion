#include "Application.h"

Application::Application() :
	TIME_PER_FRAME(sf::seconds(1.f / 60.f)),
	m_window(sf::VideoMode(800u, 600u), "Morpion"),
	m_textP1(),
	m_textP2(),
	m_font(),
	m_grid(sf::Vector2f(200.f, 200.f)),
	m_currentPlayer(Player::Player1),
	m_selectedPlayer()
{
	m_window.setKeyRepeatEnabled(false);

	if (!m_font.loadFromFile("arial.ttf"))
		std::cerr << "erreur de chargement de la police" << std::endl;

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
	m_selectedPlayer.setPosition(sf::Vector2f(bounds.left + bounds.width / 2.f, bounds.top + bounds.width / 2.f));
	m_selectedPlayer.setSize(sf::Vector2f(bounds.width, bounds.height));
}

Application::~Application()
{

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
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}

void Application::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_textP1);
	m_window.draw(m_textP2);
	m_window.draw(m_grid);
	m_window.draw(m_selectedPlayer);
	m_window.display();
}
