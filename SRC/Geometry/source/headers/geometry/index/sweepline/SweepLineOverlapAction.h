/**********************************************************************
 * $Id: SweepLineOverlapAction.h 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#ifndef GEOS_INDEX_SWEEPLINE_SWEEPLINEOVERLAPACTION_H
#define GEOS_INDEX_SWEEPLINE_SWEEPLINEOVERLAPACTION_H

// Forward declarations
namespace GEOMETRY {
	namespace index { 
		namespace sweepline {
			class SweepLineInterval;
		}
	}
}

namespace GEOMETRY {
namespace index { // geos.index
namespace sweepline { // geos:index:sweepline

class SweepLineOverlapAction {
public:
	virtual void overlap(SweepLineInterval *s0,SweepLineInterval *s1)=0;

	virtual ~SweepLineOverlapAction() {}
};


} // namespace GEOMETRY:index:sweepline
} // namespace GEOMETRY:index
} // namespace GEOMETRY

#endif // GEOS_INDEX_SWEEPLINE_SWEEPLINEOVERLAPACTION_H

/**********************************************************************
 * $Log$
 * Revision 1.2  2006/06/08 11:20:24  strk
 * Added missing virtual destructor to abstract classes.
 *
 * Revision 1.1  2006/03/21 10:01:30  strk
 * indexSweepline.h header split
 *
 **********************************************************************/

