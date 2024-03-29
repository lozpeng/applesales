/**********************************************************************
 * $Id: PolygonizeDirectedEdge.h 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2006 Refractions Research Inc.
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/


#ifndef GEOS_OP_POLYGONIZE_POLYGONIZEDIRECTEDEDGE_H
#define GEOS_OP_POLYGONIZE_POLYGONIZEDIRECTEDEDGE_H

#include <Geometry/planargraph/DirectedEdge.h> // for inheritance

// Forward declarations
namespace GEOMETRY {
	namespace geom { 
		//class LineString;
	}
	namespace planargraph { 
		class Node;
	}
	namespace operation { 
		namespace polygonize { 
			class EdgeRing;
		}
	}
}

namespace GEOMETRY {
namespace operation { // GEOMETRY::operation
namespace polygonize { // GEOMETRY::operation::polygonize

/** \brief
 * A DirectedEdge of a PolygonizeGraph, which represents
 * an edge of a polygon formed by the graph.
 *
 * May be logically deleted from the graph by setting the
 * <code>marked</code> flag.
 */
class PolygonizeDirectedEdge: public planargraph::DirectedEdge {

private:

	EdgeRing *edgeRing;

	PolygonizeDirectedEdge *next;

	long label;

public:

	/*
	 * \brief
	 * Constructs a directed edge connecting the <code>from</code> node
	 * to the <code>to</code> node.
	 *
	 * @param directionPt
	 *    specifies this DirectedEdge's direction (given by an imaginary
	 *    line from the <code>from</code> node to <code>directionPt</code>)
	 *
	 * @param edgeDirection
	 *    whether this DirectedEdge's direction is the same as or
	 *    opposite to that of the parent Edge (if any)
	 */
	PolygonizeDirectedEdge(planargraph::Node *newFrom,
			planargraph::Node *newTo,
			const geom::Coordinate& newDirectionPt,
			bool nEdgeDirection);

	/*
	 * Returns the identifier attached to this directed edge.
	 */
	long getLabel() const;

	/*
	 * Attaches an identifier to this directed edge.
	 */
	void setLabel(long newLabel);

	/*
	 * Returns the next directed edge in the EdgeRing that this
	 * directed edge is a member of.
	 */
	PolygonizeDirectedEdge* getNext() const;

	/*
	 * Sets the next directed edge in the EdgeRing that this
	 * directed edge is a member of.
	 */
	void setNext(PolygonizeDirectedEdge *newNext);

	/*
	 * Returns the ring of directed edges that this directed edge is
	 * a member of, or null if the ring has not been set.
	 * @see #setRing(EdgeRing)
	 */
	bool isInRing() const;

	/*
	 * Sets the ring of directed edges that this directed edge is
	 * a member of.
	 */
	void setRing(EdgeRing *newEdgeRing);
};
} // namespace GEOMETRY::operation::polygonize
} // namespace GEOMETRY::operation
} // namespace GEOMETRY

#endif // GEOS_OP_POLYGONIZE_POLYGONIZEDIRECTEDEDGE_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/22 11:19:06  strk
 * opPolygonize.h headers split.
 *
 **********************************************************************/
