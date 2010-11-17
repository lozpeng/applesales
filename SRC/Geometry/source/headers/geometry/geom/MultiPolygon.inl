/**********************************************************************
 * $Id: MultiPolygon.inl 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOMETRY_GEOM_MULTIPOLYGON_INL
#define GEOMETRY_GEOM_MULTIPOLYGON_INL

#include <Geometry/geom/MultiPolygon.h>
#include <Geometry/geom/GeometryCollection.h>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

INLINE 
MultiPolygon::MultiPolygon(const MultiPolygon &mp)
	:
	GeometryCollection(mp)
{
}

INLINE Geometry*
MultiPolygon::clone() const
{
	return new MultiPolygon(*this);
}

} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#endif // GEOS_GEOM_MULTIPOLYGON_INL


