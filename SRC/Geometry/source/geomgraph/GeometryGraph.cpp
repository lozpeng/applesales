/**********************************************************************
 * $Id: GeometryGraph.cpp 2519 2009-05-27 18:11:14Z pramsey $
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
 **********************************************************************/

#include <Geometry/algorithm/CGAlgorithms.h>

#include <Geometry/util/UnsupportedOperationException.h>

#include <Geometry/geomgraph/GeometryGraph.h>
#include <Geometry/geomgraph/Node.h>
#include <Geometry/geomgraph/Edge.h>
#include <Geometry/geomgraph/Label.h>
#include <Geometry/geomgraph/Position.h>

#include <Geometry/geomgraph/index/SimpleMCSweepLineIntersector.h> 
#include <Geometry/geomgraph/index/SegmentIntersector.h> 
#include <Geometry/geomgraph/index/EdgeSetIntersector.h>

#include <Geometry/geom/CoordinateArraySequence.h> 
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/Location.h>
#include <Geometry/geom/Point.h>
#include <Geometry/geom/LinearRing.h>
#include <Geometry/geom/LineString.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/MultiPoint.h>
#include <Geometry/geom/MultiLineString.h>
#include <Geometry/geom/MultiPolygon.h>
#include <Geometry/geom/GeometryCollection.h>

#include <Geometry/inline.h>

#include <vector>
#include <memory> // auto_ptr
#include <cassert>
#include <typeinfo>

#ifndef GEOS_DEBUG
#define GEOS_DEBUG 0
#endif

#ifndef GEOS_INLINE
# include "Geometry/geomgraph/GeometryGraph.inl"
#endif

using namespace std;
using namespace GEOMETRY::geomgraph::index;
using namespace GEOMETRY::algorithm;
using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace geomgraph { // geos.geomgraph

/*
 * This method implements the Boundary Determination Rule
 * for determining whether
 * a component (node or edge) that appears multiple times in elements
 * of a MultiGeometry is in the boundary or the interior of the Geometry
 * 
 * The SFS uses the "Mod-2 Rule", which this function implements
 * 
 * An alternative (and possibly more intuitive) rule would be
 * the "At Most One Rule":
 *    isInBoundary = (componentCount == 1)
 */
bool
GeometryGraph::isInBoundary(int boundaryCount)
{
	// the "Mod-2 Rule"
	return boundaryCount%2==1;
}

int
GeometryGraph::determineBoundary(int boundaryCount)
{
	return isInBoundary(boundaryCount)?Location::BOUNDARY : Location::INTERIOR;
}


EdgeSetIntersector*
GeometryGraph::createEdgeSetIntersector()
{
	// various options for computing intersections, from slowest to fastest

	//private EdgeSetIntersector esi = new SimpleEdgeSetIntersector();
	//private EdgeSetIntersector esi = new MonotoneChainIntersector();
	//private EdgeSetIntersector esi = new NonReversingChainIntersector();
	//private EdgeSetIntersector esi = new SimpleSweepLineIntersector();
	//private EdgeSetIntersector esi = new MCSweepLineIntersector();

	//return new SimpleEdgeSetIntersector();
	return new SimpleMCSweepLineIntersector();
}

/*public*/
vector<Node*>*
GeometryGraph::getBoundaryNodes()
{
	if ( ! boundaryNodes.get() )
	{
		boundaryNodes.reset(new vector<Node*>());
		getBoundaryNodes(*(boundaryNodes.get()));
	}
	return boundaryNodes.get();
}

/*public*/
CoordinateSequence*
GeometryGraph::getBoundaryPoints()
{

	if ( ! boundaryPoints.get() ) 
	{
		// Collection will be destroied by GeometryGraph dtor
		vector<Node*>* coll = getBoundaryNodes();
		boundaryPoints.reset(new CoordinateArraySequence(coll->size()));
		size_t i=0;
		for (vector<Node*>::iterator it=coll->begin(), endIt=coll->end();
			it!=endIt; ++it)
		{
			Node *node=*it;
			boundaryPoints->setAt(node->getCoordinate(), i++);
		}
	}

	// We keep ownership of this, will be destroyed by destructor
	return boundaryPoints.get();
}

Edge*
GeometryGraph::findEdge(const LineString *line)
{
	return lineEdgeMap.find(line)->second;
}

void
GeometryGraph::computeSplitEdges(vector<Edge*> *edgelist)
{
#if GEOS_DEBUG
	cerr<<"["<<this<<"] GeometryGraph::computeSplitEdges() scanning "<<edges->size()<<" local and "<<edgelist->size()<<" provided edges"<<endl;
#endif
	for (vector<Edge*>::iterator i=edges->begin(), endIt=edges->end();
		i!=endIt; ++i)
	{
		Edge *e=*i;
#if GEOS_DEBUG
		cerr<<"   "<<e->print()<<" adding split edges from arg"<<endl;
#endif
		e->eiList.addSplitEdges(edgelist);
	}
}

void
GeometryGraph::add(const Geometry *g)
	//throw (UnsupportedOperationException *)
{
	if (g->isEmpty()) return;
	// check if this Geometry should obey the Boundary Determination Rule
	// all collections except MultiPolygons obey the rule
    // FIXME - mloskot: Make this condition readable and use paranthesis
	if ((typeid(*g)==typeid(GeometryCollection)) ||
			   (typeid(*g)==typeid(MultiPoint)) ||
			   (typeid(*g)==typeid(MultiLineString)) &&
			   !(typeid(*g)==typeid(MultiPolygon)))
			useBoundaryDeterminationRule=true;
	if (typeid(*g)==typeid(Polygon))
		addPolygon((Polygon*) g);
	else if (typeid(*g)==typeid(LineString))
		addLineString((LineString*) g);
	else if (typeid(*g)==typeid(LinearRing))
		addLineString((LineString*) g);
	else if (typeid(*g)==typeid(Point))
		addPoint((Point*) g);
	else if (typeid(*g)==typeid(MultiPoint))
		addCollection((MultiPoint*) g);
	else if (typeid(*g)==typeid(MultiLineString))
		addCollection((MultiLineString*) g);
	else if (typeid(*g)==typeid(MultiPolygon))
		addCollection((MultiPolygon*) g);
	else if (typeid(*g)==typeid(GeometryCollection))
		addCollection((GeometryCollection*) g);
	else {
		string out=typeid(*g).name();
		throw util::UnsupportedOperationException("GeometryGraph::add(Geometry *): unknown geometry type: "+out);
	}
}

void
GeometryGraph::addCollection(const GeometryCollection *gc)
{
	for (size_t i=0, n=gc->getNumGeometries(); i<n; ++i)
	{
		const Geometry *g=gc->getGeometryN(i);
		add(g);
	}
}

/*
 * Add a Point to the graph.
 */
void
GeometryGraph::addPoint(const Point *p)
{
	const Coordinate& coord=*(p->getCoordinate());
	insertPoint(argIndex, coord, Location::INTERIOR);
}

/*
 * The left and right topological location arguments assume that the ring
 * is oriented CW.
 * If the ring is in the opposite orientation,
 * the left and right locations must be interchanged.
 */
void
GeometryGraph::addPolygonRing(const LinearRing *lr, int cwLeft, int cwRight)
	// throw IllegalArgumentException (see below)
{
	// skip empty component (see bug #234) 
	if ( lr->isEmpty() ) return; 
	const CoordinateSequence *lrcl = lr->getCoordinatesRO(); 	
	CoordinateSequence* coord=CoordinateSequence::removeRepeatedPoints(lrcl);
	if (coord->getSize()<4) {
		hasTooFewPointsVar=true;
		invalidPoint=coord->getAt(0); // its now a Coordinate
		delete coord;
		return;
	}
	int left=cwLeft;
	int right=cwRight;

	/*
	 * the isCCW call might throw an
	 * IllegalArgumentException if degenerate ring does
	 * not contain 3 distinct points.
	 */
	try
	{
		if (CGAlgorithms::isCCW(coord)) {
			left=cwRight;
			right=cwLeft;
		}
	}
	catch(...)
	{
		delete coord;
		throw;
	}

	Edge *e=new Edge(coord,new Label(argIndex,Location::BOUNDARY,left,right));
	lineEdgeMap[lr]=e;
	insertEdge(e);
	insertPoint(argIndex,coord->getAt(0), Location::BOUNDARY);
}

void
GeometryGraph::addPolygon(const Polygon *p)
{
	const LineString* ls;
	const LinearRing* lr;

	ls = p->getExteriorRing();
	assert(dynamic_cast<const LinearRing*>(ls));
	lr = static_cast<const LinearRing*>(ls);
	addPolygonRing(lr, Location::EXTERIOR, Location::INTERIOR);
	for (size_t i=0, n=p->getNumInteriorRing(); i<n; ++i)
	{
		// Holes are topologically labelled opposite to the shell, since
		// the interior of the polygon lies on their opposite side
		// (on the left, if the hole is oriented CW)
		ls = p->getInteriorRingN(i);
		assert(dynamic_cast<const LinearRing*>(ls));
		lr = static_cast<const LinearRing*>(ls);
		addPolygonRing(lr, Location::INTERIOR, Location::EXTERIOR);
	}
}

void
GeometryGraph::addLineString(const LineString *line)
{
	CoordinateSequence* coord=CoordinateSequence::removeRepeatedPoints(line->getCoordinatesRO());
	if(coord->getSize()<2) {
		hasTooFewPointsVar=true;
		invalidPoint=coord->getAt(0);
		delete coord;
		return;
	}

	Edge *e=new Edge(coord,new Label(argIndex,Location::INTERIOR));
	lineEdgeMap[line]=e;
	insertEdge(e);

	/*
	 * Add the boundary points of the LineString, if any.
	 * Even if the LineString is closed, add both points as if they
	 * were endpoints.
	 * This allows for the case that the node already exists and is
	 * a boundary point.
	 */
	assert(coord->size() >= 2); // found LineString with single point
	insertBoundaryPoint(argIndex, coord->getAt(0));
	insertBoundaryPoint(argIndex, coord->getAt(coord->getSize()-1));
}

/*
 * Add an Edge computed externally.  The label on the Edge is assumed
 * to be correct.
 */
void
GeometryGraph::addEdge(Edge *e)
{
	insertEdge(e);
	const CoordinateSequence* coord=e->getCoordinates();
	// insert the endpoint as a node, to mark that it is on the boundary
	insertPoint(argIndex,coord->getAt(0),Location::BOUNDARY);
	insertPoint(argIndex,coord->getAt(coord->getSize()-1),Location::BOUNDARY);
}

/*
 * Add a point computed externally.  The point is assumed to be a
 * Point Geometry part, which has a location of INTERIOR.
 */
void
GeometryGraph::addPoint(Coordinate& pt)
{
	insertPoint(argIndex,pt,Location::INTERIOR);
}

/*public*/
SegmentIntersector*
GeometryGraph::computeSelfNodes(LineIntersector *li, bool computeRingSelfNodes)
{
	SegmentIntersector *si=new SegmentIntersector(li,true,false);
    	auto_ptr<EdgeSetIntersector> esi(createEdgeSetIntersector());
	// optimized test for Polygons and Rings
	if (parentGeom==NULL)
	{
		esi->computeIntersections(edges,si,true);
	}
	else if (!computeRingSelfNodes & (typeid(*parentGeom)==typeid(LinearRing)||typeid(*parentGeom)==typeid(Polygon)||typeid(*parentGeom)==typeid(MultiPolygon)))
	{
		esi->computeIntersections(edges, si, false);
	}
	else
	{
		esi->computeIntersections(edges, si, true);
	}

#if GEOS_DEBUG
	cerr << "SegmentIntersector # tests = " << si->numTests << endl;
#endif // GEOS_DEBUG

	addSelfIntersectionNodes(argIndex);
	return si;
}

SegmentIntersector*
GeometryGraph::computeEdgeIntersections(GeometryGraph *g,
	LineIntersector *li, bool includeProper)
{
#if GEOS_DEBUG
	cerr<<"GeometryGraph::computeEdgeIntersections call"<<endl;
#endif
	SegmentIntersector *si=new SegmentIntersector(li, includeProper, true);
	newSegmentIntersectors.push_back(si);

	si->setBoundaryNodes(getBoundaryNodes(), g->getBoundaryNodes());
	auto_ptr<EdgeSetIntersector> esi(createEdgeSetIntersector());
	esi->computeIntersections(edges, g->edges, si);
#if GEOS_DEBUG
	cerr<<"GeometryGraph::computeEdgeIntersections returns"<<endl;
#endif
	return si;
}

void
GeometryGraph::insertPoint(int argIndex, const Coordinate& coord,
	int onLocation)
{
#if GEOS_DEBUG
	cerr<<"GeometryGraph::insertPoint("<<coord.toString()<<" called"<<endl;
#endif
	Node *n=nodes->addNode(coord);
	Label *lbl=n->getLabel();
	if (lbl==NULL)
	{
		n->setLabel(argIndex, onLocation);
	}
	else
	{
		lbl->setLocation(argIndex, onLocation);
	}
}

/*
 * Adds points using the mod-2 rule of SFS.  This is used to add the boundary
 * points of dim-1 geometries (Curves/MultiCurves).  According to the SFS,
 * an endpoint of a Curve is on the boundary
 * iff if it is in the boundaries of an odd number of Geometries
 */
void
GeometryGraph::insertBoundaryPoint(int argIndex,const Coordinate& coord)
{
	Node *n=nodes->addNode(coord);
	Label *lbl=n->getLabel();

	// the new point to insert is on a boundary
	int boundaryCount=1;
	// determine the current location for the point (if any)
	int loc=Location::UNDEF;
	if (lbl!=NULL) loc=lbl->getLocation(argIndex,Position::ON);
	if (loc==Location::BOUNDARY) boundaryCount++;

	// determine the boundary status of the point according to the
	// Boundary Determination Rule
	int newLoc=determineBoundary(boundaryCount);
	lbl->setLocation(argIndex,newLoc);
}

/*private*/
void
GeometryGraph::addSelfIntersectionNodes(int argIndex)
{
	for (vector<Edge*>::iterator i=edges->begin(), endIt=edges->end();
		i!=endIt; ++i)
	{
		Edge *e=*i;
		int eLoc=e->getLabel()->getLocation(argIndex);
		EdgeIntersectionList &eiL=e->eiList;
		for (EdgeIntersectionList::iterator
			eiIt=eiL.begin(), eiEnd=eiL.end();
			eiIt!=eiEnd; ++eiIt)
		{
			EdgeIntersection *ei=*eiIt;
			addSelfIntersectionNode(argIndex, ei->coord, eLoc);
		}
	}
}

/*private*/
void
GeometryGraph::addSelfIntersectionNode(int argIndex,
	const Coordinate& coord, int loc)
{
	// if this node is already a boundary node, don't change it
	if (isBoundaryNode(argIndex,coord)) return;
	if (loc==Location::BOUNDARY && useBoundaryDeterminationRule)
	{
		insertBoundaryPoint(argIndex,coord);
	}
	else
	{
		insertPoint(argIndex,coord,loc);
	}
}

vector<Edge*> *
GeometryGraph::getEdges()
{
	return edges;
}

bool
GeometryGraph::hasTooFewPoints()
{
	return hasTooFewPointsVar;
}

const Coordinate&
GeometryGraph::getInvalidPoint()
{
	return invalidPoint;
}

} // namespace GEOMETRY.geomgraph
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.30  2006/06/13 21:40:06  strk
 * Cleanups and some more debugging lines
 *
 * Revision 1.29  2006/06/12 11:29:23  strk
 * unsigned int => size_t
 *
 * Revision 1.28  2006/06/09 07:42:13  strk
 * * source/geomgraph/GeometryGraph.cpp, source/operation/buffer/OffsetCurveSetBuilder.cpp, source/operation/overlay/OverlayOp.cpp, source/operation/valid/RepeatedPointTester.cpp: Fixed warning after Polygon ring accessor methods changed to work with size_t. Small optimizations in loops.
 *
 * Revision 1.27  2006/04/07 09:54:30  strk
 * Geometry::getNumGeometries() changed to return 'unsigned int'
 * rather then 'int'
 *
 * Revision 1.26  2006/03/29 15:23:49  strk
 * Moved GeometryGraph inlines from .h to .inl file
 *
 * Revision 1.25  2006/03/15 17:16:29  strk
 * streamlined headers inclusion
 *
 **********************************************************************/


