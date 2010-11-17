/**********************************************************************
 * $Id: MonotoneChain.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOMETRY_GEOMGRAPH_INDEX_MONOTONECHAIN_H
#define GEOMETRY_GEOMGRAPH_INDEX_MONOTONECHAIN_H

#include <Geometry/geomgraph/index/SweepLineEventObj.h> // for inheritance
#include <Geometry/geomgraph/index/MonotoneChainEdge.h> // for inline

// Forward declarations
namespace GEOMETRY {
	namespace geomgraph {
		class Edge;
		namespace index {
			class SegmentIntersector;
			//class MonotoneChainEdge; 
		}
	}
}

namespace GEOMETRY {
namespace geomgraph { // GEOMETRY::geomgraph
namespace index { // GEOMETRY::geomgraph::index

/**
 * Last port: geomgraph/index/MonotoneChain.java rev. 1.3 (JTS-1.7)
 */
class MonotoneChain: public SweepLineEventOBJ {
private:
	MonotoneChainEdge *mce;
	int chainIndex;

public:

	MonotoneChain(MonotoneChainEdge *newMce, int newChainIndex):
		mce(newMce),
		chainIndex(newChainIndex)
	{}

	~MonotoneChain() {}

	void computeIntersections(MonotoneChain *mc,SegmentIntersector *si) {
		mce->computeIntersectsForChain(chainIndex,*(mc->mce),mc->chainIndex,*si);
	}
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

