/**********************************************************************
 * $Id: MCPointInRing.cpp 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2006 Refractions Research Inc.
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#include <Geometry/algorithm/MCPointInRing.h>
#include <Geometry/algorithm/RobustDeterminant.h>
#include <Geometry/index/bintree/Bintree.h>
#include <Geometry/index/bintree/Interval.h>
#include <Geometry/geom/LineSegment.h>
#include <Geometry/geom/LinearRing.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/Envelope.h>
#include <Geometry/index/chain/MonotoneChain.h> 
#include <Geometry/index/chain/MonotoneChainBuilder.h> 

#include <vector>

using namespace std;
using namespace GEOMETRY::geom;
using namespace GEOMETRY::index;

namespace GEOMETRY {
namespace algorithm { // geos.algorithm

MCPointInRing::MCSelecter::MCSelecter(const Coordinate& newP,
		MCPointInRing *prt)
{
	p=newP;
	parent=prt;
}

void
MCPointInRing::MCSelecter::select(LineSegment *ls)
{
	parent->testLineSegment(p,ls);
}

MCPointInRing::MCPointInRing(const LinearRing *newRing)
	:
	ring(newRing),
	interval(),
	pts(NULL),
	tree(NULL),
	crossings(0)
{
	buildIndex();
}

MCPointInRing::~MCPointInRing()
{
	delete tree;
	delete pts;
}

void
MCPointInRing::buildIndex()
{
	//using namespace GEOMETRY::index;

//	Envelope *env=ring->getEnvelopeInternal();
	tree=new bintree::Bintree();
	pts=CoordinateSequence::removeRepeatedPoints(ring->getCoordinatesRO());
	vector<chain::MonotoneChain*> *mcList=chain::MonotoneChainBuilder::getChains(pts);
	for(int i=0;i<(int)mcList->size();i++) {
		chain::MonotoneChain *mc=(*mcList)[i];
		Envelope *mcEnv=mc->getEnvelope();
		interval.min=mcEnv->getMinY();
		interval.max=mcEnv->getMaxY();
		tree->insert(&interval,mc);
	}
	delete mcList;
}

bool
MCPointInRing::isInside(const Coordinate& pt)
{
	crossings=0;
	// test all segments intersected by ray from pt in positive x direction
	Envelope *rayEnv=new Envelope(DoubleNegInfinity,DoubleInfinity,pt.y,pt.y);
	interval.min=pt.y;
	interval.max=pt.y;
	vector<void*> *segs=tree->query(&interval);
	//System.out.println("query size=" + segs.size());
	MCSelecter *mcSelecter=new MCSelecter(pt,this);
	for(int i=0;i<(int)segs->size();i++) {
		chain::MonotoneChain *mc=(chain::MonotoneChain*) (*segs)[i];
		testMonotoneChain(rayEnv,mcSelecter,mc);
	}
	/*
	*  p is inside if number of crossings is odd.
	*/
//	for(int i=0;i<(int)segs->size();i++) {
//		delete (chain::MonotoneChain*) (*segs)[i];
//	}
	delete segs;
	delete rayEnv;
	delete mcSelecter;
	if((crossings%2)==1) {
		return true;
	}
	return false;
}


void
MCPointInRing::testMonotoneChain(Envelope *rayEnv,
		MCSelecter *mcSelecter,
		chain::MonotoneChain *mc)
{
	mc->select(*rayEnv, *mcSelecter);
}

void
MCPointInRing::testLineSegment(Coordinate& p,LineSegment *seg)
{
	double xInt;  // x intersection of segment with ray
	double x1;    // translated coordinates
	double y1;
	double x2;
	double y2;

	/*
	*  Test if segment crosses ray from test point in positive x direction.
	*/
	Coordinate& p1=seg->p0;
	Coordinate& p2=seg->p1;
	x1=p1.x-p.x;
	y1=p1.y-p.y;
	x2=p2.x-p.x;
	y2=p2.y-p.y;
	if (((y1>0)&&(y2<=0)) || ((y2>0)&&(y1<=0))) {
		/*
		*  segment straddles x axis, so compute intersection.
		*/
		xInt=RobustDeterminant::signOfDet2x2(x1,y1,x2,y2)/(y2-y1);
		//xsave=xInt;
		/*
		*  crosses ray if strictly positive intersection.
		*/
		if (0.0<xInt) {
			crossings++;
		}
	}
}

} // namespace GEOMETRY.algorithm
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.27  2006/03/29 11:52:00  strk
 * const correctness, useless heap allocations removal
 *
 * Revision 1.26  2006/03/22 18:12:31  strk
 * indexChain.h header split.
 *
 * Revision 1.25  2006/03/22 16:01:33  strk
 * indexBintree.h header split, classes renamed to match JTS
 *
 * Revision 1.24  2006/03/21 11:12:23  strk
 * Cleanups: headers inclusion and Log section
 *
 * Revision 1.23  2006/03/09 16:46:45  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 **********************************************************************/

