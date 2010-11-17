/**********************************************************************
 * $Id: ConnectedSubgraphFinder.cpp 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/


#include <Geometry/planargraph/algorithm/ConnectedSubgraphFinder.h>
#include <Geometry/planargraph/Subgraph.h>
#include <Geometry/planargraph/Edge.h>
#include <Geometry/planargraph/Node.h>
#include <Geometry/planargraph/DirectedEdge.h>
#include <Geometry/planargraph/DirectedEdgeStar.h>

#include <vector>
#include <stack>

using namespace std;

namespace GEOMETRY {
namespace planargraph {
namespace algorithm {

void
ConnectedSubgraphFinder::getConnectedSubgraphs(vector<Subgraph *>& subgraphs)
{
	GraphComponent::setVisitedMap(graph.nodeBegin(),
			graph.nodeEnd(), false);

	for (PlanarGraph::EdgeIterator
			it=graph.edgeBegin(),
			itEnd=graph.edgeEnd();
			it!=itEnd; ++it)
	{
		Edge *e = *it;
		Node *node = e->getDirEdge(0)->getFromNode();
		if (! node->isVisited()) {
			subgraphs.push_back(findSubgraph(node));
		}
	}
 
}

/*private*/
Subgraph* 
ConnectedSubgraphFinder::findSubgraph(Node* node)
{
	Subgraph* subgraph = new Subgraph(graph);
	addReachable(node, subgraph);
	return subgraph;
}

/*private*/
void
ConnectedSubgraphFinder::addReachable(Node* startNode,
		Subgraph* subgraph)
{
	stack<Node *> nodeStack;
	nodeStack.push(startNode);
	while ( !nodeStack.empty() )
	{
		Node* node = nodeStack.top();
		nodeStack.pop();
		addEdges(node, nodeStack, subgraph);
	}
}

/*private*/
void
ConnectedSubgraphFinder::addEdges(Node* node,
		stack<Node *>& nodeStack, Subgraph* subgraph)
{
	node->setVisited(true);
	DirectedEdgeStar *des=node->getOutEdges();
	for (DirectedEdge::Vect::iterator i=des->begin(), iEnd=des->end();
			i!=iEnd; ++i)
	{
		DirectedEdge *de=*i;
		subgraph->add(de->getEdge());
		Node *toNode = de->getToNode();
		if ( ! toNode->isVisited() ) nodeStack.push(toNode);
	}
}


} // namespace GEOMETRY.planargraph.algorithm
} // namespace GEOMETRY.planargraph 
} // namespace GEOMETRY 

/**********************************************************************
 * $Log$
 * Revision 1.5  2006/03/21 21:42:54  strk
 * planargraph.h header split, planargraph:: classes renamed to match JTS symbols
 *
 **********************************************************************/
