/**********************************************************************
 * $Id: EdgeEndBundle.cpp 1820 2006-09-06 16:54:23Z mloskot $
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

#include <Geometry/operation/relate/EdgeEndBundle.h>
#include <Geometry/geom/Location.h>
#include <Geometry/geomgraph/Label.h>
#include <Geometry/geomgraph/EdgeEnd.h>
#include <Geometry/geomgraph/Edge.h>
#include <Geometry/geomgraph/GeometryGraph.h>
#include <Geometry/geomgraph/Position.h>

#include <vector>

using namespace std;
using namespace GEOMETRY::geomgraph;
using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace operation { // geos.operation
namespace relate { // geos.operation.relate

EdgeEndBundle::EdgeEndBundle(EdgeEnd *e):
	EdgeEnd(e->getEdge(),e->getCoordinate(),
		e->getDirectedCoordinate(),
		new Label(*(e->getLabel())))
{
	edgeEnds=new vector<EdgeEnd*>();
	insert(e);
}

EdgeEndBundle::~EdgeEndBundle(){
	for(size_t i=0, n=edgeEnds->size(); i<n; i++) {
		delete (*edgeEnds)[i];
	}
	delete edgeEnds;
}

Label* EdgeEndBundle::getLabel(){
	return label;
}

//Not needed
//public Iterator iterator() { return edgeEnds.iterator(); }

vector<EdgeEnd*>* EdgeEndBundle::getEdgeEnds() {
	return edgeEnds;
}

void EdgeEndBundle::insert(EdgeEnd *e){
	// Assert: start point is the same
	// Assert: direction is the same
	edgeEnds->push_back(e);
}
  

/**
* This computes the overall edge label for the set of
* edges in this EdgeStubBundle.  It essentially merges
* the ON and side labels for each edge.  These labels must be compatible
*/
void EdgeEndBundle::computeLabel() {
	// create the label.  If any of the edges belong to areas,
	// the label must be an area label
	bool isArea=false;

	for(vector<EdgeEnd*>::iterator it=edgeEnds->begin(), itEnd=edgeEnds->end();
			it != itEnd; it++)
	{
		EdgeEnd *e=*it;
		if (e->getLabel()->isArea()) isArea=true;
	}
	if (isArea) {
		delete label;
		label=new Label(Location::UNDEF,Location::UNDEF,Location::UNDEF);
	} else {
		delete label;
		label=new Label(Location::UNDEF);
	}
	// compute the On label, and the side labels if present
	for(int i=0;i<2;i++) {
		computeLabelOn(i);
		if (isArea)
			computeLabelSides(i);
	}
}


/**
* Compute the overall ON location for the list of EdgeStubs.
* (This is essentially equivalent to computing the self-overlay of a single Geometry)
* edgeStubs can be either on the boundary (eg Polygon edge)
* OR in the interior (e.g. segment of a LineString)
* of their parent Geometry.
* In addition, GeometryCollections use the mod-2 rule to determine
* whether a segment is on the boundary or not.
* Finally, in GeometryCollections it can still occur that an edge is both
* on the boundary and in the interior (e.g. a LineString segment lying on
* top of a Polygon edge.) In this case as usual the Boundary is given precendence.
* <br>
* These observations result in the following rules for computing the ON location:
* <ul>
* <li> if there are an odd number of Bdy edges, the attribute is Bdy
* <li> if there are an even number >= 2 of Bdy edges, the attribute is Int
* <li> if there are any Int edges, the attribute is Int
* <li> otherwise, the attribute is NULL.
* </ul>
*/
void EdgeEndBundle::computeLabelOn(int geomIndex) {
	// compute the ON location value
	int boundaryCount=0;
	bool foundInterior=false;

	for(vector<EdgeEnd*>::iterator it=edgeEnds->begin();it<edgeEnds->end();it++) {
		EdgeEnd *e=*it;
		int loc=e->getLabel()->getLocation(geomIndex);
		if (loc==Location::BOUNDARY) boundaryCount++;
		if (loc==Location::INTERIOR) foundInterior=true;
	}
	int loc=Location::UNDEF;
	if (foundInterior) loc=Location::INTERIOR;
	if (boundaryCount>0) {
		loc=GeometryGraph::determineBoundary(boundaryCount);
	}
	label->setLocation(geomIndex,loc);
}


/**
* Compute the labelling for each side
*/
void EdgeEndBundle::computeLabelSides(int geomIndex) {
	computeLabelSide(geomIndex,Position::LEFT);
	computeLabelSide(geomIndex,Position::RIGHT);
}

/**
* To compute the summary label for a side, the algorithm is:
*   FOR all edges
*     IF any edge's location is INTERIOR for the side, side location = INTERIOR
*     ELSE IF there is at least one EXTERIOR attribute, side location = EXTERIOR
*     ELSE  side location = NULL
*  <br>
*  Note that it is possible for two sides to have apparently contradictory information
*  i.e. one edge side may indicate that it is in the interior of a geometry, while
*  another edge side may indicate the exterior of the same geometry.  This is
*  not an incompatibility - GeometryCollections may contain two Polygons that touch
*  along an edge.  This is the reason for Interior-primacy rule above - it
*  results in the summary label having the Geometry interior on <b>both</b> sides.
*/
void EdgeEndBundle::computeLabelSide(int geomIndex, int side) {
	for(vector<EdgeEnd*>::iterator it=edgeEnds->begin();it<edgeEnds->end();it++) {
		EdgeEnd *e=*it;
		if (e->getLabel()->isArea()) {
			int loc=e->getLabel()->getLocation(geomIndex,side);
			if (loc==Location::INTERIOR) {
				label->setLocation(geomIndex,side,Location::INTERIOR);
				return;
			} else if (loc==Location::EXTERIOR) {
				label->setLocation(geomIndex,side,Location::EXTERIOR);
			}
		}
	}
}

/**
* Update the IM with the contribution for the computed label for the EdgeStubs.
*/
void EdgeEndBundle::updateIM(IntersectionMatrix *im) {
	Edge::updateIM(label,im);
}

string EdgeEndBundle::print() {
	string out="EdgeEndBundle--> Label: "+label->toString()+"\n";
	for(vector<EdgeEnd*>::iterator it=edgeEnds->begin();it<edgeEnds->end();it++) {
		EdgeEnd *e=*it;
		out+=e->print();
		out+="\n";
	}
	return out;
}

} // namespace GEOMETRY.operation.relate
} // namespace GEOMETRY.operation
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.15  2006/06/12 11:29:24  strk
 * unsigned int => size_t
 *
 * Revision 1.14  2006/03/21 13:11:29  strk
 * opRelate.h header split
 *
 * Revision 1.13  2006/03/17 16:48:55  strk
 * LineIntersector and PointLocator made complete components of RelateComputer
 * (were statics const pointers before). Reduced inclusions from opRelate.h
 * and opValid.h, updated .cpp files to allow build.
 *
 * Revision 1.12  2006/02/19 19:46:50  strk
 * Packages <-> namespaces mapping for most GEOS internal code (uncomplete, but working). Dir-level libs for index/ subdirs.
 *
 **********************************************************************/

