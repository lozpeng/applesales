/**********************************************************************
 * $Id: opOverlay.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_OPOVERLAY_H
#define GEOS_OPOVERLAY_H

namespace GEOMETRY {
namespace operation { 

/** \brief
 * Contains classes that perform a topological overlay to compute boolean
 * spatial functions.
 * 
 * The Overlay Algorithm is used in spatial analysis methods for computing
 * set-theoretic operations (boolean combinations) of input {@link Geometry}s.
 * The algorithm for computing the overlay uses the intersection operations
 * supported by topology graphs.
 * To compute an overlay it is necessary to explicitly compute the resultant
 * graph formed by the computed intersections.
 * 
 * The algorithm to compute a set-theoretic spatial analysis method has the
 * following steps:
 * 
 *  - Build topology graphs of the two input geometries.  For each geometry all
 *    self-intersection nodes are computed and added to the graph.
 *  - Compute nodes for all intersections between edges and nodes of the graphs.
 *  - Compute the labeling for the computed nodes by merging the labels from
 *    the input graphs.
 *  - Compute new edges between the compute intersection nodes. 
 *    Label the edges appropriately.
 *  - Build the resultant graph from the new nodes and edges.
 *  - Compute the labeling for isolated components of the graph.  Add the
 *    isolated components to the resultant graph.
 *  - Compute the result of the boolean combination by selecting the node
 *    and edges with the appropriate labels. Polygonize areas and sew linear
 *    geometries together.
 * 
 * <h2>Package Specification</h2>
 * 
 * - Java Topology Suite Technical Specifications
 * - <A HREF="http://www.opengis.org/techno/specs.htm">
 *   OpenGIS Simple Features Specification for SQL</A>
 * 
 */
namespace overlay { // geos.operation.overlay

} // namespace GEOMETRY.operation.overlay
} // namespace GEOMETRY.operation
} // namespace GEOMETRY

#include <Geometry/operation/overlay/OverlayOp.h>
//#include <Geometry/operation/overlay/PolygonBuilder.h>
//#include <Geometry/operation/overlay/PointBuilder.h>
//#include <Geometry/operation/overlay/LineBuilder.h>
//#include <Geometry/operation/overlay/MinimalEdgeRing.h>
//#include <Geometry/operation/overlay/MaximalEdgeRing.h>
//#include <Geometry/operation/overlay/OverlayNodeFactory.h>
//#include <Geometry/operation/overlay/EdgeSetNoder.h>
//#include <Geometry/operation/overlay/ElevationMatrix.h>

#endif

