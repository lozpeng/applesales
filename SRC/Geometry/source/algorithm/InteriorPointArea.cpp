/**********************************************************************
 * $Id: InteriorPointArea.cpp 1986 2007-06-08 15:27:42Z mloskot $
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

#include <Geometry/algorithm/InteriorPointArea.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/GeometryCollection.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/LineString.h>
#include <Geometry/geom/Envelope.h>
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/geom/CoordinateSequenceFactory.h>

#include <vector>
#include <typeinfo>

using namespace std;
using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace algorithm { // geos.algorithm

// file-statics
namespace {

  double avg(double a, double b){return (a+b)/2.0;}

}


/*public*/
InteriorPointArea::InteriorPointArea(const Geometry *g)
{
	foundInterior=false;
	maxWidth=0.0;
	factory=g->getFactory();
	add(g);
}

/*public*/
InteriorPointArea::~InteriorPointArea()
{
}

/*public*/
bool 
InteriorPointArea::getInteriorPoint(Coordinate& ret) const
{
	if ( ! foundInterior ) return false;

	ret=interiorPoint;
	return true;
}

/*public*/
void
InteriorPointArea::add(const Geometry *geom)
{
	const Polygon *poly = dynamic_cast<const Polygon*>(geom);
	if ( poly ) {
		addPolygon(geom);
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

/*public*/
void
InteriorPointArea::addPolygon(const Geometry *geometry)
{
	LineString *bisector=horizontalBisector(geometry);
	Geometry *intersections=bisector->intersection(geometry);
	const Geometry *widestIntersection=widestGeometry(intersections);
	const Envelope *env=widestIntersection->getEnvelopeInternal();
	double width=env->getWidth();
	if (!foundInterior || width>maxWidth) {
		env->centre(interiorPoint);
		maxWidth = width;
		foundInterior=true;
	}
	//delete env;
	delete bisector;
	delete intersections;
}

//@return if geometry is a collection, the widest sub-geometry; otherwise,
//the geometry itself
const Geometry*
InteriorPointArea::widestGeometry(const Geometry *geometry)
{
	const GeometryCollection *gc = dynamic_cast<const GeometryCollection*>(geometry);
	if ( gc ) {
		return widestGeometry(gc);
	} else {
		return geometry;
	}
}

const Geometry*
InteriorPointArea::widestGeometry(const GeometryCollection* gc) {
	if (gc->isEmpty()) {
		return gc;
	}
	const Geometry* widestGeometry=gc->getGeometryN(0);

	//Start at 1
	for(std::size_t i=1, n=gc->getNumGeometries(); i<n; i++)
	{
		const Envelope *env1(gc->getGeometryN(i)->getEnvelopeInternal());
		const Envelope *env2(widestGeometry->getEnvelopeInternal());
		if (env1->getWidth()>env2->getWidth()) {
				widestGeometry=gc->getGeometryN(i);
		}
	}
	return widestGeometry;
}

LineString*
InteriorPointArea::horizontalBisector(const Geometry *geometry)
{
	const Envelope *envelope=geometry->getEnvelopeInternal();
	// Assert: for areas, minx <> maxx
	double avgY=avg(envelope->getMinY(),envelope->getMaxY());

	vector<Coordinate>*cv=new vector<Coordinate>(2);
	(*cv)[0].x = envelope->getMinX();
	(*cv)[0].y = avgY;
	(*cv)[1].x = envelope->getMaxX();
	(*cv)[1].y = avgY;

	//delete envelope;

	CoordinateSequence *cl = factory->getCoordinateSequenceFactory()->create(cv);

	LineString *ret = factory->createLineString(cl);
	//delete cl;
	return ret;
}

} // namespace GEOMETRY.algorithm
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.22  2006/04/07 09:54:29  strk
 * Geometry::getNumGeometries() changed to return 'unsigned int'
 * rather then 'int'
 *
 * Revision 1.21  2006/03/21 11:12:23  strk
 * Cleanups: headers inclusion and Log section
 *
 * Revision 1.20  2006/03/09 16:46:45  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 **********************************************************************/

