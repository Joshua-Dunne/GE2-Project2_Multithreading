#ifndef NPC_H
#define NPC_H

#include "ThreadingSingleton.h"
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

		m_worldLoc = sf::Vector2f{ static_cast<float>(m_data.m_x), static_cast<float>(m_data.m_y) };

		space.setSize(sf::Vector2f{ 25.0f, 25.0f });
		space.setFillColor(pickedPathColor);
	}

	sf::RectangleShape space;

	void beginPathing(int t_dest);
	NodeData m_data;
	int m_currentCell = 0;

	void drawPath(sf::RenderWindow& t_window);

	float m_speed = 60.0f;
	sf::Vector2f m_worldLoc = sf::Vector2f{ 0,0 };

	bool atPlayer = false;
	void usePath(sf::Time& dt);

private:
	Graph<NodeData, int>& m_graph;

	std::vector<GraphNode<NodeData, int>> fullPath;
	std::vector<GraphNode<NodeData, int>*> path;

	void generatePath();
	bool generatingPath = false;

	sf::Color pickedPathColor;
	
	int m_pos = -1;
	int m_dest = -1;

	sf::Vector2f normalize(const sf::Vector2f& source)
	{
		float length = sqrt((source.x * source.x) + (source.y * source.y));
		if (length != 0)
			return sf::Vector2f(source.x / length, source.y / length);
		else
			return source;
	}
};

#endif