/**********************************************************************
 * $Id: geomgraphindex.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOMETRY_GEOMGRAPH_INDEX_H
#define GEOMETRY_GEOMGRAPH_INDEX_H

namespace GEOMETRY {
namespace geomgraph { 
namespace index { 
} 
}
}

#include <Geometry/geomgraph/index/EdgeSetIntersector.h>
# include <Geometry/geomgraph/index/SimpleEdgeSetIntersector.h>
# include <Geometry/geomgraph/index/SimpleSweepLineIntersector.h>
# include <Geometry/geomgraph/index/SimpleMCSweepLineIntersector.h>

#include <Geometry/geomgraph/index/SweepLineSegment.h>
#include <Geometry/geomgraph/index/SweepLineEvent.h>
#include <Geometry/geomgraph/index/SegmentIntersector.h>
#include <Geometry/geomgraph/index/MonotoneChain.h>
#include <Geometry/geomgraph/index/MonotoneChainIndexer.h>
#include <Geometry/geomgraph/index/MonotoneChainEdge.h>

#endif


