#ifndef NODEDATA_H
#define NODEDATA_H

///<summary>
/// A simple struct to encapsulate all the node data.               
///<summary>
struct NodeData
{
	int m_name;
	int m_cost;
	int m_distance;
	int m_x;
	int m_y;
	bool m_passable = true;
};

#endif