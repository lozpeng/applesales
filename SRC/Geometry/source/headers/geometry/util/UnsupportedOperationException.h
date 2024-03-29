/**********************************************************************
 * $Id: UnsupportedOperationException.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_UTIL_UNSUPPORTEDOPERATIONEXCEPTION_H
#define GEOS_UTIL_UNSUPPORTEDOPERATIONEXCEPTION_H

#include <string>

#include <Geometry/util/GEOSException.h>

namespace GEOMETRY {
namespace util { // GEOMETRY::util

/**
 * \class UnsupportedOperationException util.h geos.h
 *
 * \brief Indicates that the requested operation is unsopported.
 *
 * This exception is thrown - for example - when requesting the
 * X or Y member of an empty Point
 */
class UnsupportedOperationException: public GEOSException {
public:
	UnsupportedOperationException()
		:
		GEOSException("UnsupportedOperationException", "")
	{}

	UnsupportedOperationException(const std::string& msg)
		:
		GEOSException("UnsupportedOperationException", msg)
	{}

	~UnsupportedOperationException() throw() {};
};

} // namespace GEOMETRY::util
} // namespace GEOMETRY


#endif // GEOS_UTIL_UNSUPPORTEDOPERATIONEXCEPTION_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/
