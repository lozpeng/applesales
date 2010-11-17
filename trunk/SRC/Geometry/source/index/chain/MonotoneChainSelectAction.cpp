/**********************************************************************
 * $Id: MonotoneChainSelectAction.cpp 1820 2006-09-06 16:54:23Z mloskot $
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

#include <Geometry/index/chain/MonotoneChainSelectAction.h>
#include <Geometry/index/chain/MonotoneChain.h>
#include <Geometry/geom/Envelope.h>
#include <Geometry/geom/LineSegment.h>


namespace GEOMETRY {
namespace index { // geos.index
namespace chain { // geos.index.chain

MonotoneChainSelectAction::MonotoneChainSelectAction()
{
	selectedSegment=new geom::LineSegment();
	tempEnv1=new geom::Envelope();
}

MonotoneChainSelectAction::~MonotoneChainSelectAction()
{
	delete selectedSegment;
	delete tempEnv1;
}

void
MonotoneChainSelectAction::select(MonotoneChain& mc, unsigned int start)
{
	mc.getLineSegment(start, selectedSegment);
	select(selectedSegment);
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

