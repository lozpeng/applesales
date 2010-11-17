/**********************************************************************
 * $Id: SingleInteriorIntersectionFinder.cpp 2137 2008-07-25 21:00:09Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: noding/SingleInteriorIntersectionFinder.java rev. ??? (JTS-1.8)
 *
 **********************************************************************/

#include <Geometry/noding/SingleInteriorIntersectionFinder.h>
#include <Geometry/noding/SegmentString.h>
#include <Geometry/algorithm/LineIntersector.h>
#include <Geometry/geom/Coordinate.h>

using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace noding { // geos.noding

/*public (override) */
void
SingleInteriorIntersectionFinder::processIntersections(
	SegmentString* e0,  int segIndex0,
	SegmentString* e1,  int segIndex1)
{
	using GEOMETRY::geom::Coordinate;

	// short-circuit if intersection already found
	if (hasIntersection())
		return;
	
	// don't bother intersecting a segment with itself
	if (e0 == e1 && segIndex0 == segIndex1) return;

	const Coordinate& p00 = e0->getCoordinate(segIndex0);
	const Coordinate& p01 = e0->getCoordinate(segIndex0 + 1);
	const Coordinate& p10 = e1->getCoordinate(segIndex1);
	const Coordinate& p11 = e1->getCoordinate(segIndex1 + 1);
  
	li.computeIntersection(p00, p01, p10, p11);
//if (li.hasIntersection() && li.isProper()) Debug.println(li);

	if (li.hasIntersection())
	{
		if (li.isInteriorIntersection())
		{
			intSegments.resize(4);
			intSegments[0] = p00;
			intSegments[1] = p01;
			intSegments[2] = p10;
			intSegments[3] = p11;
	
			interiorIntersection = li.getIntersection(0);
		}
	}
}


} // namespace GEOMETRY.noding
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 **********************************************************************/
