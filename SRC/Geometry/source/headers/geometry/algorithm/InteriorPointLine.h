/**********************************************************************
 * $Id: InteriorPointLine.h 1880 2006-10-27 11:54:17Z strk $
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

#ifndef GEOS_ALGORITHM_INTERIORPOINTLINE_H
#define GEOS_ALGORITHM_INTERIORPOINTLINE_H

#include <Geometry/geom/Coordinate.h>

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class Geometry;
		class CoordinateSequence;
	}
}


namespace GEOMETRY {
namespace algorithm { // GEOMETRY::algorithm

/** \brief
 * Computes a point in the interior of an linear geometry.
 *
 * <h2>Algorithm</h2>
 * <ul>
 * <li>Find an interior vertex which is closest to
 * the centroid of the linestring.
 * <li>If there is no interior vertex, find the endpoint which is
 * closest to the centroid.
 * </ul>
 */
class InteriorPointLine {
public:

	InteriorPointLine(const geom::Geometry *g);

	~InteriorPointLine();

	//Coordinate* getInteriorPoint() const;

	bool getInteriorPoint(geom::Coordinate& ret) const;

private:

	bool hasInterior;

	geom::Coordinate centroid;

	double minDistance;

	geom::Coordinate interiorPoint;

	void addInterior(const geom::Geometry *geom);

	void addInterior(const geom::CoordinateSequence *pts);
	
	void addEndpoints(const geom::Geometry *geom);

	void addEndpoints(const geom::CoordinateSequence *pts);

	void add(const geom::Coordinate& point);

};

} // namespace GEOMETRY::algorithm
} // namespace GEOMETRY

#endif // GEOS_ALGORITHM_INTERIORPOINTLINE_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/09 16:46:48  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/

