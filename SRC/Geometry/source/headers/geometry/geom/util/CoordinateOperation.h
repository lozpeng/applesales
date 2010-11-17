/**********************************************************************
 * $Id: CoordinateOperation.h 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#ifndef GEOMETRY_GEOM_UTIL_COORDINATEOPERATION_H
#define GEOMETRY_GEOM_UTIL_COORDINATEOPERATION_H

#include <Geometry/geom/util/GeometryEditorOperation.h> // for inheritance

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class Geometry;
		class CoordinateSequence;
		class GeometryFactory;
	}
}


namespace GEOMETRY {
namespace geom { // geos.geom
namespace util { // geos.geom.util

/**
 * A GeometryEditorOperation which modifies the coordinate list of a
 * Geometry.
 * Operates on Geometry subclasses which contains a single coordinate list.
 */
class CoordinateOperation: public GeometryEditorOperation {

public:

	/**
	 * Return a newly created geometry 
	 */
	virtual Geometry* edit(const Geometry *geometry,
			const GeometryFactory *factory);

	/**
	 * Edits the array of Coordinate from a Geometry.
	 *
	 * @param coordinates the coordinate array to operate on
	 * @param geometry the geometry containing the coordinate list
	 * @return an edited coordinate array (which may be the same as
	 *         the input)
	 */
	virtual CoordinateSequence* edit(const CoordinateSequence* coordinates,
			const Geometry *geometry)=0;


	virtual ~CoordinateOperation() {}
};



} // namespace GEOMETRY.geom.util
} // namespace GEOMETRY.geom
} // namespace GEOMETRY

//#ifdef GEOS_INLINE
//# include "Geometry/geom/util/CoordinateOperation.inl"
//#endif

#endif

/**********************************************************************
 * $Log$
 * Revision 1.3  2006/06/08 11:20:24  strk
 * Added missing virtual destructor to abstract classes.
 *
 * Revision 1.2  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/
