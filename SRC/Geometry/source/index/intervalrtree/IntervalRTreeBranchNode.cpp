/**********************************************************************
 * $Id: IntervalRTreeBranchNode.cpp 2161 2008-08-18 16:29:09Z mloskot $
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

#include <Geometry/index/intervalrtree/IntervalRTreeBranchNode.h>
#include <Geometry/index/ItemVisitor.h>


namespace GEOMETRY {
namespace index {
namespace intervalrtree {
//
// private:
//

//
// protected:
//

//
// public:
//
	

void 
IntervalRTreeBranchNode::query( double queryMin, double queryMax, index::ItemVisitor * visitor) const
{
	if (! intersects(queryMin, queryMax)) 
		return;

	if (node1) 
		node1->query( queryMin, queryMax, visitor);

	if (node2) 
		node2->query( queryMin, queryMax, visitor);
}


} // geos::intervalrtree
} // GEOMETRY::index
} // geos

/**********************************************************************
 * $Log$
 *
 **********************************************************************/
