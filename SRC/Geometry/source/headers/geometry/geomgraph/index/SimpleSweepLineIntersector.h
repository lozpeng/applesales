/**********************************************************************
 * $Id: SimpleSweepLineIntersector.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOMETRY_GEOMGRAPH_INDEX_SIMPLESWEEPLINEINTERSECTOR_H
#define GEOMETRY_GEOMGRAPH_INDEX_SIMPLESWEEPLINEINTERSECTOR_H

#include <vector>

#include <Geometry/geomgraph/index/EdgeSetIntersector.h> // for inheritance

// Forward declarations
namespace GEOMETRY {
	namespace geomgraph {
		class Edge;
		namespace index {
			class SegmentIntersector;
			class SweepLineEvent;
		}
	}
}

namespace GEOMETRY {
namespace geomgraph { // GEOMETRY::geomgraph
namespace index { // GEOMETRY::geomgraph::index

/** \brief
 * Finds all intersections in one or two sets of edges,
 * using a simple x-axis sweepline algorithm.
 *
 * While still O(n^2) in the worst case, this algorithm
 * drastically improves the average-case time.
 */
class SimpleSweepLineIntersector: public EdgeSetIntersector {

public:

	SimpleSweepLineIntersector();

	virtual ~SimpleSweepLineIntersector();

	void computeIntersections(std::vector<Edge*> *edges,
			SegmentIntersector *si,
			bool testAllSegments);

	void computeIntersections(std::vector<Edge*> *edges0,
			std::vector<Edge*> *edges1,
			SegmentIntersector *si);

private:

	void add(std::vector<Edge*> *edges);

	std::vector<SweepLineEvent*> events;

	// statistics information
	int nOverlaps;

	void add(std::vector<Edge*> *edges, void* edgeSet);

	void add(Edge *edge,void* edgeSet);

	void prepareEvents();

	void computeIntersections(SegmentIntersector *si);

	void processOverlaps(int start, int end, SweepLineEvent *ev0,
			SegmentIntersector *si);
};




} // namespace GEOMETRY.geomgraph.index
} // namespace GEOMETRY.geomgraph
} // namespace GEOMETRY

#endif // GEOS_GEOMGRAPH_INDEX_SIMPLESWEEPLINEINTERSECTOR_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/14 12:55:55  strk
 * Headers split: geomgraphindex.h, nodingSnapround.h
 *
 **********************************************************************/

