/**********************************************************************
 * $Id: SimplePointInAreaLocator.cpp 2069 2007-12-21 20:47:01Z benjubb $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2005-2006 Refractions Research Inc.
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#include <Geometry/algorithm/CGAlgorithms.h>
#include <Geometry/algorithm/locate/SimplePointInAreaLocator.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/GeometryCollection.h>
#include <Geometry/geom/Location.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/LineString.h>

#include <typeinfo>
#include <cassert>

using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace algorithm { // geos.algorithm
namespace locate { // geos.algorithm

/**
 * locate is the main location function.  It handles both single-element
 * and multi-element Geometries.  The algorithm for multi-element Geometries
 * is more complex, since it has to take into account the boundaryDetermination rule
 */
int
SimplePointInAreaLocator::locate(const Coordinate& p, const Geometry *geom)
{
	if (geom->isEmpty()) return Location::EXTERIOR;
	if (containsPoint(p,geom))
		return Location::INTERIOR;
	return Location::EXTERIOR;
}

bool
SimplePointInAreaLocator::containsPoint(const Coordinate& p,const Geometry *geom)
{
	if (const Polygon *poly = dynamic_cast<const Polygon*>(geom))
	{
		return containsPointInPolygon(p, poly);
	}
	
	if (const GeometryCollection *col = dynamic_cast<const GeometryCollection*>(geom))
	{
		for (GeometryCollection::const_iterator
				it=col->begin(), endIt=col->end();
				it != endIt;
				++it)
		{
			const Geometry *g2=*it;
			assert (g2!=geom); 
			if (containsPoint(p,g2)) return true;
		}
	}
	return false;
}

bool
SimplePointInAreaLocator::containsPointInPolygon(const Coordinate& p, const Polygon *poly)
{
	if (poly->isEmpty()) return false;
	const LineString *shell=poly->getExteriorRing();
	const CoordinateSequence *cl;
	cl = shell->getCoordinatesRO();
	if (!CGAlgorithms::isPointInRing(p,cl)) {
		return false;
	}

	// now test if the point lies in or on the holes
	for(size_t i=0, n=poly->getNumInteriorRing(); i<n; i++)
	{
		const LineString *hole = poly->getInteriorRingN(i);
		cl = hole->getCoordinatesRO();
		if (CGAlgorithms::isPointInRing(p,cl)) {
			return false;
		}
	}
	return true;
}

} // namespace GEOMETRY.algorithm.locate
} // namespace GEOMETRY.algorithm
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.22  2006/06/12 11:29:23  strk
 * unsigned int => size_t
 *
 * Revision 1.21  2006/03/21 11:12:23  strk
 * Cleanups: headers inclusion and Log section
 *
 * Revision 1.20  2006/03/09 16:46:46  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/

