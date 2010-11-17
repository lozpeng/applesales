/**********************************************************************
 * $Id: inlines.cpp 2221 2008-11-18 03:09:56Z pramsey $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2005-2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * This file is here to make all inlined functions also 
 * available as non-inlines when building with GEOS_INLINES defined.
 *
 **********************************************************************/


// Only do something if GEOS_INLINE is defined
// Otherwise we'll end up with duplicated symbols


#ifdef GEOS_INLINE

// If using MingW with GEOS_INLINE to build a DLL then MingW's gcc
// has already generated the stubs for the contents of this file. 
// Hence we need to supress it to avoid "multiple definition" errors
// during the final link phase
#if ! defined(__MINGW32__) || defined(__MINGW32__) && !defined(DLL_EXPORT) 

// If using cygwin then we suppress the "multiple definition" errors by
// ignoring this section completely; the cygwin linker seems to handle
// the stubs correctly at link time by itself
#if ! defined(__CYGWIN__)


// Undefine GEOS_INLINE so that .inl files
// will be ready for an implementation file
#undef GEOS_INLINE 

#include <Geometry/inline.h>

#include <Geometry/io/WKTReader.inl>
#include <Geometry/io/ByteOrderDataInStream.inl>
#include <Geometry/operation/overlay/MinimalEdgeRing.inl>
#include <Geometry/geomgraph/DirectedEdge.inl>
#include <Geometry/geomgraph/GeometryGraph.inl>
#include <Geometry/algorithm/ConvexHull.inl>
#include <Geometry/geom/GeometryCollection.inl>
#include <Geometry/geom/LineSegment.inl>
#include <Geometry/geom/PrecisionModel.inl>
#include <Geometry/geom/Geometry.inl>
#include <Geometry/geom/Envelope.inl>
#include <Geometry/geom/Coordinate.inl>
#include <Geometry/geom/GeometryFactory.inl>
#include <Geometry/geom/MultiLineString.inl>
#include <Geometry/geom/MultiPolygon.inl>
#include <Geometry/geom/CoordinateArraySequenceFactory.inl>
#include <Geometry/noding/SegmentString.inl>
#include <Geometry/noding/snapround/HotPixel.inl>
#include <Geometry/noding/snapround/MCIndexSnapRounder.inl>
#include <Geometry/noding/MCIndexNoder.inl>

#endif // defined __CYGWIN__
#endif // defined __MINGW32__ and !defined DLL_EXPORT

#endif // defined GEOS_INLINE
