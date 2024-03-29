/**********************************************************************
 * $Id: EnhancedPrecisionOp.h 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2005-2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: precision/EnhancedPrecisionOp.java rev. 1.9 (JTS-1.7)
 *
 **********************************************************************/

#ifndef GEOS_PRECISION_ENHANCEDPRECISIONOP_H
#define GEOS_PRECISION_ENHANCEDPRECISIONOP_H

#include <Geometry/platform.h> // for int64

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class Geometry;
	}
}

namespace GEOMETRY {
namespace precision { // geos.precision

/** \brief
 * Provides versions of Geometry spatial functions which use
 * enhanced precision techniques to reduce the likelihood of robustness
 * problems.
 */
class EnhancedPrecisionOp {

public:

	/** \brief
	 * Computes the set-theoretic intersection of two
	 * Geometrys, using enhanced precision.
	 *
	 * @param geom0 the first Geometry
	 * @param geom1 the second Geometry
	 * @return the Geometry representing the set-theoretic
	 * intersection of the input Geometries.
	 */
	static geom::Geometry* intersection(
			const geom::Geometry *geom0,
			const geom::Geometry *geom1);

	/**
	 * Computes the set-theoretic union of two Geometrys,
	 * using enhanced precision.
	 * @param geom0 the first Geometry
	 * @param geom1 the second Geometry
	 * @return the Geometry representing the set-theoretic
	 * union of the input Geometries.
	 */
	static geom::Geometry* Union(
			const geom::Geometry *geom0,
			const geom::Geometry *geom1);

	/**
	 * Computes the set-theoretic difference of two Geometrys,
	 * using enhanced precision.
	 * @param geom0 the first Geometry
	 * @param geom1 the second Geometry
	 * @return the Geometry representing the set-theoretic
	 * difference of the input Geometries.
	 */
	static geom::Geometry* difference(
			const geom::Geometry *geom0,
			const geom::Geometry *geom1);

	/**
	 * Computes the set-theoretic symmetric difference of two
	 * Geometrys, using enhanced precision.
	 * @param geom0 the first Geometry
	 * @param geom1 the second Geometry
	 * @return the Geometry representing the set-theoretic symmetric
	 * difference of the input Geometries.
	 */
	static geom::Geometry* symDifference(
			const geom::Geometry *geom0,
			const geom::Geometry *geom1);

	/**
	 * Computes the buffer of a Geometry, using enhanced precision.
	 * This method should no longer be necessary, since the buffer
	 * algorithm now is highly robust.
	 *
	 * @param geom0 the first Geometry
	 * @param distance the buffer distance
	 * @return the Geometry representing the buffer of the input Geometry.
	 */
	static geom::Geometry* buffer(
			const geom::Geometry *geom,
			double distance);
};


} // namespace GEOMETRY.precision
} // namespace GEOMETRY

#endif // GEOS_PRECISION_ENHANCEDPRECISIONOP_H

/**********************************************************************
 * $Log$
 * Revision 1.2  2006/04/06 14:36:52  strk
 * Cleanup in GEOMETRY::precision namespace (leaks plugged, auto_ptr use, ...)
 *
 * Revision 1.1  2006/03/23 09:17:19  strk
 * precision.h header split, minor optimizations
 *
 **********************************************************************/
