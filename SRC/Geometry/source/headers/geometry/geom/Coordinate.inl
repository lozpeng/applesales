/**********************************************************************
 * $Id: Coordinate.inl 2131 2008-07-15 22:04:51Z mloskot $
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

#ifndef GEOMETRY_GEOM_COORDINATE_INL
#define GEOMETRY_GEOM_COORDINATE_INL

#include <Geometry/geom/Coordinate.h>
//#include <Geometry/geom/PrecisionModel.h> // we need it for makePrecise, possibly to be obsoleted
#include <Geometry/platform.h> // for DoubleNotANumber

#include <cassert>
#include <cmath>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

INLINE void
Coordinate::setNull()
{
	x=DoubleNotANumber;
	y=DoubleNotANumber;
	z=DoubleNotANumber;
	m=DoubleNotANumber;
}

INLINE Coordinate&
Coordinate::getNull()
{
	return nullCoord;
}

INLINE
Coordinate::~Coordinate()
{
}

INLINE
Coordinate::Coordinate(double xNew, double yNew, double zNew,double mNew)
	:
	x(xNew),
	y(yNew),
	z(zNew),
	m(mNew)
{}

#if 0
INLINE
Coordinate::Coordinate(const Coordinate& c)
	:
	x(c.x),
	y(c.y),
	z(c.z),
	m(c.m)
{
}

INLINE Coordinate&
Coordinate::operator=(const Coordinate &c)
{
	if ( this == &c ) return *this;
	x=c.x;
	y=c.y;
	z=c.z;
	m=c.m;
	return *this;
}
#endif

INLINE bool
Coordinate::equals2D(const Coordinate& other) const
{
	//kdk,修改为误差在1e-14以内
	if (abs(x -other.x)>1e-14) return false;
	if (abs(y - other.y)>1e-14) return false;
	return true;
}

INLINE bool
Coordinate::equals(const Coordinate& other) const
{
	return equals2D(other);
}

INLINE int
Coordinate::compareTo(const Coordinate& other) const
{
	if (x < other.x) return -1;
	if (x > other.x) return 1;
	if (y < other.y) return -1;
	if (y > other.y) return 1;
	return 0;
}

INLINE bool
Coordinate::equals3D(const Coordinate& other) const
{
	return (x == other.x) && ( y == other.y) && 
		((z == other.z)||(ISNAN(z) && ISNAN(other.z)));
}

#if 0
INLINE void
Coordinate::makePrecise(const PrecisionModel *pm)
{
	x = pm->makePrecise(x);
	y = pm->makePrecise(y);
}
#endif

INLINE double
Coordinate::distance(const Coordinate& p) const
{
	double dx = x - p.x;
	double dy = y - p.y;
	return std::sqrt(dx * dx + dy * dy);
}

INLINE int
Coordinate::hashCode() const
{
	//Algorithm from Effective Java by Joshua Bloch [Jon Aquino]
	int result = 17;
	result = 37 * result + hashCode(x);
	result = 37 * result + hashCode(y);
	return result;
}

/*static*/
INLINE int
Coordinate::hashCode(double d)
{
	int64 f = (int64)(d);
	return (int)(f^(f>>32));
}

INLINE bool
CoordinateLessThen::operator()(const Coordinate* a, const Coordinate* b) const
{
	if (a->compareTo(*b)<0) return true;
	else return false;
}

INLINE bool
CoordinateLessThen::operator()(const Coordinate& a, const Coordinate& b) const
{
	if (a.compareTo(b)<0) return true;
	else return false;
}

INLINE bool
operator==(const Coordinate& a, const Coordinate& b)
{
	return a.equals2D(b);
}

INLINE bool
operator!=(const Coordinate& a, const Coordinate& b)
{
	return ! a.equals2D(b);
}

INLINE void Coordinate::Scale(const GEOMETRY::geom::Coordinate &OriginPt, double &dx, double &dy)
{
	
	x =OriginPt.x -(OriginPt.x -x)*dx;
	y =OriginPt.y -(OriginPt.y -y)*dy;


}

INLINE void Coordinate::Rotate(const GEOMETRY::geom::Coordinate &OriginPt, double angle)
{
	double dx =x-OriginPt.x;
	double dy =y-OriginPt.y;

	x=dx*cos(angle)-dy*sin(angle)+OriginPt.x; 
	y=dy*cos(angle)+dx*sin(angle)+OriginPt.y; 
}

} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#endif // GEOS_GEOM_COORDINATE_INL

