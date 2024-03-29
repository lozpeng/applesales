/**********************************************************************
 * $Id: HotPixel.inl 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_NODING_SNAPROUND_HOTPIXEL_INL
#define GEOS_NODING_SNAPROUND_HOTPIXEL_INL

#include <Geometry/noding/snapround/HotPixel.h>
#include <Geometry/util/math.h>
#include <Geometry/geom/Coordinate.h>

namespace GEOMETRY {
namespace noding { // GEOMETRY::noding
namespace snapround { // GEOMETRY::noding::snapround

INLINE double
HotPixel::scale(double val) const
{
	// Math.round
	//return round(val*scaleFactor);
	return util::round(val*scaleFactor);
}

INLINE void
HotPixel::copyScaled(const geom::Coordinate& p, geom::Coordinate& pScaled) const
{
	pScaled.x = scale(p.x);
	pScaled.y = scale(p.y);
}

} // namespace GEOMETRY::noding::snapround
} // namespace GEOMETRY::noding
} // namespace GEOMETRY

#endif // GEOS_NODING_SNAPROUND_HOTPIXEL_INL

