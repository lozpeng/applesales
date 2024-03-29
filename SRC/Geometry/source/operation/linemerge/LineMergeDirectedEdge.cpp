/**********************************************************************
 * $Id: LineMergeDirectedEdge.cpp 1820 2006-09-06 16:54:23Z mloskot $
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

#include <Geometry/operation/linemerge/LineMergeDirectedEdge.h>
#include <Geometry/planargraph/DirectedEdge.h>
#include <Geometry/planargraph/Node.h>

#include <cassert>

//using namespace GEOMETRY::planargraph;
using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace operation { // geos.operation
namespace linemerge { // geos.operation.linemerge

LineMergeDirectedEdge::LineMergeDirectedEdge(
		planargraph::Node *newFrom,
		planargraph::Node *newTo,
		const Coordinate& newDirectionPt,
		bool nEdgeDirection)
	:
	planargraph::DirectedEdge(newFrom, newTo,
			newDirectionPt, nEdgeDirection)
{}

/**
 * Returns the directed edge that starts at this directed edge's end point,
 * or null if there are zero or multiple directed edges starting there.  
 * @return
 */
LineMergeDirectedEdge*
LineMergeDirectedEdge::getNext()
{
	if (getToNode()->getDegree()!=2) {
		return NULL;
	}
	if (getToNode()->getOutEdges()->getEdges()[0]==getSym()) {
		return (LineMergeDirectedEdge*) getToNode()->getOutEdges()->getEdges()[1];
	}
	assert(getToNode()->getOutEdges()->getEdges()[1]==getSym());

	LineMergeDirectedEdge* nextedge = dynamic_cast<LineMergeDirectedEdge*>(getToNode()->getOutEdges()->getEdges()[0]);
	assert(nextedge);

	return nextedge;
}

} // namespace GEOMETRY.operation.linemerge
} // namespace GEOMETRY.operation
} //namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.8  2006/03/22 10:13:54  strk
 * opLinemerge.h split
 *
 * Revision 1.7  2006/03/21 21:42:54  strk
 * planargraph.h header split, planargraph:: classes renamed to match JTS symbols
 *
 **********************************************************************/

