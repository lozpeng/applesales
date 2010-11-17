/**********************************************************************
 * $Id: PreparedPolygonCovers.h 2159 2008-08-18 16:27:02Z mloskot $
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

#ifndef GEOMETRY_GEOM_PREP_PREPAREDPOLYGONCOVERS_H
#define GEOMETRY_GEOM_PREP_PREPAREDPOLYGONCOVERS_H

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
 * Computes the <tt>covers</tt> spatial relationship predicate
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
class PreparedPolygonCovers : public AbstractPreparedPolygonContains 
{
private:
protected:
	/**
	 * Computes the full topological <tt>covers</tt> predicate.
	 * Used when short-circuit tests are not conclusive.
	 * 
	 * @param geom the test geometry
	 * @return true if this prepared polygon contains the test geometry
	 */
	bool fullTopologicalPredicate( const geom::Geometry * geom);

public:
	/**
	 * Computes the </tt>covers</tt> predicate between a {@link PreparedPolygon}
	 * and a {@link Geometry}.
	 * 
	 * @param prep the prepared polygon
	 * @param geom a test geometry
	 * @return true if the polygon covers the geometry
	 */
	static bool covers(const PreparedPolygon * const prep, const geom::Geometry * geom)
	{
	    PreparedPolygonCovers polyInt(prep);
		return polyInt.covers(geom);
	}

	/**
	 * Creates an instance of this operation.
	 * 
	 * @param prepPoly the PreparedPolygon to evaluate
	 */
	PreparedPolygonCovers(const PreparedPolygon * const prep)
	:	AbstractPreparedPolygonContains( prep, false) 
	{ }
		
	/**
	 * Tests whether this PreparedPolygon <tt>covers</tt> a given geometry.
	 * 
	 * @param geom the test geometry
	 * @return true if the test geometry is contained
	 */
	bool covers( const Geometry * geom)
	{
		return eval( geom);
	}
	
};

} // GEOMETRY::geom::prep
} // GEOMETRY::geom
} // geos

#endif // GEOS_GEOM_PREP_PREPAREDPOLYGONCOVERS_H
/**********************************************************************
 * $Log$
 **********************************************************************/

