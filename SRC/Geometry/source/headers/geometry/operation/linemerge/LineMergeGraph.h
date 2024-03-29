/**********************************************************************
 * $Id: LineMergeGraph.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_OP_LINEMERGE_LINEMERGEGRAPH_H
#define GEOS_OP_LINEMERGE_LINEMERGEGRAPH_H

#include <Geometry/planargraph/PlanarGraph.h> // for inheritance

#include <vector>

// Forward declarations 
namespace GEOMETRY {
	namespace geom { 
		class LineString;
		class Coordinate;
	}
	namespace planargraph { 
		class Node;
		class Edge;
		class DirectedEdge;
	}
}


namespace GEOMETRY {
namespace operation { // GEOMETRY::operation
namespace linemerge { // GEOMETRY::operation::linemerge

/** \brief
 * A planar graph of edges that is analyzed to sew the edges together.
 *
 * The <code>marked</code> flag on planargraph::Edge
 * and planargraph::Node indicates whether they have been
 * logically deleted from the graph.
 */
class LineMergeGraph: public planargraph::PlanarGraph {

private:

	planargraph::Node* getNode(const geom::Coordinate &coordinate);

	std::vector<planargraph::Node*> newNodes;

	std::vector<planargraph::Edge*> newEdges;

	std::vector<planargraph::DirectedEdge*> newDirEdges;

public:

	/**
	 * Adds an Edge, DirectedEdges, and Nodes for the given
	 * LineString representation of an edge. 
	 */
	void addEdge(const geom::LineString *lineString);

	~LineMergeGraph();
};
} // namespace GEOMETRY::operation::linemerge
} // namespace GEOMETRY::operation
} // namespace GEOMETRY

#endif // GEOS_OP_LINEMERGE_LINEMERGEGRAPH_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/22 10:13:53  strk
 * opLinemerge.h split
 *
 **********************************************************************/
