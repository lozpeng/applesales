/**********************************************************************
 * $Id: SweepLineInterval.cpp 1820 2006-09-06 16:54:23Z mloskot $
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

#include <Geometry/index/sweepline/SweepLineInterval.h>

namespace GEOMETRY {
namespace index { // geos.index
namespace sweepline { // geos.index.sweepline

SweepLineInterval::SweepLineInterval(double newMin, double newMax, void* newItem)
{
	min=newMin<newMax?newMin:newMax;
	max=newMax>newMin?newMax:newMin;
	item=newItem;
}

double
SweepLineInterval::getMin()
{
	return min;
}

double
SweepLineInterval::getMax()
{
	return max;
}

void*
SweepLineInterval::getItem()
{
	return item;
}

} // namespace GEOMETRY.index.sweepline
} // namespace GEOMETRY.index
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.8  2006/03/21 10:01:30  strk
 * indexSweepline.h header split
 *
 * Revision 1.7  2006/02/20 10:14:18  strk
 * - namespaces GEOMETRY::index::*
 * - Doxygen documentation cleanup
 *
 * Revision 1.6  2004/07/02 13:28:27  strk
 * Fixed all #include lines to reflect headers layout change.
 * Added client application build tips in README.
 *
 * Revision 1.5  2003/11/07 01:23:42  pramsey
 * Add standard CVS headers licence notices and copyrights to all cpp and h
 * files.
 *
 *
 **********************************************************************/

