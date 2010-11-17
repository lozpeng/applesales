/**********************************************************************
 * $Id: EdgeIntersection.h 1820 2006-09-06 16:54:23Z mloskot $
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


#ifndef GEOMETRY_GEOMGRAPH_EDGEINTERSECTION_H
#define GEOMETRY_GEOMGRAPH_EDGEINTERSECTION_H

#include <string>

#include <Geometry/geom/Coordinate.h> // for CoordinateLessThen

#include <Geometry/inline.h>


namespace GEOMETRY {
namespace geomgraph { // geos.geomgraph

class EdgeIntersection {
public:
	geom::Coordinate coord;
	int segmentIndex;
	double dist;
	EdgeIntersection(const geom::Coordinate& newCoord, int newSegmentIndex, double newDist);
	virtual ~EdgeIntersection();
	int compare(int newSegmentIndex, double newDist) const;
	bool isEndPoint(int maxSegmentIndex);
	std::string print() const;
	int compareTo(const EdgeIntersection *) const;
};

struct EdgeIntersectionLessThen {
	bool operator()(const EdgeIntersection *ei1,
		const EdgeIntersection *ei2) const
	{
		if ( ei1->segmentIndex<ei2->segmentIndex ||
			( ei1->segmentIndex==ei2->segmentIndex &&
		     	ei1->dist<ei2->dist ) ) return true;
		return false;
	}
};


} // namespace GEOMETRY.geomgraph
} // namespace GEOMETRY

//#ifdef GEOS_INLINE
//# include "Geometry/geomgraph/EdgeIntersection.inl"
//#endif

#endif // ifndef GEOS_GEOMGRAPH_EDGEINTERSECTION_H

/**********************************************************************
 * $Log$
 * Revision 1.2  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/

