/**********************************************************************
 * $Id: GeometryFactory.inl 1820 2006-09-06 16:54:23Z mloskot $
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
 **********************************************************************
 *
 * Last port: geom/GeometryFactory.java rev. 1.48
 *
 **********************************************************************
 *
 * This is just a stub, there are a lot of candidates for inlining
 * but it's not worth checking that at the moment
 *
 **********************************************************************/

#ifndef GEOMETRY_GEOM_GEOMETRYFACTORY_INL
#define GEOMETRY_GEOM_GEOMETRYFACTORY_INL

#include <Geometry/geom/GeometryFactory.h>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

INLINE int
GeometryFactory::getSRID() const
{
	return SRID;
}

INLINE const CoordinateSequenceFactory*
GeometryFactory::getCoordinateSequenceFactory() const
{
	return coordinateListFactory;
}

} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#endif // GEOS_GEOM_GEOMETRYFACTORY_INL


