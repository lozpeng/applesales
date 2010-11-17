/**********************************************************************
 * $Id: MonotoneChainIndexer.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOMETRY_GEOMGRAPH_INDEX_MONOTONECHAININDEXER_H
#define GEOMETRY_GEOMGRAPH_INDEX_MONOTONECHAININDEXER_H

#include <vector>

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class CoordinateSequence;
	}
}

namespace GEOMETRY {
namespace geomgraph { // GEOMETRY::geomgraph
namespace index { // GEOMETRY::geomgraph::index


class MonotoneChainIndexer{

public:

	MonotoneChainIndexer(){};

	void getChainStartIndices(const geom::CoordinateSequence*, std::vector<int>&);

private:

	int findChainEnd(const geom::CoordinateSequence* pts, int start);

};

} // namespace GEOMETRY.geomgraph.index
} // namespace GEOMETRY.geomgraph
} // namespace GEOMETRY

#endif // GEOS_GEOMGRAPH_INDEX_MONOTONECHAININDEXER_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/14 12:55:55  strk
 * Headers split: geomgraphindex.h, nodingSnapround.h
 *
 **********************************************************************/

