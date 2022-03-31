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

	const int c_MAX_NPCs = 50;
	std::vector<NPC*> m_NPCs;

	const int c_PLAYER_X = 2, c_PLAYER_Y = 2;

	bool drawGraph = true;

	float viewMoveSpeed = 200.0f;
	float viewZoom = 1.0f;
	sf::View gameView;

public:
	void run();
	void processInput();
	void update(sf::Time& dt);
	void render();

	void beginPath();

	CellGenerator cg;
};

#endif