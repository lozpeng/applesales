/**********************************************************************
 * $Id: FastSegmentSetIntersectionFinder.cpp 2161 2008-08-18 16:29:09Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#include <Geometry/noding/FastSegmentSetIntersectionFinder.h>
#include <Geometry/noding/SegmentString.h>
#include <Geometry/noding/SegmentIntersectionDetector.h>
#include <Geometry/noding/SegmentSetMutualIntersector.h>
#include <Geometry/noding/MCIndexSegmentSetMutualIntersector.h>
#include <Geometry/algorithm/LineIntersector.h>

namespace GEOMETRY {
namespace noding { // GEOMETRY::noding

/*
 * private:
 */

/*
 * protected:
 */

/*
 * public:
 */
FastSegmentSetIntersectionFinder::
FastSegmentSetIntersectionFinder( noding::SegmentString::ConstVect * baseSegStrings)
:	segSetMutInt( new MCIndexSegmentSetMutualIntersector()),
	lineIntersector( new LineIntersector())
{
	segSetMutInt->setBaseSegments( baseSegStrings);
}

FastSegmentSetIntersectionFinder::
~FastSegmentSetIntersectionFinder()
{
	delete lineIntersector;
	delete segSetMutInt;
}


bool 
FastSegmentSetIntersectionFinder::
intersects( noding::SegmentString::ConstVect * segStrings)
{
	SegmentIntersectionDetector intFinder( lineIntersector);

	return this->intersects( segStrings, &intFinder);
}

bool 
FastSegmentSetIntersectionFinder::
intersects( noding::SegmentString::ConstVect * segStrings, 
			SegmentIntersectionDetector * intDetector)
{
	segSetMutInt->setSegmentIntersector( intDetector);
	segSetMutInt->process( segStrings);

	return intDetector->hasIntersection();
}

} // GEOMETRY::noding
} // geos

/**********************************************************************
 * $Log$
 *
 **********************************************************************/
