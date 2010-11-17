/**********************************************************************
 * $Id: MonotoneChainOverlapAction.cpp 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#include <Geometry/index/chain/MonotoneChainOverlapAction.h>
#include <Geometry/index/chain/MonotoneChain.h>
#include <Geometry/geom/Envelope.h>
#include <Geometry/geom/LineSegment.h>
#include <Geometry/profiler.h>

//#include <stdio.h>

namespace GEOMETRY {
namespace index { // geos.index
namespace chain { // geos.index.chain

MonotoneChainOverlapAction::MonotoneChainOverlapAction() {
	overlapSeg1=new geom::LineSegment();
	overlapSeg2=new geom::LineSegment();
	tempEnv1=new geom::Envelope();
	tempEnv2=new geom::Envelope();

}

MonotoneChainOverlapAction::~MonotoneChainOverlapAction() {
	delete overlapSeg1;
	delete overlapSeg2;
	delete tempEnv1;
	delete tempEnv2;
}


/**
 * This function can be overridden if the original chains are needed
 */
void
MonotoneChainOverlapAction::overlap(MonotoneChain *mc1, int start1,
		MonotoneChain *mc2, int start2)
{
	mc1->getLineSegment(start1,overlapSeg1);
	mc2->getLineSegment(start2,overlapSeg2);
	overlap(overlapSeg1,overlapSeg2);
}

} // namespace GEOMETRY.index.chain
} // namespace GEOMETRY.index
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.11  2006/03/22 18:12:32  strk
 * indexChain.h header split.
 *
 **********************************************************************/

