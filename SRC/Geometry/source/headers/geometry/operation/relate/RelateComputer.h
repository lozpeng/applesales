/**********************************************************************
 * $Id: RelateComputer.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_OP_RELATE_RELATECOMPUTER_H
#define GEOS_OP_RELATE_RELATECOMPUTER_H

#include <Geometry/algorithm/PointLocator.h> // for RelateComputer composition
#include <Geometry/algorithm/LineIntersector.h> // for RelateComputer composition
#include <Geometry/geomgraph/NodeMap.h> // for RelateComputer composition
#include <Geometry/geom/Coordinate.h> // for RelateComputer composition

#include <vector>

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class IntersectionMatrix;
		class Geometry;
	}
	namespace geomgraph {
		class GeometryGraph;
		class Edge;
		class EdgeEnd;
		class Node;
		namespace index {
			class SegmentIntersector;
		}
	}
}


namespace GEOMETRY {
namespace operation { // GEOMETRY::operation
namespace relate { // GEOMETRY::operation::relate

/** \brief
 * Computes the topological relationship between two Geometries.
 *
 * RelateComputer does not need to build a complete graph structure to compute
 * the IntersectionMatrix.  The relationship between the geometries can
 * be computed by simply examining the labelling of edges incident on each node.
 * 
 * RelateComputer does not currently support arbitrary GeometryCollections.
 * This is because GeometryCollections can contain overlapping Polygons.
 * In order to correct compute relate on overlapping Polygons, they
 * would first need to be noded and merged (if not explicitly, at least
 * implicitly).
 *
 */
class RelateComputer {
public:
	//RelateComputer();
	virtual ~RelateComputer();
	RelateComputer(std::vector<geomgraph::GeometryGraph*> *newArg);
	geom::IntersectionMatrix* computeIM();
private:

	algorithm::LineIntersector li;

	algorithm::PointLocator ptLocator;

	/// the arg(s) of the operation
	std::vector<geomgraph::GeometryGraph*> *arg; 

	geomgraph::NodeMap nodes;

	/// this intersection matrix will hold the results compute for the relate
	geom::IntersectionMatrix *im;

	std::vector<geomgraph::Edge*> isolatedEdges;

	/// the intersection point found (if any)
	geom::Coordinate invalidPoint;

	void insertEdgeEnds(std::vector<geomgraph::EdgeEnd*> *ee);

	void computeProperIntersectionIM(geomgraph::index::SegmentIntersector *intersector,
			geom::IntersectionMatrix *imX);

	void copyNodesAndLabels(int argIndex);
	void computeIntersectionNodes(int argIndex);
	void labelIntersectionNodes(int argIndex);
	void computeDisjointIM(geom::IntersectionMatrix *imX);
	void labelNodeEdges();
	void updateIM(geom::IntersectionMatrix *imX);
	void labelIsolatedEdges(int thisIndex,int targetIndex);
	void labelIsolatedEdge(geomgraph::Edge *e,int targetIndex, const geom::Geometry *target);
	void labelIsolatedNodes();
	void labelIsolatedNode(geomgraph::Node *n,int targetIndex);
};


} // namespace GEOMETRY:operation:relate
} // namespace GEOMETRY:operation
} // namespace GEOMETRY

#endif // GEOS_OP_RELATE_RELATECOMPUTER_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/21 13:11:29  strk
 * opRelate.h header split
 *
 **********************************************************************/

