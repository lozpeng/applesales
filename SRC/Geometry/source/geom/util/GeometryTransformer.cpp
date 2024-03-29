/**********************************************************************
 * $Id: GeometryTransformer.cpp 2521 2009-05-27 18:20:09Z pramsey $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: geom/util/GeometryTransformer.java rev. 1.6 (JTS-1.7.1+)
 *
 **********************************************************************/

#include <Geometry/geom/util/GeometryTransformer.h>
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/geom/CoordinateSequenceFactory.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/MultiPoint.h>
#include <Geometry/geom/MultiPolygon.h>
#include <Geometry/geom/MultiLineString.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/Point.h>
#include <Geometry/geom/LineString.h>
#include <Geometry/geom/LinearRing.h>
#include <Geometry/geom/GeometryCollection.h>
#include <Geometry/util/IllegalArgumentException.h>
#include <Geometry/util.h>

#include <typeinfo>
#include <cassert>

#ifndef GEOS_DEBUG
#define GEOS_DEBUG 0
#endif

#ifdef GEOS_DEBUG
#include <iostream>
#endif

using namespace std;

namespace GEOMETRY {
namespace geom { // geos.geom
namespace util { // geos.geom.util


/*public*/
GeometryTransformer::GeometryTransformer()
	:
	factory(NULL),
	inputGeom(NULL),
	pruneEmptyGeometry(true),
	preserveGeometryCollectionType(true),
	preserveCollections(false),
	preserveType(false)
{}

GeometryTransformer::~GeometryTransformer()
{
}

/*public*/
auto_ptr<Geometry>
GeometryTransformer::transform(const Geometry* nInputGeom)
{
	using GEOMETRY::util::IllegalArgumentException;

#if GEOS_DEBUG
	std::cerr << "GeometryTransformer::transform(Geometry " << nInputGeom << ");" << std::endl;
#endif

	inputGeom = nInputGeom;
	factory = inputGeom->getFactory();

	if ( const Point* p=dynamic_cast<const Point*>(inputGeom) )
		return transformPoint(p, NULL);
	if ( const MultiPoint* mp=dynamic_cast<const MultiPoint*>(inputGeom) )
		return transformMultiPoint(mp, NULL);
	if ( const LinearRing* lr=dynamic_cast<const LinearRing*>(inputGeom) )
		return transformLinearRing(lr, NULL);
	if ( const LineString* ls=dynamic_cast<const LineString*>(inputGeom) )
		return transformLineString(ls, NULL);
	if ( const MultiLineString* mls=dynamic_cast<const MultiLineString*>(inputGeom) )
		return transformMultiLineString(mls, NULL);
	if ( const Polygon* p=dynamic_cast<const Polygon*>(inputGeom) )
		return transformPolygon(p, NULL);
	if ( const MultiPolygon* mp=dynamic_cast<const MultiPolygon*>(inputGeom) )
		return transformMultiPolygon(mp, NULL);
	if ( const GeometryCollection* gc=dynamic_cast<const GeometryCollection*>(inputGeom) )
		return transformGeometryCollection(gc, NULL);

	throw IllegalArgumentException("Unknown Geometry subtype.");
}
 
std::auto_ptr<CoordinateSequence>
GeometryTransformer::createCoordinateSequence(
		std::auto_ptr< std::vector<Coordinate> > coords)
{
	return std::auto_ptr<CoordinateSequence>(
		factory->getCoordinateSequenceFactory()->create(
				coords.release())
	);
}

std::auto_ptr<CoordinateSequence>
GeometryTransformer::transformCoordinates(
		const CoordinateSequence* coords,
		const Geometry* parent)
{

    UNREFERENCED_PARAMETER(parent);
#if GEOS_DEBUG
	std::cerr << "GeometryTransformer::transformCoordinates(CoordinateSequence " << coords <<", Geometry " << parent << ");" << std::endl;
#endif

	return std::auto_ptr<CoordinateSequence>(coords->clone());
}

Geometry::AutoPtr
GeometryTransformer::transformPoint(
		const Point* geom,
		const Geometry* parent)
{
    UNREFERENCED_PARAMETER(parent);

#if GEOS_DEBUG
	std::cerr << "GeometryTransformer::transformPoint(Point " << geom <<", Geometry " << parent << ");" << std::endl;
#endif

	CoordinateSequence::AutoPtr cs(transformCoordinates(
		geom->getCoordinatesRO(), geom));

	return Geometry::AutoPtr(factory->createPoint(cs.release()));
}

Geometry::AutoPtr
GeometryTransformer::transformMultiPoint(
		const MultiPoint* geom,
		const Geometry* parent)
{
    UNREFERENCED_PARAMETER(parent);

#if GEOS_DEBUG
	std::cerr << "GeometryTransformer::transformMultiPoint(MultiPoint " << geom <<", Geometry " << parent << ");" << std::endl;
#endif

	vector<Geometry*>* transGeomList = new vector<Geometry*>();

	for (unsigned int i=0, n=geom->getNumGeometries(); i<n; i++)
	{
		assert(dynamic_cast<const Point*>(geom->getGeometryN(i)));
		const Point* p = static_cast<const Point*>(
				geom->getGeometryN(i));

		Geometry::AutoPtr transformGeom = transformPoint(p, geom);
		if ( transformGeom.get() == NULL ) continue;
		if ( transformGeom->isEmpty() ) continue;

		// If an exception is thrown we'll leak
		transGeomList->push_back(transformGeom.release());
	}

	return Geometry::AutoPtr(factory->buildGeometry(transGeomList));

}

Geometry::AutoPtr
GeometryTransformer::transformLinearRing(
		const LinearRing* geom,
		const Geometry* parent)
{
    UNREFERENCED_PARAMETER(parent);

#if GEOS_DEBUG
	std::cerr << "GeometryTransformer::transformLinearRing(LinearRing " << geom <<", Geometry " << parent << ");" << std::endl;
#endif

	CoordinateSequence::AutoPtr seq(transformCoordinates(
		geom->getCoordinatesRO(), geom));

	unsigned int seqSize = seq->size();

	// ensure a valid LinearRing
	if ( seqSize > 0 && seqSize < 4 && ! preserveType )
	{
		return factory->createLineString(seq);
	}

	return factory->createLinearRing(seq);

}

Geometry::AutoPtr
GeometryTransformer::transformLineString(
		const LineString* geom,
		const Geometry* parent)
{
    UNREFERENCED_PARAMETER(parent);

#if GEOS_DEBUG
	std::cerr << "GeometryTransformer::transformLineString(LineString " << geom <<", Geometry " << parent << ");" << std::endl;
#endif

	// should check for 1-point sequences and downgrade them to points
	return factory->createLineString(
		transformCoordinates(geom->getCoordinatesRO(), geom));
}

Geometry::AutoPtr
GeometryTransformer::transformMultiLineString(
		const MultiLineString* geom,
		const Geometry* parent)
{
    UNREFERENCED_PARAMETER(parent);

#if GEOS_DEBUG
	std::cerr << "GeometryTransformer::transformMultiLineString(MultiLineString " << geom <<", Geometry " << parent << ");" << std::endl;
#endif

	vector<Geometry*>* transGeomList = new vector<Geometry*>();

	for (unsigned int i=0, n=geom->getNumGeometries(); i<n; i++)
	{
		assert(dynamic_cast<const LineString*>(geom->getGeometryN(i)));
		const LineString* l = static_cast<const LineString*>(
				geom->getGeometryN(i));

		Geometry::AutoPtr transformGeom = transformLineString(l, geom);
		if ( transformGeom.get() == NULL ) continue;
		if ( transformGeom->isEmpty() ) continue;

		// If an exception is thrown we'll leak
		transGeomList->push_back(transformGeom.release());
	}

	return Geometry::AutoPtr(factory->buildGeometry(transGeomList));

}

Geometry::AutoPtr
GeometryTransformer::transformPolygon(
		const Polygon* geom,
		const Geometry* parent)
{
    UNREFERENCED_PARAMETER(parent);

#if GEOS_DEBUG
	std::cerr << "GeometryTransformer::transformPolygon(Polygon " << geom <<", Geometry " << parent << ");" << std::endl;
#endif

	bool isAllValidLinearRings = true;

	assert(dynamic_cast<const LinearRing*>(geom->getExteriorRing()));
	const LinearRing* lr = static_cast<const LinearRing*>(
			geom->getExteriorRing());

	Geometry::AutoPtr shell = transformLinearRing(lr, geom);
	if ( shell.get() == NULL
		|| ! dynamic_cast<LinearRing*>(shell.get()) 
		|| shell->isEmpty() )
	{
		isAllValidLinearRings = false;
	}

	vector<Geometry*>* holes = new vector<Geometry*>();
	for (unsigned int i=0, n=geom->getNumInteriorRing(); i<n; i++)
	{
		assert(dynamic_cast<const LinearRing*>(
			geom->getInteriorRingN(i)));
		const LinearRing* lr = static_cast<const LinearRing*>(
			geom->getInteriorRingN(i));

		Geometry::AutoPtr hole(transformLinearRing(lr, geom));

		if ( hole.get() == NULL || hole->isEmpty() ) {
			continue;
		}

		if ( ! dynamic_cast<LinearRing*>(hole.get()) )
		{
			isAllValidLinearRings = false;
		}

		holes->push_back(hole.release());
	}

	if ( isAllValidLinearRings)
	{
		Geometry* sh = shell.release();
		assert(dynamic_cast<LinearRing*>(sh));
		return Geometry::AutoPtr(factory->createPolygon(
			static_cast<LinearRing*>(sh),
			holes));
	}
	else
	{
		// would like to use a manager constructor here
		vector<Geometry*>* components = new vector<Geometry*>();
		if ( shell.get() != NULL ) {
			components->push_back(shell.release());
		}

		components->insert(components->end(),
			holes->begin(), holes->end());

		delete holes; // :(

		return Geometry::AutoPtr(factory->buildGeometry(components));
	}

}

Geometry::AutoPtr
GeometryTransformer::transformMultiPolygon(
		const MultiPolygon* geom,
		const Geometry* parent)
{
    UNREFERENCED_PARAMETER(parent);

#if GEOS_DEBUG
	std::cerr << "GeometryTransformer::transformMultiPolygon(MultiPolygon " << geom <<", Geometry " << parent << ");" << std::endl;
#endif

	auto_ptr< vector<Geometry*> > transGeomList( new vector<Geometry*>() );

	for (unsigned int i=0, n=geom->getNumGeometries(); i<n; i++)
	{
		assert(dynamic_cast<const Polygon*>(geom->getGeometryN(i)));
		const Polygon* p = static_cast<const Polygon*>(
				geom->getGeometryN(i));

		Geometry::AutoPtr transformGeom = transformPolygon(p, geom);
		if ( transformGeom.get() == NULL ) continue;
		if ( transformGeom->isEmpty() ) continue;

		// If an exception is thrown we'll leak
		transGeomList->push_back(transformGeom.release());
	}

	return Geometry::AutoPtr(factory->buildGeometry(transGeomList.release()));

}

Geometry::AutoPtr
GeometryTransformer::transformGeometryCollection(
		const GeometryCollection* geom,
		const Geometry* parent)
{
    UNREFERENCED_PARAMETER(parent);

#if GEOS_DEBUG
	std::cerr << "GeometryTransformer::transformGeometryCollection(GeometryCollection " << geom <<", Geometry " << parent << ");" << std::endl;
#endif

	vector<Geometry*>* transGeomList = new vector<Geometry*>();

	for (unsigned int i=0, n=geom->getNumGeometries(); i<n; i++)
	{
		Geometry::AutoPtr transformGeom = transform(
			geom->getGeometryN(i)); // no parent ?
		if ( transformGeom.get() == NULL ) continue;
		if ( pruneEmptyGeometry && transformGeom->isEmpty() ) continue;

		// If an exception is thrown we'll leak
		transGeomList->push_back(transformGeom.release());
	}

	if ( preserveGeometryCollectionType )
	{
		return Geometry::AutoPtr(factory->createGeometryCollection(
			transGeomList));
	}
	else
	{
		return Geometry::AutoPtr(factory->buildGeometry(transGeomList));
	}

}


} // namespace GEOMETRY.geom.util
} // namespace GEOMETRY.geom
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.3  2006/06/19 21:20:22  strk
 * updated port info
 *
 * Revision 1.2  2006/04/11 16:04:34  strk
 * GEOMETRY::simplify::DouglasPeukerSimplifier class + unit test
 *
 * Revision 1.1  2006/04/11 12:21:48  strk
 * GeometryTransformer class ported
 *
 **********************************************************************/

