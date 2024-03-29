/**********************************************************************
 * $Id: ElevationMatrix.h 1820 2006-09-06 16:54:23Z mloskot $
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
 **********************************************************************/

#ifndef GEOS_OP_OVERLAY_ELEVATIONMATRIX_H
#define GEOS_OP_OVERLAY_ELEVATIONMATRIX_H

#include <vector>
#include <string>

#include <Geometry/geom/CoordinateFilter.h> // for inheritance 
#include <Geometry/geom/Envelope.h> // for composition
#include <Geometry/operation/overlay/ElevationMatrixCell.h> // for composition

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class Coordinate;
		class Geometry;
	}
	namespace operation {
		namespace overlay {
			class ElevationMatrixFilter;
			class ElevationMatrix;
		}
	}
}

namespace GEOMETRY {
namespace operation { // GEOMETRY::operation
namespace overlay { // GEOMETRY::operation::overlay


/*
 * This is the CoordinateFilter used by ElevationMatrix.
 * filter_ro is used to add Geometry Coordinate's Z
 * values to the matrix.
 * filter_rw is used to actually elevate Geometries.
 */
class ElevationMatrixFilter: public geom::CoordinateFilter
{
public:
	ElevationMatrixFilter(ElevationMatrix &em);
	~ElevationMatrixFilter();
	void filter_rw(geom::Coordinate *c) const;
	void filter_ro(const geom::Coordinate *c);
private:
	ElevationMatrix &em;
	double avgElevation;
};


/*
 */
class ElevationMatrix {
friend class ElevationMatrixFilter;
public:
	ElevationMatrix(const geom::Envelope &extent, unsigned int rows,
		unsigned int cols);
	~ElevationMatrix();
	void add(const geom::Geometry *geom);
	void elevate(geom::Geometry *geom) const;
	// set Z value for each cell w/out one
	double getAvgElevation() const;
	ElevationMatrixCell &getCell(const geom::Coordinate &c);
	const ElevationMatrixCell &getCell(const geom::Coordinate &c) const;
	std::string print() const;
private:
	ElevationMatrixFilter filter;
	void add(const geom::Coordinate &c);
	geom::Envelope env;
	unsigned int cols;
	unsigned int rows;
	double cellwidth;
	double cellheight;
	mutable bool avgElevationComputed;
	mutable double avgElevation;
	std::vector<ElevationMatrixCell>cells;
};


} // namespace GEOMETRY::operation::overlay
} // namespace GEOMETRY::operation
} // namespace GEOMETRY

#endif // ndef GEOS_OP_OVERLAY_ELEVATIONMATRIX_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/17 13:24:59  strk
 * opOverlay.h header splitted. Reduced header inclusions in operation/overlay implementation files. ElevationMatrixFilter code moved from own file to ElevationMatrix.cpp (ideally a class-private).
 *
 **********************************************************************/

