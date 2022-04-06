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
#include <vector>

class CellGenerator
{
	Graph<NodeData, int> m_graph;

	bool fileExists(const char* fileName);

	void generateNodesFile();
	void generateArcsFile();

public:
	CellGenerator();

	static const int c_MAX_X = 1000;
	static const int c_MAX_Y = 1000;
	static const int c_NODE_SIZE = 25;

	std::vector<std::vector<NodeData>> m_data; // grid of nodes

	void populateData();
	inline Graph<NodeData, int>& getGraph() { return m_graph; };
};

#endif