/**********************************************************************
 * $Id: RepeatedPointTester.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_OP_REPEATEDPOINTTESTER_H
#define GEOS_OP_REPEATEDPOINTTESTER_H

#include <Geometry/geom/Coordinate.h> // for composition

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		//class Coordinate;
		class CoordinateSequence;
		class Geometry;
		class Polygon;
		class MultiPolygon;
		class MultiLineString;
		class GeometryCollection;
	}
}

namespace GEOMETRY {
namespace operation { // GEOMETRY::operation
namespace valid { // GEOMETRY::operation::valid

/** \brief
 * Implements the appropriate checks for repeated points
 * (consecutive identical coordinates) as defined in the
 * JTS spec.
 */
class RepeatedPointTester {
public:
	RepeatedPointTester() {};
	geom::Coordinate& getCoordinate();
	bool hasRepeatedPoint(const geom::Geometry *g);
	bool hasRepeatedPoint(const geom::CoordinateSequence *coord);
private:
	geom::Coordinate repeatedCoord;
	bool hasRepeatedPoint(const geom::Polygon *p);
	bool hasRepeatedPoint(const geom::GeometryCollection *gc);
	bool hasRepeatedPoint(const geom::MultiPolygon *gc);
	bool hasRepeatedPoint(const geom::MultiLineString *gc);
};


} // namespace GEOMETRY.operation.valid
} // namespace GEOMETRY.operation
} // namespace GEOMETRY

#endif // GEOS_OP_REPEATEDPOINTTESTER_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/20 16:57:44  strk
 * spatialindex.h and opValid.h headers split
 *
 **********************************************************************/

