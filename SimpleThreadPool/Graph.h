#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <queue>
#include <vector>
#include <functional>
#include "NodeComparer.h"
#include <iostream>
template <class NodeType, class ArcType> class GraphArc;
template <class NodeType, class ArcType> class GraphNode;

// ---------------------------------------------------------------------
//  Name:           Graph
//  Description:    Manages the nodes and connections (arc) between them
// ---------------------------------------------------------------------
template<class NodeType, class ArcType>
class Graph 
{
public:        
	// typedef the classes to make our lives easier.
	typedef GraphArc<NodeType, ArcType> Arc;
	typedef GraphNode<NodeType, ArcType> Node;

    // Constructor and destructor functions
    Graph( int size );
    ~Graph();

    // Accessors
    Node * nodeIndex(int index) const 
	{
		return m_nodes.at(index);
    }

    // Public member functions.
    bool addNode( NodeType data, int index );
    void removeNode( int index );
    bool addArc( int from, int to, ArcType weight );
    void removeArc( int from, int to );
    Arc* getArc( int from, int to );        
    void clearMarks();
    void aStar(Node* start, Node* dest, std::vector<Node*>& path);
    void reset();
private:
	
	// Container of all the nodes in the graph.
    std::vector<Node*> m_nodes;
};

/// <summary>
/// Constructor, this constructs an empty graph.
/// </summary>
/// <param name="maxNodes">The maximum number of nodes.</param>
template<class NodeType, class ArcType>
Graph<NodeType, ArcType>::Graph( int maxNodes ) : m_nodes( maxNodes, nullptr) 
{  
}

/// <summary>
/// Destructor, deletes every node.
/// </summary>
template<class NodeType, class ArcType>
Graph<NodeType, ArcType>::~Graph() {
   for(size_t index = 0; index < m_nodes.size(); index++ ) 
   {
        if( m_nodes[index] != nullptr ) 
		{
			delete m_nodes.at(index);
        }
   }
}

/// <summary>
/// Adds a node at a given index in the graph.
/// </summary>
/// <param name="data">Data to store in the node</param>
/// <param name="index">Index to store the node</param>
/// <returns></returns>
template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::addNode( NodeType data, int index ) 
{
   bool nodeNotPresent = false;
   // find out if a node does not exist at that index.
   if ( nullptr == m_nodes.at(index) ) 
   {
      nodeNotPresent = true;
      // create a new node, put the data in it, and unmark it.
	  m_nodes.at(index) = new Node;
	  m_nodes.at(index)->m_data = data;
	  m_nodes.at(index)->setMarked(false);
    }
        
    return nodeNotPresent;
}

/// <summary>
/// Removes a node from the graph
/// </summary>
/// <param name="index">The index of the node to return</param>
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::removeNode( int index ) 
{
     // Only proceed if node does exist.
     if( nullptr != m_nodes.at(index) ) 
	 {
         // now find every arc that points to the node that
         // is being removed and remove it.        
         Arc* arc;

         // loop through every node
         for( int node = 0; node < m_nodes.size(); node++ ) 
		 {
              // if the node is valid...
              if( nullptr != m_nodes.at(node) ) {
                  // see if the node has an arc pointing to the current node.
                  arc = m_nodes.at(node)->getArc(m_nodes.at(index) );
              }
              // if it has an arc pointing to the current node, then
              // remove the arc.
              if( arc != 0 ) {
                  removeArc( node, index );
              }
         }
        

        // now that every arc pointing to the current node has been removed,
        // the node can be deleted.
        delete m_nodes.at(index);
		m_nodes.at(index) = nullptr;       
    }
}

/// <summary>
/// Adds an arc from the first index to the second index with the specified weight.
/// </summary>
/// <param name="from">The originating node index</param>
/// <param name="to">The ending node index</param>
/// <param name="weight">Weight of the arc</param>
/// <returns>True if successful</returns>
template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::addArc( int from, int to, ArcType weight ) 
{
     bool proceed = true; 
     // make sure both nodes exist.
     if( nullptr == m_nodes.at(from) || nullptr == m_nodes.at(to) ) 
	 {
         proceed = false;
     }
        
     // if an arc already exists we should not proceed
     if( m_nodes.at(from)->getArc( m_nodes.at(to) ) != nullptr ) 
	 {
         proceed = false;
     }

     if (proceed == true) 
	 {
        // add the arc to the "from" node.
		 m_nodes.at(from)->addArc(m_nodes.at(to), weight );
     }
        
     return proceed;
}

/// <summary>
/// Removes the arc from the first index to the second index
/// </summary>
/// <param name="from">Originating node index</param>
/// <param name="to">Ending node index</param>
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::removeArc( int from, int to ) 
{
     // Make sure that the node exists before trying to remove
     // an arc from it.
     bool nodeExists = true;
     if( nullptr == m_nodes.at(from) || nullptr == m_nodes.at(to) ) 
	 {
         nodeExists = false;
     }

     if (nodeExists == true) 
	 {
        // remove the arc.
		 m_nodes.at(from)->removeArc(m_nodes.at(to) );
     }
}

/// <summary>
/// Gets a pointer to an arc from the first index to the second index.
/// </summary>
/// <param name="from">Originating node index</param>
/// <param name="to">Ending node index</param>
/// <returns>A pointer to the arc, or 0 if it doesn't exist.</returns>
template<class NodeType, class ArcType>
GraphArc<NodeType, ArcType>* Graph<NodeType, ArcType>::getArc( int from, int to ) 
{
     Arc* arc = 0;
     // make sure the to and from nodes exist
     if( nullptr != m_nodes.at(from) && nullptr != m_nodes.at(to) ) 
	 {
         arc = m_nodes.at(from)->getArc(m_nodes.at(to) );
     }
                
     return arc;
}

/// <summary>
/// Clears every mark on all nodes
/// </summary>
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::clearMarks() 
{
     for( size_t index = 0; index < m_nodes.size(); index++ ) 
	 {
          if( nullptr != m_nodes.at(index) ) 
		  {
			  m_nodes.at(index)->setMarked(false);
          }
     }
}

/// <summary>
/// Uses A* to generate a path from the start node to the end node.
/// This path is stored through a referenced vector, so nothing has to be returned.
/// </summary>
/// <param name="start">Starting node</param>
/// <param name="dest">Destination node (goal)</param>
/// <param name="path">Path generated after a successful function run</param>
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::aStar(Node* start, Node* dest, std::vector<Node*>& path)
{
    reset(); // resets all nodes set as previous for a new calculation
    clearMarks(); // clears all nodes that are "marked" (already processed)

    if (start && dest) // make sure the passed in nodes exist
    {   
        std::priority_queue<Node*, std::vector<Node*>, NodeComparer<NodeType, ArcType>> pq;
        bool goalReached = false;
        Node* closestNode = dest;
        Node* lastNode = nullptr;

        for (Node* node : m_nodes)
        {
            node->m_data.m_cost = std::numeric_limits<int>::max()-100000; // we do not know the cost until we discover it

            // however, we can calculate the distance to the other nodes here
            node->m_data.m_distance = static_cast<int>(sqrt(pow(dest->m_data.m_x - node->m_data.m_x,2) + pow(dest->m_data.m_y - node->m_data.m_y, 2)));

        }

        start->m_data.m_cost = 0;
        start->setMarked(true);
        pq.push(start);
        
        closestNode->m_data.m_distance = 40000;
        

        while (!pq.empty() && pq.top() != dest)
        { // while there are nodes to go through, and the top node isn't the destination
            for (auto arc : pq.top()->arcList())
            { // go through all the arcs for the top node
                if (arc.node() != pq.top()->previous())
                { // make sure we do not process the node we're arcing from
                    int distantChild = pq.top()->m_data.m_cost + arc.weight() + arc.node()->m_data.m_distance;

                    if (arc.node()->m_data.m_passable)
                    {
                        if (distantChild < arc.node()->m_data.m_distance + arc.node()->m_data.m_cost)
                        {
                            arc.node()->m_data.m_cost = pq.top()->m_data.m_cost + arc.weight();
                            arc.node()->setPrevious(pq.top());
                        }
                    }
                    if (!arc.node()->marked())
                    {
                        pq.push(arc.node());
                        arc.node()->setMarked(true);
                    }
                }
            }

            lastNode = pq.top();

            if ((lastNode->m_data.m_distance) < (closestNode->m_data.m_distance))
            {
                closestNode = lastNode;
            }

            pq.pop();
        }

        // After picking the path to move to, add it to the queue backwards
        
        if (pq.size() > 0)
        {
            Node* current = pq.top();
            while (current != nullptr)
            {
                path.push_back(current);

                current = current->previous();

            }
        }
        else
        {
            std::cout << "PQ empty!" << std::endl;
        }
        
    }
}

template<class NodeType, class ArcType>
inline void Graph<NodeType, ArcType>::reset()
{
    for (size_t index = 0; index < m_nodes.size(); index++)
    {
        
        m_nodes[index]->setPrevious(nullptr);
        
    }
}


#include "GraphNode.h"
#include "GraphArc.h"


#endif
