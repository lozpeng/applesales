/**********************************************************************
 * $Id: GeometryCollection.inl 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOMETRY_GEOMETRYCOLLECTION_INL
#define GEOMETRY_GEOMETRYCOLLECTION_INL

#include <Geometry/geom/GeometryCollection.h>

#include <vector>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

INLINE GeometryCollection::const_iterator
GeometryCollection::begin() const
{
	return geometries->begin();
}

INLINE GeometryCollection::const_iterator
GeometryCollection::end() const
{
	return geometries->end();
}


} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#endif // GEOS_GEOMETRYCOLLECTION_INL
