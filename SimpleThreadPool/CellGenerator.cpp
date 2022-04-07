#include "CellGenerator.h"

CellGenerator::CellGenerator() : m_graph(c_MAX_X * c_MAX_Y)
{
}

/// <summary>
/// Check to see if a file exists already.
/// </summary>
/// <param name="fileName">Path to file</param>
/// <returns>If the file already exists on the path</returns>
bool CellGenerator::fileExists(const char* fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}



/// <summary>
/// Populate our Data array, getting the X/Y positions of each Node, and a name.
/// </summary>
void CellGenerator::populateData()
{
	int currCell = 0;
	
	// Node generation
	for (int yPos = 0; yPos < c_MAX_Y; yPos++)
	{
		m_data.push_back(std::vector<NodeData>());
		for (int xPos = 0; xPos < c_MAX_X; xPos++, currCell++)
		{
			m_data[yPos].push_back(NodeData());
			m_data[yPos][xPos].m_x = xPos * c_NODE_SIZE;
			m_data[yPos][xPos].m_y = yPos * c_NODE_SIZE;
			m_data[yPos][xPos].m_name = currCell;

			if(c_MAX_X == 1000)
				if ((xPos == 100 && yPos < 800) || (xPos == 400 && yPos > 200) || (xPos == 700 && yPos < 800))
					m_data[yPos][xPos].m_passable = false;

			if (c_MAX_X == 100)
				if ((xPos == 10 && yPos < 80) || (xPos == 40 && yPos > 20) || (xPos == 70 && yPos < 80))
					m_data[yPos][xPos].m_passable = false;

			if (c_MAX_X == 30)
				if ((xPos == 5 && yPos < 15) || (xPos == 12 && yPos > 15) || (xPos == 22 && yPos < 15))
					m_data[yPos][xPos].m_passable = false;
			
			m_graph.addNode(m_data[yPos][xPos], currCell);
		}
	}

	// Arc Generation
	for (int row = 0; row < c_MAX_Y; row++)
	{
		for (int col = 0; col < c_MAX_X; col++)
		{
			for (int direction = 0; direction < 9; direction++) {
				if (direction == 4) continue; // Skip 4, this is ourself.

				int n_row = row + ((direction % 3) - 1); // Neighbor row
				int n_col = col + ((direction / 3) - 1); // Neighbor column

				// Check the bounds:
				if (n_row >= 0 && n_row < c_MAX_Y && n_col >= 0 && n_col < c_MAX_X) {
					int cost;

					// 0,2,6,8 are Diagonal, so we need to apply the correct cost
					if (direction == 0 || direction % 2 == 0)
					{
						continue;
					}
					else // 1,3,5,7 are next to the node, so give them the correct cost
					{
						cost = c_NODE_SIZE;
						m_graph.addArc(m_data[row][col].m_name, m_data[n_row][n_col].m_name, cost);
					}
				}
			}
		}
	}

	// Now that the Data has been filled, generate required files
	// Uncomment to view data in text file for debugging purposes
	generateNodesFile();
	generateArcsFile();
}

/// <summary>
/// Generate a file called "nodes.txt" based on the generated Node data.
/// </summary>
void CellGenerator::generateNodesFile()
{
	std::string saveFileName{ "assets/generated/nodes.txt" };

	if (!fileExists(saveFileName.c_str()))
	{ // if the file doesn't exist, create it and fill it with our data
	  // if it already exists, we don't need to run this code again

		std::fstream saveToFile;

		saveToFile.open(saveFileName, std::fstream::out);

		if (saveToFile.is_open()) // make sure the file has opened successfully
		{
			for (int yPos = 0; yPos < c_MAX_Y; yPos++)
			{
				for (int xPos = 0; xPos < c_MAX_X; xPos++)
				{
					saveToFile << m_data[yPos][xPos].m_name <<
						   "," << m_data[yPos][xPos].m_x <<
						   "," << m_data[yPos][xPos].m_y << std::endl;

				}
			}

		}

		saveToFile.close();
	}
}

/// <summary>
/// Generate a file called "arcs.txt".
/// </summary>
void CellGenerator::generateArcsFile()
{
	// We don't need to check if the file is already real here
	// since there's information we need to process as well

	std::string saveFileName{ "assets/generated/arcs.txt" };
	std::fstream saveToFile;
	saveToFile.open(saveFileName, std::fstream::out);

	if (!fileExists(saveFileName.c_str()))
	{
		if (saveToFile.is_open())
		{
			for (int row = 0; row < c_MAX_Y; row++)
			{
				for (int col = 0; col < c_MAX_X; col++)
				{
					for (int direction = 0; direction < 9; direction++) {
						if (direction == 4) continue; // Skip 4, this is ourself.

						int n_row = row + ((direction % 3) - 1); // Neighbor row
						int n_col = col + ((direction / 3) - 1); // Neighbor column

						// Check the bounds:
						if (n_row >= 0 && n_row < c_MAX_Y && n_col >= 0 && n_col < c_MAX_X) {
							int cost;

							// 0,2,6,8 are Diagonal, so we need to apply the correct cost
							if (direction == 0 || direction % 2 == 0)
							{
								cost = c_NODE_SIZE * 2;
							}
							else // 1,3,5,7 are next to the node, so give them the correct cost
							{
								cost = c_NODE_SIZE;
							}

							// Now that it's been added to the Graph, output it to our file
							saveToFile << m_data[row][col].m_name <<
								"," << m_data[n_row][n_col].m_name <<
								"," << cost << std::endl;
						}
					}
				}
			}
		}
	}
	
	saveToFile.close(); // now that we're done, close the file
}
