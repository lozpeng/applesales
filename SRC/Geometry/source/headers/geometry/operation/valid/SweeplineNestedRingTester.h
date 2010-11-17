/**********************************************************************
 * $Id: SweeplineNestedRingTester.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_OP_SWEEPLINENESTEDRINGTESTER_H
#define GEOS_OP_SWEEPLINENESTEDRINGTESTER_H

#include <vector>

#include <Geometry/geom/Envelope.h> // for inline
//#include <Geometry/indexSweepline.h> // for inline and inheritance 
#include <Geometry/index/sweepline/SweepLineOverlapAction.h> // for inheritance
#include <Geometry/index/sweepline/SweepLineIndex.h> // for inlines

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class LinearRing;
		class Envelope;
		class Coordinate;
	}
	namespace index {
		namespace sweepline {
			class SweepLineIndex;
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
 * nested inside another ring in the set, using an
 * index::sweepline::SweepLineIndex to speed up the comparisons.
 */
class SweeplineNestedRingTester {

private:
	geomgraph::GeometryGraph *graph;  // used to find non-node vertices
	std::vector<geom::LinearRing*> rings;
	geom::Envelope *totalEnv;
	index::sweepline::SweepLineIndex *sweepLine;
	geom::Coordinate *nestedPt;
	void buildIndex();

public:

	SweeplineNestedRingTester(geomgraph::GeometryGraph *newGraph)
		:
		graph(newGraph),
		rings(),
		totalEnv(new geom::Envelope()),
		sweepLine(new index::sweepline::SweepLineIndex()),
		nestedPt(NULL)
	{}

	~SweeplineNestedRingTester()
	{
		delete totalEnv;
		delete sweepLine;
	}

	/*
	 * Be aware that the returned Coordinate (if != NULL)
	 * will point to storage owned by one of the LinearRing
	 * previously added. If you destroy them, this
	 * will point to an invalid memory address.
	 */
	geom::Coordinate *getNestedPoint() { return nestedPt; }

	void add(geom::LinearRing* ring) {
		rings.push_back(ring);
	}

	bool isNonNested();
	bool isInside(geom::LinearRing *innerRing, geom::LinearRing *searchRing);
	class OverlapAction: public index::sweepline::SweepLineOverlapAction {
	public:
		bool isNonNested;
		OverlapAction(SweeplineNestedRingTester *p);
		void overlap(index::sweepline::SweepLineInterval *s0,
				index::sweepline::SweepLineInterval *s1);
	private:
		SweeplineNestedRingTester *parent;
	};
};


} // namespace GEOMETRY::operation::valid
} // namespace GEOMETRY::operation
} // namespace GEOMETRY

#endif // GEOS_OP_SWEEPLINENESTEDRINGTESTER_H

/**********************************************************************
 * $Log$
 * Revision 1.2  2006/06/01 10:28:47  strk
 * Reduced number of installed headers for the GEOMETRY::index namespace
 *
 * Revision 1.1  2006/03/20 16:57:44  strk
 * spatialindex.h and opValid.h headers split
 *
 **********************************************************************/

