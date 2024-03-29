/**********************************************************************
 * $Id: RelateNodeGraph.h 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#ifndef GEOS_OP_RELATE_RELATENODEGRAPH_H
#define GEOS_OP_RELATE_RELATENODEGRAPH_H

#include <map>
#include <vector>

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class Coordinate;
		struct CoordinateLessThen;
	}
	namespace geomgraph {
		//class EdgeEndStar;
		class Node;
		class GeometryGraph;
		class EdgeEnd;
		class NodeMap;
	}
}


namespace GEOMETRY {
namespace operation { // GEOMETRY::operation
namespace relate { // GEOMETRY::operation::relate

/** \brief
 * Implements the simple graph of Nodes and geomgraph::EdgeEnd which is all that is
 * required to determine topological relationships between Geometries.
 *
 * Also supports building a topological graph of a single Geometry, to
 * allow verification of valid topology.
 * 
 * It is <b>not</b> necessary to create a fully linked
 * PlanarGraph to determine relationships, since it is sufficient
 * to know how the Geometries interact locally around the nodes.
 * In fact, this is not even feasible, since it is not possible to compute
 * exact intersection points, and hence the topology around those nodes
 * cannot be computed robustly.
 * The only Nodes that are created are for improper intersections;
 * that is, nodes which occur at existing vertices of the Geometries.
 * Proper intersections (e.g. ones which occur between the interior of
 * line segments)
 * have their topology determined implicitly, without creating a geomgraph::Node object
 * to represent them.
 *
 */
class RelateNodeGraph {

public:

	RelateNodeGraph();

	virtual ~RelateNodeGraph();

	std::map<geom::Coordinate*, geomgraph::Node*,
			geom::CoordinateLessThen> &getNodeMap();

	void build(geomgraph::GeometryGraph *geomGraph);

	void computeIntersectionNodes(geomgraph::GeometryGraph *geomGraph,
			int argIndex);

	void copyNodesAndLabels(geomgraph::GeometryGraph *geomGraph,int argIndex);

	void insertEdgeEnds(std::vector<geomgraph::EdgeEnd*> *ee);

private:

	geomgraph::NodeMap *nodes;
};


} // namespace GEOMETRY:operation:relate
} // namespace GEOMETRY:operation
} // namespace GEOMETRY

#endif // GEOS_OP_RELATE_RELATENODEGRAPH_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/21 13:11:29  strk
 * opRelate.h header split
 *
 **********************************************************************/

