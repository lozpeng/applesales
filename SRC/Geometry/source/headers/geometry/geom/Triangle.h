/**********************************************************************
 * $Id: Triangle.h 1820 2006-09-06 16:54:23Z mloskot $
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
 **********************************************************************/

#ifndef GEOMETRY_GEOM_TRIANGLE_H
#define GEOMETRY_GEOM_TRIANGLE_H

#include <Geometry/geom/Coordinate.h> 

#include <Geometry/inline.h>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

/**
 * \brief
 * Represents a planar triangle, and provides methods for calculating various
 * properties of triangles.
 */
class Triangle {
public:
	Coordinate p0, p1, p2;

	Triangle(const Coordinate& nP0, const Coordinate& nP1, const Coordinate& nP2)
		:
		p0(nP0),
		p1(nP1),
		p2(nP2)
	{}

	/**
	 * The inCentre of a triangle is the point which is equidistant
	 * from the sides of the triangle.  This is also the point at which the bisectors
	 * of the angles meet.
	 *
	 * @param resultPoint the point into which to write the inCentre of the triangle
	 */
	void inCentre(Coordinate& resultPoint);
};


} // namespace GEOMETRY::geom
} // namespace GEOMETRY

//#ifdef GEOS_INLINE
//# include "Geometry/geom/Triangle.inl"
//#endif

#endif // ndef GEOS_GEOM_TRIANGLE_H

/**********************************************************************
 * $Log$
 * Revision 1.2  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/
