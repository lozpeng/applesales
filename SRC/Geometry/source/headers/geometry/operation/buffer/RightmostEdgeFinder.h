/**********************************************************************
 * $Id: RightmostEdgeFinder.h 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: operation/buffer/RightmostEdgeFinder.java rev. 1.13 (JTS-1.7)
 *
 **********************************************************************/

#ifndef GEOS_OP_BUFFER_RIGHTMOSTEDGEFINDER_H
#define GEOS_OP_BUFFER_RIGHTMOSTEDGEFINDER_H

#include <Geometry/geom/Coordinate.h> // for composition

#include <vector>

// Forward declarations
namespace GEOMETRY {
	namespace geom {
	}
	namespace geomgraph {
		class DirectedEdge;
	}
}

namespace GEOMETRY {
namespace operation { // geos.operation
namespace buffer { // geos.operation.buffer

/**
 * \brief
 * A RightmostEdgeFinder find the geomgraph::DirectedEdge in a list which has
 * the highest coordinate, and which is oriented L to R at that point.
 * (I.e. the right side is on the RHS of the edge.)
 */
class RightmostEdgeFinder {

private:

	int minIndex;

	geom::Coordinate minCoord;

	geomgraph::DirectedEdge *minDe;

	geomgraph::DirectedEdge *orientedDe;

	void findRightmostEdgeAtNode();

	void findRightmostEdgeAtVertex();

	void checkForRightmostCoordinate(geomgraph::DirectedEdge *de);

	int getRightmostSide(geomgraph::DirectedEdge *de, int index);

	int getRightmostSideOfSegment(geomgraph::DirectedEdge *de, int i);

public:

	/** \brief
	 * A RightmostEdgeFinder finds the geomgraph::DirectedEdge with the
	 * rightmost coordinate.
	 *
	 * The geomgraph::DirectedEdge returned is guaranteed to have the R of
	 * the world on its RHS.
	 */
	RightmostEdgeFinder();

	geomgraph::DirectedEdge* getEdge();

	geom::Coordinate& getCoordinate();

	/// Note that only Forward DirectedEdges will be checked
	void findEdge(std::vector<geomgraph::DirectedEdge*>* dirEdgeList);
};

/*public*/
inline geomgraph::DirectedEdge*
RightmostEdgeFinder::getEdge()
{
	return orientedDe;
}

/*public*/
inline geom::Coordinate&
RightmostEdgeFinder::getCoordinate()
{
	return minCoord;
}




} // namespace GEOMETRY::operation::buffer
} // namespace GEOMETRY::operation
} // namespace GEOMETRY

#endif // ndef GEOS_OP_BUFFER_RIGHTMOSTEDGEFINDER_H

/**********************************************************************
 * $Log$
 * Revision 1.3  2006/05/04 12:19:59  strk
 * Added note about findEdge() only scanning for forward DirectedEdges
 *
 * Revision 1.2  2006/04/05 09:20:25  strk
 * Added port informations and many assertion checking.
 * Fixed bug in getRightmostSide() method ( a "testing-only" corner case )
 *
 * Revision 1.1  2006/03/14 00:19:40  strk
 * opBuffer.h split, streamlined headers in some (not all) files in operation/buffer/
 *
 **********************************************************************/

