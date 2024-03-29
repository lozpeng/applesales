/**********************************************************************
 * $Id: MCIndexSnapRounder.inl 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_NODING_SNAPROUND_MCINDEXSNAPROUNDER_INL
#define GEOS_NODING_SNAPROUND_MCINDEXSNAPROUNDER_INL

#include <Geometry/noding/snapround/MCIndexSnapRounder.h>
#include <Geometry/noding/snapround/MCIndexPointSnapper.h>
#include <Geometry/noding/SegmentString.h>
#include <Geometry/geom/PrecisionModel.h>

#include <memory>

namespace GEOMETRY {
namespace noding { // GEOMETRY::noding
namespace snapround { // GEOMETRY::noding::snapround

INLINE std::vector<SegmentString*>*
MCIndexSnapRounder::getNodedSubstrings() const
{
	return SegmentString::getNodedSubstrings(*nodedSegStrings);
}

INLINE
MCIndexSnapRounder::MCIndexSnapRounder(geom::PrecisionModel& nPm)
		:
		pm(nPm),
		scaleFactor(nPm.getScale()),
		pointSnapper(0)
{}

} // namespace GEOMETRY::noding::snapround
} // namespace GEOMETRY::noding
} // namespace GEOMETRY

#endif // GEOS_NODING_SNAPROUND_MCINDEXSNAPROUNDER_INL

