#ifndef NPC_H
#define NPC_H

#include <ThreadingSingleton.h>
#include <SFML/Graphics.hpp>
#include "CellGenerator.h"

class NPC
{
	ThreadingSingleton* s = s->getInstance();

public:
	NPC() = delete;
	NPC(Graph<NodeData, int>& t_graph, int t_position) : m_graph(t_graph), m_pos(t_position) 
	{
		m_data = m_graph.nodeIndex(m_pos)->m_data;
		int initialColor = 25;

		int randR = (rand() % 256) + initialColor, randG = (rand() % 256) + initialColor, randB = (rand() % 256) + initialColor;

		if (randR > 255) randR = 255;
		if (randG > 255) randG = 255;
		if (randB > 255) randB = 255;

		pickedPathColor = sf::Color(randR, randG, randB);
	}

	void beginPathing(int t_dest);
	NodeData m_data;

	void drawPath(sf::RenderWindow& t_window);

private:
	Graph<NodeData, int>& m_graph;
	std::vector<GraphNode<NodeData, int>> path;

	void generatePath();

	bool generatingPath = false;

	sf::Color pickedPathColor;
	
	int m_pos = -1;
	int m_dest = -1;
};

#endif