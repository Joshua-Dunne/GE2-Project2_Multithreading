#include "NPC.h"

std::mutex Graph<NodeData, int>::mtx;

void NPC::beginPathing(int t_dest)
{
	m_dest = t_dest;

	path.clear();

	//m_graph.aStar(m_graph.nodeIndex(m_pos), m_graph.nodeIndex(m_dest), path);

	s->pool().addTask([this]() {this->generatePath(); });
}

void NPC::drawPath(sf::RenderWindow& t_window)
{
	if (!generatingPath)
	{
		sf::RectangleShape space;
		space.setSize(sf::Vector2f{ 25.0f, 25.0f });
		space.setFillColor(pickedPathColor);

		for (size_t i = 0; i < path.size(); i++)
		{
			NodeData current;

			current = path[i].m_data;

			space.setPosition(static_cast<float>(current.m_x), static_cast<float>(current.m_y));

			t_window.draw(space);
		}
	}
}

void NPC::generatePath()
{
	generatingPath = true;
	m_graph.aStarAmbush(m_graph.nodeIndex(m_pos), m_graph.nodeIndex(m_dest), path);
	generatingPath = false;
}
