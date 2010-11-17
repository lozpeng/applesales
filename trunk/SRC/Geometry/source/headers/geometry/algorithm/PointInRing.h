/**********************************************************************
 * $Id: PointInRing.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_ALGORITHM_POINTINRING_H
#define GEOS_ALGORITHM_POINTINRING_H


// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class Coordinate;
	}
}

namespace GEOMETRY {
namespace algorithm { // GEOMETRY::algorithm

class PointInRing{
public:
	virtual ~PointInRing(){};
	virtual bool isInside(const geom::Coordinate& pt)=0;
};

} // namespace GEOMETRY::algorithm
} // namespace GEOMETRY


#endif

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/09 16:46:48  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/

