/**********************************************************************
 * $Id: MCPointInRing.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_ALGORITHM_MCPOINTINRING_H
#define GEOS_ALGORITHM_MCPOINTINRING_H

#include <Geometry/index/chain/MonotoneChainSelectAction.h> // for inheritance
#include <Geometry/algorithm/PointInRing.h> // for inheritance
#include <Geometry/geom/Coordinate.h> // for composition
#include <Geometry/index/bintree/Interval.h> // for composition

#include <vector>

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class Coordinate;
		class LineSegment;
		class LinearRing;
		class CoordinateSequence;
		class CoordinateSequence;
	}
	namespace index {
		namespace bintree {
			class Bintree;
			class Interval;
		}
		namespace chain {
			class MonotoneChain;
		}
	}
}

namespace GEOMETRY {
namespace algorithm { // GEOMETRY::algorithm

class MCPointInRing: public PointInRing {
public:
	MCPointInRing(const geom::LinearRing *newRing);
	~MCPointInRing();
	bool isInside(const geom::Coordinate& pt);
	void testLineSegment(geom::Coordinate& p, geom::LineSegment *seg);

	class MCSelecter: public index::chain::MonotoneChainSelectAction {
	using MonotoneChainSelectAction::select;
	private:
		geom::Coordinate p;
		MCPointInRing *parent;
	public:
		MCSelecter(const geom::Coordinate& newP, MCPointInRing *prt);
		void select(geom::LineSegment *ls);
	};

private:
	const geom::LinearRing *ring;
	index::bintree::Interval interval;
	geom::CoordinateSequence *pts;
	index::bintree::Bintree *tree;
	int crossings;  // number of segment/ray crossings
	void buildIndex();
	void testMonotoneChain(geom::Envelope *rayEnv,
			MCSelecter *mcSelecter,
			index::chain::MonotoneChain *mc);
};

} // namespace GEOMETRY::algorithm
} // namespace GEOMETRY

#endif // GEOS_ALGORITHM_MCPOINTINRING_H

/**********************************************************************
 * $Log$
 * Revision 1.4  2006/03/29 11:52:00  strk
 * const correctness, useless heap allocations removal
 *
 * Revision 1.3  2006/03/22 18:12:31  strk
 * indexChain.h header split.
 *
 * Revision 1.2  2006/03/22 16:01:33  strk
 * indexBintree.h header split, classes renamed to match JTS
 *
 * Revision 1.1  2006/03/09 16:46:48  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/

