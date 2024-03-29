/**********************************************************************
 * $Id: AssertionFailedException.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_UTIL_ASSERTIONFAILEDEXCEPTION_H
#define GEOS_UTIL_ASSERTIONFAILEDEXCEPTION_H

#include <string>

#include <Geometry/util/GEOSException.h>

namespace GEOMETRY {
namespace util { // geos.util

/** \class AssertionFailedException util.h geos.h
 * \brief Indicates a bug in GEOS code.
 */
class AssertionFailedException: public GEOSException {

public:

	AssertionFailedException()
		:
		GEOSException("AssertionFailedException", "")
	{}

	AssertionFailedException(const std::string& msg)
		:
		GEOSException("AssertionFailedException", msg)
	{}

	~AssertionFailedException() throw() {}
};

} // namespace GEOMETRY.util
} // namespace GEOMETRY


#endif // GEOS_UTIL_ASSERTIONFAILEDEXCEPTION_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/
