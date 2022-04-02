#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ThreadingSingleton.h"
#include "CellGenerator.h"
#include "NPC.h"

class Game
{
	ThreadingSingleton* s = s->getInstance();
public:
	Game();
	~Game();
private:
	sf::RenderWindow m_window;
	sf::Clock m_updateClock;

	const int c_MAX_NPCs = 500;
	std::vector<NPC*> m_NPCs;

	const int c_PLAYER_X = 2, c_PLAYER_Y = 2;

	bool m_graphExists = true;
	bool m_drawGraph = true;

	int m_currentShownPath = 0;
	bool m_showIndividualPaths = false;

	float m_viewMoveSpeed = 800.0f;
	float m_viewZoom = 1.0f;
	sf::View m_gameView;

	sf::RectangleShape m_space;
	sf::RenderTexture m_gridTexture;

public:
	void run();
	void processInput();
	void update(sf::Time& dt);
	void render();

	void beginPath();

	CellGenerator cg;
};

#endif