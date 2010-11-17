/**********************************************************************
 * $Id: geomUtil.h 2120 2008-01-30 22:34:13Z benjubb $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#ifndef GEOMETRY_GEOMUTIL_H
#define GEOMETRY_GEOMUTIL_H

#include <Geometry/geom/util/GeometryEditor.h>
#include <Geometry/geom/util/GeometryEditorOperation.h>
#include <Geometry/geom/util/CoordinateOperation.h>
#include <Geometry/geom/util/LinearComponentExtracter.h>
#include <Geometry/geom/util/PointExtracter.h>
#include <Geometry/geom/util/PolygonExtracter.h>
#include <Geometry/geom/util/ShortCircuitedGeometryVisitor.h>

namespace GEOMETRY {
namespace geom { // geos.geom

/** \brief
 * Provides classes that parse and modify Geometry objects.
 */
namespace util { // geos.geom.util

} // namespace GEOMETRY.geom.util
} // namespace GEOMETRY.geom
} // namespace GEOMETRY

#endif

/**********************************************************************
 * $Log$
 * Revision 1.9  2006/03/09 16:46:48  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/
