#include "Game.h"

Game::Game() :	m_window(sf::VideoMode(1920u, 1080u), "A*mbush Thread Pooling")
{
	m_gameView = m_window.getDefaultView();
	//m_window.setFramerateLimit(60u);
	cg.populateData();

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

	if (cg.c_MAX_X != 1000)
	{ // because of the limits of textures, we will not create a render texture for giant graphs
		if (!m_gridTexture.create(cg.c_MAX_X * 25u, cg.c_MAX_Y * 25u))
		{
			std::cerr << "Failed to create grid texture in Game.cpp!" << std::endl;
			throw(std::exception("Failed to create grid texture in Game.cpp!"));
		}
	}
	else
	{
		m_drawGraph = false;
		m_graphExists = false;
	}
	

	m_space.setSize(sf::Vector2f{ 25.0f, 25.0f });
	m_space.setFillColor(sf::Color::Black);
	m_space.setOutlineColor(sf::Color::White);
	m_space.setOutlineThickness(2.0f);

	auto& data = cg.m_data;
	NodeData& current = data[0][0];
	

	for (int y = 0; y < cg.c_MAX_Y; y++)
	{
		for (int x = 0; x < cg.c_MAX_X; x++)
		{
			current = data[y][x];

			m_space.setPosition(static_cast<float>(current.m_x), static_cast<float>(current.m_y));

			m_gridTexture.draw(m_space);
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
				s->pool().initializeThreads();
				beginPath();
			}

			if (event.key.code == sf::Keyboard::Enter)
			{
				m_drawGraph = !m_drawGraph;
			}

			if (event.key.code == sf::Keyboard::BackSpace)
			{
				m_showIndividualPaths = !m_showIndividualPaths;
			}

			if (m_showIndividualPaths)
			{
				if (event.key.code == sf::Keyboard::Add)
				{
					m_currentShownPath++;

					if (m_currentShownPath > static_cast<int>(m_NPCs.size()) - 1) m_currentShownPath = 0;
				}

				if (event.key.code == sf::Keyboard::Subtract)
				{
					m_currentShownPath--;

					if (m_currentShownPath < 0) m_currentShownPath = m_NPCs.size() - 1;
				}
			}
			
		}

		if (event.type == sf::Event::MouseWheelMoved)
		{
			m_gameView.zoom(1.0f - event.mouseWheel.delta / 50.0f);
		}
	}
}

void Game::update(sf::Time& dt)
{
	// Update elements
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_gameView.move(0, -m_viewMoveSpeed * dt.asSeconds());
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_gameView.move(-m_viewMoveSpeed * dt.asSeconds(), 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_gameView.move(0, m_viewMoveSpeed * dt.asSeconds());
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_gameView.move(m_viewMoveSpeed * dt.asSeconds(), 0);
	}

	m_window.setView(m_gameView);

	s->pool().clearThreads();
	
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Draw elements

	auto data = cg.m_data;

	// Draw Graph
	if(m_drawGraph)
	{
		m_gridTexture.display();
		m_window.draw(sf::Sprite(m_gridTexture.getTexture()));
	}

	// draw any paths
	if (!m_showIndividualPaths)
	{
		for (auto ai : m_NPCs)
		{
			ai->drawPath(m_window);
		}
	}
	else
	{
		m_NPCs[m_currentShownPath]->drawPath(m_window);
	}
	

	// with graph drawn, now draw NPCs
	for (auto ai : m_NPCs)
	{
		NodeData current = ai->m_data;

		m_space.setPosition(static_cast<float>(current.m_x), static_cast<float>(current.m_y));
		m_space.setFillColor(sf::Color::Red);

		m_window.draw(m_space);
	}

	// finally, draw the Player
	m_space.setPosition(static_cast<float>(cg.m_data[c_PLAYER_X][c_PLAYER_Y].m_x), static_cast<float>(cg.m_data[c_PLAYER_X][c_PLAYER_Y].m_y));
	m_space.setFillColor(sf::Color::Magenta);
	m_window.draw(m_space);
	

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
