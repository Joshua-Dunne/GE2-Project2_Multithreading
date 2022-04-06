#include "NPC.h"

std::mutex Graph<NodeData, int>::mtx;

void NPC::beginPathing(int t_dest)
{
	m_dest = t_dest;

	path.clear();

	generatingPath = true;

	s->pool().addTask([this]() {this->generatePath(); });
}

void NPC::drawPath(sf::RenderWindow& t_window)
{
	if (!generatingPath)
	{
		space.setSize(sf::Vector2f{ 25.0f, 25.0f });
		space.setFillColor(pickedPathColor);

		for (size_t i = 0; i < fullPath.size(); i++)
		{
			space.setPosition(static_cast<float>(fullPath[i].m_data.m_x), static_cast<float>(fullPath[i].m_data.m_y));

			t_window.draw(space);
		}
	}
}

void NPC::usePath(sf::Time& dt)
{
	if (fullPath.size() > 0 && m_currentCell < static_cast<int>(fullPath.size()) - 1)
	{
		sf::Vector2f destination = sf::Vector2f{ static_cast<float>(fullPath[m_currentCell].m_data.m_x), static_cast<float>(fullPath[m_currentCell].m_data.m_y) };
		float xClac = m_worldLoc.x - destination.x;
		float yCalc = m_worldLoc.y - destination.y;
		float distance = std::sqrtf((xClac * xClac) + (yCalc * yCalc));

		sf::Vector2f heading = normalize(m_worldLoc - destination);
		m_worldLoc -= (heading * m_speed) * dt.asSeconds();

		if (distance < 2.0f)
		{
			m_currentCell++;
		}

		if (fullPath.size() > 0 && m_currentCell >= static_cast<int>(fullPath.size()) - 1)
		{
			atPlayer = true;
		}
	}
}

void NPC::generatePath()
{
	m_graph.aStarAmbush(m_graph.nodeIndex(m_pos), m_graph.nodeIndex(m_dest), path);

	for (auto current : path)
	{
		fullPath.push_back(*current);
	}

	std::reverse(fullPath.begin(), fullPath.end());

	path.clear();

	generatingPath = false;
}