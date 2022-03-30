#include "Game.h"

Game::Game() :	m_window(sf::VideoMode(1920u, 1080u), "A*mbush Thread Pooling")
{
	//m_window.setFramerateLimit(60u);
	cg.populateData();

	for (int i = 0; i < c_MAX_NPCs; i++)
	{
		int randX = (rand() % cg.c_MAX_X);
		int randY = (rand() % cg.c_MAX_Y);
		m_NPCs.push_back(new NPC(cg.getGraph(), cg.m_data[randY][randX].m_name));
	}
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

	// Draw Graph
	for (int y = 0; y < cg.c_MAX_Y; y++)
	{
		for (int x = 0; x < cg.c_MAX_X; x++)
		{
			NodeData current;

			current = data[y][x];

			sf::RectangleShape space;
			space.setSize(sf::Vector2f{ 25.0f, 25.0f });
			space.setPosition(static_cast<float>(current.m_x), static_cast<float>(current.m_y));

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

		// for each row, flip the color
		(alternate == 0) ? alternate = 1 : alternate = 0;
	}

	// with graph drawn, now draw NPCs
	for (auto ai : m_NPCs)
	{
		NodeData current = ai->m_data;

		sf::RectangleShape space;
		space.setSize(sf::Vector2f{ 25.0f, 25.0f });
		space.setPosition(static_cast<float>(current.m_x), static_cast<float>(current.m_y));
		space.setFillColor(sf::Color::Red);

		m_window.draw(space);
	}

	m_window.display();
}
