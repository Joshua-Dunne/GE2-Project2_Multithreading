#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "CellGenerator.h"
#include "NPC.h"

class Game
{
public:
	Game();
	~Game();
private:
	sf::RenderWindow m_window;
	sf::Clock m_updateClock;

	const int c_MAX_NPCs = 5;
	std::vector<NPC*> m_NPCs;

public:
	void run();
	void processInput();
	void update(sf::Time& dt);
	void render();

	CellGenerator cg;
};

#endif