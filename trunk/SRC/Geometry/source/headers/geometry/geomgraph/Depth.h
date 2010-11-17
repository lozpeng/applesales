/**********************************************************************
 * $Id: Depth.h 1820 2006-09-06 16:54:23Z mloskot $
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


#ifndef GEOMETRY_GEOMGRAPH_DEPTH_H
#define GEOMETRY_GEOMGRAPH_DEPTH_H

#include <string>

#include <Geometry/inline.h>

// Forward declarations
namespace GEOMETRY {
	namespace geomgraph {
		class Label;
	}
}

namespace GEOMETRY {
namespace geomgraph { // geos.geomgraph

class Depth {
public:
	static int depthAtLocation(int location);
	Depth();
	virtual ~Depth(); // FIXME: shoudn't be virtual!
	int getDepth(int geomIndex,int posIndex) const;
	void setDepth(int geomIndex,int posIndex,int depthValue);
	int getLocation(int geomIndex,int posIndex) const;
	void add(int geomIndex,int posIndex,int location);
	bool isNull() const;
	bool isNull(int geomIndex) const;
	bool isNull(int geomIndex, int posIndex) const;
	int getDelta(int geomIndex) const;
	void normalize();
	void add(const Label& lbl);
	std::string toString() const;
private:
	enum {
		DEPTHNULL=-1 //Replaces NULL
	};
//	static const int DEPTHNULL=-1; //Replaces NULL
	int depth[2][3];
};

} // namespace GEOMETRY.geomgraph
} // namespace GEOMETRY

//#ifdef GEOS_INLINE
//# include "Geometry/geomgraph/Depth.inl"
//#endif

#endif // ifndef GEOS_GEOMGRAPH_DEPTH_H

/**********************************************************************
 * $Log$
 * Revision 1.2  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/

