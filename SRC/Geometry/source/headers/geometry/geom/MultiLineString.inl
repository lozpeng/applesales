/**********************************************************************
 * $Id: MultiLineString.inl 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOMETRY_GEOM_MULTILINESTRING_INL
#define GEOMETRY_GEOM_MULTILINESTRING_INL

#include <Geometry/geom/MultiLineString.h>
#include <Geometry/geom/MultiPoint.h>

//#include <cassert>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

INLINE 
MultiLineString::MultiLineString(const MultiLineString &mp)
	:
	GeometryCollection(mp)
{
	//设置是否有Z或M值
	this->SetbZ(mp.HasZ());
	this->SetbM(mp.HasM());
}

INLINE Geometry*
MultiLineString::clone() const
{
	return new MultiLineString(*this);
}

} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#endif // GEOS_GEOM_MULTILINESTRING_INL


