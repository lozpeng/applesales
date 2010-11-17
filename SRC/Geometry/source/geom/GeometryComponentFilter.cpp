/**********************************************************************
 * $Id: GeometryComponentFilter.cpp 2127 2008-05-20 21:25:21Z mloskot $
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

#include <cassert>

#include <Geometry/geom/GeometryComponentFilter.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/util.h>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

void GeometryComponentFilter::filter_rw(Geometry *geom) {
	geom->geometryChangedAction();
}

void GeometryComponentFilter::filter_ro(const Geometry *geom)
{
    UNREFERENCED_PARAMETER(geom);
	//assert(0);
}


} // namespace GEOMETRY::geom
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.12  2006/04/13 14:25:17  strk
 * TopologyPreservingSimplifier initial port
 *
 * Revision 1.11  2006/03/22 16:58:34  strk
 * Removed (almost) all inclusions of geom.h.
 * Removed obsoleted .cpp files.
 * Fixed a bug in WKTReader not using the provided CoordinateSequence
 * implementation, optimized out some memory allocations.
 *
 **********************************************************************/

