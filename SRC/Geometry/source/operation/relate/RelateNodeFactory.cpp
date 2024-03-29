/**********************************************************************
 * $Id: RelateNodeFactory.cpp 1820 2006-09-06 16:54:23Z mloskot $
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

#include <Geometry/operation/relate/RelateNodeFactory.h>
#include <Geometry/operation/relate/RelateNode.h>
#include <Geometry/operation/relate/EdgeEndBundleStar.h>

using namespace GEOMETRY::geom;
using namespace GEOMETRY::geomgraph;

namespace GEOMETRY {
namespace operation { // geos.operation
namespace relate { // geos.operation.relate

Node*
RelateNodeFactory::createNode(const Coordinate &coord) const
{
	return new RelateNode(coord, new EdgeEndBundleStar());
}

const NodeFactory &
RelateNodeFactory::instance() 
{
	static const RelateNodeFactory rnf;
	return rnf;
}


} // namespace GEOMETRY.operation.relate
} // namespace GEOMETRY.operation
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.10  2006/03/21 13:11:29  strk
 * opRelate.h header split
 *
 * Revision 1.9  2006/03/20 16:57:44  strk
 * spatialindex.h and opValid.h headers split
 *
 * Revision 1.8  2006/02/19 19:46:50  strk
 * Packages <-> namespaces mapping for most GEOS internal code (uncomplete, but working). Dir-level libs for index/ subdirs.
 **********************************************************************/

