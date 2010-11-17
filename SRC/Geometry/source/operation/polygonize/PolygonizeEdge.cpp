/**********************************************************************
 * $Id: PolygonizeEdge.cpp 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2005-2006 Refractions Research Inc.
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/


#include <Geometry/operation/polygonize/PolygonizeEdge.h>

using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace operation { // geos.operation
namespace polygonize { // geos.operation.polygonize

PolygonizeEdge::PolygonizeEdge(const LineString *newLine) {
	line=newLine;
}

const LineString *
PolygonizeEdge::getLine() {
	return line;
}

} // namespace GEOMETRY.operation.polygonize
} // namespace GEOMETRY.operation
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.5  2006/03/22 11:19:06  strk
 * opPolygonize.h headers split.
 *
 **********************************************************************/
