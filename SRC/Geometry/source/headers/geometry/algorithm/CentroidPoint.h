/**********************************************************************
 * $Id: CentroidPoint.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_ALGORITHM_CENTROIDPOINT_H
#define GEOS_ALGORITHM_CENTROIDPOINT_H

#include <Geometry/geom/Coordinate.h>

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class Geometry;
	}
}


namespace GEOMETRY {
namespace algorithm { // GEOMETRY::algorithm

class CentroidPoint {

private:

	int ptCount;

	geom::Coordinate centSum;

public:

	CentroidPoint()
		:
		ptCount(0),
		centSum(0.0, 0.0)
	{}

	~CentroidPoint()
	{}

	/**
	 * Adds the point(s) defined by a Geometry to the centroid total.
	 * If the geometry is not of dimension 0 it does not contribute to the
	 * centroid.
	 * @param geom the geometry to add
	 */
	void add(const geom::Geometry *geom);

	void add(const geom::Coordinate *pt);

	geom::Coordinate* getCentroid() const;

	/// Return false if centroid could not be computed
	bool getCentroid(geom::Coordinate& ret) const;
};

} // namespace GEOMETRY::algorithm
} // namespace GEOMETRY

#endif // GEOS_ALGORITHM_CENTROIDPOINT_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/09 16:46:48  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/

