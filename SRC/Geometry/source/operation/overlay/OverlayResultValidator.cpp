/**********************************************************************
 * $Id: OverlayResultValidator.cpp 1941 2006-12-13 10:55:55Z strk $
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
 ***********************************************************************
 *
 * Last port: operation/overlay/validate/OverlayResultValidator.java rev. 1.1
 * (we should move in GEOS too, probably)
 *
 **********************************************************************/

#include <Geometry/operation/overlay/OverlayResultValidator.h>
#include <Geometry/operation/overlay/FuzzyPointLocator.h>
#include <Geometry/operation/overlay/OffsetPointGenerator.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/MultiPoint.h>
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/geom/CoordinateSequenceFactory.h>

#include <cassert>
#include <functional>
#include <vector>
#include <memory> // for auto_ptr
#include <algorithm>

#ifndef GEOS_DEBUG
#define GEOS_DEBUG 0
#endif

#if GEOS_DEBUG
#include <iomanip> // for setprecision
#endif

#define COMPUTE_Z 1
#define USE_ELEVATION_MATRIX 1
#define USE_INPUT_AVGZ 0

using namespace std;
using namespace GEOMETRY::geom;
using namespace GEOMETRY::geomgraph;
using namespace GEOMETRY::algorithm;

namespace GEOMETRY {
namespace operation { // geos.operation
namespace overlay { // geos.operation.overlay

double OverlayResultValidator::_TOLERANCE = 0.000001;

namespace { // anonymous namespace

bool
isArea(const Geometry& g)
{
        GeometryTypeId type = g.getGeometryTypeId();
        if ( type == GEOS_POLYGON ) return true;
        if ( type == GEOS_MULTIPOLYGON ) return true;
#if GEOS_DEBUG
	cerr << "OverlayResultValidator: one of the geoms being checked is not a POLYGON or MULTIPOLYGON, blindly returning a positive answer (is valid)" << endl;
#endif
        return false;
}

auto_ptr<MultiPoint>
toMultiPoint(vector<Coordinate>& coords)
{
	const GeometryFactory& gf = *(GeometryFactory::getDefaultInstance());
	const CoordinateSequenceFactory& csf = 
			*(gf.getCoordinateSequenceFactory());

	auto_ptr< vector<Coordinate> > nc ( new vector<Coordinate>(coords) );
	auto_ptr<CoordinateSequence> cs(csf.create(nc.release()));

	auto_ptr<MultiPoint> mp ( gf.createMultiPoint(*cs) );

	return mp;
}

} // anonymous namespace


/* static public */
bool
OverlayResultValidator::isValid(const Geometry& geom0, const Geometry& geom1,
		OverlayOp::OpCode opCode,
		const Geometry& result)
{
	OverlayResultValidator validator(geom0, geom1, result);
	return validator.isValid(opCode);
}

/*public*/
OverlayResultValidator::OverlayResultValidator(
		const Geometry& geom0,
		const Geometry& geom1,
		const Geometry& result)
	:
	g0(geom0),
	g1(geom1),
	gres(result),
	fpl0(g0, _TOLERANCE),
	fpl1(g1, _TOLERANCE),
	fplres(gres, _TOLERANCE),
	invalidLocation()
{
}

/*public*/
bool
OverlayResultValidator::isValid(OverlayOp::OpCode overlayOp)
{
	// The check only works for areal geoms
#if 0 // now that FuzzyPointLocator extracts polygonal geoms,
      // there should be no problem here
	if ( ! isArea(g0) ) return true;
	if ( ! isArea(g1) ) return true;
	if ( ! isArea(gres) ) return true;
#endif

	addTestPts(g0);
	addTestPts(g1);
	addTestPts(gres);

	if (! testValid(overlayOp) )
	{
#if GEOS_DEBUG
	cerr << "OverlayResultValidator:" << endl
		<< "Points:" << *toMultiPoint(testCoords) << endl
		<< "Geom0: " << g0 << endl
		<< "Geom1: " << g1 << endl
		<< "Reslt: " << gres << endl
		<< "Locat: " << getInvalidLocation()
		<< endl;
#endif
		return false;
	}


	return true;
}

/*private*/
void
OverlayResultValidator::addTestPts(const Geometry& g)
{
	OffsetPointGenerator ptGen(g, 5 * _TOLERANCE);
	auto_ptr< vector<geom::Coordinate> > pts = ptGen.getPoints();
	testCoords.insert(testCoords.end(), pts->begin(), pts->end());
}

/*private*/
void
OverlayResultValidator::addVertices(const Geometry& g)
{
	// TODO: optimize this by not copying coordinates
	//       and pre-allocating memory
	auto_ptr<CoordinateSequence> cs ( g.getCoordinates() );
	const vector<Coordinate>* coords = cs->toVector();
	testCoords.insert(testCoords.end(), coords->begin(), coords->end());
}

/*private*/
bool
OverlayResultValidator::testValid(OverlayOp::OpCode overlayOp)
{
	for (size_t i=0, n=testCoords.size(); i<n; ++i)
	{
		Coordinate& pt = testCoords[i];
		if (! testValid(overlayOp, pt)) {
			invalidLocation = pt;
			return false;
		}
	}
	return true;
}

/*private*/
bool
OverlayResultValidator::testValid(OverlayOp::OpCode overlayOp,
		const Coordinate& pt)
{
	std::vector<geom::Location::Value> location(3);

	location[0] = fpl0.getLocation(pt);
	location[1] = fpl1.getLocation(pt);
	location[2] = fplres.getLocation(pt);

#if GEOS_DEBUG
	cerr << setprecision(10) << "Point " << pt << endl
		<< "Loc0: " << location[0] << endl
		<< "Loc1: " << location[1] << endl
		<< "Locr: " << location[2] << endl;
#endif

	/*
	 * If any location is on the Boundary, can't deduce anything,
	 * so just return true
	 */
	if ( find(location.begin(), location.end(), Location::BOUNDARY) != location.end() )
	{
#if GEOS_DEBUG
		cerr << "OverlayResultValidator: testpoint " << pt << " is on the boundary, blindly returning a positive answer (is valid)" << endl;
#endif
		return true;
	}

	return isValidResult(overlayOp, location);
}

/* private */
bool
OverlayResultValidator::isValidResult(OverlayOp::OpCode overlayOp,
	std::vector<geom::Location::Value>& location)
{
	bool expectedInterior = OverlayOp::isResultOfOp(location[0],
			location[1], overlayOp);

	bool resultInInterior = (location[2] == Location::INTERIOR);

	bool isValid = ! (expectedInterior ^ resultInInterior);

	return isValid;
}



} // namespace GEOMETRY.operation.overlay
} // namespace GEOMETRY.operation
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 **********************************************************************/

