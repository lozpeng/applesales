/**********************************************************************
 * $Id: IndexedPointInAreaLocator.cpp 2161 2008-08-18 16:29:09Z mloskot $
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


#include <Geometry/algorithm/locate/IndexedPointInAreaLocator.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/MultiPolygon.h>
#include <Geometry/geom/LineString.h>
#include <Geometry/geom/LineSegment.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/util/LinearComponentExtracter.h>
#include <Geometry/index/intervalrtree/SortedPackedIntervalRTree.h>
#include <Geometry/util/IllegalArgumentException.h>
#include <Geometry/algorithm/RayCrossingCounter.h>
#include <Geometry/index/ItemVisitor.h> 

#include <algorithm>
#include <typeinfo>

namespace GEOMETRY {
namespace algorithm { 
namespace locate { 
//
// private:
//
IndexedPointInAreaLocator::IntervalIndexedGeometry::IntervalIndexedGeometry( const geom::Geometry & g)
{
	index = new index::intervalrtree::SortedPackedIntervalRTree();
	init( g);
}

IndexedPointInAreaLocator::IntervalIndexedGeometry::~IntervalIndexedGeometry( )
{
	delete index;
}

void 
IndexedPointInAreaLocator::IntervalIndexedGeometry::init( const geom::Geometry & g)
{
	geom::LineString::ConstVect lines;
	geom::util::LinearComponentExtracter::getLines( g, lines);

	for ( size_t i = 0, ni = lines.size(); i < ni; i++ )
	{
		const geom::LineString * line = lines[ i ];
		geom::CoordinateSequence * pts = line->getCoordinates();

		addLine( pts);

		delete pts;
	}
}

void 
IndexedPointInAreaLocator::IntervalIndexedGeometry::addLine( geom::CoordinateSequence * pts)
{
	for ( size_t i = 1, ni = pts->size(); i < ni; i++ ) 
	{
		geom::LineSegment * seg = new geom::LineSegment( (*pts)[ i - 1 ], (*pts)[ i ]);

		double min = std::min( seg->p0.y, seg->p1.y);
		double max = std::max( seg->p0.y, seg->p1.y);
		
		index->insert( min, max, seg);
	}
} 


void 
IndexedPointInAreaLocator::buildIndex( const geom::Geometry & g)
{
	index = new IndexedPointInAreaLocator::IntervalIndexedGeometry( g);
}


//
// protected:
//

//
// public:
//
IndexedPointInAreaLocator::IndexedPointInAreaLocator( const geom::Geometry & g)
:	areaGeom( g)
{
	if (	typeid( areaGeom) != typeid( geom::Polygon)
		&&	typeid( areaGeom) != typeid( geom::MultiPolygon) ) 
		throw new util::IllegalArgumentException("Argument must be Polygonal");

	//areaGeom = g;
	
	buildIndex( areaGeom);
}

IndexedPointInAreaLocator::~IndexedPointInAreaLocator()
{
	delete index;
}

int 
IndexedPointInAreaLocator::locate( const geom::Coordinate * /*const*/ p)
{
	algorithm::RayCrossingCounter rcc( p);

	IndexedPointInAreaLocator::SegmentVisitor visitor( &rcc);

	index->query( p->y, p->y, &visitor);

	return rcc.getLocation();
}

void 
IndexedPointInAreaLocator::SegmentVisitor::visitItem( void * item)
{
	geom::LineSegment * seg = (geom::LineSegment *)item;

	counter->countSegment( &(*seg)[ 0 ], &(*seg)[ 1 ]);
}

void 
IndexedPointInAreaLocator::IntervalIndexedGeometry::query( double min, double max, index::ItemVisitor * visitor)
{
	index->query( min, max, visitor);
}


} // GEOMETRY::algorithm::locate
} // GEOMETRY::algorithm
} // geos

/**********************************************************************
 * $Log$
 *
 **********************************************************************/
