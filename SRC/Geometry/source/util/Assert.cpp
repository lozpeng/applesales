/**********************************************************************
 * $Id: Assert.cpp 1820 2006-09-06 16:54:23Z mloskot $
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

#include <string>

#include <Geometry/util/Assert.h>
#include <Geometry/util/AssertionFailedException.h>
#include <Geometry/geom/Coordinate.h>

using std::string;
using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace util { // geos.util

void
Assert::isTrue(bool assertion, const string& message)
{
	if (!assertion) {
		if (message.empty()) {
			throw  AssertionFailedException();
		} else {
			throw  AssertionFailedException(message);
		}
	}
}

void
Assert::equals(const Coordinate& expectedValue,
		const Coordinate& actualValue, const string& message)
{
	if (!(actualValue==expectedValue)) {
		throw  AssertionFailedException("Expected " + expectedValue.toString() + " but encountered "
			+ actualValue.toString() + (!message.empty() ? ": " + message : ""));
	}
}


void Assert::shouldNeverReachHere(const string& message) {
	throw  AssertionFailedException("Should never reach here"
		+ (!message.empty() ? ": " + message : ""));
}

} // namespace GEOMETRY.util
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.14  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 * Revision 1.13  2006/03/06 19:40:47  strk
 * GEOMETRY::util namespace. New GeometryCollection::iterator interface, many cleanups.
 *
 * Revision 1.12  2006/03/03 10:46:22  strk
 * Removed 'using namespace' from headers, added missing headers in .cpp files, removed useless includes in headers (bug#46)
 *
 * Revision 1.11  2006/02/23 11:54:21  strk
 * - MCIndexPointSnapper
 * - MCIndexSnapRounder
 * - SnapRounding BufferOp
 * - ScaledNoder
 * - GEOSException hierarchy cleanups
 * - SpatialIndex memory-friendly query interface
 * - GeometryGraph::getBoundaryNodes memory-friendly
 * - NodeMap::getBoundaryNodes memory-friendly
 * - Cleanups in geomgraph::Edge
 * - Added an XML test for snaprounding buffer (shows leaks, working on it)
 *
 * Revision 1.10  2006/02/09 15:52:47  strk
 * GEOSException derived from std::exception; always thrown and cought by const ref.
 *
 * Revision 1.9  2004/07/02 13:28:29  strk
 * Fixed all #include lines to reflect headers layout change.
 * Added client application build tips in README.
 *
 * Revision 1.8  2003/11/07 01:23:43  pramsey
 * Add standard CVS headers licence notices and copyrights to all cpp and h
 * files.
 *
 *
 **********************************************************************/

