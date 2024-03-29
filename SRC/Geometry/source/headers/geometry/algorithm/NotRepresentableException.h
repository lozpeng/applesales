/**********************************************************************
 * $Id: NotRepresentableException.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_ALGORITHM_NOTREPRESENTABLEEXCEPTION_H
#define GEOS_ALGORITHM_NOTREPRESENTABLEEXCEPTION_H

#include <string>
#include <Geometry/util/GEOSException.h>

namespace GEOMETRY {
namespace algorithm { // GEOMETRY::algorithm

/**
 * \class NotRepresentableException geosAlgorithm.h geos/geosAlgorithm.h
 * \brief
 * Indicates that a HCoordinate has been computed which is
 * not representable on the Cartesian plane.
 *
 * @version 1.4
 * @see HCoordinate
 */
class NotRepresentableException: public util::GEOSException {
public:
	NotRepresentableException();
	NotRepresentableException(std::string msg);
	~NotRepresentableException() throw() {}
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

