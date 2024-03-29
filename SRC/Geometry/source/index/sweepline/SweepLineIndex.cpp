/**********************************************************************
 * $Id: SweepLineIndex.cpp 1986 2007-06-08 15:27:42Z mloskot $
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

#include <Geometry/index/sweepline/SweepLineIndex.h>
#include <Geometry/index/sweepline/SweepLineEvent.h>
#include <Geometry/index/sweepline/SweepLineInterval.h>
#include <Geometry/index/sweepline/SweepLineOverlapAction.h>

#include <algorithm>

using namespace std;

namespace GEOMETRY {
namespace index { // geos.index
namespace sweepline { // geos.index.sweepline

SweepLineIndex::SweepLineIndex()
	:
	nOverlaps(0)
{
	//events=new vector<SweepLineEvent*>();
	//nOverlaps=0;
}

SweepLineIndex::~SweepLineIndex()
{
	//delete events;
}

void
SweepLineIndex::add(SweepLineInterval *sweepInt)
{
	// FIXME: who's going to delete the newly-created events ?
	SweepLineEvent *insertEvent=new SweepLineEvent(sweepInt->getMin(),NULL,sweepInt);
	events.push_back(insertEvent);
	events.push_back(new SweepLineEvent(sweepInt->getMax(), insertEvent, sweepInt));
}

/*private*/
void
SweepLineIndex::buildIndex()
{
    if (!indexBuilt)
    {
        sort(events.begin(), events.end(), SweepLineEventLessThen());
        const std::vector<SweepLineEvent*>::size_type n = events.size();
        for(std::vector<SweepLineEvent*>::size_type i = 0; i < n; i++)
        {
            SweepLineEvent *ev=events[i];
            if (ev->isDelete())
            {
                ev->getInsertEvent()->setDeleteEventIndex(static_cast<int>(i));
            }
        }
        indexBuilt = true;
    }
}

void
SweepLineIndex::computeOverlaps(SweepLineOverlapAction *action)
{
    nOverlaps = 0;
    
    buildIndex();

    const std::vector<SweepLineEvent*>::size_type n=events.size();
    for(std::vector<SweepLineEvent*>::size_type i=0; i<n; i++)
    {
        SweepLineEvent *ev=events[i];
        if (ev->isInsert())
        {
            processOverlaps(static_cast<int>(i),
                ev->getDeleteEventIndex(),
                ev->getInterval(), action);
        }
    }
}

void
SweepLineIndex::processOverlaps(int start, int end,
		SweepLineInterval *s0, SweepLineOverlapAction *action)
{
	/**
	 * Since we might need to test for self-intersections,
	 * include current insert event object in list of event objects to test.
	 * Last index can be skipped, because it must be a Delete event.
	 */
	for(int i=start; i<end; i++)
	{
		SweepLineEvent *ev=events[i];
		if (ev->isInsert()) {
			SweepLineInterval *s1=ev->getInterval();
			action->overlap(s0,s1);
			nOverlaps++;
		}
	}
}

} // namespace GEOMETRY.index.sweepline
} // namespace GEOMETRY.index
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.10  2006/06/12 11:29:23  strk
 * unsigned int => size_t
 *
 * Revision 1.9  2006/03/21 10:01:30  strk
 * indexSweepline.h header split
 *
 * Revision 1.8  2006/02/20 10:14:18  strk
 * - namespaces GEOMETRY::index::*
 * - Doxygen documentation cleanup
 *
 **********************************************************************/

