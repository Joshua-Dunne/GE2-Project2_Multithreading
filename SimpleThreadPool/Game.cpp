#include "Game.h"

Game::Game() :	m_window(sf::VideoMode(1920u, 1080u), "A*mbush Thread Pooling")
{
	gameView = m_window.getDefaultView();
	//m_window.setFramerateLimit(60u);
	cg.populateData();

	s->pool().initializeThreads();

	std::vector<std::pair<int, int>> choices;

	for (int i = 0; i < c_MAX_NPCs; i++)
	{
		int randX = (rand() % cg.c_MAX_X);
		int randY = (rand() % cg.c_MAX_Y);
		bool reset = false;

		for (auto choice : choices)
		{
			if (randX == choice.first && randY == choice.second)
			{
				i--; // if this spot is already picked,
					 // reset the current working NPC and reroll
				reset = true;
				continue;
			}	
		}

		if (randX == c_PLAYER_X && randY == c_PLAYER_Y) // reroll position if this spot is where the player is
			reset = true;

		if (reset) continue;

		m_NPCs.push_back(new NPC(cg.getGraph(), cg.m_data[randY][randX].m_name));
		choices.push_back(std::pair<int, int>(randX, randY));
	}

	if (!m_gridTexture.create(2500, 2500))
	{
		std::cerr << "Failed to create grid texture in Game.cpp!" << std::endl;
		throw(std::exception("Failed to create grid texture in Game.cpp!"));
	}

	space.setSize(sf::Vector2f{ 25.0f, 25.0f });
	space.setFillColor(sf::Color::Black);
	space.setOutlineColor(sf::Color::White);
	space.setOutlineThickness(2.0f);

	for (int y = 0; y < cg.c_MAX_Y; y++)
	{
		for (int x = 0; x < cg.c_MAX_X; x++)
		{
			NodeData current;

			current = cg.m_data[y][x];

			space.setPosition(static_cast<float>(current.m_x), static_cast<float>(current.m_y));

			m_gridTexture.draw(space);
		}
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

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				//s->pool().initializeThreads();
				beginPath();
			}

			if (event.key.code == sf::Keyboard::Enter)
			{
				drawGraph = !drawGraph;
			}
		}

		if (event.type == sf::Event::MouseWheelMoved)
		{
			gameView.zoom(1.0f - event.mouseWheel.delta / 50.0f);
		}
	}
}

void Game::update(sf::Time& dt)
{
	// Update elements
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		gameView.move(0, -viewMoveSpeed * dt.asSeconds());
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		gameView.move(-viewMoveSpeed * dt.asSeconds(), 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		gameView.move(0, viewMoveSpeed * dt.asSeconds());
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		gameView.move(viewMoveSpeed * dt.asSeconds(), 0);
	}
	m_window.setView(gameView);
	
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Draw elements

	auto data = cg.m_data;

	sf::RectangleShape space;
	space.setSize(sf::Vector2f{ 25.0f, 25.0f });
	space.setFillColor(sf::Color::Black);
	space.setOutlineColor(sf::Color::White);
	space.setOutlineThickness(2.0f);

	// Draw Graph
	if(drawGraph)
	{
		m_gridTexture.display();
		m_window.draw(sf::Sprite(m_gridTexture.getTexture()));
	}

	// draw any paths
	for (auto ai : m_NPCs)
	{
		ai->drawPath(m_window);
	}

	// with graph drawn, now draw NPCs
	for (auto ai : m_NPCs)
	{
		NodeData current = ai->m_data;

		space.setPosition(static_cast<float>(current.m_x), static_cast<float>(current.m_y));
		space.setFillColor(sf::Color::Red);

		m_window.draw(space);
	}

	// finally, draw the Player
	space.setPosition(static_cast<float>(cg.m_data[c_PLAYER_X][c_PLAYER_Y].m_x), static_cast<float>(cg.m_data[c_PLAYER_X][c_PLAYER_Y].m_y));
	space.setFillColor(sf::Color::Magenta);
	m_window.draw(space);
	

	m_window.display();
}

void Game::beginPath()
{
	int playerCell = cg.m_data[c_PLAYER_Y][c_PLAYER_X].m_name;

	std::cout << playerCell << std::endl;

	for (auto AI : m_NPCs)
	{
		AI->beginPathing(playerCell);
	}
}
