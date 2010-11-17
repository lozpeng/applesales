/**********************************************************************
 * $Id: PrecisionModel.inl 1820 2006-09-06 16:54:23Z mloskot $
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
 * Last port: geom/PrecisionModel.java rev. 1.51 (JTS-1.7)
 *
 **********************************************************************/

#ifndef GEOMETRY_GEOM_PRECISIONMODEL_INL
#define GEOMETRY_GEOM_PRECISIONMODEL_INL

#include <Geometry/geom/PrecisionModel.h>

#include <cassert>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

/*public*/
INLINE 
PrecisionModel::~PrecisionModel(void)
{
}

/*public*/
INLINE void
PrecisionModel::makePrecise(Coordinate* coord) const
{
	assert(coord);
	return makePrecise(*coord);
}

/*public*/
INLINE PrecisionModel::Type
PrecisionModel::getType() const
{
	return modelType;
}

/*public*/
INLINE double
PrecisionModel::getScale() const
{
	return scale;
}


} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#endif // GEOS_GEOM_PRECISIONMODEL_INL

