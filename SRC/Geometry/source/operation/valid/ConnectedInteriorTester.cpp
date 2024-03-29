/**********************************************************************
 * $Id: ConnectedInteriorTester.cpp 1820 2006-09-06 16:54:23Z mloskot $
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
 **********************************************************************
 *
 * Last port: operation/valid/ConnectedInteriorTester.java rev. 1.14
 *
 **********************************************************************
 * 
 * TODO:
 *
 *  - Remove heap allocation of GeometryFactory (might use a singleton)
 *  - Track MaximalEdgeRing references: we might be deleting them 
 *    leaving dangling refs around.
 *
 **********************************************************************/

#include <Geometry/operation/valid/ConnectedInteriorTester.h> 
#include <Geometry/operation/overlay/MaximalEdgeRing.h>
#include <Geometry/operation/overlay/MinimalEdgeRing.h>
#include <Geometry/operation/overlay/OverlayNodeFactory.h>
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/Location.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/MultiPolygon.h>
#include <Geometry/geom/MultiPolygon.h>
#include <Geometry/geom/LineString.h>
#include <Geometry/geomgraph/GeometryGraph.h>
#include <Geometry/geomgraph/PlanarGraph.h>
#include <Geometry/geomgraph/EdgeRing.h>
#include <Geometry/geomgraph/DirectedEdge.h>
#include <Geometry/geomgraph/Position.h>
#include <Geometry/geomgraph/Label.h>

#include <vector>
#include <cassert>
#include <typeinfo>

#ifndef GEOS_DEBUG
#define GEOS_DEBUG 0
#endif

#if GEOS_DEBUG
#include <iostream>
#endif

using namespace std;
using namespace GEOMETRY::geom;
using namespace GEOMETRY::geomgraph;
using namespace GEOMETRY::operation::overlay;

namespace GEOMETRY {
namespace operation { // geos.operation
namespace valid { // geos.operation.valid

ConnectedInteriorTester::ConnectedInteriorTester(GeometryGraph &newGeomGraph):
	geometryFactory(new GeometryFactory()),
	geomGraph(newGeomGraph),
	disconnectedRingcoord()
{
}

ConnectedInteriorTester::~ConnectedInteriorTester()
{
	delete geometryFactory;
}

Coordinate&
ConnectedInteriorTester::getCoordinate()
{
	return disconnectedRingcoord;
}

const Coordinate&
ConnectedInteriorTester::findDifferentPoint(const CoordinateSequence *coord,
		const Coordinate& pt)
{
	assert(coord);
	size_t npts=coord->getSize();
	for(size_t i=0; i<npts; ++i)
	{
		if(!(coord->getAt(i)==pt))
			return coord->getAt(i);
	}
	return Coordinate::getNull();
}

/*public*/
bool
ConnectedInteriorTester::isInteriorsConnected()
{

	// node the edges, in case holes touch the shell
	std::vector<Edge*> splitEdges;
	geomGraph.computeSplitEdges(&splitEdges);

	// form the edges into rings
	PlanarGraph graph(operation::overlay::OverlayNodeFactory::instance());

	graph.addEdges(splitEdges);
	setInteriorEdgesInResult(graph);
	graph.linkResultDirectedEdges();

	// Someone has to delete the returned vector and its contents
	std::vector<EdgeRing*>* edgeRings=buildEdgeRings(graph.getEdgeEnds());
	assert(edgeRings);

#if GEOS_DEBUG
	cerr << "buildEdgeRings constructed " << edgeRings->size() << " edgeRings." << endl;
#endif

	/*
	 * Mark all the edges for the edgeRings corresponding to the shells
	 * of the input polygons. 
	 * 
	 * Only ONE ring gets marked for each shell - if there are others
	 * which remain unmarked this indicates a disconnected interior.
	 */
	visitShellInteriors(geomGraph.getGeometry(), graph);

#if GEOS_DEBUG
	cerr << "after visitShellInteriors edgeRings are " << edgeRings->size() << " edgeRings." << endl;
#endif

	/*
	 * If there are any unvisited shell edges
	 * (i.e. a ring which is not a hole and which has the interior
	 * of the parent area on the RHS)
	 * this means that one or more holes must have split the interior of the
	 * polygon into at least two pieces.  The polygon is thus invalid.
	 */
	bool res=!hasUnvisitedShellEdge(edgeRings);

	assert(edgeRings);
#if GEOS_DEBUG
	cerr << "releasing " << edgeRings->size() << " edgeRings." << endl;
#endif
	// Release memory allocated by buildEdgeRings
	for(size_t i=0, n=edgeRings->size(); i<n; ++i)
	{
		EdgeRing* er = (*edgeRings)[i];
#if GEOS_DEBUG
		cerr<<*er<<endl;
#endif
		assert(er);
		delete er;
#if GEOS_DEBUG
	cerr << "releasing edgeRing at " << er << endl;
#endif
	}
	delete edgeRings;

	// Release memory allocated by MaximalEdgeRings
	// There should be no more references to this object
	// how to check this ? boost::shared_ptr<> comes to mind.
	//
	for (size_t i=0, n=maximalEdgeRings.size(); i<n; i++)
	{
		delete maximalEdgeRings[i];
	}
	maximalEdgeRings.clear();

	return res;
}

void
ConnectedInteriorTester::setInteriorEdgesInResult(PlanarGraph &graph)
{
	std::vector<EdgeEnd*> *ee=graph.getEdgeEnds();
	for(size_t i=0, n=ee->size(); i<n; ++i)
	{
		// Unexpected non DirectedEdge in graphEdgeEnds
		assert(dynamic_cast<DirectedEdge*>((*ee)[i]));
		DirectedEdge *de=static_cast<DirectedEdge*>((*ee)[i]);
		if ( de->getLabel()->getLocation(0, Position::RIGHT) == Location::INTERIOR)
		{
			de->setInResult(true);
		}
	}
}

/*private*/
std::vector<EdgeRing*>*
ConnectedInteriorTester::buildEdgeRings(std::vector<EdgeEnd*> *dirEdges)
{
#if GEOS_DEBUG
	cerr << __FUNCTION__ << " got " << dirEdges->size() << " EdgeEnd vector" << endl;
#endif
	std::vector<MinimalEdgeRing*> minEdgeRings;
	for(size_t i=0, n=dirEdges->size(); i<n; ++i)
	{
		assert(dynamic_cast<DirectedEdge*>((*dirEdges)[i]));
		DirectedEdge *de=static_cast<DirectedEdge*>((*dirEdges)[i]);

#if GEOS_DEBUG
		cerr << "DirectedEdge " << i << ": " << de->print() << endl;
#endif

		// if this edge has not yet been processed
		if(de->isInResult() && de->getEdgeRing()==NULL)
		{
			//EdgeRing *er=new MaximalEdgeRing(de,geometryFactory);
			//edgeRings->push_back(er);

			MaximalEdgeRing* er=new MaximalEdgeRing(de, geometryFactory);
			// We track MaximalEdgeRings allocations
			// using the private maximalEdgeRings vector
			maximalEdgeRings.push_back(er);

			er->linkDirectedEdgesForMinimalEdgeRings();
			er->buildMinimalRings(minEdgeRings);
		}
	}
	std::vector<EdgeRing*> *edgeRings=new std::vector<EdgeRing*>();
	edgeRings->assign(minEdgeRings.begin(), minEdgeRings.end());
	return edgeRings;
}

/**
 * Mark all the edges for the edgeRings corresponding to the shells
 * of the input polygons.  Note only ONE ring gets marked for each shell.
 */
void
ConnectedInteriorTester::visitShellInteriors(const Geometry *g, PlanarGraph &graph)
{
	if (const Polygon* p=dynamic_cast<const Polygon*>(g))
	{
		visitInteriorRing(p->getExteriorRing(), graph);
	}

	if (const MultiPolygon* mp=dynamic_cast<const MultiPolygon*>(g))
	{
		for (size_t i=0, n=mp->getNumGeometries(); i<n; i++) {
			const Polygon *p=static_cast<const Polygon*>(mp->getGeometryN(i));
			visitInteriorRing(p->getExteriorRing(), graph);
		}
	}
}

void
ConnectedInteriorTester::visitInteriorRing(const LineString *ring, PlanarGraph &graph)
{
	const CoordinateSequence *pts=ring->getCoordinatesRO();
	const Coordinate& pt0=pts->getAt(0);

	/**
	 * Find first point in coord list different to initial point.
	 * Need special check since the first point may be repeated.
	 */
    	const Coordinate& pt1=findDifferentPoint(pts, pt0);
	Edge *e=graph.findEdgeInSameDirection(pt0, pt1);
	DirectedEdge *de=static_cast<DirectedEdge*>(graph.findEdgeEnd(e));
	DirectedEdge *intDe=NULL;
	if (de->getLabel()->getLocation(0,Position::RIGHT)==Location::INTERIOR) {
		intDe=de;
	} else if (de->getSym()->getLabel()->getLocation(0,Position::RIGHT)==Location::INTERIOR) {
		intDe=de->getSym();
	}
	assert(intDe!=NULL); // unable to find dirEdge with Interior on RHS
	visitLinkedDirectedEdges(intDe);
}


void
ConnectedInteriorTester::visitLinkedDirectedEdges(DirectedEdge *start)
{
	DirectedEdge *startDe=start;
	DirectedEdge *de=start;
	//Debug.println(de);
	do {
		// found null Directed Edge
		assert(de!=NULL);

		de->setVisited(true);
		de=de->getNext();
		//Debug.println(de);
	} while (de!=startDe);
}

/*private*/
bool
ConnectedInteriorTester::hasUnvisitedShellEdge(std::vector<EdgeRing*> *edgeRings)
{

#if GEOS_DEBUG
	cerr << "hasUnvisitedShellEdge called with " << edgeRings->size() << " edgeRings." << endl;
#endif

	for(std::vector<EdgeRing*>::iterator
		it=edgeRings->begin(), itEnd=edgeRings->end();
		it != itEnd;
		++it)
	{
		EdgeRing *er=*it;
		assert(er);

		// don't check hole rings
		if (er->isHole()) continue;

		std::vector<DirectedEdge*>& edges=er->getEdges();
		DirectedEdge *de=edges[0];
		assert(de);

		// don't check CW rings which are holes
		// (MD - this check may now be irrelevant - 2006-03-09)
		assert(de->getLabel());
		if (de->getLabel()->getLocation(0, Position::RIGHT) != Location::INTERIOR) continue;

		/*
		 * the edgeRing is CW ring which surrounds the INT
		 * of the area, so check all edges have been visited. 
		 * If any are unvisited, this is a disconnected part
		 * of the interior
		 */
		for(std::vector<DirectedEdge*>::iterator
			jt=edges.begin(), jtEnd=edges.end();
			jt != jtEnd;
			++jt)
		{
			de=*jt;
			assert(de);
			//Debug.print("visted? "); Debug.println(de);
			if (!de->isVisited()) {
				//Debug.print("not visited "); Debug.println(de);
				disconnectedRingcoord=de->getCoordinate();
				return true;
			}
		}
	}
	return false;
}

} // namespace GEOMETRY.operation.valid
} // namespace GEOMETRY.operation
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.29  2006/06/12 11:29:24  strk
 * unsigned int => size_t
 *
 * Revision 1.28  2006/04/06 12:45:28  strk
 * Delayed deletion of newly allocated MaximalEdgeRings.
 * Existing 'valid' operation tests don't should instability with
 * this patch.
 *
 * Revision 1.27  2006/03/29 13:53:59  strk
 * EdgeRing equipped with Invariant testing function and lots of exceptional assertions. Removed useless heap allocations, and pointers usages.
 *
 * Revision 1.26  2006/03/27 16:02:34  strk
 * Added INL file for MinimalEdgeRing, added many debugging blocks,
 * fixed memory leak in ConnectedInteriorTester (bug #59)
 *
 * Revision 1.25  2006/03/27 14:20:46  strk
 * Added paranoid assertion checking and a note in header about responsibility of return from buildMaximalEdgeRings()
 *
 * Revision 1.24  2006/03/20 16:57:44  strk
 * spatialindex.h and opValid.h headers split
 *
 * Revision 1.23  2006/03/17 16:48:55  strk
 * LineIntersector and PointLocator made complete components of RelateComputer
 * (were statics const pointers before). Reduced inclusions from opRelate.h
 * and opValid.h, updated .cpp files to allow build.
 *
 **********************************************************************/
