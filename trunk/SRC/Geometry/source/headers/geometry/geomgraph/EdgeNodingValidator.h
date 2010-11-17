/**********************************************************************
 * $Id: EdgeNodingValidator.h 1939 2006-12-11 17:42:55Z strk $
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


#ifndef GEOMETRY_GEOMGRAPH_EDGENODINGVALIDATOR_H
#define GEOMETRY_GEOMGRAPH_EDGENODINGVALIDATOR_H

#include <vector>

//#include <Geometry/noding/NodingValidator.h> // for composition
#include <Geometry/noding/FastNodingValidator.h> // for composition

#include <Geometry/inline.h>

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class CoordinateSequence;
	}
	namespace noding {
		class SegmentString;
	}
	namespace geomgraph {
		class Edge;
	}
}

namespace GEOMETRY {
namespace geomgraph { // geos.geomgraph

/**
 * Validates that a collection of SegmentStrings is correctly noded.
 * Throws an appropriate exception if an noding error is found.
 *
 * @version 1.4
 */
class EdgeNodingValidator {

private:
	std::vector<noding::SegmentString*>& toSegmentStrings(std::vector<Edge*>& edges);

	// Make sure this member is initialized *before*
	// the NodingValidator, as initialization of
	// NodingValidator will use toSegmentString(), that
	// in turn expects this member to be initialized
	std::vector<noding::SegmentString*> segStr;

	// Make sure this member is initialized *before*
	// the NodingValidator, as initialization of
	// NodingValidator will use toSegmentString(), that
	// in turn expects this member to be initialized
	std::vector<geom::CoordinateSequence*> newCoordSeq;

	noding::FastNodingValidator nv;
	//noding::NodingValidator nv;

public:

	EdgeNodingValidator(std::vector<Edge*>& edges)
		:
		segStr(), 
		newCoordSeq(),
		nv(toSegmentStrings(edges))
	{}

	~EdgeNodingValidator();

	void checkValid() { nv.checkValid(); }
};


} // namespace GEOMETRY.geomgraph
} // namespace GEOMETRY

//#ifdef GEOS_INLINE
//# include "Geometry/geomgraph/EdgeNodingValidator.inl"
//#endif

#endif // ifndef GEOS_GEOMGRAPH_EDGENODINGVALIDATOR_H

/**********************************************************************
 * $Log$
 * Revision 1.2  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/

