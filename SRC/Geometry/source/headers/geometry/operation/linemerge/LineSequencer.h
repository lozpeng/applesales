/**********************************************************************
 * $Id: LineSequencer.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_OP_LINEMERGE_LINESEQUENCER_H
#define GEOS_OP_LINEMERGE_LINESEQUENCER_H

#include <Geometry/operation/linemerge/LineMergeGraph.h> // for composition
#include <Geometry/geom/Geometry.h> // for inlines
#include <Geometry/geom/LineString.h> // for inlines

#include <vector>
#include <list>
#include <memory> // for auto_ptr

// Forward declarations 
namespace GEOMETRY {
	namespace geom { 
		class GeometryFactory;
		class Geometry;
		class LineString;
	}
	namespace planargraph { 
		class DirectedEdge;
		class Subgraph;
		class Node;
	}
}


namespace GEOMETRY {
namespace operation { // GEOMETRY::operation
namespace linemerge { // GEOMETRY::operation::linemerge

/** \brief
 * Builds a sequence from a set of LineStrings so that
 * they are ordered end to end.
 *
 * A sequence is a complete non-repeating list of the linear
 * components of the input.  Each linestring is oriented
 * so that identical endpoints are adjacent in the list.
 *
 * The input linestrings may form one or more connected sets.
 * The input linestrings should be correctly noded, or the results may
 * not be what is expected.
 * The output of this method is a single MultiLineString containing the ordered
 * linestrings in the sequence.
 * 
 * The sequencing employs the classic <b>Eulerian path</b> graph algorithm.
 * Since Eulerian paths are not uniquely determined,
 * further rules are used to
 * make the computed sequence preserve as much as possible of the input
 * ordering.
 * Within a connected subset of lines, the ordering rules are:
 *
 * - If there is degree-1 node which is the start
 *   node of an linestring, use that node as the start of the sequence
 * - If there is a degree-1 node which is the end
 *   node of an linestring, use that node as the end of the sequence
 * - If the sequence has no degree-1 nodes, use any node as the start
 *
 * Not all arrangements of lines can be sequenced.
 * For a connected set of edges in a graph,
 * Euler's Theorem states that there is a sequence containing each edge once
 * if and only if there are no more than 2 nodes of odd degree.
 * If it is not possible to find a sequence, the isSequenceable method
 * will return <code>false</code>.
 *
 * Last port: operation/linemerge/LineSequencer.java rev. 1.5 (JTS-1.7)
 */
class LineSequencer {

private:
	typedef std::list<planargraph::DirectedEdge*> DirEdgeList;
	typedef std::vector< DirEdgeList* > Sequences;

	LineMergeGraph graph;
	const geom::GeometryFactory *factory;
	unsigned int lineCount;
	bool isRun;
	std::auto_ptr<geom::Geometry> sequencedGeometry;
	bool isSequenceableVar;

	void addLine(const geom::LineString *lineString);
	void computeSequence();
	Sequences* findSequences();
	DirEdgeList* findSequence(planargraph::Subgraph& graph);

	/// return a newly allocated LineString
	static geom::LineString* reverse(const geom::LineString *line);

	/**
	 * Builds a geometry ({@link LineString} or {@link MultiLineString} )
	 * representing the sequence.
	 *
	 * @param sequences a vector of vectors of const planarDirectedEdges
	 *                  with LineMergeEdges as their parent edges.
	 * @return the sequenced geometry, possibly NULL
	 *         if no sequence exists
	 */
	geom::Geometry* buildSequencedGeometry(const Sequences& sequences);

	static const planargraph::Node* findLowestDegreeNode(
			const planargraph::Subgraph& graph);

	void addReverseSubpath(const planargraph::DirectedEdge *de,
		DirEdgeList& deList,
		DirEdgeList::iterator lit,
		bool expectedClosed);
	
	/**
	 * Finds an {@link DirectedEdge} for an unvisited edge (if any),
	 * choosing the dirEdge which preserves orientation, if possible.
	 *
	 * @param node the node to examine
	 * @return the dirEdge found, or <code>null</code>
	 *         if none were unvisited
	 */
	static const planargraph::DirectedEdge* findUnvisitedBestOrientedDE(
			const planargraph::Node* node);

	/**
	 * Computes a version of the sequence which is optimally
	 * oriented relative to the underlying geometry.
	 * 
	 * Heuristics used are:
	 * 
	 * - If the path has a degree-1 node which is the start
	 *   node of an linestring, use that node as the start of the sequence
	 * - If the path has a degree-1 node which is the end
	 *   node of an linestring, use that node as the end of the sequence
	 * - If the sequence has no degree-1 nodes, use any node as the start
	 *   (NOTE: in this case could orient the sequence according to the
	 *   majority of the linestring orientations)
	 *
	 * @param seq a List of planarDirectedEdges 
	 * @return the oriented sequence, possibly same as input if already
	 *         oriented
	 */
	DirEdgeList* orient(DirEdgeList* seq);

	/**
	 * Reverse the sequence.
	 * This requires reversing the order of the dirEdges, and flipping
	 * each dirEdge as well
	 *
	 * @param seq a List of DirectedEdges, in sequential order
	 * @return the reversed sequence
	 */
	DirEdgeList* reverse(DirEdgeList& seq);

	/**
	 * Tests whether a complete unique path exists in a graph
	 * using Euler's Theorem.
	 *
	 * @param graph the subgraph containing the edges
	 * @return <code>true</code> if a sequence exists
	 */
	bool hasSequence(planargraph::Subgraph& graph);

public:

	LineSequencer()
		:
		factory(0),
		lineCount(0),
		isRun(false),
		sequencedGeometry(0),
		isSequenceableVar(false)
		{}

	/**
	 * Tests whether a {@link Geometry} is sequenced correctly.
	 * {@llink LineString}s are trivially sequenced.
	 * {@link MultiLineString}s are checked for correct sequencing.
	 * Otherwise, <code>isSequenced</code> is defined
	 * to be <code>true</code> for geometries that are not lineal.
	 *
	 * @param geom the geometry to test
	 * @return true if the geometry is sequenced or is not lineal
	 */
	static bool isSequenced(const geom::Geometry* geom);

	/**
	 * Tests whether the arrangement of linestrings has a valid
	 * sequence.
	 *
	 * @return <code>true</code> if a valid sequence exists.
	 */
	bool isSequenceable() {
		computeSequence();
		return isSequenceableVar;
	}

	/**
	 * Adds a {@link Geometry} to be sequenced.
	 * May be called multiple times.
	 * Any dimension of Geometry may be added; the constituent
	 * linework will be extracted.
	 *
	 * @param geometry the geometry to add
	 */
	void add(const geom::Geometry& geometry) {
		geometry.applyComponentFilter(*this);
	}

	/**
	 * Act as a GeometryComponentFilter so to extract
	 * the linearworks
	 */
	void filter(const geom::Geometry* g)
	{
		if (const geom::LineString *ls=dynamic_cast<const geom::LineString *>(g))
		{
			addLine(ls);
		}
	}

	/**
	 * Returns the LineString or MultiLineString
	 * built by the sequencing process, if one exists.
	 *
	 * @param release release ownership of computed Geometry
	 * @return the sequenced linestrings,
	 *         or <code>null</code> if a valid sequence
	 *         does not exist.
	 */
	geom::Geometry*
	getSequencedLineStrings(bool release=1) {
		computeSequence();
		if (release) return sequencedGeometry.release();
		else return sequencedGeometry.get();
	}


};

} // namespace GEOMETRY::operation::linemerge
} // namespace GEOMETRY::operation
} // namespace GEOMETRY

#endif // GEOS_OP_LINEMERGE_LINESEQUENCER_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/22 10:13:53  strk
 * opLinemerge.h split
 *
 **********************************************************************/
