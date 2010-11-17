/**********************************************************************
 * $Id: MCIndexNoder.inl 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_NODINGMCINDEXNODER_INL
#define GEOS_NODINGMCINDEXNODER_INL

#include <Geometry/noding/MCIndexNoder.h>
#include <Geometry/noding/SegmentString.h>

#include <cassert>

namespace GEOMETRY {
namespace noding { // GEOMETRY::noding

INLINE index::SpatialIndex&
MCIndexNoder::getIndex()
{
	return index;
}

INLINE std::vector<SegmentString*>*
MCIndexNoder::getNodedSubstrings() const
{
	assert(nodedSegStrings); // must have colled computeNodes before!
	return SegmentString::getNodedSubstrings(*nodedSegStrings);
}

} // namespace GEOMETRY::noding
} // namespace GEOMETRY

#endif // GEOS_NODINGMCINDEXNODER_INL

