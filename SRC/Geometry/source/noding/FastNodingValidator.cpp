/**********************************************************************
 * $Id: FastNodingValidator.cpp 2137 2008-07-25 21:00:09Z mloskot $
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
 * Last port: noding/FastNodingValidator.java rev. ??? (JTS-1.8)
 *
 **********************************************************************/

#include <Geometry/noding/FastNodingValidator.h>
#include <Geometry/noding/MCIndexNoder.h> // for checkInteriorIntersections()
#include <Geometry/noding/SingleInteriorIntersectionFinder.h>
#include <Geometry/util/TopologyException.h> // for checkValid()
#include <Geometry/geom/Coordinate.h>
#include <Geometry/io/WKTWriter.h> // for getErrorMessage()

#include <string>
#include <iostream>

namespace GEOMETRY {
namespace noding { // geos.noding

/*private*/
void
FastNodingValidator::checkInteriorIntersections()
{
	isValidVar = true;
	segInt.reset(new SingleInteriorIntersectionFinder(li));
	MCIndexNoder noder;
	noder.setSegmentIntersector(segInt.get());
	noder.computeNodes(&segStrings);
	if (segInt->hasIntersection()) {
		isValidVar = false;
		return;
	}
}

/*public*/
std::string
FastNodingValidator::getErrorMessage() const
{
	using GEOMETRY::io::WKTWriter;
	using GEOMETRY::geom::Coordinate;

	if (isValidVar) return std::string("no intersections found");

	//return std::string("found non-noded intersection etc etc");
	
	const std::vector<Coordinate>& intSegs = segInt->getIntersectionSegments();
	assert(intSegs.size() == 4);
	return "found non-noded intersection between "
		+ WKTWriter::toLineString(intSegs[0], intSegs[1])
		+ " and "
		+ WKTWriter::toLineString(intSegs[2], intSegs[3]);
}

void
FastNodingValidator::checkValid()
{
	execute();
	if (! isValidVar)
	{
		//std::cerr << "Not valid: " << getErrorMessage() << " interior intersection: " << segInt->getInteriorIntersection() << std::endl;
		throw util::TopologyException(getErrorMessage(), segInt->getInteriorIntersection());
	}
}

} // namespace GEOMETRY.noding
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 **********************************************************************/
