/**********************************************************************
 * $Id: geomgraph.h 1820 2006-09-06 16:54:23Z mloskot $
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
 **********************************************************************
 *
 * Try not to include this header directly. It is kept
 * for backward compatibility.
 * Please include geomgraph/classname.h for new code.
 *
 **********************************************************************/


#ifndef GEOMETRY_GEOMGRAPH_H
#define GEOMETRY_GEOMGRAPH_H

namespace GEOMETRY {

/** \brief
 * Contains classes that implement topology graphs.
 * 
 * The Java Topology Suite (JTS) is a Java API that implements a core
 * set of spatial data operations using an explicit precision model
 * and robust geometric algorithms. JTS is int ended to be used in the
 * development of applications that support the validation, cleaning,
 * integration and querying of spatial datasets.
 *
 * JTS attempts to implement the OpenGIS Simple Features Specification (SFS)
 * as accurately as possible.  In some cases the SFS is unclear or omits a
 * specification; in this case JTS attempts to choose a reasonable and
 * consistent alternative.  Differences from and elaborations of the SFS
 * are documented in this specification.
 * 
 * <h2>Package Specification</h2>
 * 
 * <ul>
 *   <li>Java Topology Suite Technical Specifications
 *   <li><A HREF="http://www.opengis.org/techno/specs.htm">
 *       OpenGIS Simple Features Specification for SQL</A>
 * </ul>
 * 
 */
namespace geomgraph { // geos.geomgraph
} // namespace GEOMETRY.geomgraph
} // namespace GEOMETRY

//#include <Geometry/geomgraph/Depth.h>
//#include <Geometry/geomgraph/DirectedEdge.h>
//#include <Geometry/geomgraph/DirectedEdgeStar.h>
//#include <Geometry/geomgraph/Edge.h>
#include <Geometry/geomgraph/EdgeEnd.h>
#include <Geometry/geomgraph/EdgeEndStar.h>
//#include <Geometry/geomgraph/EdgeIntersection.h>
//#include <Geometry/geomgraph/EdgeIntersectionList.h>
#include <Geometry/geomgraph/EdgeList.h>
//#include <Geometry/geomgraph/EdgeNodingValidator.h>
//#include <Geometry/geomgraph/EdgeRing.h>
#include <Geometry/geomgraph/GeometryGraph.h>
#include <Geometry/geomgraph/GraphComponent.h>
//#include <Geometry/geomgraph/Label.h>
#include <Geometry/geomgraph/Node.h>
//#include <Geometry/geomgraph/NodeFactory.h>
#include <Geometry/geomgraph/NodeMap.h>
#include <Geometry/geomgraph/PlanarGraph.h>
//#include <Geometry/geomgraph/Position.h>
//#include <Geometry/geomgraph/Quadrant.h>
//#include <Geometry/geomgraph/TopologyLocation.h>

#endif // ifndef GEOS_GEOMGRAPH_H

/**********************************************************************
 * $Log$
 * Revision 1.42  2006/06/01 11:49:35  strk
 * Reduced installed headers form geomgraph namespace
 *
 * Revision 1.41  2006/03/09 16:46:48  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 * Revision 1.40  2006/03/06 19:40:46  strk
 * GEOMETRY::util namespace. New GeometryCollection::iterator interface, many cleanups.
 *
 * Revision 1.39  2006/03/03 10:46:21  strk
 * Removed 'using namespace' from headers, added missing headers in .cpp files, removed useless includes in headers (bug#46)
 *
 * Revision 1.38  2006/03/02 14:34:30  strk
 * GeometryGraphOperation::li made a non-static member, and not more a pointer
 *
 * Revision 1.37  2006/02/28 14:34:05  strk
 * Added many assertions and debugging output hunting for a bug in BufferOp
 *
 *
 **********************************************************************/

