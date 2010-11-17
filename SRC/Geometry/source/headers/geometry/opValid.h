/**********************************************************************
 * $Id: opValid.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_OPVALID_H
#define GEOS_OPVALID_H

namespace GEOMETRY {
namespace operation { // geos.operation

/// Provides classes for testing the validity of geometries.
namespace valid { // geos.operation.valid

} // namespace GEOMETRY.operation.valid
} // namespace GEOMETRY.operation
} // namespace GEOMETRY

//#include <Geometry/operation/valid/ConnectedInteriorTester.h>
//#include <Geometry/operation/valid/ConsistentAreaTester.h>
#include <Geometry/operation/valid/IsValidOp.h>
//#include <Geometry/operation/valid/QuadtreeNestedRingTester.h>
//#include <Geometry/operation/valid/RepeatedPointTester.h>
//#include <Geometry/operation/valid/SimpleNestedRingTester.h>
//#include <Geometry/operation/valid/SweeplineNestedRingTester.h>
#include <Geometry/operation/valid/TopologyValidationError.h>

#endif
