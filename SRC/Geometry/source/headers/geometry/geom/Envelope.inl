/**********************************************************************
 * $Id: Envelope.inl 2054 2007-12-21 20:03:37Z benjubb $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2005-2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#ifndef GEOMETRY_GEOM_ENVELOPE_INL
#define GEOMETRY_GEOM_ENVELOPE_INL

#include <cassert>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/Envelope.h>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

/*public*/
INLINE double
Envelope::getMaxY() const { return maxy; }

/*public*/
INLINE double
Envelope::getMaxX() const { return maxx; }

/*public*/
INLINE double
Envelope::getMinY() const { return miny; }

/*public*/
INLINE double
Envelope::getMinX() const { return minx; }

/*public*/
INLINE bool
Envelope::intersects(const Coordinate& other) const
{
	return (other.x <= maxx && other.x >= minx &&
		other.y <= maxy && other.y >= miny);
}

/*public*/
INLINE bool
Envelope::intersects(const Envelope& other) const
{
	return intersects(&other);
}

/*public*/
INLINE bool
Envelope::isNull(void) const
{
	return maxx < minx;
}

/*public*/
INLINE bool
Envelope::intersects(const Envelope* other) const
{
	// Optimized to reduce function calls
	if ( isNull() || other->isNull() ) return false;
	return !(other->minx > maxx ||
			 other->maxx < minx ||
			 other->miny > maxy ||
			 other->maxy < miny);
}

/*public*/
INLINE bool
Envelope::intersects(double x, double y) const
{
	return (x <= maxx && x >= minx && y <= maxy && y >= miny);
}


/*public*/
INLINE bool 
Envelope::covers(double x, double y) const
{
	if (isNull()) return false;
	return x >= minx &&
		x <= maxx &&
		y >= miny &&
		y <= maxy;
}

/*public*/
INLINE bool 
Envelope::covers( const Coordinate *p) const
{
	return covers(p->x, p->y);
}

/*public*/
INLINE bool 
Envelope::covers( const Envelope *other) const
{
	if (isNull() || other->isNull()) return false;

	return 
		other->getMinX() >= minx &&
		other->getMaxX() <= maxx &&
		other->getMinY() >= miny &&
		other->getMaxY() <= maxy;
}

/*public*/
INLINE bool 
Envelope::covers( const Envelope &other) const 
{ 
	return covers( &other); 
}


} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#endif // GEOS_GEOM_ENVELOPE_INL

