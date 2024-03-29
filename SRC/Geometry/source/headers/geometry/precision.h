/**********************************************************************
 * $Id: precision.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_PRECISION_H
#define GEOS_PRECISION_H

namespace GEOMETRY {

/// Provides classes for manipulating the precision model of Geometries
namespace precision { // geos.precision

} // namespace GEOMETRY.precision
} // namespace GEOMETRY

//#include <Geometry/precision/CommonBits.h>
#include <Geometry/precision/CommonBitsOp.h>
//#include <Geometry/precision/CommonBitsRemover.h>
#include <Geometry/precision/EnhancedPrecisionOp.h>
#include <Geometry/precision/SimpleGeometryPrecisionReducer.h>

#endif
