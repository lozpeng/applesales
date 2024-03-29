/**********************************************************************
 * $Id: EdgeEndBuilder.cpp 1820 2006-09-06 16:54:23Z mloskot $
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
 **********************************************************************
 *
 **********************************************************************/

#include <Geometry/operation/relate/EdgeEndBuilder.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geomgraph/Edge.h>
#include <Geometry/geomgraph/EdgeEnd.h>
#include <Geometry/geomgraph/EdgeIntersectionList.h>
#include <Geometry/geomgraph/Label.h>

#include <vector>

using namespace std;
using namespace GEOMETRY::geomgraph;
using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace operation { // geos.operation
namespace relate { // geos.operation.relate

vector<EdgeEnd*> *
EdgeEndBuilder::computeEdgeEnds(vector<Edge*> *edges)
{
	vector<EdgeEnd*> *l=new vector<EdgeEnd*>();
	for(vector<Edge*>::iterator i=edges->begin();i<edges->end();i++) {
		Edge *e=*i;
		computeEdgeEnds(e,l);
	}
	return l;
}

/**
 * Creates stub edges for all the intersections in this
 * Edge (if any) and inserts them into the graph.
 */
void
EdgeEndBuilder::computeEdgeEnds(Edge *edge, vector<EdgeEnd*> *l)
{
	EdgeIntersectionList &eiList=edge->getEdgeIntersectionList();
	//Debug.print(eiList);
	// ensure that the list has entries for the first and last point of the edge
	eiList.addEndpoints();

	EdgeIntersectionList::iterator it=eiList.begin();
	// no intersections, so there is nothing to do
	if (it==eiList.end()) return;

	EdgeIntersection *eiPrev=NULL;
	EdgeIntersection *eiCurr=NULL;

	EdgeIntersection *eiNext=*it;
	it++;
	do {
		eiPrev=eiCurr;
		eiCurr=eiNext;
		eiNext=NULL;
		if (it!=eiList.end()) {
			eiNext=*it;
			it++;
		}
		if (eiCurr!=NULL) {
			createEdgeEndForPrev(edge,l,eiCurr,eiPrev);
			createEdgeEndForNext(edge,l,eiCurr,eiNext);
		}
	} while (eiCurr!=NULL);
}

/**
 * Create a EdgeStub for the edge before the intersection eiCurr.
 * The previous intersection is provided
 * in case it is the endpoint for the stub edge.
 * Otherwise, the previous point from the parent edge will be the endpoint.
 * 
 * eiCurr will always be an EdgeIntersection, but eiPrev may be null.
 */
void
EdgeEndBuilder::createEdgeEndForPrev(Edge *edge, vector<EdgeEnd*> *l,
		EdgeIntersection *eiCurr, EdgeIntersection *eiPrev)
{
	int iPrev=eiCurr->segmentIndex;
	if (eiCurr->dist==0.0) {
		// if at the start of the edge there is no previous edge
		if (iPrev==0) return;
		iPrev--;
	}
	Coordinate pPrev(edge->getCoordinate(iPrev));
	// if prev intersection is past the previous vertex, use it instead
	if (eiPrev!=NULL && eiPrev->segmentIndex>=iPrev)
		pPrev=eiPrev->coord; 
	Label *label=new Label(*(edge->getLabel()));
	// since edgeStub is oriented opposite to it's parent edge, have to flip sides for edge label
	label->flip();
	EdgeEnd *e=new EdgeEnd(edge,eiCurr->coord,pPrev,label);
	//e.print(System.out);  System.out.println();
	l->push_back(e);
}

/**
 * Create a StubEdge for the edge after the intersection eiCurr.
 * The next intersection is provided
 * in case it is the endpoint for the stub edge.
 * Otherwise, the next point from the parent edge will be the endpoint.
 * 
 * eiCurr will always be an EdgeIntersection, but eiNext may be null.
 */
void
EdgeEndBuilder::createEdgeEndForNext(Edge *edge, vector<EdgeEnd*> *l,
		EdgeIntersection *eiCurr, EdgeIntersection *eiNext)
{
	int iNext=eiCurr->segmentIndex + 1;
	// if there is no next edge there is nothing to do
	if (iNext>=edge->getNumPoints() && eiNext==NULL) return;
	Coordinate pNext(edge->getCoordinate(iNext));
	// if the next intersection is in the same segment as the current, use it as the endpoint
	if (eiNext!=NULL && eiNext->segmentIndex==eiCurr->segmentIndex)
		pNext=eiNext->coord; 
	EdgeEnd *e=new EdgeEnd(edge,eiCurr->coord,pNext,new Label(*(edge->getLabel())));
	//Debug.println(e);
	l->push_back(e);
}

} // namespace GEOMETRY.operation.relate
} // namespace GEOMETRY.operation
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.17  2006/03/21 13:11:29  strk
 * opRelate.h header split
 *
 * Revision 1.16  2006/03/20 16:57:44  strk
 * spatialindex.h and opValid.h headers split
 *
 * Revision 1.15  2006/02/19 19:46:50  strk
 * Packages <-> namespaces mapping for most GEOS internal code (uncomplete, but working). Dir-level libs for index/ subdirs.
 *
 **********************************************************************/

