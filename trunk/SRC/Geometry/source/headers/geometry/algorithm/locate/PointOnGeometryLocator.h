/**********************************************************************
 * $Id: PointOnGeometryLocator.h 2263 2009-01-29 18:56:00Z mloskot $
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
 *
 **********************************************************************/

#ifndef GEOS_ALGORITHM_LOCATE_POINTONGEOMETRYLOCATOR_H
#define GEOS_ALGORITHM_LOCATE_POINTONGEOMETRYLOCATOR_H

namespace GEOMETRY {
	namespace geom {
		class Coordinate; 
	}
}

namespace GEOMETRY {
namespace algorithm { // GEOMETRY::algorithm
namespace locate { // GEOMETRY::algorithm::locate

/** \brief
 * An interface for classes which determine the {@link Location} of
 * points in {@link Polygon} or {@link MultiPolygon} geometries.
 * 
 * @author Martin Davis
 */
class PointOnGeometryLocator
{
private:
protected:
public:
	virtual ~PointOnGeometryLocator() 
	{ }

	/**
	 * Determines the {@link Location} of a point in an areal {@link Geometry}.
	 * 
	 * @param p the point to test
	 * @return the location of the point in the geometry  
	 */
	virtual int locate( const geom::Coordinate * /*const*/ p) =0;
};

} // GEOMETRY::algorithm::locate
} // GEOMETRY::algorithm
} // geos

#endif // GEOS_ALGORITHM_LOCATE_POINTONGEOMETRYLOCATOR_H
/**********************************************************************
 * $Log$
 **********************************************************************/

