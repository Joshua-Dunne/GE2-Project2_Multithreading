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
	}

	void beginPathing(int t_dest);
	void generatePath();
	//void moveOnPath();
	
	NodeData m_data;

private:
	Graph<NodeData, int>& m_graph;
	std::vector<GraphNode<NodeData, int>*> path;
	
	int m_pos = -1;
	int m_dest = -1;
};

#endif