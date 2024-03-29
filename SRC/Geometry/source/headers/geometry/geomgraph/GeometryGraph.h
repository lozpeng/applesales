/**********************************************************************
 * $Id: GeometryGraph.h 1820 2006-09-06 16:54:23Z mloskot $
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


#ifndef GEOMETRY_GEOMGRAPH_GEOMETRYGRAPH_H
#define GEOMETRY_GEOMGRAPH_GEOMETRYGRAPH_H

#include <map>
#include <vector>
#include <memory>

#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/CoordinateSequence.h> // for auto_ptr<CoordinateSequence>
#include <Geometry/geomgraph/PlanarGraph.h>
#include <Geometry/geom/LineString.h> // for LineStringLT

#include <Geometry/inline.h>

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class LineString;
		class LinearRing;
		class Polygon;
		class Geometry;
		class GeometryCollection;
		class Point;
	}
	namespace algorithm {
		class LineIntersector;
	}
	namespace geomgraph {
		class Edge;
		class Node;
		namespace index {
			class SegmentIntersector;
			class EdgeSetIntersector;
		}
	}
}

namespace GEOMETRY {
namespace geomgraph { // geos.geomgraph

class GeometryGraph: public PlanarGraph {
using PlanarGraph::add;
using PlanarGraph::findEdge;

private:

	const geom::Geometry* parentGeom;

	/**
	 * The lineEdgeMap is a map of the linestring components of the
	 * parentGeometry to the edges which are derived from them.
	 * This is used to efficiently perform findEdge queries
	 *
	 * Following the above description there's no need to
	 * compare LineStrings other then by pointer value.
	 */
//std::map<const geom::LineString*,Edge*,geom::LineStringLT> lineEdgeMap;
	std::map<const geom::LineString*, Edge*> lineEdgeMap;

	/**
	 * If this flag is true, the Boundary Determination Rule will
	 * used when deciding whether nodes are in the boundary or not
	 */
	bool useBoundaryDeterminationRule;

	/**
	 * the index of this geometry as an argument to a spatial function
	 * (used for labelling)
	 */
	int argIndex;

	/// Cache for fast responses to getBoundaryPoints
	std::auto_ptr< geom::CoordinateSequence > boundaryPoints;

	std::auto_ptr< std::vector<Node*> > boundaryNodes;

	bool hasTooFewPointsVar;

	geom::Coordinate invalidPoint; 

	std::vector<index::SegmentIntersector*> newSegmentIntersectors;

	/// Allocates a new EdgeSetIntersector. Remember to delete it!
	index::EdgeSetIntersector* createEdgeSetIntersector();

	void add(const geom::Geometry *g);
		// throw(UnsupportedOperationException);

	void addCollection(const geom::GeometryCollection *gc);

	void addPoint(const geom::Point *p);

	void addPolygonRing(const geom::LinearRing *lr,
			int cwLeft, int cwRight);

	void addPolygon(const geom::Polygon *p);

	void addLineString(const geom::LineString *line);

	void insertPoint(int argIndex, const geom::Coordinate& coord,
			int onLocation);

	void insertBoundaryPoint(int argIndex, const geom::Coordinate& coord);

	void addSelfIntersectionNodes(int argIndex);

	/** \brief
	 * Add a node for a self-intersection.
	 *
	 * If the node is a potential boundary node (e.g. came from an edge
	 * which is a boundary) then insert it as a potential boundary node.
	 * Otherwise, just add it as a regular node.
	 */
	void addSelfIntersectionNode(int argIndex,
		const geom::Coordinate& coord, int loc);

public:

	static bool isInBoundary(int boundaryCount);

	static int determineBoundary(int boundaryCount);

	GeometryGraph();

	GeometryGraph(int newArgIndex, const geom::Geometry *newParentGeom);

	virtual ~GeometryGraph();


	const geom::Geometry* getGeometry();

	/// Returned object is owned by this GeometryGraph
	std::vector<Node*>* getBoundaryNodes();

	void getBoundaryNodes(std::vector<Node*>&bdyNodes);

	/// Returned object is owned by this GeometryGraph
	geom::CoordinateSequence* getBoundaryPoints();

	Edge* findEdge(const geom::LineString *line);

	void computeSplitEdges(std::vector<Edge*> *edgelist);

	void addEdge(Edge *e);

	void addPoint(geom::Coordinate& pt);

	/**
	 * \brief
	 * Compute self-nodes, taking advantage of the Geometry type to
	 * minimize the number of intersection tests.  (E.g. rings are
	 * not tested for self-intersection, since
	 * they are assumed to be valid).
	 *
	 * @param li the LineIntersector to use
	 *
	 * @param computeRingSelfNodes if <false>, intersection checks are
	 *	optimized to not test rings for self-intersection
	 *
	 * @return the SegmentIntersector used, containing information about
	 *	the intersections found
	 */
	index::SegmentIntersector* computeSelfNodes(
			algorithm::LineIntersector *li,
			bool computeRingSelfNodes);

	// Quick inline calling the function above, the above should probably
	// be deprecated.
	index::SegmentIntersector* computeSelfNodes(
			algorithm::LineIntersector& li,
			bool computeRingSelfNodes);

	index::SegmentIntersector* computeEdgeIntersections(GeometryGraph *g,
		algorithm::LineIntersector *li, bool includeProper);

	std::vector<Edge*> *getEdges();

	bool hasTooFewPoints();

	const geom::Coordinate& getInvalidPoint(); 

};


} // namespace GEOMETRY.geomgraph
} // namespace GEOMETRY

#ifdef GEOS_INLINE
# include "Geometry/geomgraph/GeometryGraph.inl"
#endif

#endif // ifndef GEOS_GEOMGRAPH_GEOMETRYGRAPH_H

/**********************************************************************
 * $Log$
 * Revision 1.4  2006/06/13 22:00:26  strk
 * Changed GeometryGraph::lineEdgeMap set comparison function to be pointer-based. Should be safe and much faster. Available tests all succeed.
 *
 * Revision 1.3  2006/03/29 15:23:49  strk
 * Moved GeometryGraph inlines from .h to .inl file
 *
 * Revision 1.2  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/

