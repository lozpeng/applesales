/**********************************************************************
 * $Id: CentroidLine.cpp 1986 2007-06-08 15:27:42Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 * Copyright (C) 2005 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 **********************************************************************/

#include <Geometry/algorithm/CentroidLine.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/GeometryCollection.h>
#include <Geometry/geom/LineString.h>

#include <typeinfo>

using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace algorithm { // geos.algorithm

/*public*/
void
CentroidLine::add(const Geometry *geom)
{
	const LineString* ls = dynamic_cast<const LineString*>(geom);
	if ( ls )
	{
		add(ls->getCoordinatesRO());
		return;
	}

	const GeometryCollection* gc = dynamic_cast<const GeometryCollection*>(geom);
	if (gc)
	{
        for(std::size_t i=0, n=gc->getNumGeometries(); i<n; i++) {
			add(gc->getGeometryN(i));
		}
	}
}

/*public*/
void
CentroidLine::add(const CoordinateSequence *pts)
{
	std::size_t const npts=pts->getSize();

	for(std::size_t i=1; i<npts; ++i)
	{
		const Coordinate &p1=pts->getAt(i-1);
		const Coordinate &p2=pts->getAt(i);

		double segmentLen=p1.distance(p2);
		totalLength+=segmentLen;
		double midx=(p1.x+p2.x)/2;
		centSum.x+=segmentLen*midx;
		double midy=(p1.y+p2.y)/2;
		centSum.y+=segmentLen*midy;
	}
}

Coordinate *
CentroidLine::getCentroid() const
{
	return new Coordinate(centSum.x/totalLength, centSum.y/totalLength);
}

bool
CentroidLine::getCentroid(Coordinate& c) const
{
	if ( totalLength == 0.0 ) return false;
	c=Coordinate(centSum.x/totalLength, centSum.y/totalLength);
	return true;
}

} // namespace GEOMETRY.algorithm
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.16  2006/03/21 11:12:23  strk
 * Cleanups: headers inclusion and Log section
 *
 * Revision 1.15  2006/03/09 16:46:45  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/

