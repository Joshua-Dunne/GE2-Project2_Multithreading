#ifndef GRAPHARC_H
#define GRAPHARC_H

#include "GraphNode.h"

/// <summary>
/// This is the arc class. 
/// The arc class points to a graph node, and contains a weight.
/// </summary>
template<class NodeType, class ArcType>
class GraphArc 
{
private:

// Pointer to the node that the arc points to
    GraphNode<NodeType, ArcType>* m_node;

// Weight of the arc
    ArcType m_weight;

public:    
    
    // Accessor functions
    GraphNode<NodeType, ArcType>* node() const 
	{
        return m_node;
    }
                              
    ArcType weight() const 
	{
        return m_weight;
    }
    
    // Manipulator functions
    void setNode(GraphNode<NodeType, ArcType>* node) 
	{
       m_node = node;
    }
    
    void setWeight(ArcType weight) 
	{
       m_weight = weight;
    }
    
};

#endif
