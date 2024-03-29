/**********************************************************************
 * $Id: PreparedPolygonContainsProperly.cpp 2331 2009-04-08 16:04:37Z pramsey $
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


#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/MultiPolygon.h>
#include <Geometry/geom/prep/PreparedPolygon.h>
#include <Geometry/geom/prep/PreparedPolygonContainsProperly.h>
#include <Geometry/geom/prep/PreparedPolygonPredicate.h>
#include <Geometry/noding/SegmentString.h>
#include <Geometry/noding/SegmentStringUtil.h>
#include <Geometry/noding/FastSegmentSetIntersectionFinder.h>

namespace GEOMETRY {
namespace geom { // geos.geom
namespace prep { // geos.geom.prep
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
PreparedPolygonContainsProperly::containsProperly( const geom::Geometry * geom)
{
	// Do point-in-poly tests first, since they are cheaper and may result
	// in a quick negative result.
	// If a point of any test components does not lie in target, result is false
	bool isAllInPrepGeomArea = isAllTestComponentsInTargetInterior( geom);
	if ( !isAllInPrepGeomArea ) 
		return false;
	
	// If any segments intersect, result is false
	noding::SegmentString::ConstVect lineSegStr;
	noding::SegmentStringUtil::extractSegmentStrings( geom, lineSegStr);
	bool segsIntersect = prepPoly->getIntersectionFinder()->intersects( &lineSegStr);

	for ( size_t i = 0, ni = lineSegStr.size(); i < ni; i++ ) {
		delete lineSegStr[ i ]->getCoordinates();
		delete lineSegStr[ i ];
	}

	if (segsIntersect) 
		return false;
	
	if (	geom->getGeometryTypeId() == GEOMETRY::geom::GEOS_MULTIPOLYGON  
		||	geom->getGeometryTypeId() == GEOMETRY::geom::GEOS_POLYGON )
	{
		// TODO: generalize this to handle GeometryCollections
		bool isTargetGeomInTestArea = isAnyTargetComponentInTestArea( geom, prepPoly->getRepresentativePoints());
		if (isTargetGeomInTestArea) 
			return false;
	}
	
	return true;
}

} // namespace GEOMETRY.geom.prep
} // namespace GEOMETRY.geom
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 *
 **********************************************************************/
