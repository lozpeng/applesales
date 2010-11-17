/**********************************************************************
 * $Id: RelateNode.cpp 1820 2006-09-06 16:54:23Z mloskot $
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

#include <Geometry/operation/relate/RelateNode.h>
#include <Geometry/operation/relate/EdgeEndBundleStar.h>
#include <Geometry/geom/IntersectionMatrix.h>
#include <Geometry/geomgraph/Label.h>
#include <Geometry/geomgraph/Node.h>

#include <cassert>

using namespace GEOMETRY::geomgraph;
using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace operation { // geos.operation
namespace relate { // geos.operation.relate

RelateNode::RelateNode(const Coordinate& coord, EdgeEndStar *edges):
	Node(coord,edges)
{}

RelateNode::~RelateNode()
{
}

/**
 * Update the IM with the contribution for this component.
 * A component only contributes if it has a labelling for both parent geometries
 */
void
RelateNode::computeIM(IntersectionMatrix *im)
{
	im->setAtLeastIfValid(label->getLocation(0),label->getLocation(1),0);
}

/**
 * Update the IM with the contribution for the EdgeEnds incident on this node.
 */
void
RelateNode::updateIMFromEdges(IntersectionMatrix *im)
{
	assert(dynamic_cast<EdgeEndBundleStar*>(edges));
	EdgeEndBundleStar* eebs=static_cast<EdgeEndBundleStar*>(edges);

	eebs->updateIM(im);
}

} // namespace GEOMETRY.operation.relate
} // namespace GEOMETRY.operation
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.12  2006/03/21 13:11:29  strk
 * opRelate.h header split
 *
 * Revision 1.11  2006/03/20 16:57:44  strk
 * spatialindex.h and opValid.h headers split
 *
 * Revision 1.10  2006/02/19 19:46:50  strk
 * Packages <-> namespaces mapping for most GEOS internal code (uncomplete, but working). Dir-level libs for index/ subdirs.
 *
 **********************************************************************/

