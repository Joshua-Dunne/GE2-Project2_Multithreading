#include "Game.h"

Game::Game() :	m_window(sf::VideoMode(1920u, 1080u), "A*mbush Thread Pooling")
{
	//m_window.setFramerateLimit(60u);
	cg.populateData();
}

Game::~Game()
{
}

/// <summary>
/// Run the main Game loop
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	while (m_window.isOpen())
	{
		processInput();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame);
		}
		render();
	}
}

/// <summary>
/// Processes inputs from Events
/// </summary>
void Game::processInput()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void Game::update(sf::Time& dt)
{
	// Update elements
	
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Draw elements

	auto data = cg.m_data;

	int alternate = 0;

	for (int y = 0; y < cg.c_MAX_Y; y++)
	{
		for (int x = 0; x < cg.c_MAX_X; x++)
		{
			NodeData current;

			current = data[y][x];

			sf::RectangleShape space;
			space.setSize(sf::Vector2f{ 25.0f, 25.0f });
			space.setPosition(current.m_x, current.m_y);

			switch (alternate)
			{
			case 0:
				alternate++;
				space.setFillColor(sf::Color::White);
				break;
			case 1:
				alternate--;
				space.setFillColor(sf::Color::Green);
				break;
			}

			m_window.draw(space);
		}
	}

	m_window.display();
}
