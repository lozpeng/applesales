/**********************************************************************
 * $Id: RectangleContains.cpp 2113 2008-01-29 17:49:18Z benjubb $
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
 **********************************************************************
 *
 * Last port: operation/predicate/RectangleContains.java rev 1.1 (JTS-1.7)
 *
 **********************************************************************/

#include <Geometry/operation/predicate/RectangleContains.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/Envelope.h>
#include <Geometry/geom/Point.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/LineString.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/CoordinateSequence.h>

using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace operation { // geos.operation
namespace predicate { // geos.operation.predicate

bool
RectangleContains::contains(const Geometry& geom)
{
	if ( ! rectEnv.contains(geom.getEnvelopeInternal()) )
		return false;

	// check that geom is not contained entirely in the rectangle boundary
	if (isContainedInBoundary(geom))
		return false;

	return true;
}

/*private*/
bool
RectangleContains::isContainedInBoundary(const Geometry& geom)
{
	// polygons can never be wholely contained in the boundary
	if (dynamic_cast<const geom::Polygon *>(&geom)) return false;
	if (const Point *p=dynamic_cast<const Point *>(&geom))
		return isPointContainedInBoundary(*p);
	if (const LineString *l=dynamic_cast<const LineString *>(&geom))
		return isLineStringContainedInBoundary(*l);

	for (unsigned i=0, n=geom.getNumGeometries(); i<n; ++i)
	{
		const Geometry &comp = *(geom.getGeometryN(i));
		if ( !isContainedInBoundary(comp) ) 
			return false;
	}

	return true;
}

/*private*/
bool
RectangleContains::isPointContainedInBoundary(const Point& point)
{
	return isPointContainedInBoundary(*(point.getCoordinate()));
}

/*private*/
bool
RectangleContains::isPointContainedInBoundary(const Coordinate& pt)
{
	// we already know that the point is contained in the
	// rectangle envelope
	return 	
		pt.x == rectEnv.getMinX() || pt.x == rectEnv.getMaxX() ||
	    pt.y == rectEnv.getMinY() || pt.y == rectEnv.getMaxY();

	return true;
}

/*private*/
bool
RectangleContains::isLineStringContainedInBoundary(const LineString& line)
{
	const CoordinateSequence &seq = *(line.getCoordinatesRO());
	for (unsigned int i=0, n=seq.getSize()-1; i<n; ++i) {
		const Coordinate& p0=seq.getAt(i);
		const Coordinate& p1=seq.getAt(i+1);
		if (! isLineSegmentContainedInBoundary(p0, p1))
			return false;
	}
	return true;
}

/*private*/
bool
RectangleContains::isLineSegmentContainedInBoundary(const Coordinate& p0,
		const Coordinate& p1)
{
	if (p0.equals2D(p1))
		return isPointContainedInBoundary(p0);

	// we already know that the segment is contained in
	// the rectangle envelope
	if (p0.x == p1.x) {
		if (p0.x == rectEnv.getMinX() ||
			p0.x == rectEnv.getMaxX() )
		{
			return true;
		}
	}
	else if (p0.y == p1.y) {
		if (p0.y == rectEnv.getMinY() ||
			p0.y == rectEnv.getMaxY() )
		{
			return true;
		}
	}

	/**
	 * Either
	 *   both x and y values are different
	 * or
	 *   one of x and y are the same, but the other ordinate
	 *   is not the same as a boundary ordinate
	 *
	 * In either case, the segment is not wholely in the boundary
	 */
	return false;
}



} // namespace GEOMETRY.operation.predicate
} // namespace GEOMETRY.operation
} // namespace GEOMETRY



