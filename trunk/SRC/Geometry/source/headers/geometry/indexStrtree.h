/**********************************************************************
 * $Id: indexStrtree.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_INDEXSTRTREE_H
#define GEOS_INDEXSTRTREE_H

namespace GEOMETRY {
namespace index { // geos.index

/// Contains 2-D and 1-D versions of the Sort-Tile-Recursive (STR) tree, a query-only R-tree.
namespace strtree { // geos.index.strtree

} // namespace GEOMETRY.index.strtree
} // namespace GEOMETRY.index
} // namespace GEOMETRY

#include <Geometry/index/strtree/AbstractNode.h>
#include <Geometry/index/strtree/AbstractSTRtree.h>
#include <Geometry/index/strtree/Boundable.h>
#include <Geometry/index/strtree/Interval.h>
//#include <Geometry/index/strtree/ItemBoundable.h>
#include <Geometry/index/strtree/SIRtree.h>
#include <Geometry/index/strtree/STRtree.h>

#endif // GEOS_INDEXSTRTREE_H

/**********************************************************************
 * $Log$
 * Revision 1.17  2006/06/01 10:28:46  strk
 * Reduced number of installed headers for the GEOMETRY::index namespace
 *
 * Revision 1.16  2006/03/21 10:47:34  strk
 * indexStrtree.h split
 *
 * Revision 1.15  2006/03/09 16:46:48  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 **********************************************************************/

