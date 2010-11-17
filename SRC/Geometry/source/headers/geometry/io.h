/**********************************************************************
 * $Id: io.h 2174 2008-08-28 22:20:50Z sgillies $
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

#ifndef GEOS_IO_H
#define GEOS_IO_H

namespace GEOMETRY {

/// Contains the interfaces for converting JTS objects to and from other formats.
//
/// The Java Topology Suite (JTS) is a Java API that implements a core
/// set of spatial data operations usin g an explicit precision model
/// and robust geometric algorithms. JTS is intended to be used in the
/// devel opment of applications that support the validation, cleaning,
/// integration and querying of spatial data sets.
///
/// JTS attempts to implement the OpenGIS Simple Features Specification
/// (SFS) as accurately as possible.  In some cases the SFS is unclear
/// or omits a specification; in this case JTS attempts to choose a reaso
/// nable and consistent alternative.  Differences from and elaborations
/// of the SFS are documented in this specification.
///
/// <h2>Package Specification</h2>
///
/// <ul>
/// <li>Java Topology Suite Technical Specifications
/// <li><A HREF="http://www.opengis.org/techno/specs.htm">
///   OpenGIS Simple Features Specification for SQL</A>
/// </ul>
///
namespace io { // geos.io

} // namespace GEOMETRY.io
} // namespace GEOMETRY

#include <Geometry/io/ByteOrderDataInStream.h>
#include <Geometry/io/ByteOrderValues.h>
#include <Geometry/io/ParseException.h>
//#include <Geometry/io/StringTokenizer.h>
#include <Geometry/io/WKBConstants.h>
#include <Geometry/io/WKBReader.h>
#include <Geometry/io/WKBWriter.h>
#include <Geometry/io/WKTReader.h>
#include <Geometry/io/WKTWriter.h>
#include <Geometry/io/CLocalizer.h>
//#include <Geometry/io/Writer.h>

#include <Geometry/io/GeometrySerializor.h>

#ifdef __GNUC__
#warning *** DEPRECATED: You are using deprecated header io.h. Please, update your sources according to new layout of GEOS headers and namespaces
#endif

using namespace GEOMETRY::io;

#endif

/**********************************************************************
 * $Log$
 * Revision 1.29  2006/07/21 16:45:28  mloskot
 * Wrapped FIXME message with #warning directive to shout about potential headers removal in future.
 *
 * Revision 1.28  2006/06/01 11:49:36  strk
 * Reduced installed headers form geomgraph namespace
 *
 * Revision 1.27  2006/03/20 18:18:14  strk
 * io.h header split
 *
 **********************************************************************/

