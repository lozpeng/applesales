/**********************************************************************
 * $Id: PreparedPoint.h 2159 2008-08-18 16:27:02Z mloskot $
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

#ifndef GEOMETRY_GEOM_PREP_PREPAREDPOINT_H
#define GEOMETRY_GEOM_PREP_PREPAREDPOINT_H

#include <Geometry/geom/prep/BasicPreparedGeometry.h> // for inheritance

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom
namespace prep { // GEOMETRY::geom::prep

/**
 * \brief
 * A prepared version of {@link Point} or {@link MultiPoint} geometries.
 * 
 * @author Martin Davis
 *
 */
class PreparedPoint: public BasicPreparedGeometry 
{
private:
protected:
public:
	PreparedPoint(const Geometry * geom) 
		: BasicPreparedGeometry( geom) 
	{ }

	/**
	 * Tests whether this point intersects a {@link Geometry}.
	 * <p>
	 * The optimization here is that computing topology for the test geometry
	 * is avoided.  This can be significant for large geometries.
	 */
	bool intersects(geom::Geometry* g);

};

} // namespace GEOMETRY::geom::prep
} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#endif // GEOS_GEOM_PREP_PREPAREDPOINT_H
/**********************************************************************
 * $Log$
 **********************************************************************/

