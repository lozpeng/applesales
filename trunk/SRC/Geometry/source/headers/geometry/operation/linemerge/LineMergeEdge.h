/**********************************************************************
 * $Id: LineMergeEdge.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_OP_LINEMERGE_LINEMERGEEDGE_H
#define GEOS_OP_LINEMERGE_LINEMERGEEDGE_H

#include <Geometry/planargraph/Edge.h> // for inheritance

// Forward declarations 
namespace GEOMETRY {
	namespace geom { 
		class LineString;
	}
}


namespace GEOMETRY {
namespace operation { // GEOMETRY::operation
namespace linemerge { // GEOMETRY::operation::linemerge

/** \brief
 * An edge of a LineMergeGraph. The <code>marked</code> field indicates
 * whether this Edge has been logically deleted from the graph.
 */
class LineMergeEdge: public planargraph::Edge {
private:
	const geom::LineString *line;
public:
	/**
	 * Constructs a LineMergeEdge with vertices given by the specified
	 * LineString.
	 */
	LineMergeEdge(const geom::LineString *newLine);

	/**
	 * Returns the LineString specifying the vertices of this edge.
	 */
	const geom::LineString* getLine() const;
};


} // namespace GEOMETRY::operation::linemerge
} // namespace GEOMETRY::operation
} // namespace GEOMETRY

#endif // GEOS_OP_LINEMERGE_LINEMERGEEDGE_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/22 10:13:53  strk
 * opLinemerge.h split
 *
 **********************************************************************/
