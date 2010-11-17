/**********************************************************************
 * $Id: geom.h 2045 2007-12-19 20:18:24Z mloskot $
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

#ifndef GEOMETRY_GEOM_H
#define GEOMETRY_GEOM_H

/** \mainpage GEOS - Geometry Engine Open Source
 *
 * \section intro_sec Introduction
 *
 * Geometry Engine Open Source is a C++ port of the Java Topology Suite
 * released under the LGPL license.
 * It has interfaces for C++, C and python (though swig).
 *
 * \section getstart_sec Getting Started
 *	
 * The recommended low-level interface to the GEOS library
 * is the simplified \ref c_iface. This will ensure stability of the
 * API and the ABI of the library during performance improvements
 * that will likely change classes definitions.
 *
 * If you prefer troubles you can use the \ref cpp_iface.
 */

/** \page c_iface C wrapper interface
 *
 * \section Overview
 *
 * This is the preferred access method for GEOS.
 *
 * It is designed to keep binary compatibility across releases.
 *
 * \section Usage
 *
 * In order to use the C-API of geos you must link your code against
 * libgeos_c.so and include the geos_c.h header file, which also contain
 * function-level documentation.
 *
 */

/** \page cpp_iface C++ interface
 *
 * \section Overview
 *
 * Main class is GEOMETRY::geometry, from which all geometry types
 * derive.
 *
 * Construction and destruction of Geometries is done
 * using GEOMETRY::geom::GeometryFactory.
 *
 * You'll feed it GEOMETRY::geom::CoordinateSequence
 * for base geometries or vectors of geometries for collections.
 *
 * If you need to construct geometric shaped geometries, you
 * can use GEOMETRY::geom::GeometricShapeFactory.
 *
 * GEOS version info (as a string) can be obtained using
 * GEOMETRY::geom::geosversion(). The JTS version this release has been
 * ported from is available throu GEOMETRY::geom::jtsport().
 *
 * \section io_sect Input / Output
 *
 * For WKT input/output you can use GEOMETRY::io::WKTReader and GEOMETRY::io::WKTWriter
 *
 * For WKB input/output you can use GEOMETRY::io::WKBReader and GEOMETRY::io::WKBWriter
 *
 * \section exc_sect Exceptions
 *
 * Internal exceptions are thrown as instances GEOMETRY::util::GEOSException or
 * derived classes. GEOSException derives from std::exception.
 *
 * Note that prior to version 3.0.0, GEOSException were trown by
 * pointer, and did not derive from std::exception.
 *
 */ 


namespace GEOMETRY {

/// Contains the <CODE>Geometry</CODE> interface hierarchy and supporting classes.
//
/// The Java Topology Suite (JTS) is a Java API that implements a core
/// set of spatial data operations using an explicit precision model
/// and robust geometric algorithms. JTS is int ended to be used in the
/// development of applications that support the validation, cleaning,
/// integration and querying of spatial datasets.
///
/// JTS attempts to implement the OpenGIS Simple Features Specification
/// (SFS) as accurately as possible.  In some cases the SFS is unclear
/// or omits a specification; in this case J TS attempts to choose
/// a reasonable and consistent alternative.  Differences from and
/// elaborations of the SFS are documented in this specification.
///
/// <h2>Package Specification</h2>
///
/// - Java Topology Suite Technical Specifications
/// - <A HREF="http://www.opengis.org/techno/specs.htm">
///   OpenGIS Simple Features Specification for SQL</A>
///
namespace geom { // GEOMETRY::geom

} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/CoordinateArraySequence.h>
#include <Geometry/geom/CoordinateArraySequenceFactory.h>
#include <Geometry/geom/CoordinateFilter.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/CoordinateSequenceFactory.h>
#include <Geometry/geom/Dimension.h>
#include <Geometry/geom/Envelope.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/GeometryCollection.h>
#include <Geometry/geom/GeometryComponentFilter.h>
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/geom/GeometryFilter.h>
#include <Geometry/geom/LineString.h>
#include <Geometry/geom/LinearRing.h>
#include <Geometry/geom/MultiLineString.h>
#include <Geometry/geom/MultiPoint.h>
#include <Geometry/geom/MultiPolygon.h>
#include <Geometry/geom/Point.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/Circle.h>
#include <Geometry/geom/Ellipse.h>
#include <Geometry/geom/BezierSpline.h>
#include <Geometry/geom/PrecisionModel.h>
#include <Geometry/geom/LineSegment.h>
#include <Geometry/geom/IntersectionMatrix.h>
#include <Geometry/geom/Location.h>
//#include <Geometry/geom/Triangle.h>

#ifdef __GNUC__
#warning *** DEPRECATED: You are using deprecated header geom.h. Please, update your sources according to new layout of GEOS headers and namespaces
#endif

using namespace GEOMETRY::geom;



#endif // ndef GEOS_GEOM_H

