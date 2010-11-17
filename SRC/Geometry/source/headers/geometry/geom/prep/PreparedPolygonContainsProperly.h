/**********************************************************************
 * $Id: PreparedPolygonContainsProperly.h 2159 2008-08-18 16:27:02Z mloskot $
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

#ifndef GEOMETRY_GEOM_PREP_PREPAREDPOLYGONCONTAINSPROPERLY_H
#define GEOMETRY_GEOM_PREP_PREPAREDPOLYGONCONTAINSPROPERLY_H

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
 * Computes the <tt>containsProperly</tt> spatial relationship predicate
 * for {@link PreparedPolygon}s relative to all other {@link Geometry} classes.
 *
 * Uses short-circuit tests and indexing to improve performance. 
 * 
 * A Geometry A <tt>containsProperly</tt> another Geometry B iff
 * all points of B are contained in the Interior of A.
 * Equivalently, B is contained in A AND B does not intersect 
 * the Boundary of A.
 * 
 * The advantage to using this predicate is that it can be computed
 * efficiently, with no need to compute topology at individual points.
 * In a situation with many geometries intersecting the boundary 
 * of the target geometry, this can make a performance difference.
 * 
 * @author Martin Davis
 */
class PreparedPolygonContainsProperly : public PreparedPolygonPredicate
{
private:
protected:
public:
	/**
	 * Computes the </tt>containsProperly</tt> predicate between a {@link PreparedPolygon}
	 * and a {@link Geometry}.
	 * 
	 * @param prep the prepared polygon
	 * @param geom a test geometry
	 * @return true if the polygon properly contains the geometry
	 */
	static 
	bool 
	containsProperly( const PreparedPolygon * const prep, const geom::Geometry * geom)
	{
		PreparedPolygonContainsProperly polyInt( prep);
		return polyInt.containsProperly( geom);
	}

	/**
	 * Creates an instance of this operation.
	 * 
	 * @param prepPoly the PreparedPolygon to evaluate
	 */
	PreparedPolygonContainsProperly( const PreparedPolygon * const prep)
	:	PreparedPolygonPredicate( prep)
	{ }
	
	/**
	 * Tests whether this PreparedPolygon containsProperly a given geometry.
	 * 
	 * @param geom the test geometry
	 * @return true if the test geometry is contained properly
	 */
	bool 
	containsProperly( const geom::Geometry * geom);

};

} // GEOMETRY::geom::prep
} // GEOMETRY::geom
} // geos

#endif // GEOS_GEOM_PREP_PREPAREDPOLYGONCONTAINSPROPERLY_H
/**********************************************************************
 * $Log$
 **********************************************************************/

