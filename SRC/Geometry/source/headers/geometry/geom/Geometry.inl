/**********************************************************************
 * $Id: Geometry.inl 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOMETRY_GEOM_GEOMETRY_INL
#define GEOMETRY_GEOM_GEOMETRY_INL

#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/GeometryFactory.h>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

INLINE const PrecisionModel*
Geometry::getPrecisionModel() const
{
	return factory->getPrecisionModel();
}

} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#endif // GEOS_GEOM_GEOMETRY_INL


