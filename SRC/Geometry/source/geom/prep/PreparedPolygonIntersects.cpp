/**********************************************************************
 * $Id: PreparedPolygonIntersects.cpp 2331 2009-04-08 16:04:37Z pramsey $
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


#include <Geometry/geom/prep/PreparedPolygonIntersects.h>
#include <Geometry/geom/prep/PreparedPolygon.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/MultiPolygon.h>
#include <Geometry/geom/prep/PreparedPolygonPredicate.h>
#include <Geometry/noding/SegmentString.h>
#include <Geometry/noding/SegmentStringUtil.h>
#include <Geometry/noding/FastSegmentSetIntersectionFinder.h>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom
namespace prep { // GEOMETRY::geom::prep
//
// private:
//

//
// protected:
//

//
// public:
//
bool 
PreparedPolygonIntersects::intersects( const geom::Geometry * geom)
{
	// Do point-in-poly tests first, since they are cheaper and may result
	// in a quick positive result.
	// If a point of any test components lie in target, result is true
	bool isInPrepGeomArea = isAnyTestComponentInTargetArea( geom);
	if ( isInPrepGeomArea ) 
		return true;
	
	// If any segments intersect, result is true
	noding::SegmentString::ConstVect lineSegStr;
	noding::SegmentStringUtil::extractSegmentStrings( geom, lineSegStr );
	bool segsIntersect = prepPoly->getIntersectionFinder()->intersects( &lineSegStr);

	for ( size_t i = 0, ni = lineSegStr.size(); i < ni; i++ ) 
	{
		delete lineSegStr[ i ]->getCoordinates();
		delete lineSegStr[ i ];
	}
	
	if (segsIntersect) 
		return true;
	
	// If the test has dimension = 2 as well, it is necessary to
	// test for proper inclusion of the target.
	// Since no segments intersect, it is sufficient to test representative points.
	if ( geom->getDimension() == 2) 
	{
		// TODO: generalize this to handle GeometryCollections
		bool isPrepGeomInArea = isAnyTargetComponentInTestArea( geom, prepPoly->getRepresentativePoints());
		if ( isPrepGeomInArea ) 
			return true;
	}
	
	return false;
}

} // GEOMETRY::geom::prep
} // GEOMETRY::geom
} // geos

/**********************************************************************
 * $Log$
 *
 **********************************************************************/