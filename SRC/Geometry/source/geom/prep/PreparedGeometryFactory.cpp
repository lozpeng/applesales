/**********************************************************************
 * $Id: PreparedGeometryFactory.cpp 2187 2008-09-16 20:58:49Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/


#include <Geometry/geom/Point.h>
#include <Geometry/geom/MultiPoint.h>
#include <Geometry/geom/LineString.h>
#include <Geometry/geom/LinearRing.h>
#include <Geometry/geom/MultiLineString.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/MultiPolygon.h>
#include <Geometry/geom/prep/PreparedGeometryFactory.h>
#include <Geometry/geom/prep/PreparedGeometry.h>
#include <Geometry/geom/prep/BasicPreparedGeometry.h>
#include <Geometry/geom/prep/PreparedPolygon.h>
#include <Geometry/geom/prep/PreparedLineString.h>
#include <Geometry/geom/prep/PreparedPoint.h>
#include <Geometry/util/IllegalArgumentException.h>

namespace GEOMETRY {
namespace geom { // geos.geom
namespace prep { // geos.geom.prep

const PreparedGeometry *
PreparedGeometryFactory::create( const geom::Geometry * g) const
{
    using GEOMETRY::geom::GeometryTypeId;

    if (0 == g)
    {
        throw util::IllegalArgumentException("PreparedGeometry constructd with null Geometry object");
    }

	PreparedGeometry* pg = 0;

	switch ( g->getGeometryTypeId() )
	{
		case GEOS_MULTIPOINT:
		case GEOS_POINT:
			pg = new PreparedPoint( g);
			break;

		case GEOS_LINEARRING:
		case GEOS_LINESTRING:
		case GEOS_MULTILINESTRING:
			pg = new PreparedLineString( g);
			break;

		case GEOS_POLYGON:
		case GEOS_MULTIPOLYGON:
			pg = new PreparedPolygon( g);
			break;

		default:
			pg = new BasicPreparedGeometry( g);
	}
	return pg;
}

} // namespace GEOMETRY.geom.prep
} // namespace GEOMETRY.geom
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 *
 **********************************************************************/
