/**********************************************************************
 * $Id: operation.h 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 * Copyright (C) 2005 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Don't include this file, rather include from <Geometry/operation/class.h>
 *
 **********************************************************************/

#ifndef GEOS_OPERATION_H
#define GEOS_OPERATION_H

namespace GEOMETRY {

/// Provides classes for implementing operations on geometries
namespace operation { // geos.operation

} // namespace GEOMETRY.operation
} // namespace GEOMETRY

#include <Geometry/operation/EndpointInfo.h>
#include <Geometry/operation/GeometryGraphOperation.h>
#include <Geometry/operation/IsSimpleOp.h>

#endif
