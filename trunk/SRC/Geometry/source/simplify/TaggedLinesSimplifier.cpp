/**********************************************************************
 * $Id: TaggedLinesSimplifier.cpp 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: simplify/TaggedLinesSimplifier.java rev. 1.4 (JTS-1.7.1)
 *
 **********************************************************************/

#include <Geometry/simplify/TaggedLinesSimplifier.h>
#include <Geometry/simplify/LineSegmentIndex.h>
#include <Geometry/simplify/TaggedLineStringSimplifier.h>
#include <Geometry/algorithm/LineIntersector.h>

#include <cassert>
#include <algorithm>
#include <memory>

#ifndef GEOS_DEBUG
#define GEOS_DEBUG 0
#endif

#ifdef GEOS_DEBUG
#include <iostream>
#endif

using namespace GEOMETRY::geom;
using namespace std;

namespace GEOMETRY {
namespace simplify { // GEOMETRY::simplify

/*public*/
TaggedLinesSimplifier::TaggedLinesSimplifier()
	:
	inputIndex(new LineSegmentIndex()),
	outputIndex(new LineSegmentIndex()),
	taggedlineSimplifier(new TaggedLineStringSimplifier(inputIndex.get(),
		outputIndex.get()))
{
}

/*public*/
void
TaggedLinesSimplifier::setDistanceTolerance(double d)
{
	taggedlineSimplifier->setDistanceTolerance(d);
}

/*private*/
void
TaggedLinesSimplifier::simplify(TaggedLineString& tls)
{
	taggedlineSimplifier->simplify(&tls);
}

} // namespace GEOMETRY::simplify
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.3  2006/05/24 11:41:23  strk
 *         * source/headers/geos/simplify/TaggedLinesSimplifier.h,
 *         source/simplify/TaggedLinesSimplifier.cpp,
 *         source/simplify/TopologyPreservingSimplifier.cpp:
 *         fixed bug in TopologyPreservingSimplifier failing to
 *         detect intersections, refactored TaggedLinesSimplifier
 *         class to more closely match JTS and use templated
 *         functions.
 *
 * Revision 1.2  2006/04/13 14:25:17  strk
 * TopologyPreservingSimplifier initial port
 *
 * Revision 1.1  2006/04/13 10:39:12  strk
 * Initial implementation of TaggedLinesSimplifier class
 *
 **********************************************************************/
