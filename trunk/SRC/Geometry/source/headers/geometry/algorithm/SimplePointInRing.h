/**********************************************************************
 * $Id: SimplePointInRing.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_ALGORITHM_SIMPLEPOINTINRING_H
#define GEOS_ALGORITHM_SIMPLEPOINTINRING_H

#include <Geometry/algorithm/PointInRing.h> // for inheritance

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class Coordinate;
		class LinearRing;
		class CoordinateSequence;
	}
}

namespace GEOMETRY {
namespace algorithm { // GEOMETRY::algorithm

class SimplePointInRing: public PointInRing {
public:
	SimplePointInRing(geom::LinearRing *ring);
	virtual ~SimplePointInRing();
	bool isInside(const geom::Coordinate& pt);
private:
	const geom::CoordinateSequence* pts;
};

} // namespace GEOMETRY::algorithm
} // namespace GEOMETRY


#endif // GEOS_ALGORITHM_SIMPLEPOINTINRING_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/09 16:46:48  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/

