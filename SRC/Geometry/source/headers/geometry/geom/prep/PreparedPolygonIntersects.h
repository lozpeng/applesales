/**********************************************************************
 * $Id: PreparedPolygonIntersects.h 2159 2008-08-18 16:27:02Z mloskot $
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

#ifndef GEOMETRY_GEOM_PREP_PREPAREDPOLYGONINTERSECTS_H
#define GEOMETRY_GEOM_PREP_PREPAREDPOLYGONINTERSECTS_H

#include <Geometry/geom/prep/PreparedPolygonPredicate.h> // inherited

namespace GEOMETRY {
	namespace geom { 
		class Geometry;

		namespace prep { 
			class PreparedPolygon;
		}
	}
}

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom
namespace prep { // GEOMETRY::geom::prep

/**
 * \brief
 * Computes the <tt>intersects</tt> spatial relationship predicate
 * for {@link PreparedPolygon}s relative to all other {@link Geometry} classes.
 * 
 * Uses short-circuit tests and indexing to improve performance. 
 * 
 * @author Martin Davis
 *
 */
class PreparedPolygonIntersects : public PreparedPolygonPredicate
{
private:
protected:
public:
	/**
	 * Computes the intersects predicate between a {@link PreparedPolygon}
	 * and a {@link Geometry}.
	 * 
	 * @param prep the prepared polygon
	 * @param geom a test geometry
	 * @return true if the polygon intersects the geometry
	 */
	static bool intersects( const PreparedPolygon * const prep, const geom::Geometry * geom)
	{
		PreparedPolygonIntersects polyInt(prep);
		return polyInt.intersects( geom);
	}
	
	/**
	 * Creates an instance of this operation.
	 * 
	 * @param prepPoly the PreparedPolygon to evaluate
	 */
	PreparedPolygonIntersects( const PreparedPolygon * const prep)
	:	PreparedPolygonPredicate( prep)
	{ }
	
	/**
	 * Tests whether this PreparedPolygon intersects a given geometry.
	 * 
	 * @param geom the test geometry
	 * @return true if the test geometry intersects
	 */
	bool intersects( const geom::Geometry * geom);

};

} // GEOMETRY::geom::prep
} // GEOMETRY::geom
} // geos

#endif // GEOS_GEOM_PREP_PREPAREDPOLYGONINTERSECTS_H
/**********************************************************************
 * $Log$
 **********************************************************************/

