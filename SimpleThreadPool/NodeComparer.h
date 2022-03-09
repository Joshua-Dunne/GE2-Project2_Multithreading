#ifndef NODE_COMPARER_H
#define NODE_COMPARER_H

#include "GraphNode.h"

///<summary>
/// Compares two nodes, and determines if the first has a greater cost & distance than the other node
///</summary>
template<class NodeType, class ArcType>
class NodeComparer
{
	typedef GraphNode<NodeType, ArcType> Node;

public:
	bool operator() (Node* first, Node* second)
	{
		return first->m_data.m_cost + first->m_data.m_distance > second->m_data.m_cost + second->m_data.m_distance;
	}

};

#endif