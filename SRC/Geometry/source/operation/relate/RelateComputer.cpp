/**********************************************************************
 * $Id: RelateComputer.cpp 1820 2006-09-06 16:54:23Z mloskot $
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

#include <Geometry/operation/relate/RelateComputer.h>
#include <Geometry/operation/relate/RelateNodeFactory.h>
#include <Geometry/operation/relate/RelateNode.h>
#include <Geometry/operation/relate/EdgeEndBuilder.h>
#include <Geometry/algorithm/LineIntersector.h>
#include <Geometry/algorithm/PointLocator.h>
#include <Geometry/geom/IntersectionMatrix.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/Envelope.h>
#include <Geometry/geomgraph/index/SegmentIntersector.h>
#include <Geometry/geomgraph/GeometryGraph.h>
#include <Geometry/geomgraph/Label.h>
#include <Geometry/geomgraph/Edge.h>
#include <Geometry/geomgraph/EdgeEndStar.h>
#include <Geometry/geomgraph/Node.h>
#include <Geometry/geomgraph/EdgeIntersectionList.h>
#include <Geometry/geomgraph/EdgeIntersection.h>

#include <vector>
#include <cassert>

using namespace GEOMETRY::geom;
using namespace GEOMETRY::geomgraph;
using namespace GEOMETRY::geomgraph::index;
using namespace GEOMETRY::algorithm;

namespace GEOMETRY {
namespace operation { // geos.operation
namespace relate { // geos.operation.relate

RelateComputer::RelateComputer(std::vector<GeometryGraph*> *newArg):
	arg(newArg),
	nodes(RelateNodeFactory::instance()),
	im(new IntersectionMatrix())
{
}

RelateComputer::~RelateComputer()
{
}

IntersectionMatrix*
RelateComputer::computeIM()
{
	// since Geometries are finite and embedded in a 2-D space, the EE element must always be 2
	im->set(Location::EXTERIOR,Location::EXTERIOR,2);
	// if the Geometries don't overlap there is nothing to do
	const Envelope *e1=(*arg)[0]->getGeometry()->getEnvelopeInternal();
	const Envelope *e2=(*arg)[1]->getGeometry()->getEnvelopeInternal();
	if (!e1->intersects(e2)) {
		computeDisjointIM(im);
		//delete e1;
		//delete e2;
		return im;
	}

	SegmentIntersector *si1=(*arg)[0]->computeSelfNodes(&li,false);
	SegmentIntersector *si2=(*arg)[1]->computeSelfNodes(&li,false);

	// compute intersections between edges of the two input geometries
	SegmentIntersector *intersector=(*arg)[0]->computeEdgeIntersections((*arg)[1], &li,false);
	computeIntersectionNodes(0);
	computeIntersectionNodes(1);

	/*
	 * Copy the labelling for the nodes in the parent Geometries.
	 * These override any labels determined by intersections
	 * between the geometries.
	 */
	copyNodesAndLabels(0);
	copyNodesAndLabels(1);

	/*
	 * complete the labelling for any nodes which only have a
	 * label for a single geometry
	 */
	//Debug.addWatch(nodes.find(new Coordinate(110, 200)));
	//Debug.printWatch();
	labelIsolatedNodes();
	//Debug.printWatch();

	/*
	 * If a proper intersection was found, we can set a lower bound
	 * on the IM.
	 */
	computeProperIntersectionIM(intersector, im);

	/*
	 * Now process improper intersections
	 * (eg where one or other of the geometrys has a vertex at the
	 * intersection point)
	 * We need to compute the edge graph at all nodes to determine
	 * the IM.
	 */
	// build EdgeEnds for all intersections
	EdgeEndBuilder eeBuilder;
	std::vector<EdgeEnd*> *ee0=eeBuilder.computeEdgeEnds((*arg)[0]->getEdges());
	insertEdgeEnds(ee0);
	std::vector<EdgeEnd*> *ee1=eeBuilder.computeEdgeEnds((*arg)[1]->getEdges());
	insertEdgeEnds(ee1);
	//Debug.println("==== NodeList ===");
	//Debug.print(nodes);
	labelNodeEdges();

	/**
	 * Compute the labeling for isolated components.
	 * Isolated components are components that do not touch any
	 * other components in the graph.
	 * They can be identified by the fact that they will
	 * contain labels containing ONLY a single element, the one for
	 * their parent geometry.
	 * We only need to check components contained in the input graphs,
	 * since isolated components will not have been replaced by new
	 * components formed by intersections.
	 */
	//debugPrintln("Graph A isolated edges - ");
	labelIsolatedEdges(0,1);
	//debugPrintln("Graph B isolated edges - ");
	labelIsolatedEdges(1,0);
	// update the IM from all components
	updateIM(im);
	delete si1;
	delete si2;
	delete intersector;
	delete ee0;
	delete ee1;
	return im;
}

void
RelateComputer::insertEdgeEnds(std::vector<EdgeEnd*> *ee)
{
	for(std::vector<EdgeEnd*>::iterator i=ee->begin();i<ee->end();i++) {
		EdgeEnd *e=*i;
		nodes.add(e);
	}
}

void
RelateComputer::computeProperIntersectionIM(SegmentIntersector *intersector,IntersectionMatrix *imX)
{
	// If a proper intersection is found, we can set a lower bound on the IM.
	int dimA=(*arg)[0]->getGeometry()->getDimension();
	int dimB=(*arg)[1]->getGeometry()->getDimension();
	bool hasProper=intersector->hasProperIntersection();
	bool hasProperInterior=intersector->hasProperInteriorIntersection();
	// For Geometry's of dim 0 there can never be proper intersections.
	/**
	* If edge segments of Areas properly intersect, the areas must properly overlap.
	*/
	if (dimA==2 && dimB==2) {
		if (hasProper) imX->setAtLeast("212101212");
	}
	/**
	* If an Line segment properly intersects an edge segment of an Area,
	* it follows that the Interior of the Line intersects the Boundary of the Area.
	* If the intersection is a proper <i>interior</i> intersection, then
	* there is an Interior-Interior intersection too.
	* Note that it does not follow that the Interior of the Line intersects the Exterior
	* of the Area, since there may be another Area component which contains the rest of the Line.
	*/
	 else if (dimA==2 && dimB==1) {
		if (hasProper) imX->setAtLeast("FFF0FFFF2");
		if (hasProperInterior) imX->setAtLeast("1FFFFF1FF");
	} else if (dimA==1 && dimB==2) {
		if (hasProper) imX->setAtLeast("F0FFFFFF2");
		if (hasProperInterior) imX->setAtLeast("1F1FFFFFF");
	}
	/* If edges of LineStrings properly intersect *in an interior point*, all
	we can deduce is that
	the interiors intersect.  (We can NOT deduce that the exteriors intersect,
	since some other segments in the geometries might cover the points in the
	neighbourhood of the intersection.)
	It is important that the point be known to be an interior point of
	both Geometries, since it is possible in a self-intersecting geometry to
	have a proper intersection on one segment that is also a boundary point of another segment.
	*/
	else if (dimA==1 && dimB==1) {
		if (hasProperInterior) imX->setAtLeast("0FFFFFFFF");
	}
}

/**
 * Copy all nodes from an arg geometry into this graph.
 * The node label in the arg geometry overrides any previously computed
 * label for that argIndex.
 * (E.g. a node may be an intersection node with
 * a computed label of BOUNDARY,
 * but in the original arg Geometry it is actually
 * in the interior due to the Boundary Determination Rule)
 */
void
RelateComputer::copyNodesAndLabels(int argIndex)
{
	const NodeMap* nm = (*arg)[argIndex]->getNodeMap();
	NodeMap::const_iterator nodeIt=nm->begin(), nodeEnd=nm->end();

	for( ; nodeIt!=nodeEnd; nodeIt++)
	{
		Node *graphNode=nodeIt->second;
		Node *newNode=nodes.addNode(graphNode->getCoordinate());
		newNode->setLabel(argIndex,
				graphNode->getLabel()->getLocation(argIndex));
		//node.print(System.out);
	}
}


/**
 * Insert nodes for all intersections on the edges of a Geometry.
 * Label the created nodes the same as the edge label if they do not
 * already have a label.
 * This allows nodes created by either self-intersections or
 * mutual intersections to be labelled.
 * Endpoint nodes will already be labelled from when they were inserted.
 */
void
RelateComputer::computeIntersectionNodes(int argIndex)
{
	std::vector<Edge*> *edges=(*arg)[argIndex]->getEdges();
	for(std::vector<Edge*>::iterator i=edges->begin();i<edges->end();i++)
	{
		Edge *e=*i;
		int eLoc=e->getLabel()->getLocation(argIndex);
		EdgeIntersectionList &eiL=e->getEdgeIntersectionList();
		EdgeIntersectionList::iterator it=eiL.begin();
		EdgeIntersectionList::iterator end=eiL.end();
		for( ; it!=end; ++it)
		{
			EdgeIntersection *ei=*it;
			assert(dynamic_cast<RelateNode*>(nodes.addNode(ei->coord)));
			RelateNode *n=static_cast<RelateNode*>(nodes.addNode(ei->coord));
			if (eLoc==Location::BOUNDARY)
			{
				n->setLabelBoundary(argIndex);
			}
			else
			{
				if (n->getLabel()->isNull(argIndex))
				  n->setLabel(argIndex,Location::INTERIOR);
			}
		}
	}
}

/*
 * For all intersections on the edges of a Geometry,
 * label the corresponding node IF it doesn't already have a label.
 * This allows nodes created by either self-intersections or
 * mutual intersections to be labelled.
 * Endpoint nodes will already be labelled from when they were inserted.
 */
void
RelateComputer::labelIntersectionNodes(int argIndex)
{
	std::vector<Edge*> *edges=(*arg)[argIndex]->getEdges();
	for(std::vector<Edge*>::iterator i=edges->begin();i<edges->end();i++) {
		Edge *e=*i;
		int eLoc=e->getLabel()->getLocation(argIndex);
		EdgeIntersectionList &eiL=e->getEdgeIntersectionList();
		EdgeIntersectionList::iterator eiIt=eiL.begin();
		EdgeIntersectionList::iterator eiEnd=eiL.end();
		
		for( ; eiIt!=eiEnd; ++eiIt)
		{
			EdgeIntersection *ei=*eiIt;
			RelateNode *n=(RelateNode*) nodes.find(ei->coord);
			if (n->getLabel()->isNull(argIndex)) {
				if (eLoc==Location::BOUNDARY)
				  n->setLabelBoundary(argIndex);
				else
				  n->setLabel(argIndex,Location::INTERIOR);
			}
		}
	}
}

/**
 * If the Geometries are disjoint, we need to enter their dimension and
 * boundary dimension in the Ext rows in the IM
 */
void
RelateComputer::computeDisjointIM(IntersectionMatrix *imX)
{
	const Geometry *ga=(*arg)[0]->getGeometry();
	if (!ga->isEmpty()) {
		imX->set(Location::INTERIOR,Location::EXTERIOR,ga->getDimension());
		imX->set(Location::BOUNDARY,Location::EXTERIOR,ga->getBoundaryDimension());
	}
	const Geometry *gb=(*arg)[1]->getGeometry();
	if (!gb->isEmpty()) {
		imX->set(Location::EXTERIOR,Location::INTERIOR,gb->getDimension());
		imX->set(Location::EXTERIOR,Location::BOUNDARY,gb->getBoundaryDimension());
	}
}


void
RelateComputer::labelNodeEdges()
{
	std::map<Coordinate*,Node*,CoordinateLessThen> &nMap=nodes.nodeMap;
	std::map<Coordinate*,Node*,CoordinateLessThen>::iterator nodeIt;
	for(nodeIt=nMap.begin();nodeIt!=nMap.end();nodeIt++)
	{
		assert(dynamic_cast<RelateNode*>(nodeIt->second));
		RelateNode *node=static_cast<RelateNode*>(nodeIt->second);
		node->getEdges()->computeLabelling(arg);
		//Debug.print(node.getEdges());
		//node.print(System.out);
	}
}

/**
 * update the IM with the sum of the IMs for each component
 */
void
RelateComputer::updateIM(IntersectionMatrix *imX)
{
	//Debug.println(im);
	std::vector<Edge *>::iterator ei=isolatedEdges.begin();
	for ( ; ei<isolatedEdges.end(); ++ei)
	{
		Edge *e=*ei;
		e->GraphComponent::updateIM(imX);
		//Debug.println(im);
	}
	std::map<Coordinate*,Node*,CoordinateLessThen> &nMap=nodes.nodeMap;
	std::map<Coordinate*,Node*,CoordinateLessThen>::iterator nodeIt;
	for(nodeIt=nMap.begin();nodeIt!=nMap.end();nodeIt++) {
		RelateNode *node=(RelateNode*) nodeIt->second;
		node->updateIM(imX);
		//Debug.println(im);
		node->updateIMFromEdges(imX);
		//Debug.println(im);
		//node.print(System.out);
	}
}

/**
* Processes isolated edges by computing their labelling and adding them
* to the isolated edges list.
* Isolated edges are guaranteed not to touch the boundary of the target (since if they
* did, they would have caused an intersection to be computed and hence would
* not be isolated)
*/
void RelateComputer::labelIsolatedEdges(int thisIndex,int targetIndex) {
	std::vector<Edge*> *edges=(*arg)[thisIndex]->getEdges();
	for(std::vector<Edge*>::iterator i=edges->begin();i<edges->end();i++) {
		Edge *e=*i;
		if (e->isIsolated()) {
			labelIsolatedEdge(e,targetIndex,(*arg)[targetIndex]->getGeometry());
			isolatedEdges.push_back(e);
		}
	}
}

/**
 * Label an isolated edge of a graph with its relationship to the target geometry.
 * If the target has dim 2 or 1, the edge can either be in the interior or the exterior.
 * If the target has dim 0, the edge must be in the exterior
 */
void
RelateComputer::labelIsolatedEdge(Edge *e, int targetIndex, const Geometry *target)
{
	// this won't work for GeometryCollections with both dim 2 and 1 geoms
	if (target->getDimension()>0) {
		// since edge is not in boundary, may not need the full generality of PointLocator?
		// Possibly should use ptInArea locator instead?  We probably know here
		// that the edge does not touch the bdy of the target Geometry
		int loc=ptLocator.locate(e->getCoordinate(), target);
		e->getLabel()->setAllLocations(targetIndex,loc);
	} else {
		e->getLabel()->setAllLocations(targetIndex,Location::EXTERIOR);
	}
	//System.out.println(e.getLabel());
}

/**
 * Isolated nodes are nodes whose labels are incomplete
 * (e.g. the location for one Geometry is null).
 * This is the case because nodes in one graph which don't intersect
 * nodes in the other are not completely labelled by the initial process
 * of adding nodes to the nodeList.
 * To complete the labelling we need to check for nodes that lie in the
 * interior of edges, and in the interior of areas.
 */
void
RelateComputer::labelIsolatedNodes()
{
	NodeMap::iterator nodeIt=nodes.begin(), nodeEnd=nodes.end();
	for( ; nodeIt!=nodeEnd; nodeIt++)
	{
		Node *n=nodeIt->second;
		Label *label=n->getLabel();
		// isolated nodes should always have at least one geometry in their label
		assert(label->getGeometryCount()>0); // node with empty label found
		if (n->isIsolated()) {
			if (label->isNull(0))
				labelIsolatedNode(n,0);
			else
				labelIsolatedNode(n,1);
		}
	}
}

/**
 * Label an isolated node with its relationship to the target geometry.
 */
void
RelateComputer::labelIsolatedNode(Node *n,int targetIndex)
{
	int loc=ptLocator.locate(n->getCoordinate(),
			(*arg)[targetIndex]->getGeometry());
	n->getLabel()->setAllLocations(targetIndex,loc);
	//debugPrintln(n.getLabel());
}

} // namespace GEOMETRY.operation.relate
} // namespace GEOMETRY.operation
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.32  2006/03/21 13:11:29  strk
 * opRelate.h header split
 *
 * Revision 1.31  2006/03/20 16:57:44  strk
 * spatialindex.h and opValid.h headers split
 *
 * Revision 1.30  2006/03/17 16:48:55  strk
 * LineIntersector and PointLocator made complete components of RelateComputer
 * (were statics const pointers before). Reduced inclusions from opRelate.h
 * and opValid.h, updated .cpp files to allow build.
 *
 * Revision 1.29  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 * Revision 1.28  2006/03/06 19:40:47  strk
 * GEOMETRY::util namespace. New GeometryCollection::iterator interface, many cleanups.
 *
 **********************************************************************/

