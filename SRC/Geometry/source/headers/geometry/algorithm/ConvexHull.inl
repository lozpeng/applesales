/**********************************************************************
 * $Id: ConvexHull.inl 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_ALGORITHM_CONVEXHULL_INL
#define GEOS_ALGORITHM_CONVEXHULL_INL

#include <cassert>
#include <Geometry/algorithm/ConvexHull.h>
#include <Geometry/util/UniqueCoordinateArrayFilter.h>
#include <Geometry/geom/Geometry.h>

namespace GEOMETRY {
namespace algorithm { // GEOMETRY::algorithm

INLINE 
ConvexHull::ConvexHull(const geom::Geometry *newGeometry)
	:
	geomFactory(newGeometry->getFactory())
{
	extractCoordinates(newGeometry);
}

INLINE 
ConvexHull::~ConvexHull()
{
}

INLINE void
ConvexHull::extractCoordinates(const geom::Geometry *geom)
{
	util::UniqueCoordinateArrayFilter filter(inputPts);
	geom->apply_ro(&filter);
}

} // namespace GEOMETRY::algorithm
} // namespace GEOMETRY

#endif // GEOS_ALGORITHM_CONVEXHULL_INL
