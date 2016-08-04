#include "Application.h"

Application::Application() :
TIME_PER_FRAME(sf::seconds(1.f / 60.f)),
m_window(sf::VideoMode(800, 600, 32), "Morpion"),
m_textJ1(),
m_textJ2(),
m_font(),
m_grid()
{
	m_window.setKeyRepeatEnabled(false);

	if (!m_font.loadFromFile("arial.ttf"))
		std::cerr << "erreur de chargement de la police" << std::endl;

	m_textJ1.setString("Joueur 1 : 0");
	m_textJ1.setFont(m_font);
	m_textJ1.setColor(sf::Color::Black);
	m_textJ1.setPosition(sf::Vector2f(100.f, 100.f));

	m_textJ2.setString("Joueur 2 : 0");
	m_textJ2.setFont(m_font);
	m_textJ2.setColor(sf::Color::Black);
	m_textJ2.setPosition(sf::Vector2f(500.f, 100.f));
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
	m_window.draw(m_textJ1);
	m_window.draw(m_textJ2);
	m_window.draw(m_grid);
	m_window.display();
}
