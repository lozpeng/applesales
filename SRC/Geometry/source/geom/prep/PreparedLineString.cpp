/**********************************************************************
 * $Id: PreparedLineString.cpp 2158 2008-08-18 16:24:18Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/


#include <Geometry/geom/prep/PreparedLineString.h>
#include <Geometry/geom/prep/PreparedLineStringIntersects.h>
#include <Geometry/noding/SegmentStringUtil.h>
#include <Geometry/noding/FastSegmentSetIntersectionFinder.h>

namespace GEOMETRY {
namespace geom { // geos.geom
namespace prep { // geos.geom.prep

/*
 * public:
 */

noding::FastSegmentSetIntersectionFinder * 
PreparedLineString::getIntersectionFinder()
{
	if (! segIntFinder)
	{
		//noding::SegmentString::ConstVect ss;
		noding::SegmentStringUtil::extractSegmentStrings( &getGeometry(), segStrings );
		segIntFinder = new noding::FastSegmentSetIntersectionFinder( &segStrings );

		//for ( size_t i = 0, ni = ss.size(); i < ni; i++ )
		//	delete ss[ i ];
	}

	return segIntFinder;
}

bool 
PreparedLineString::intersects(const geom::Geometry * g) const
{
	if (! envelopesIntersect(g))
    {
        return false;
    }
    
    PreparedLineString& prep = *(const_cast<PreparedLineString*>(this));
    
    return PreparedLineStringIntersects::intersects(prep, g);
}

} // namespace GEOMETRY.geom.prep
} // namespace GEOMETRY.geom
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 *
 **********************************************************************/

