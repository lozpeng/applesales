/**********************************************************************
 * $Id: MCIndexSnapRounder.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_NODING_SNAPROUND_MCINDEXSNAPROUNDER_H
#define GEOS_NODING_SNAPROUND_MCINDEXSNAPROUNDER_H

#include <vector>

#include <Geometry/inline.h>

#include <Geometry/noding/Noder.h> // for inheritance
#include <Geometry/algorithm/LineIntersector.h> // for composition
#include <Geometry/geom/Coordinate.h> // for use in vector

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class PrecisionModel;
	}
	namespace algorithm {
		class LineIntersector;
	}
	namespace noding {
		class SegmentString;
		class MCIndexNoder;
		namespace snapround {
			//class HotPixel;
			class MCIndexPointSnapper;
		}
	}
}

namespace GEOMETRY {
namespace noding { // GEOMETRY::noding
namespace snapround { // GEOMETRY::noding::snapround


/** \brief
 * Uses Snap Rounding to compute a rounded,
 * fully noded arrangement from a set of SegmentString
 *
 * Implements the Snap Rounding technique described in Hobby, Guibas & Marimont,
 * and Goodrich et al.
 *
 * Snap Rounding assumes that all vertices lie on a uniform grid
 * (hence the precision model of the input must be fixed precision,
 * and all the input vertices must be rounded to that precision).
 * 
 * This implementation uses a monotone chains and a spatial index to
 * speed up the intersection tests.
 *
 * This implementation appears to be fully robust using an integer
 * precision model.
 *
 * It will function with non-integer precision models, but the
 * results are not 100% guaranteed to be correctly noded.
 *
 * Last port: noding/snapround/MCIndexSnapRounder.java rev. 1.1 (JTS-1.7)
 *
 */
class MCIndexSnapRounder: public Noder { // implments Noder

private:

	/// externally owned
	geom::PrecisionModel& pm;

	algorithm::LineIntersector li;

	double scaleFactor;

	std::vector<SegmentString*>* nodedSegStrings;

	std::auto_ptr<MCIndexPointSnapper> pointSnapper;

	void snapRound(MCIndexNoder& noder, std::vector<SegmentString*>* segStrings);

	
	/**
	 * Computes all interior intersections in the collection of SegmentStrings,
	 * and push their Coordinate to the provided vector.
	 *
	 * Does NOT node the segStrings.
	 *
	 */
	void findInteriorIntersections(MCIndexNoder& noder,
			std::vector<SegmentString*>* segStrings,
			std::vector<geom::Coordinate>& intersections);

	/**
	 * Computes nodes introduced as a result of snapping
	 * segments to snap points (hot pixels)
	 */
	void computeIntersectionSnaps(std::vector<geom::Coordinate>& snapPts);

	/**
	 * Performs a brute-force comparison of every segment in each {@link SegmentString}.
	 * This has n^2 performance.
	 */
	void computeEdgeVertexSnaps(SegmentString* e);
	
	void checkCorrectness(std::vector<SegmentString*>& inputSegmentStrings);

public:

	MCIndexSnapRounder(geom::PrecisionModel& nPm);

	std::vector<SegmentString*>* getNodedSubstrings() const;

	void computeNodes(std::vector<SegmentString*>* segStrings);
 
	/**
	 * Computes nodes introduced as a result of
	 * snapping segments to vertices of other segments
	 *
	 * @param segStrings the list of segment strings to snap together
	 */
	void computeVertexSnaps(std::vector<SegmentString*>& edges);

};


} // namespace GEOMETRY::noding::snapround
} // namespace GEOMETRY::noding
} // namespace GEOMETRY

#ifdef GEOS_INLINE
# include <Geometry/noding/snapround/MCIndexSnapRounder.inl>
#endif

#endif // GEOS_NODING_SNAPROUND_MCINDEXSNAPROUNDER_H

/**********************************************************************
 * $Log$
 * Revision 1.2  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.1  2006/03/14 12:55:56  strk
 * Headers split: geomgraphindex.h, nodingSnapround.h
 *
 **********************************************************************/

