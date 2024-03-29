/**********************************************************************
 * $Id: QuadtreeNestedRingTester.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_OP_QUADTREENESTEDRINGTESTER_H
#define GEOS_OP_QUADTREENESTEDRINGTESTER_H

#include <Geometry/geom/Envelope.h> // for composition

#include <vector>

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class LinearRing;
		class Coordinate;
	}
	namespace index {
		namespace quadtree {
			class Quadtree;
		}
	}
	namespace geomgraph {
		class GeometryGraph;
	}
}

namespace GEOMETRY {
namespace operation { // GEOMETRY::operation
namespace valid { // GEOMETRY::operation::valid

/** \brief
 * Tests whether any of a set of {@link LinearRing}s are
 * nested inside another ring in the set, using a {@link Quadtree}
 * index to speed up the comparisons.
 *
 */
class QuadtreeNestedRingTester {
public:

	/// Caller retains ownership of GeometryGraph
	QuadtreeNestedRingTester(geomgraph::GeometryGraph* newGraph);

	~QuadtreeNestedRingTester();

	/*
	 * Be aware that the returned Coordinate (if != NULL)
	 * will point to storage owned by one of the LinearRing
	 * previously added. If you destroy them, this
	 * will point to an invalid memory address.
	 */
	geom::Coordinate* getNestedPoint();

	void add(const geom::LinearRing* ring);

	bool isNonNested();

private:

	geomgraph::GeometryGraph* graph;  // used to find non-node vertices

	std::vector<const geom::LinearRing*> rings;

	geom::Envelope totalEnv;

	index::quadtree::Quadtree* qt;

	geom::Coordinate* nestedPt;

	void buildQuadtree();
};

} // namespace GEOMETRY::operation::valid
} // namespace GEOMETRY::operation
} // namespace GEOMETRY

#endif // GEOS_OP_QUADTREENESTEDRINGTESTER_H

/**********************************************************************
 * $Log$
 * Revision 1.2  2006/03/29 11:48:53  strk
 * Removed useless heap allocations in construction, enforced const correctness
 *
 * Revision 1.1  2006/03/20 16:57:44  strk
 * spatialindex.h and opValid.h headers split
 *
 **********************************************************************/

