#include "Application.h"

Application::Application() :
m_window(sf::VideoMode(800, 600), "Morpion")
{

}

Application::~Application()
{

}

void Application::run()
{
	while (m_window.isOpen())
	{
		processEvents();
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
	m_window.clear();
	m_window.display();
}
