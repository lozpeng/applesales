/**********************************************************************
 * $Id: DouglasPeuckerSimplifier.cpp 2127 2008-05-20 21:25:21Z mloskot $
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
 * Last port: simplify/DouglasPeuckerSimplifier.java rev. 1.5 (JTS-1.7)
 *
 **********************************************************************/

#include <Geometry/simplify/DouglasPeuckerSimplifier.h>
#include <Geometry/simplify/DouglasPeuckerLineSimplifier.h>
#include <Geometry/geom/Geometry.h> // for AutoPtr typedefs
#include <Geometry/geom/MultiPolygon.h> 
#include <Geometry/geom/CoordinateSequence.h> // for AutoPtr typedefs
#include <Geometry/geom/GeometryFactory.h> 
#include <Geometry/geom/CoordinateSequenceFactory.h> 
#include <Geometry/geom/util/GeometryTransformer.h> // for DPTransformer inheritance
#include <Geometry/util/IllegalArgumentException.h>
#include <Geometry/util.h>

#include <memory> // for auto_ptr
#include <cassert>

#ifndef GEOS_DEBUG
#define GEOS_DEBUG 0
#endif

#ifdef GEOS_DEBUG
#include <iostream>
#endif

using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace simplify { // GEOMETRY::simplify

class DPTransformer: public geom::util::GeometryTransformer {

public:

	DPTransformer(double tolerance);

protected:

	CoordinateSequence::AutoPtr transformCoordinates(
			const CoordinateSequence* coords,
			const Geometry* parent);

	Geometry::AutoPtr transformPolygon(
			const Polygon* geom,
			const Geometry* parent);

	Geometry::AutoPtr transformMultiPolygon(
			const MultiPolygon* geom,
			const Geometry* parent);

private:

	/*
	 * Creates a valid area geometry from one that possibly has
	 * bad topology (i.e. self-intersections).
	 * Since buffer can handle invalid topology, but always returns
	 * valid geometry, constructing a 0-width buffer "corrects" the
	 * topology.
	 * Note this only works for area geometries, since buffer always returns
	 * areas.  This also may return empty geometries, if the input
	 * has no actual area.
	 *
	 * @param roughAreaGeom an area geometry possibly containing
	 *        self-intersections
	 * @return a valid area geometry
	 */
	Geometry::AutoPtr createValidArea(const Geometry* roughAreaGeom);

	double distanceTolerance;

};

DPTransformer::DPTransformer(double t)
	:
	distanceTolerance(t)
{
}

Geometry::AutoPtr
DPTransformer::createValidArea(const Geometry* roughAreaGeom)
{
	return Geometry::AutoPtr(roughAreaGeom->buffer(0.0));
}

CoordinateSequence::AutoPtr
DPTransformer::transformCoordinates(
		const CoordinateSequence* coords,
		const Geometry* parent)
{
    UNREFERENCED_PARAMETER(parent);

	const Coordinate::Vect* inputPts = coords->toVector();
	assert(inputPts);

	std::auto_ptr<Coordinate::Vect> newPts =
			DouglasPeuckerLineSimplifier::simplify(*inputPts,
				distanceTolerance);

	return CoordinateSequence::AutoPtr(
		factory->getCoordinateSequenceFactory()->create(
			newPts.release()
		));
}

Geometry::AutoPtr
DPTransformer::transformPolygon(
		const Polygon* geom,
		const Geometry* parent)
{

#if GEOS_DEBUG
	std::cerr << "DPTransformer::transformPolygon(Polygon " << geom << ", Geometry " << parent << ");" << std::endl;
#endif

	Geometry::AutoPtr roughGeom(GeometryTransformer::transformPolygon(geom, parent));

        // don't try and correct if the parent is going to do this
	if ( dynamic_cast<const MultiPolygon*>(parent) )
	{
		return roughGeom;
	}

	return createValidArea(roughGeom.get());
}

Geometry::AutoPtr
DPTransformer::transformMultiPolygon(
		const MultiPolygon* geom,
		const Geometry* parent)
{
#if GEOS_DEBUG
	std::cerr << "DPTransformer::transformMultiPolygon(MultiPolygon " << geom << ", Geometry " << parent << ");" << std::endl;
#endif
	Geometry::AutoPtr roughGeom(GeometryTransformer::transformMultiPolygon(geom, parent));
        return createValidArea(roughGeom.get());
}

/************************************************************************/



//DouglasPeuckerSimplifier::

/*public static*/
Geometry::AutoPtr
DouglasPeuckerSimplifier::simplify(const Geometry* geom,
		double tolerance)
{
	DouglasPeuckerSimplifier tss(geom);
	tss.setDistanceTolerance(tolerance);
	return tss.getResultGeometry();
}

/*public*/
DouglasPeuckerSimplifier::DouglasPeuckerSimplifier(const Geometry* geom)
	:
	inputGeom(geom)
{
}

/*public*/
void
DouglasPeuckerSimplifier::setDistanceTolerance(double tol)
{
	if (tol < 0.0)
		throw util::IllegalArgumentException("Tolerance must be non-negative");
	distanceTolerance = tol;
}

Geometry::AutoPtr
DouglasPeuckerSimplifier::getResultGeometry()
{
	DPTransformer t(distanceTolerance);
	return t.transform(inputGeom);

}

} // namespace GEOMETRY::simplify
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.2  2006/04/13 16:44:49  strk
 * Fixed a bug in DPTransformer handling of MultiPolygons
 *
 * Revision 1.1  2006/04/11 16:04:34  strk
 * GEOMETRY::simplify::DouglasPeukerSimplifier class + unit test
 *
 **********************************************************************/
