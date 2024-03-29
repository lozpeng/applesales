/**********************************************************************
 * $Id: DouglasPeuckerLineSimplifier.cpp 1928 2006-12-04 10:31:17Z strk $
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
 * Last port: simplify/DouglasPeuckerLineSimplifier.java rev. 1.4
 *
 **********************************************************************/

#include <Geometry/simplify/DouglasPeuckerLineSimplifier.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/LineSegment.h>

#include <vector>
#include <memory> // for auto_ptr

namespace GEOMETRY {

/// Line simplification algorithms
namespace simplify { // GEOMETRY::simplify

/*public static*/
DouglasPeuckerLineSimplifier::CoordsVectAutoPtr
DouglasPeuckerLineSimplifier::simplify(
		const DouglasPeuckerLineSimplifier::CoordsVect& nPts,
		double distanceTolerance)
{
	DouglasPeuckerLineSimplifier simp(nPts);
	simp.setDistanceTolerance(distanceTolerance);
	return simp.simplify();
}

/*public*/
DouglasPeuckerLineSimplifier::DouglasPeuckerLineSimplifier(
		const DouglasPeuckerLineSimplifier::CoordsVect& nPts)
	:
	pts(nPts)
{
}

/*public*/
void
DouglasPeuckerLineSimplifier::setDistanceTolerance(
		double nDistanceTolerance)
{
	distanceTolerance=nDistanceTolerance;
}

/*public*/
DouglasPeuckerLineSimplifier::CoordsVectAutoPtr
DouglasPeuckerLineSimplifier::simplify()
{
	CoordsVectAutoPtr coordList(new CoordsVect());

	// empty coordlist is the simplest, won't simplify further
	if ( ! pts.size() ) return coordList;

	usePt = BoolVectAutoPtr(new BoolVect(pts.size(), true));
	simplifySection(0, pts.size() - 1);

	for (size_t i=0, n=pts.size(); i<n; ++i)
	{
		if ( usePt->operator[](i) )
		{
			coordList->push_back(pts[i]);
		}
	}

	// auto_ptr transfer ownership to its
	// returned copy
	return coordList;
}

/*private*/
void
DouglasPeuckerLineSimplifier::simplifySection(
		size_t i,
		size_t j)
{
	if ( (i+1) == j ) return;

	GEOMETRY::geom::LineSegment seg(pts[i], pts[j]);
	double maxDistance = -1.0;

	size_t maxIndex = i;

	for (size_t k=i+1; k<j; k++)
	{
		double distance = seg.distance(pts[k]);
		if (distance > maxDistance) {
			maxDistance = distance;
			maxIndex = k;
		}
	}
	if (maxDistance <= distanceTolerance) {
		for(size_t k =i+1; k<j; k++)
		{
			usePt->operator[](k) = false;
		}
	}
	else {
		simplifySection(i, maxIndex);
		simplifySection(maxIndex, j);
	}
}

} // namespace GEOMETRY::simplify
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.3  2006/06/12 11:29:24  strk
 * unsigned int => size_t
 *
 * Revision 1.2  2006/06/03 22:29:39  hobu
 * Use a fully qualified namespace for LineSegment because we're inside of GEOMETRY::simplify at the time
 *
 * Revision 1.1  2006/04/03 10:16:11  strk
 * DouglasPeuckerLineSimplifier class port
 *
 **********************************************************************/
