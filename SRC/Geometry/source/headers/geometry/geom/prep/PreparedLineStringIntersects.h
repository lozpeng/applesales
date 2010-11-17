/**********************************************************************
 * $Id: PreparedLineStringIntersects.h 2159 2008-08-18 16:27:02Z mloskot $
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

#ifndef GEOMETRY_GEOM_PREP_PREPAREDLINESTRINGINTERSECTS_H
#define GEOMETRY_GEOM_PREP_PREPAREDLINESTRINGINTERSECTS_H

#include <Geometry/geom/prep/PreparedLineString.h>
#include <Geometry/algorithm/PointLocator.h> 
#include <Geometry/geom/util/ComponentCoordinateExtracter.h> 
#include <Geometry/geom/Coordinate.h> 
#include <Geometry/noding/SegmentStringUtil.h>

using namespace GEOMETRY::algorithm;
using namespace GEOMETRY::geom::util;

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom
namespace prep { // GEOMETRY::geom::prep

/**
 * \brief
 * Computes the <tt>intersects</tt> spatial relationship predicate
 * for a target {@link PreparedLineString} relative to other {@link Geometry} classes.
 * 
 * Uses short-circuit tests and indexing to improve performance. 
 * 
 * @author Martin Davis
 *
 */
class PreparedLineStringIntersects
{
private:
protected:
	PreparedLineString & prepLine;
	//PreparedLineString * prepLine;

	/**
	 * Tests whether any representative point of the test Geometry intersects
	 * the target geometry.
	 * Only handles test geometries which are Puntal (dimension 0)
	 * 
	 * @param geom a Puntal geometry to test
	 * @return true if any point of the argument intersects the prepared geometry
	 */
	bool isAnyTestPointInTarget(const geom::Geometry * testGeom) const;
	//{
	//	/**
	//	 * This could be optimized by using the segment index on the lineal target.
	//	 * However, it seems like the L/P case would be pretty rare in practice.
	//	 */
	//	PointLocator * locator = new PointLocator();

	//	geom::Coordinate::ConstVect coords;
	//	ComponentCoordinateExtracter::getCoordinates( *testGeom, coords);

	//	for (size_t i=0, n=coords.size(); i<n; i++)
	//	{
	//		geom::Coordinate c = *(coords[i]);
	//		if ( locator->intersects( c, &(prepLine->getGeometry()) ))
	//			return true;
	//	}
	//	return false;
	//}


public:

	/**
	 * Computes the intersects predicate between a {@link PreparedLineString}
	 * and a {@link Geometry}.
	 * 
	 * @param prep the prepared linestring
	 * @param geom a test geometry
	 * @return true if the linestring intersects the geometry
	 */
	static bool intersects(  PreparedLineString & prep, const geom::Geometry * geom ) 
	{
		PreparedLineStringIntersects * op = new PreparedLineStringIntersects( prep);
		return op->intersects( geom);
	}

    /**
     * \todo FIXME - mloskot: Why not taking linestring through const reference?
     */
	PreparedLineStringIntersects(PreparedLineString & prep) 
		: prepLine( prep)
	{ }

	/**
	 * Tests whether this geometry intersects a given geometry.
	 * 
	 * @param geom the test geometry
	 * @return true if the test geometry intersects
	 */
	bool intersects(const geom::Geometry * g) const;

};



} // namespace GEOMETRY::geom::prep
} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#endif // GEOS_GEOM_PREP_PREPAREDLINESTRINGINTERSECTS_H
/**********************************************************************
 * $Log$
 **********************************************************************/

