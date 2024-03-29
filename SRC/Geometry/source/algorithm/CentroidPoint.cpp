/**********************************************************************
 * $Id: CentroidPoint.cpp 1986 2007-06-08 15:27:42Z mloskot $
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

#include <Geometry/algorithm/CentroidPoint.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/GeometryCollection.h>
#include <Geometry/geom/MultiPoint.h>
#include <Geometry/geom/Point.h>

#include <typeinfo>

using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace algorithm { // geos.algorithm


void
CentroidPoint::add(const Geometry *geom)
{
	if (typeid(*geom)==typeid(Point)) {
		add(geom->getCoordinate());
	} else if ((typeid(*geom)==typeid(GeometryCollection)) ||
				(typeid(*geom)==typeid(MultiPoint))) {
		GeometryCollection *gc=(GeometryCollection*) geom;
		for(std::size_t i=0, n=gc->getNumGeometries(); i<n; ++i)
		{
			add(gc->getGeometryN(i));
		}
	}
}

void
CentroidPoint::add(const Coordinate *pt)
{
	ptCount+=1;
	centSum.x += pt->x;
	centSum.y += pt->y;
}

Coordinate*
CentroidPoint::getCentroid() const
{
	return new Coordinate(centSum.x/ptCount, centSum.y/ptCount);
}

bool
CentroidPoint::getCentroid(Coordinate& ret) const
{
	if ( ptCount == 0.0 ) return false;
	ret=Coordinate(centSum.x/ptCount, centSum.y/ptCount);
	return true;
}

} // namespace GEOMETRY.algorithm
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.12  2006/04/07 09:54:29  strk
 * Geometry::getNumGeometries() changed to return 'unsigned int'
 * rather then 'int'
 *
 * Revision 1.11  2006/03/21 11:12:23  strk
 * Cleanups: headers inclusion and Log section
 *
 * Revision 1.10  2006/03/09 16:46:45  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 **********************************************************************/

