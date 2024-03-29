/**********************************************************************
 * $Id: SweepLineSegment.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOMETRY_GEOMGRAPH_INDEX_SWEEPLINESEGMENT_H
#define GEOMETRY_GEOMGRAPH_INDEX_SWEEPLINESEGMENT_H

#include <Geometry/geomgraph/index/SweepLineEventObj.h> // for inheritance

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class CoordinateSequence;
	}
	namespace geomgraph {
		class Edge;
		namespace index {
			class SegmentIntersector;
		}
	}
}

namespace GEOMETRY {
namespace geomgraph { // GEOMETRY::geomgraph
namespace index { // GEOMETRY::geomgraph::index

class SweepLineSegment: public SweepLineEventOBJ {
public:
	SweepLineSegment(Edge *newEdge, int newPtIndex);
	~SweepLineSegment();
	double getMinX();
	double getMaxX();
	void computeIntersections(SweepLineSegment *ss, SegmentIntersector *si);
protected:
	Edge *edge;
	const geom::CoordinateSequence* pts;
	int ptIndex;
};



} // namespace GEOMETRY.geomgraph.index
} // namespace GEOMETRY.geomgraph
} // namespace GEOMETRY

#endif

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/14 12:55:56  strk
 * Headers split: geomgraphindex.h, nodingSnapround.h
 *
 **********************************************************************/

