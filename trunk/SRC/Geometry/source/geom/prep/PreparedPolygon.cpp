/**********************************************************************
 * $Id: PreparedPolygon.cpp 2194 2008-09-23 23:01:00Z mloskot $
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

#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/prep/PreparedPolygon.h>
#include <Geometry/geom/prep/PreparedPolygonContains.h>
#include <Geometry/geom/prep/PreparedPolygonContainsProperly.h>
#include <Geometry/geom/prep/PreparedPolygonCovers.h>
#include <Geometry/geom/prep/PreparedPolygonIntersects.h>
#include <Geometry/geom/prep/PreparedPolygonPredicate.h>
#include <Geometry/noding/FastSegmentSetIntersectionFinder.h>
#include <Geometry/noding/SegmentStringUtil.h>
#include <Geometry/operation/predicate/RectangleContains.h>
#include <Geometry/operation/predicate/RectangleIntersects.h>
#include <Geometry/algorithm/locate/PointOnGeometryLocator.h>
#include <Geometry/algorithm/locate/IndexedPointInAreaLocator.h>
// std
#include <cstddef>

namespace GEOMETRY {
namespace geom { // geos.geom
namespace prep { // geos.geom.prep
//
// public:
//
PreparedPolygon::PreparedPolygon(const geom::Geometry * geom) 
    : BasicPreparedGeometry(geom), segIntFinder(0), ptOnGeomLoc(0)
{
	isRectangle = getGeometry().isRectangle();
}

PreparedPolygon::~PreparedPolygon()
{
	delete segIntFinder;
	delete ptOnGeomLoc;

	for ( std::size_t i = 0, ni = segStrings.size(); i < ni; i++ )
	{
		delete segStrings[ i ]->getCoordinates();
		delete segStrings[ i ];
	}
}


noding::FastSegmentSetIntersectionFinder * 
PreparedPolygon::
getIntersectionFinder() const
{
	if (! segIntFinder)
	{
		noding::SegmentStringUtil::extractSegmentStrings( &getGeometry(), segStrings );
		segIntFinder = new noding::FastSegmentSetIntersectionFinder( &segStrings );
	}
	return segIntFinder;
}

algorithm::locate::PointOnGeometryLocator * 
PreparedPolygon::
getPointLocator() const
{
	if (! ptOnGeomLoc) 
		ptOnGeomLoc = new algorithm::locate::IndexedPointInAreaLocator( getGeometry() );

	return ptOnGeomLoc;
}

bool 
PreparedPolygon::
contains( const geom::Geometry * g) const
{
    // short-circuit test
    if ( !envelopeCovers( g) ) 
		return false;
  	
    // optimization for rectangles
    if ( isRectangle )
    {
        geom::Geometry const& geom = getGeometry();
        geom::Polygon const& poly = static_cast<geom::Polygon const&>(geom);
        
        return operation::predicate::RectangleContains::contains(poly, *g);
    }

	return PreparedPolygonContains::contains( this, g);
}

bool 
PreparedPolygon::
containsProperly( const geom::Geometry* g) const
{
    // short-circuit test
    if ( !envelopeCovers( g) ) 
		return false;

	return PreparedPolygonContainsProperly::containsProperly( this, g);
}

bool 
PreparedPolygon::
covers( const geom::Geometry* g) const
{
    // short-circuit test
    if ( !envelopeCovers( g) ) 
		return false;

    // optimization for rectangle arguments
    if ( isRectangle) 
		return true;

	return PreparedPolygonCovers::covers( this, g);
}

bool 
PreparedPolygon::
intersects( const geom::Geometry* g) const
{
  	// envelope test
  	if ( !envelopesIntersect( g) ) 
		return false;
  	
    // optimization for rectangles
    if ( isRectangle )
    {
        geom::Geometry const& geom = getGeometry();
        geom::Polygon const& poly = static_cast<geom::Polygon const&>(geom);
        
        return operation::predicate::RectangleIntersects::intersects(poly, *g);
    }
    
	return PreparedPolygonIntersects::intersects( this, g);
}

} // namespace GEOMETRY.geom.prep
} // namespace GEOMETRY.geom
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 *
 **********************************************************************/

