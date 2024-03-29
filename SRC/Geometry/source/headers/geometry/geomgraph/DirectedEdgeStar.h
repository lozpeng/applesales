/**********************************************************************
 * $Id: DirectedEdgeStar.h 1820 2006-09-06 16:54:23Z mloskot $
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


#ifndef GEOMETRY_GEOMGRAPH_DIRECTEDEDGEENDSTAR_H
#define GEOMETRY_GEOMGRAPH_DIRECTEDEDGEENDSTAR_H

#include <set>
#include <string>
#include <vector>

#include <Geometry/geomgraph/EdgeEndStar.h>  // for inheritance
#include <Geometry/geomgraph/Label.h>  // for private member
#include <Geometry/geom/Coordinate.h>  // for p0,p1

#include <Geometry/inline.h>

// Forward declarations
namespace GEOMETRY {
	namespace geomgraph {
		class DirectedEdge;
		class EdgeRing;
	}
}

namespace GEOMETRY {
namespace geomgraph { // geos.geomgraph

/**
 * \brief
 * A DirectedEdgeStar is an ordered list of <b>outgoing</b> DirectedEdges around a node.
 *
 * It supports labelling the edges as well as linking the edges to form both
 * MaximalEdgeRings and MinimalEdgeRings.
 *
 * Last port: geomgraph/DirectedEdgeStar.java rev. 1.4 (JTS-1.7)
 */
class DirectedEdgeStar: public EdgeEndStar {

public:

	DirectedEdgeStar()
		:
		EdgeEndStar(),
		resultAreaEdgeList(0),
		label()
	{}

	~DirectedEdgeStar() {
		delete resultAreaEdgeList;
	}

	/// Insert a directed edge in the list
	void insert(EdgeEnd *ee);

	Label &getLabel() { return label; }

	int getOutgoingDegree();

	int getOutgoingDegree(EdgeRing *er);

	DirectedEdge* getRightmostEdge();

	/** \brief
	 * Compute the labelling for all dirEdges in this star, as well
	 * as the overall labelling
	 */
	void computeLabelling(std::vector<GeometryGraph*> *geom); // throw(TopologyException *);

	/** \brief
	 * For each dirEdge in the star,
	 * merge the label from the sym dirEdge into the label
	 */
	void mergeSymLabels();

	/// Update incomplete dirEdge labels from the labelling for the node
	void updateLabelling(Label *nodeLabel);


	/**
	 * Traverse the star of DirectedEdges, linking the included edges together.
	 * To link two dirEdges, the <next> pointer for an incoming dirEdge
	 * is set to the next outgoing edge.
	 * 
	 * DirEdges are only linked if:
	 * 
	 * - they belong to an area (i.e. they have sides)
	 * - they are marked as being in the result
	 * 
	 * Edges are linked in CCW order (the order they are stored).
	 * This means that rings have their face on the Right
	 * (in other words,
	 * the topological location of the face is given by the RHS label of the DirectedEdge)
	 * 
	 * PRECONDITION: No pair of dirEdges are both marked as being in the result
	 */
	void linkResultDirectedEdges(); // throw(TopologyException *);

	void linkMinimalDirectedEdges(EdgeRing *er);

	void linkAllDirectedEdges();

	/** \brief
	 * Traverse the star of edges, maintaing the current location in the result
	 * area at this node (if any).
	 *
	 * If any L edges are found in the interior of the result, mark them as covered.
	 */
	void findCoveredLineEdges();

	/** \brief
	 * Compute the DirectedEdge depths for a subsequence of the edge array.
	 *
	 * @return the last depth assigned (from the R side of the last edge visited)
	 */
	void computeDepths(DirectedEdge *de);

	std::string print();

private:

	/**
	 * A list of all outgoing edges in the result, in CCW order
	 */
	std::vector<DirectedEdge*> *resultAreaEdgeList;

	Label label;

	/// \brief
	/// Returned vector is onwed by DirectedEdgeStar object, but
	/// lazily created
	std::vector<DirectedEdge*>* getResultAreaEdges();

	/// States for linResultDirectedEdges
	enum {
		SCANNING_FOR_INCOMING=1,
		LINKING_TO_OUTGOING
	};

	int computeDepths(EdgeEndStar::iterator startIt,
		EdgeEndStar::iterator endIt, int startDepth);
};


} // namespace GEOMETRY.geomgraph
} // namespace GEOMETRY

//#ifdef GEOS_INLINE
//# include "Geometry/geomgraph/DirectedEdgeEndStar.inl"
//#endif

#endif // ifndef GEOS_GEOMGRAPH_DIRECTEDEDGEENDSTAR_H

/**********************************************************************
 * $Log$
 * Revision 1.4  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.3  2006/03/23 15:10:29  strk
 * Dropped by-pointer TopologyException constructor, various small cleanups
 *
 * Revision 1.2  2006/03/15 17:17:41  strk
 * Added missing forward declarations
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/

