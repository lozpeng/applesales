/**********************************************************************
 * $Id: LineMerger.cpp 2231 2009-01-05 23:42:08Z swongu $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2005-2006 Refractions Research Inc.
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#include <Geometry/operation/linemerge/LineMerger.h>
#include <Geometry/operation/linemerge/LineMergeDirectedEdge.h>
#include <Geometry/operation/linemerge/EdgeString.h>
#include <Geometry/planargraph/DirectedEdge.h>
#include <Geometry/planargraph/Edge.h>
#include <Geometry/planargraph/Node.h>
#include <Geometry/geom/GeometryComponentFilter.h>
#include <Geometry/geom/LineString.h>

#include <cassert>
#include <functional>
#include <vector>

using namespace std;
using namespace GEOMETRY::planargraph;
using namespace GEOMETRY::geom;

#ifndef GEOS_DEBUG
#define GEOS_DEBUG 0
#endif

namespace GEOMETRY {
namespace operation { // geos.operation
namespace linemerge { // geos.operation.linemerge

void
LineMerger::add(vector<Geometry*> *geometries)
{
	for(size_t i=0, n=geometries->size(); i<n; i++) {
		Geometry *geometry=(*geometries)[i];
		add(geometry);
	}
}

LineMerger::LineMerger():
	mergedLineStrings(NULL),
	factory(NULL)
{
}

LineMerger::~LineMerger()
{
	for (size_t i=0, n=edgeStrings.size(); i<n; ++i) {
		delete edgeStrings[i];
	}
}


struct LMGeometryComponentFilter: public GeometryComponentFilter {
	LineMerger *lm;

	LMGeometryComponentFilter(LineMerger *newLm): lm(newLm) {}

	void filter(const Geometry *geom) {
		const LineString *ls = dynamic_cast<const LineString *>(geom);
		if ( ls ) lm->add(ls);
	}
};


/**
 * Adds a Geometry to be processed. May be called multiple times.
 * Any dimension of Geometry may be added; the constituent linework will be
 * extracted.
 */  
void
LineMerger::add(const Geometry *geometry)
{
	LMGeometryComponentFilter lmgcf(this);
	geometry->applyComponentFilter(lmgcf);
}

void
LineMerger::add(const LineString *lineString)
{
	if (factory==NULL) factory=lineString->getFactory();
	graph.addEdge(lineString);
}

void
LineMerger::merge()
{
	if (mergedLineStrings!=NULL) return;

	buildEdgeStringsForObviousStartNodes();
	buildEdgeStringsForIsolatedLoops();

	unsigned numEdgeStrings = edgeStrings.size();
	mergedLineStrings=new vector<LineString*>(numEdgeStrings);
	for (size_t i=0; i<numEdgeStrings; ++i)
	{
		EdgeString *edgeString=edgeStrings[i];
		(*mergedLineStrings)[i]=edgeString->toLineString();
	}    
}

void
LineMerger::buildEdgeStringsForObviousStartNodes()
{
	buildEdgeStringsForNonDegree2Nodes();
}

void
LineMerger::buildEdgeStringsForIsolatedLoops()
{
	buildEdgeStringsForUnprocessedNodes();
}  

void
LineMerger::buildEdgeStringsForUnprocessedNodes()
{
#if GEOS_DEBUG
	cerr<<__FUNCTION__<<endl;
#endif
	vector<Node*> *nodes=graph.getNodes();
	for (size_t i=0; i<nodes->size(); ++i) {
		Node *node=(*nodes)[i];
#if GEOS_DEBUG
		cerr<<"Node "<<i<<": "<<*node<<endl;
#endif
		if (!node->isMarked()) { 
			assert(node->getDegree()==2);
			buildEdgeStringsStartingAt(node);
			node->setMarked(true);
#if GEOS_DEBUG
			cerr<<" setMarked(true) : "<<*node<<endl;
#endif
		}
	}
	delete nodes;
}

void
LineMerger::buildEdgeStringsForNonDegree2Nodes()
{
#if GEOS_DEBUG
	cerr<<__FUNCTION__<<endl;
#endif
	vector<Node*> *nodes=graph.getNodes();
	size_t size=nodes->size();
	for (size_t i=0; i<size; i++) {
		Node *node=(*nodes)[i];
#if GEOS_DEBUG
		cerr<<"Node "<<i<<": "<<*node<<endl;
#endif
		if (node->getDegree()!=2) { 
			buildEdgeStringsStartingAt(node);
			node->setMarked(true);
#if GEOS_DEBUG
			cerr<<" setMarked(true) : "<<*node<<endl;
#endif
		}
	}
	delete nodes;
}

void
LineMerger::buildEdgeStringsStartingAt(Node *node)
{
	vector<planargraph::DirectedEdge*> &edges=node->getOutEdges()->getEdges();
	size_t size = edges.size();
	for (size_t i=0; i<size; i++)
	{
		assert(dynamic_cast<LineMergeDirectedEdge*>(edges[i]));
		LineMergeDirectedEdge *directedEdge=\
			static_cast<LineMergeDirectedEdge*> (edges[i]);
		if (directedEdge->getEdge()->isMarked()) {
			continue;
		}
		edgeStrings.push_back(buildEdgeStringStartingWith(directedEdge));
	}
}

EdgeString*
LineMerger::buildEdgeStringStartingWith(LineMergeDirectedEdge *start)
{    
	EdgeString *edgeString = new EdgeString(factory);
	LineMergeDirectedEdge *current=start;
	do {
		edgeString->add(current);
		current->getEdge()->setMarked(true);
		current=current->getNext();      
	} while (current!=NULL && current!=start);
	return edgeString;
}

/**
 * Returns the LineStrings built by the merging process.
 */
vector<LineString*>*
LineMerger::getMergedLineStrings()
{
	merge();

	// Explicitly give ownership to the caller.
	vector<LineString*>* ret = mergedLineStrings;
	mergedLineStrings = NULL;
	return ret;
}

} // namespace GEOMETRY.operation.linemerge
} // namespace GEOMETRY.operation
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.15  2006/06/12 11:29:24  strk
 * unsigned int => size_t
 *
 * Revision 1.14  2006/03/22 10:13:54  strk
 * opLinemerge.h split
 *
 * Revision 1.13  2006/03/21 21:42:54  strk
 * planargraph.h header split, planargraph:: classes renamed to match JTS symbols
 *
 **********************************************************************/
 

