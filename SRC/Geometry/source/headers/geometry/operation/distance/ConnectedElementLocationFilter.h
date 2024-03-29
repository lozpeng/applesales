/**********************************************************************
 * $Id: ConnectedElementLocationFilter.h 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#ifndef GEOS_OP_DISTANCE_CONNECTEDELEMENTLOCATIONFILTER_H
#define GEOS_OP_DISTANCE_CONNECTEDELEMENTLOCATIONFILTER_H

#include <Geometry/geom/GeometryFilter.h> // for inheritance

#include <vector>

// Forward declarations
namespace GEOMETRY {
	namespace geom { 
		class Geometry;
	}
	namespace operation { 
		namespace distance {
			class GeometryLocation;
		}
	}
}


namespace GEOMETRY {
namespace operation { // GEOMETRY::operation
namespace distance { // GEOMETRY::operation::distance

/** \brief
 * A ConnectedElementPointFilter extracts a single point
 * from each connected element in a Geometry
 * (e.g. a polygon, linestring or point)
 * and returns them in a list. The elements of the list are 
 * DistanceOp::GeometryLocation.
 */
class ConnectedElementLocationFilter: public geom::GeometryFilter {
private:

	std::vector<GeometryLocation*> *locations;

public:
	/**
	 * Returns a list containing a point from each Polygon, LineString, and Point
	 * found inside the specified geometry. Thus, if the specified geometry is
	 * not a GeometryCollection, an empty list will be returned. The elements of the list 
	 * are {@link com.vividsolutions.jts.operation.distance.GeometryLocation}s.
	 */  
	static std::vector<GeometryLocation*>* getLocations(const geom::Geometry *geom);

	ConnectedElementLocationFilter(std::vector<GeometryLocation*> *newLocations)
		:
		locations(newLocations)
	{}

	void filter_ro(const geom::Geometry *geom);
	void filter_rw(geom::Geometry *geom);
};


} // namespace GEOMETRY::operation::distance
} // namespace GEOMETRY::operation
} // namespace GEOMETRY

#endif // GEOS_OP_DISTANCE_CONNECTEDELEMENTLOCATIONFILTER_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/21 17:55:01  strk
 * opDistance.h header split
 *
 **********************************************************************/

