/**********************************************************************
 * $Id: opBuffer.h 1820 2006-09-06 16:54:23Z mloskot $
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
 **********************************************************************/

#ifndef GEOS_OPBUFFER_H
#define GEOS_OPBUFFER_H

namespace GEOMETRY {
namespace operation { // geos.operation

/// Provides classes for computing buffers of geometries
namespace buffer { 
} // namespace GEOMETRY.operation.buffer
} // namespace GEOMETRY.operation
} // namespace GEOMETRY

#include <Geometry/operation/buffer/BufferOp.h>

// This is needed for enum values
#include <Geometry/operation/buffer/OffsetCurveBuilder.h>

//#include <Geometry/operation/buffer/BufferBuilder.h>
//#include <Geometry/operation/buffer/OffsetCurveSetBuilder.h>
//#include <Geometry/operation/buffer/BufferSubgraph.h>
//#include <Geometry/operation/buffer/SubgraphDepthLocater.h>
//#include <Geometry/operation/buffer/RightmostEdgeFinder.h>

#endif // ndef GEOS_OPBUFFER_H

