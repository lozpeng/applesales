/**********************************************************************
 * $Id: GraphComponent.h 1820 2006-09-06 16:54:23Z mloskot $
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


#ifndef GEOMETRY_GEOMGRAPH_GRAPHCOMPONENT_H
#define GEOMETRY_GEOMGRAPH_GRAPHCOMPONENT_H

#include <Geometry/inline.h>

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class IntersectionMatrix;
	}
	namespace geomgraph {
		class Label;
	}
}

namespace GEOMETRY {
namespace geomgraph { // geos.geomgraph


class GraphComponent {
public:
	GraphComponent();

	/*
	 * GraphComponent takes ownership of the given Label.
	 * newLabel is deleted by destructor.
	 */
	GraphComponent(Label* newLabel); 
	virtual ~GraphComponent();
	Label* getLabel();
	virtual void setLabel(Label* newLabel);
	virtual void setInResult(bool isInResult) { isInResultVar=isInResult; }
	virtual bool isInResult() const { return isInResultVar; }
	virtual void setCovered(bool isCovered);
	virtual bool isCovered() const { return isCoveredVar; }
	virtual bool isCoveredSet() const { return isCoveredSetVar; }
	virtual bool isVisited() const { return isVisitedVar; }
	virtual void setVisited(bool isVisited) { isVisitedVar = isVisited; }
	virtual bool isIsolated() const=0;
	virtual void updateIM(geom::IntersectionMatrix *im);
protected:
	Label* label;
	virtual void computeIM(geom::IntersectionMatrix *im)=0;
private:
	bool isInResultVar;
	bool isCoveredVar;
	bool isCoveredSetVar;
	bool isVisitedVar;
};

} // namespace GEOMETRY.geomgraph
} // namespace GEOMETRY

//#ifdef GEOS_INLINE
//# include "Geometry/geomgraph/GraphComponent.inl"
//#endif

#endif // ifndef GEOS_GEOMGRAPH_GRAPHCOMPONENT_H

/**********************************************************************
 * $Log$
 * Revision 1.2  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/

