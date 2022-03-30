#include "NPC.h"

void NPC::beginPathing(int t_dest)
{
	m_dest = t_dest;

	s->pool().addTask([this]() {this->generatePath(); });
}

void NPC::generatePath()
{
	m_graph.aStar(m_graph.nodeIndex(m_pos), m_graph.nodeIndex(m_dest), path);

	std::cout << path[0]->m_data.m_name << std::endl;
}
