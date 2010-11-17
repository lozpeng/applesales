/**********************************************************************
 * $Id: MinimalEdgeRing.inl 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_OP_OVERLAY_MINIMALEDGERING_INL
#define GEOS_OP_OVERLAY_MINIMALEDGERING_INL

#include <Geometry/operation/overlay/MinimalEdgeRing.h>

#if GEOS_DEBUG
#include <iostream>
#endif

namespace GEOMETRY {
namespace operation { // GEOMETRY::operation
namespace overlay { // GEOMETRY::operation::overlay

INLINE void
MinimalEdgeRing::setEdgeRing(geomgraph::DirectedEdge *de, geomgraph::EdgeRing *er)
{
	de->setMinEdgeRing(er);
}

INLINE geomgraph::DirectedEdge*
MinimalEdgeRing::getNext(geomgraph::DirectedEdge *de)
{
	return de->getNextMin();
}

INLINE
MinimalEdgeRing::~MinimalEdgeRing()
{
#if GEOS_DEBUG
	std::cerr << "MinimalEdgeRing[" << this << "] dtor" << std::endl;
#endif
}

} // namespace GEOMETRY::operation::overlay
} // namespace GEOMETRY::operation
} // namespace GEOMETRY

#endif // GEOS_OP_OVERLAY_MINIMALEDGERING_INL

