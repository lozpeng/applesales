/**********************************************************************
 * $Id: CommonBitsRemover.h 1820 2006-09-06 16:54:23Z mloskot $
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
 **********************************************************************/

#ifndef GEOS_PRECISION_COMMONBITSREMOVER_H
#define GEOS_PRECISION_COMMONBITSREMOVER_H

#include <Geometry/geom/Coordinate.h> // for composition

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class Geometry;
	}
	namespace precision {
		class CommonBitsRemover;
		class CommonCoordinateFilter;
	}
}

namespace GEOMETRY {
namespace precision { // geos.precision

/** \brief
 * Allow computing and removing common mantissa bits from one or
 * more Geometries.
 *
 */
class CommonBitsRemover {

private:

	geom::Coordinate commonCoord;

	CommonCoordinateFilter *ccFilter;

public:

	CommonBitsRemover();

	~CommonBitsRemover();

	/**
	 * Add a geometry to the set of geometries whose common bits are
	 * being computed.  After this method has executed the
	 * common coordinate reflects the common bits of all added
	 * geometries.
	 *
	 * @param geom a Geometry to test for common bits
	 */
	void add(const geom::Geometry *geom);

	/**
	 * The common bits of the Coordinates in the supplied Geometries.
	 */
	geom::Coordinate& getCommonCoordinate();

	/** \brief
	 * Removes the common coordinate bits from a Geometry.
	 * The coordinates of the Geometry are changed.
	 *
	 * @param geom the Geometry from which to remove the common
	 *             coordinate bits
	 * @return the shifted Geometry
	 */
	geom::Geometry* removeCommonBits(geom::Geometry *geom);

	/** \brief
	 * Adds the common coordinate bits back into a Geometry.
	 * The coordinates of the Geometry are changed.
	 *
	 * @param geom the Geometry to which to add the common coordinate bits
	 * @return the shifted Geometry
	 */
	geom::Geometry* addCommonBits(geom::Geometry *geom);
};

} // namespace GEOMETRY.precision
} // namespace GEOMETRY

#endif // GEOS_PRECISION_COMMONBITSREMOVER_H

/**********************************************************************
 * $Log$
 * Revision 1.3  2006/04/07 08:30:30  strk
 * made addCommonBits/removeCommonBits interface consistent, doxygen comments
 *
 * Revision 1.2  2006/04/06 14:36:52  strk
 * Cleanup in GEOMETRY::precision namespace (leaks plugged, auto_ptr use, ...)
 *
 * Revision 1.1  2006/03/23 09:17:19  strk
 * precision.h header split, minor optimizations
 *
 **********************************************************************/
