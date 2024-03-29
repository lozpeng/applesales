/**********************************************************************
 * $Id: Bintree.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_IDX_BINTREE_BINTREE_H
#define GEOS_IDX_BINTREE_BINTREE_H

#include <vector>

// Forward declarations
namespace GEOMETRY {
	namespace index { 
		namespace bintree { 
			class Interval;
			class Root;
		}
	}
}

namespace GEOMETRY {
namespace index { // GEOMETRY::index
namespace bintree { // GEOMETRY::index::bintree

/** \brief
 * An BinTree (or "Binary Interval Tree")
 * is a 1-dimensional version of a quadtree.
 *
 * It indexes 1-dimensional intervals (which of course may
 * be the projection of 2-D objects on an axis).
 * It supports range searching
 * (where the range may be a single point).
 *
 * This implementation does not require specifying the extent of the inserted
 * items beforehand.  It will automatically expand to accomodate any extent
 * of dataset.
 * 
 * This index is different to the Interval Tree of Edelsbrunner
 * or the Segment Tree of Bentley.
 */
class Bintree {

public:

	static Interval* ensureExtent(Interval *itemInterval, double minExtent);

	Bintree();

	~Bintree();

	int depth();

	int size();

	int nodeSize();

	void insert(Interval *itemInterval,void* item);

	std::vector<void*>* iterator();

	std::vector<void*>* query(double x);

	std::vector<void*>* query(Interval *interval);

	void query(Interval *interval,
			std::vector<void*> *foundItems);

private:

	std::vector<Interval *>newIntervals;

	Root *root;

	/**
	 *  Statistics
	 *
	 * minExtent is the minimum extent of all items
	 * inserted into the tree so far. It is used as a heuristic value
	 * to construct non-zero extents for features with zero extent.
	 * Start with a non-zero extent, in case the first feature inserted has
	 * a zero extent in both directions.  This value may be non-optimal, but
	 * only one feature will be inserted with this value.
	 */
	double minExtent;

	void collectStats(Interval *interval);
};

} // namespace GEOMETRY::index::bintree
} // namespace GEOMETRY::index
} // namespace GEOMETRY

#endif // GEOS_IDX_BINTREE_BINTREE_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/22 16:01:33  strk
 * indexBintree.h header split, classes renamed to match JTS
 *
 **********************************************************************/

