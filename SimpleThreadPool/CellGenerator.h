#ifndef CELL_GEN_H
#define CELL_GEN_H

#include "NodeData.h"
#include "Graph.h"
#include "GraphNode.h"
#include "NodeData.h"
#include "NodeComparer.h"
#include <vector>
#include <fstream>
#include <sstream>

class CellGenerator
{
	static const int c_MAX_X = 100;
	static const int c_MAX_Y = 100;

	static const int c_NODE_SIZE = 25;

	Graph<NodeData, int> m_graph;
	NodeData m_data[c_MAX_Y][c_MAX_X]; // 100x100 grid of nodes

	bool fileExists(const char* fileName);

	void generateNodesFile();
	void generateArcsFile();

public:
	CellGenerator();

	void populateData();
	inline Graph<NodeData, int>& getGraph() { return m_graph; };
};

#endif