/**********************************************************************
 * $Id: SweepLineEvent.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOMETRY_GEOMGRAPH_INDEX_SWEEPLINEEVENT_H
#define GEOMETRY_GEOMGRAPH_INDEX_SWEEPLINEEVENT_H

#include <string>

// Forward declarations
namespace GEOMETRY {
	namespace geomgraph {
		namespace index {
			class SweepLineEventOBJ;
		}
	}
}

namespace GEOMETRY {
namespace geomgraph { // GEOMETRY::geomgraph
namespace index { // GEOMETRY::geomgraph::index

//class SweepLineEventLessThen; // needed ??

class SweepLineEvent{
friend class SweepLineEventLessThen;

public:

	enum {
		INSERT_EVENT = 1,
		DELETE_EVENT
	};

	SweepLineEvent(void* newEdgeSet, double x,
			SweepLineEvent *newInsertEvent,
			SweepLineEventOBJ *newObj);

	virtual ~SweepLineEvent();

	bool isInsert() { return insertEvent==NULL; }

	bool isDelete() { return insertEvent!=NULL; }

	SweepLineEvent* getInsertEvent() { return insertEvent; }

	int getDeleteEventIndex() { return deleteEventIndex; }

	void setDeleteEventIndex(int newDeleteEventIndex) {
		deleteEventIndex=newDeleteEventIndex;
	}

	SweepLineEventOBJ* getObject() const { return obj; }

	int compareTo(SweepLineEvent *sle);

	std::string print();

	void* edgeSet;    // used for red-blue intersection detection

protected:

	SweepLineEventOBJ* obj;

private:

	double xValue;

	int eventType;

	SweepLineEvent *insertEvent; // null if this is an INSERT_EVENT event

	int deleteEventIndex;
};

class SweepLineEventLessThen {
public:
	bool operator()(const SweepLineEvent *f, const SweepLineEvent *s) const
	{
		if (f->xValue<s->xValue) return true;
		if (f->xValue>s->xValue) return false;
		if (f->eventType<s->eventType) return true;
		return false;
	}
};



} // namespace GEOMETRY.geomgraph.index
} // namespace GEOMETRY.geomgraph
} // namespace GEOMETRY

#endif

/**********************************************************************
 * $Log$
 * Revision 1.2  2006/03/15 17:17:42  strk
 * Added missing forward declarations
 *
 * Revision 1.1  2006/03/14 12:55:56  strk
 * Headers split: geomgraphindex.h, nodingSnapround.h
 *
 **********************************************************************/

