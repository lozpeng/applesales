/**********************************************************************
 * $Id: PreparedPolygonContains.h 2194 2008-09-23 23:01:00Z mloskot $
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

#ifndef GEOMETRY_GEOM_PREP_PREPAREDPOLYGONCONTAINS_H
#define GEOMETRY_GEOM_PREP_PREPAREDPOLYGONCONTAINS_H

#include <Geometry/geom/prep/AbstractPreparedPolygonContains.h> // inherited

// forward declarations
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
 * Computes the <tt>contains</tt> spatial relationship predicate
 * for a {@link PreparedPolygon} relative to all other {@link Geometry} classes.
 * 
 * Uses short-circuit tests and indexing to improve performance. 
 * 
 * It is not possible to short-circuit in all cases, in particular
 * in the case where the test geometry touches the polygon linework.
 * In this case full topology must be computed.
 * 
 * @author Martin Davis
 *
 */
class PreparedPolygonContains : public AbstractPreparedPolygonContains 
{
public:

	/**
	 * Creates an instance of this operation.
	 * 
	 * @param prepPoly the PreparedPolygon to evaluate
	 */
	PreparedPolygonContains(const PreparedPolygon * const prepPoly);

	/**
	 * Tests whether this PreparedPolygon <tt>contains</tt> a given geometry.
	 * 
	 * @param geom the test geometry
	 * @return true if the test geometry is contained
	 */
	bool contains(const geom::Geometry * geom)
	{
		return eval(geom);
	}

	/**
	 * Computes the </tt>contains</tt> predicate between a {@link PreparedPolygon}
	 * and a {@link Geometry}.
	 * 
	 * @param prep the prepared polygon
	 * @param geom a test geometry
	 * @return true if the polygon contains the geometry
	 */
	static bool contains(const PreparedPolygon * const prep, const geom::Geometry * geom)
	{
		PreparedPolygonContains polyInt(prep);
		return polyInt.contains(geom);
	}

protected:
	/**
	* Computes the full topological <tt>contains</tt> predicate.
	* Used when short-circuit tests are not conclusive.
	* 
	* @param geom the test geometry
	* @return true if this prepared polygon contains the test geometry
	*/
	bool fullTopologicalPredicate(const geom::Geometry * geom);

};

} // GEOMETRY::geom::prep
} // GEOMETRY::geom
} // geos

#endif // GEOS_GEOM_PREP_PREPAREDPOLYGONCONTAINS_H
/**********************************************************************
 * $Log$
 **********************************************************************/

