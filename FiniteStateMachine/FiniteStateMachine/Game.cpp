#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::Run()
{
	int windowWidth = 900, windowHeight = 900;
	sf::Vector2i mouseScreenPosition;

	// Window creation
	sf::String programName = "EvolutionAI";
	m_Window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), programName, sf::Style::Default);
	m_Window->setFramerateLimit(60);
	m_Window->setVerticalSyncEnabled(true);

	sf::Clock deltaClock;

	float dt;

	bool running = true, focus = true;

	while (running)
	{
		dt = deltaClock.restart().asSeconds();

		sf::Event event;
		while (m_Window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				running = false;
			if (event.type == sf::Event::GainedFocus)
				focus = true;
			if (event.type == sf::Event::LostFocus)
				focus = false;
			if (event.type == sf::Event::Resized)
			{
				int newWidth = event.size.width, newHeight = event.size.height;
			}
		}

		if (focus)
		{
			mouseScreenPosition = sf::Mouse::getPosition(*m_Window);

			// --------------------Update--------------------

			Update(dt, mouseScreenPosition);

			// --------------------Render--------------------
			m_Window->clear(sf::Color(255, 255, 255, 255));
			Render();

			// End frame
			m_Window->display();
		}
		else
		{
			sf::Time time = sf::milliseconds(100);
			sf::sleep(time);
		}
	}
}

void Game::Update(float dt, sf::Vector2i mousePosition)
{

}

void Game::Render()
{

}