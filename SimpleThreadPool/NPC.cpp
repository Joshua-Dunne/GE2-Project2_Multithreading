#include "NPC.h"

void NPC::beginPathing(int t_dest)
{
	m_dest = t_dest;

	path.clear();

	//m_graph.aStar(m_graph.nodeIndex(m_pos), m_graph.nodeIndex(m_dest), path);

	s->pool().addTask([this]() {this->generatePath(); });
}

void NPC::drawPath(sf::RenderWindow& t_window)
{
	sf::RectangleShape space;
	space.setSize(sf::Vector2f{ 25.0f, 25.0f });
	space.setFillColor(sf::Color::Black);

	for (auto cell : path)
	{
		NodeData current;

		current = cell->m_data;

		space.setPosition(static_cast<float>(current.m_x), static_cast<float>(current.m_y));

		t_window.draw(space);
	}
}

void NPC::generatePath()
{
	m_graph.aStar(m_graph.nodeIndex(m_pos), m_graph.nodeIndex(m_dest), path);

	//std::cout << path[0]->m_data.m_name << std::endl;
}
