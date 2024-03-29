/**********************************************************************
 * $Id: BufferSubgraph.cpp 1986 2007-06-08 15:27:42Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 * Copyright (C) 2005 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: operation/buffer/BufferSubgraph.java rev. 1.17
 *
 **********************************************************************/

#include <Geometry/operation/buffer/BufferSubgraph.h>
#include <Geometry/util/TopologyException.h>
#include <Geometry/geom/Envelope.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geomgraph/Node.h>
#include <Geometry/geomgraph/Edge.h>
#include <Geometry/geomgraph/DirectedEdge.h>
#include <Geometry/geomgraph/DirectedEdgeStar.h>
#include <Geometry/geomgraph/EdgeEndStar.h>
#include <Geometry/geomgraph/Position.h>

#include <cassert>
#include <vector>
#include <iostream>
#include <list>

#ifndef GEOS_DEBUG
#define GEOS_DEBUG 0
#endif

using namespace std;
using namespace GEOMETRY::geomgraph;
using namespace GEOMETRY::algorithm;
using namespace GEOMETRY::operation;
using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace operation { // geos.operation
namespace buffer { // geos.operation.buffer

// Argument is unused
BufferSubgraph::BufferSubgraph(CGAlgorithms* /*cga*/):
	rightMostCoord(NULL),
	env(NULL)
{
}

BufferSubgraph::~BufferSubgraph()
{
	delete env;
}

/*public*/
void
BufferSubgraph::create(Node *node)
{
	addReachable(node);

	// We are assuming that dirEdgeList 
	// contains *at leas* ONE forward DirectedEdge
	finder.findEdge(&dirEdgeList);

	rightMostCoord=&(finder.getCoordinate());

	// this is what happen if no forward DirectedEdge
	// is passed to the RightmostEdgeFinder
	assert(rightMostCoord);
}

/*private*/
void
BufferSubgraph::addReachable(Node *startNode)
{
	vector<Node*> nodeStack;
	nodeStack.push_back(startNode);
	while (!nodeStack.empty()) {
		Node *node=nodeStack.back();
		nodeStack.pop_back();
		add(node, &nodeStack);
	}
}

/*private*/
void
BufferSubgraph::add(Node *node, vector<Node*> *nodeStack)
{
	node->setVisited(true);
	nodes.push_back(node);
	EdgeEndStar *ees=node->getEdges();
	EdgeEndStar::iterator it=ees->begin();
	EdgeEndStar::iterator endIt=ees->end();
	for( ; it!=endIt; ++it)
	{
		assert(dynamic_cast<DirectedEdge*>(*it));
		DirectedEdge *de=static_cast<DirectedEdge*>(*it);
		dirEdgeList.push_back(de);
		DirectedEdge *sym=de->getSym();
		Node *symNode=sym->getNode();
		/**
		 * NOTE: this is a depth-first traversal of the graph.
		 * This will cause a large depth of recursion.
		 * It might be better to do a breadth-first traversal.
		 */
		if (! symNode->isVisited()) nodeStack->push_back(symNode);
	}
}

/*private*/
void
BufferSubgraph::clearVisitedEdges()
{
	for(size_t i=0, n=dirEdgeList.size(); i<n; ++i)
	{
		DirectedEdge *de=dirEdgeList[i];
		de->setVisited(false);
	}
}

/*public*/
void
BufferSubgraph::computeDepth(int outsideDepth)
{
	clearVisitedEdges();
	// find an outside edge to assign depth to
	DirectedEdge *de=finder.getEdge();
#if GEOS_DEBUG
cerr<<"outside depth: "<<outsideDepth<<endl;
#endif
	//Node *n=de->getNode();
	//Label *label=de->getLabel();

	// right side of line returned by finder is on the outside
	de->setEdgeDepths(Position::RIGHT, outsideDepth);
	copySymDepths(de);

	//computeNodeDepth(n, de);
	computeDepths(de);
}

void
BufferSubgraph::computeNodeDepth(Node *n)
	// throw(TopologyException *)
{
	// find a visited dirEdge to start at
	DirectedEdge *startEdge=NULL;

	assert(dynamic_cast<DirectedEdgeStar *>(n->getEdges()));
	DirectedEdgeStar *ees=static_cast<DirectedEdgeStar *>(n->getEdges());

	EdgeEndStar::iterator endIt=ees->end();

	EdgeEndStar::iterator it=ees->begin();
	for(; it!=endIt; ++it)
	{
		assert(dynamic_cast<DirectedEdge*>(*it));
		DirectedEdge *de=static_cast<DirectedEdge*>(*it);
		if (de->isVisited() || de->getSym()->isVisited()) {
			startEdge=de;
			break;
		}
	}
	// MD - testing  Result: breaks algorithm
	//if (startEdge==null) return;
	//assert(startEdge!=NULL);
	if (startEdge==NULL)
	{
		throw util::TopologyException(
			"unable to find edge to compute depths",
			n->getCoordinate());
	}

	ees->computeDepths(startEdge);

	// copy depths to sym edges
	for(it=ees->begin(); it!=endIt; ++it)
	{
		assert(dynamic_cast<DirectedEdge*>(*it));
		DirectedEdge *de=static_cast<DirectedEdge*>(*it);
		de->setVisited(true);
		copySymDepths(de);
	}
}

/*private*/
void
BufferSubgraph::copySymDepths(DirectedEdge *de)
{
#if GEOS_DEBUG
	cerr << "copySymDepths: " << de->getDepth(Position::LEFT)
	     << ", " << de->getDepth(Position::RIGHT)
	     << endl;
#endif
	DirectedEdge *sym=de->getSym();
	sym->setDepth(Position::LEFT, de->getDepth(Position::RIGHT));
	sym->setDepth(Position::RIGHT, de->getDepth(Position::LEFT));
}

/*public*/
void
BufferSubgraph::findResultEdges()
{
#if GEOS_DEBUG
	cerr<<"BufferSubgraph::findResultEdges got "<<dirEdgeList.size()<<" edges"<<endl;
#endif
	for(size_t i=0, n=dirEdgeList.size(); i<n; ++i)
	{
		DirectedEdge *de=dirEdgeList[i];

		/**
		 * Select edges which have an interior depth on the RHS
		 * and an exterior depth on the LHS.
		 * Note that because of weird rounding effects there may be
		 * edges which have negative depths!  Negative depths
		 * count as "outside".
		 */
		// <FIX> - handle negative depths
#if GEOS_DEBUG
		cerr << " dirEdge "<<i<<": " << de->printEdge() << endl
		     << "         depth right: " << de->getDepth(Position::RIGHT) << endl
		     << "          depth left: " << de->getDepth(Position::LEFT) << endl
		     << "    interiorAreaEdge: " << de->isInteriorAreaEdge()<<endl;
#endif
		if ( de->getDepth(Position::RIGHT)>=1
			&&  de->getDepth(Position::LEFT)<=0
			&& !de->isInteriorAreaEdge()) {
					de->setInResult(true);
#if GEOS_DEBUG
					cerr<<"   IN RESULT"<<endl;
#endif
		}
	}
}

/*public*/
int
BufferSubgraph::compareTo(BufferSubgraph *graph)
{
	assert(rightMostCoord);
	if (rightMostCoord->x<graph->rightMostCoord->x) {
		return -1;
	}
	if (rightMostCoord->x>graph->rightMostCoord->x) {
		return 1;
	}
	return 0;
}

/*private*/
void
BufferSubgraph::computeDepths(DirectedEdge *startEdge)
{
	set<Node *> nodesVisited; 
	list<Node*> nodeQueue; // Used to be a vector
	Node *startNode=startEdge->getNode();
	nodeQueue.push_back(startNode);
	//nodesVisited.push_back(startNode);
	nodesVisited.insert(startNode);
	startEdge->setVisited(true);

	while (! nodeQueue.empty())
	{
		//System.out.println(nodes.size() + " queue: " + nodeQueue.size());
		Node *n=nodeQueue.front(); // [0];
		//nodeQueue.erase(nodeQueue.begin());
		nodeQueue.pop_front(); 

		nodesVisited.insert(n);

		// compute depths around node, starting at this edge since it has depths assigned
		computeNodeDepth(n);

		// add all adjacent nodes to process queue,
		// unless the node has been visited already
		EdgeEndStar *ees=n->getEdges();
		EdgeEndStar::iterator endIt=ees->end();
		EdgeEndStar::iterator it=ees->begin();
		for(; it!=endIt; ++it)
		{
			assert(dynamic_cast<DirectedEdge*>(*it));
			DirectedEdge *de=static_cast<DirectedEdge*>(*it);
			DirectedEdge *sym=de->getSym();
			if (sym->isVisited()) continue;
			Node *adjNode=sym->getNode();

			//if (! contains(nodesVisited,adjNode))
			if(nodesVisited.insert(adjNode).second)
			{
				nodeQueue.push_back(adjNode);
				//nodesVisited.insert(adjNode);
			}
		}
	}
}

/*private*/
bool
BufferSubgraph::contains(set<Node*>&nodeSet, Node *node)
{
	//bool result=false;
	if ( nodeSet.find(node) != nodeSet.end() ) return true;
	return false;
}

/*public*/
Envelope *
BufferSubgraph::getEnvelope()
{
	if (env == NULL) {
		env = new Envelope();
		std::size_t const size = dirEdgeList.size();
		for(std::size_t i=0; i<size; ++i)
		{
			DirectedEdge *dirEdge=dirEdgeList[i];
			const CoordinateSequence *pts = dirEdge->getEdge()->getCoordinates();
			std::size_t const n = pts->getSize()-1;
			for (std::size_t j=0; j<n; ++j) {
				env->expandToInclude(pts->getAt(j));
			}
		}
	}
	return env;
}

std::ostream& operator<< (std::ostream& os, const BufferSubgraph& bs)
{
	os << "BufferSubgraph[" << &bs << "] "
	   << bs.nodes.size() << " nodes, "
	   << bs.dirEdgeList.size() << " directed edges" << std::endl;

	for (size_t i=0, n=bs.nodes.size(); i<n; i++)
		os << "  Node " << i << ": " << *(bs.nodes[i]) << std::endl;

	for (size_t i=0, n=bs.dirEdgeList.size(); i<n; i++)
	{
		os << "  DirEdge " << i << ": " << std::endl
		   << bs.dirEdgeList[i]->printEdge() << std::endl;
	}

	return os;
}

} // namespace GEOMETRY.operation.buffer
} // namespace GEOMETRY.operation
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.34  2006/06/12 11:29:23  strk
 * unsigned int => size_t
 *
 * Revision 1.33  2006/05/04 12:33:32  strk
 * Added some comments about RightmostEdgeFinder only considering forward DirectedEdge
 *
 * Revision 1.32  2006/03/22 11:18:39  strk
 * Changed back 'unable to find edge to compute depths' from assertion to TopologyException
 *
 **********************************************************************/

