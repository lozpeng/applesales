/**********************************************************************
 * $Id: util.h 2160 2008-08-18 16:27:58Z mloskot $
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
 **********************************************************************
 *
 * Utility header to retain a bit of backward compatibility.
 * Try to avoid including this header directly.
 *
 **********************************************************************/

#ifndef GEOS_UTIL_H
#define GEOS_UTIL_H

//#include <Geometry/util/AssertionFailedException.h>
#include <Geometry/util/GEOSException.h>
#include <Geometry/util/IllegalArgumentException.h>
#include <Geometry/util/TopologyException.h>
//#include <Geometry/util/UnsupportedOperationException.h>
//#include <Geometry/util/CoordinateArrayFilter.h>
//#include <Geometry/util/UniqueCoordinateArrayFilter.h>
#include <Geometry/util/GeometricShapeFactory.h>
//#include <Geometry/util/math.h>

//
// Private macros definition 
// 

#ifndef UNREFERENCED_PARAMETER 
#define UNREFERENCED_PARAMETER(p) ((void)p)
#endif 

#endif // GEOS_UTIL_H
