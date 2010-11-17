/**********************************************************************
 * $Id: CoordinateOperation.cpp 2168 2008-08-19 17:00:43Z mloskot $
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

#include <typeinfo>

//#include <Geometry/geomUtil.h>
//#include <Geometry/util.h> // to be removed when util.h is finished
#include <Geometry/geom/util/CoordinateOperation.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/LinearRing.h>
#include <Geometry/geom/LineString.h>
#include <Geometry/geom/Point.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/GeometryFactory.h>

namespace GEOMETRY {
namespace geom { // geos.geom
namespace util { // geos.geom.util

Geometry*
CoordinateOperation::edit(const Geometry *geometry,
		const GeometryFactory *factory)
{
		const LinearRing *ring = dynamic_cast<const LinearRing *>(geometry);
		if (ring) {
			const CoordinateSequence *coords = ring->getCoordinatesRO();
			CoordinateSequence *newCoords = edit(coords,geometry);
            // LinearRing instance takes over ownership of newCoords instance
			return factory->createLinearRing(newCoords);
		}
		const LineString *line = dynamic_cast<const LineString *>(geometry);
		if (line) {
			const CoordinateSequence *coords = line->getCoordinatesRO();
			CoordinateSequence *newCoords = edit(coords,geometry);
			return factory->createLineString(newCoords);
		}
		if (typeid(*geometry)==typeid(Point)) {
			CoordinateSequence *coords = geometry->getCoordinates();
			CoordinateSequence *newCoords = edit(coords,geometry);
			delete coords;
			return factory->createPoint(newCoords);
		}

		return geometry->clone();
}


} // namespace GEOMETRY.geom.util
} // namespace GEOMETRY.geom
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/09 16:46:47  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/

