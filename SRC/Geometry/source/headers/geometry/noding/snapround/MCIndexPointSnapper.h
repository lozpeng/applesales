/**********************************************************************
 * $Id: MCIndexPointSnapper.h 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2006      Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#ifndef GEOS_NODING_SNAPROUND_MCINDEXPOINTSNAPPER_H
#define GEOS_NODING_SNAPROUND_MCINDEXPOINTSNAPPER_H

#include <Geometry/inline.h>

// Forward declarations
namespace GEOMETRY {
	namespace index {
		class SpatialIndex;
	}
	namespace noding {
		class SegmentString;
		namespace snapround {
			class HotPixel;
		}
	}
}

namespace GEOMETRY {
namespace noding { // GEOMETRY::noding
namespace snapround { // GEOMETRY::noding::snapround

/** \brief
 * "Snaps" all {@link SegmentString}s in a {@link SpatialIndex} containing
 * {@link MonotoneChain}s to a given {@link HotPixel}.
 *
 * Last port: noding/snapround/MCIndexPointSnapper.java rev. 1.2 (JTS-1.7)
 */
class MCIndexPointSnapper {

private:

	index::SpatialIndex& index;

public:
 

	MCIndexPointSnapper(index::SpatialIndex& nIndex)
		:
		index(nIndex)
	{}


	/**
	 * Snaps (nodes) all interacting segments to this hot pixel.
	 * The hot pixel may represent a vertex of an edge,
	 * in which case this routine uses the optimization
	 * of not noding the vertex itself
	 *
	 * @param hotPixel the hot pixel to snap to
	 * @param parentEdge the edge containing the vertex,
	 *        if applicable, or <code>null</code>
	 * @param vertexIndex the index of the vertex, if applicable, or -1
	 * @return <code>true</code> if a node was added for this pixel
	 */
	bool snap(const HotPixel& hotPixel, SegmentString* parentEdge,
			unsigned int vertexIndex);

	bool snap(const HotPixel& hotPixel) {
		return snap(hotPixel, 0, 0);
	}
		
};


} // namespace GEOMETRY::noding::snapround
} // namespace GEOMETRY::noding
} // namespace GEOMETRY

//#ifdef GEOS_INLINE
//# include "Geometry/noding/snapround/MCIndexPointSnapper.inl"
//#endif

#endif // GEOS_NODING_SNAPROUND_MCINDEXPOINTSNAPPER_H

/**********************************************************************
 * $Log$
 * Revision 1.3  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.2  2006/03/22 18:12:31  strk
 * indexChain.h header split.
 *
 * Revision 1.1  2006/03/14 12:55:56  strk
 * Headers split: geomgraphindex.h, nodingSnapround.h
 *
 **********************************************************************/

