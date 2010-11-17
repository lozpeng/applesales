/**********************************************************************
 * $Id: IteratedNoder.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_NODING_ITERATEDNODER_H
#define GEOS_NODING_ITERATEDNODER_H

#include <vector>
#include <iostream>

#include <Geometry/inline.h>

#include <Geometry/algorithm/LineIntersector.h>
#include <Geometry/noding/SegmentString.h> // due to inlines
#include <Geometry/noding/Noder.h> // for inheritance

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class PrecisionModel;
	}
}

namespace GEOMETRY {
namespace noding { // GEOMETRY::noding

/**
 * Nodes a set of SegmentStrings completely.
 * The set of segmentStrings is fully noded;
 * i.e. noding is repeated until no further
 * intersections are detected.
 * <p>
 * Iterated noding using a FLOATING precision model is not guaranteed to converge,
 * due to roundoff error.   This problem is detected and an exception is thrown.
 * Clients can choose to rerun the noding using a lower precision model.
 *
 * Last port: noding/IteratedNoder.java rev. 1.6 (JTS-1.7)
 */
class IteratedNoder : public Noder { // implements Noder

private:
	static const int MAX_ITER = 5;


	const geom::PrecisionModel *pm;
	algorithm::LineIntersector li;
	std::vector<SegmentString*>* nodedSegStrings;
	int maxIter;

	/**
	 * Node the input segment strings once
	 * and create the split edges between the nodes
	 */
	void node(std::vector<SegmentString*>* segStrings,
			int *numInteriorIntersections);

public:

	IteratedNoder(const geom::PrecisionModel *newPm)
		:
		pm(newPm),
		li(pm),
		maxIter(MAX_ITER)
	{
	}

	virtual ~IteratedNoder() {}

	/**
	 * Sets the maximum number of noding iterations performed before
	 * the noding is aborted.
	 * Experience suggests that this should rarely need to be changed
	 * from the default.
	 * The default is MAX_ITER.
	 *
	 * @param n the maximum number of iterations to perform
	 */
	void setMaximumIterations(int n) { maxIter = n; }

	std::vector<SegmentString*>* getNodedSubstrings() const {
		return SegmentString::getNodedSubstrings(*nodedSegStrings);
	}
 

	/**
	 * Fully nodes a list of {@link SegmentStrings}, i.e. peforms noding iteratively
	 * until no intersections are found between segments.
	 * Maintains labelling of edges correctly through
	 * the noding.
	 *
	 * @param segStrings a collection of SegmentStrings to be noded
	 * @throws TopologyException if the iterated noding fails to converge.
	 */
	void computeNodes(std::vector<SegmentString*>* inputSegmentStrings); // throw(GEOSException);
};

} // namespace GEOMETRY::noding
} // namespace GEOMETRY


//#ifdef GEOS_INLINE
//# include "Geometry/noding/IteratedNoder.inl"
//#endif

#endif // GEOS_NODING_ITERATEDNODER_H

/**********************************************************************
 * $Log$
 * Revision 1.2  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/

