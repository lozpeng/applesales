/**********************************************************************
 * $Id: Location.h 1835 2006-09-07 10:30:02Z strk $
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

#ifndef GEOMETRY_GEOM_LOCATION_H
#define GEOMETRY_GEOM_LOCATION_H

#include <iostream> // for ostream

#include <Geometry/inline.h>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

/** \brief
 *
 *  Constants representing the location of a point relative to a geometry.
 *
 *  They  can also be thought of as the row or column index of a DE-9IM matrix.
 *  For a description of the DE-9IM, see the <A
 *  HREF="http://www.opengis.org/techno/specs.htm">OpenGIS Simple Features
 *  Specification for SQL</A> .
 */
class Location {
public:
	enum Value {

		/**
		 *  Used for uninitialized location values.
		 */
		UNDEF=-1,   // Instead of NULL

		/**
		 * DE-9IM row index of the interior of the first geometry and
		 * column index of the interior of the second geometry.
		 * Location value for the interior of a geometry.
		 */
		INTERIOR = 0,

		/**
		 * DE-9IM row index of the boundary of the first geometry and
		 * column index of the boundary of the second geometry.
		 * Location value for the boundary of a geometry.
		 */
		BOUNDARY = 1,

		/**
		 * DE-9IM row index of the exterior of the first geometry and
		 * column index of the exterior of the second geometry.
		 * Location value for the exterior of a geometry.
		 */
		EXTERIOR = 2
	};

	static char toLocationSymbol(int locationValue);
};

} // namespace GEOMETRY::geom
} // namespace GEOMETRY

//#ifdef GEOS_INLINE
//# include "Geometry/geom/Location.inl"
//#endif

#endif // ndef GEOS_GEOM_LOCATION_H

