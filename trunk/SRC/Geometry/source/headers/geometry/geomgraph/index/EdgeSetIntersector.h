/**********************************************************************
 * $Id: EdgeSetIntersector.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOMETRY_GEOMGRAPH_INDEX_EDGESETINTERSECTOR_H
#define GEOMETRY_GEOMGRAPH_INDEX_EDGESETINTERSECTOR_H

#include <vector>

// Forward declarations
namespace GEOMETRY {
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

/* 
 * This is derived from a Java interface.
 */
class EdgeSetIntersector {
public:
	/**
	 * Computes all self-intersections between edges in a set of edges,
	 * allowing client to choose whether self-intersections are computed.
	 *
	 * @param edges a list of edges to test for intersections
	 * @param si the SegmentIntersector to use
	 * @param testAllSegments true if self-intersections are to be tested as well
	 */
	virtual void computeIntersections(std::vector<Edge*> *edges,
			SegmentIntersector *si, bool testAllSegments)=0;

	/**
	 * Computes all mutual intersections between two sets of edges
	 */
	virtual void computeIntersections(std::vector<Edge*> *edges0,
			std::vector<Edge*> *edges1,
			SegmentIntersector *si)=0;

	virtual ~EdgeSetIntersector(){};
};


} // namespace GEOMETRY.geomgraph.index
} // namespace GEOMETRY.geomgraph
} // namespace GEOMETRY

#endif

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/14 12:55:55  strk
 * Headers split: geomgraphindex.h, nodingSnapround.h
 *
 **********************************************************************/
