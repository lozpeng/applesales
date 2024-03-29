/**********************************************************************
 * $Id: InteriorPointPoint.cpp 1986 2007-06-08 15:27:42Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2005-2006 Refractions Research Inc.
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#include <Geometry/algorithm/InteriorPointPoint.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/GeometryCollection.h>
#include <Geometry/geom/LineString.h>
#include <Geometry/geom/Point.h>
#include <Geometry/geom/CoordinateSequence.h>

#include <typeinfo>
#include <cassert>

using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace algorithm { // geos.algorithm

/*public*/
InteriorPointPoint::InteriorPointPoint(const Geometry *g)
{
	minDistance=DoubleInfinity;
	if ( ! g->getCentroid(centroid) ) {
		hasInterior=false;
	} else {
		hasInterior=true;
		add(g);
	}
}

/*private*/
void
InteriorPointPoint::add(const Geometry *geom)
{
	const Point *po = dynamic_cast<const Point*>(geom);
	if ( po ) {
		add(po->getCoordinate());
		return;
	}

	const GeometryCollection *gc = dynamic_cast<const GeometryCollection*>(geom);
	if ( gc )
	{
		for(std::size_t i=0, n=gc->getNumGeometries(); i<n; i++) {
			add(gc->getGeometryN(i));
		}
	}
}

/*private*/
void
InteriorPointPoint::add(const Coordinate *point)
{
	assert ( point ); // we wouldn't been called if this was an empty geom
	double dist=point->distance(centroid);
	if (dist<minDistance) {
		interiorPoint=*point;
		minDistance=dist;
	}
}

/*public*/
bool
InteriorPointPoint::getInteriorPoint(Coordinate& ret) const
{
	if ( ! hasInterior ) return false;
	ret=interiorPoint;
	return true;
}

} // namespace GEOMETRY.algorithm
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.14  2006/03/21 11:12:23  strk
 * Cleanups: headers inclusion and Log section
 *
 * Revision 1.13  2006/03/09 16:46:45  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 **********************************************************************/

