/**********************************************************************
 * $Id: CoordinateArraySequenceFactory.inl 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOMETRY_GEOM_COORDINATEARRAYSEQUENCEFACTORY_INL
#define GEOMETRY_GEOM_COORDINATEARRAYSEQUENCEFACTORY_INL

#include <cassert>
#include <Geometry/geom/CoordinateArraySequenceFactory.h>
#include <Geometry/geom/CoordinateArraySequence.h>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

INLINE CoordinateSequence*
CoordinateArraySequenceFactory::create(std::vector<Coordinate> *coords) const
{
	return new CoordinateArraySequence(coords);
}

INLINE CoordinateSequence *
CoordinateArraySequenceFactory::create(std::vector<Coordinate> *coords,
		size_t /* dimension */) const
{
	return new CoordinateArraySequence(coords);
}

INLINE CoordinateSequence *
CoordinateArraySequenceFactory::create(size_t size, size_t /* dimension */)
		const
{
	/* CoordinateArraySequence only accepts 3d Coordinates */
	return new CoordinateArraySequence(size);
}


} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#endif // GEOS_GEOM_COORDINATEARRAYSEQUENCEFACTORY_INL

