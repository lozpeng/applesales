/**********************************************************************
 * $Id: Key.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_IDX_BINTREE_KEY_H
#define GEOS_IDX_BINTREE_KEY_H

// Forward declarations
namespace GEOMETRY {
	namespace index { 
		namespace bintree { 
			class Interval;
		}
	}
}

namespace GEOMETRY {
namespace index { // GEOMETRY::index
namespace bintree { // GEOMETRY::index::bintree

/** \brief
 * A Key is a unique identifier for a node in a tree.
 *
 * It contains a lower-left point and a level number.
 * The level number is the power of two for the size of the node envelope
 */
class Key {

public:

	static int computeLevel(Interval *newInterval);

	Key(Interval *newInterval);

	~Key();

	double getPoint();

	int getLevel();

	Interval* getInterval();

	void computeKey(Interval *itemInterval);

private:

	// the fields which make up the key
	double pt;
	int level;

	// auxiliary data which is derived from the key for use in computation
	Interval *interval;

	void computeInterval(int level, Interval *itemInterval);
};

} // namespace GEOMETRY::index::bintree
} // namespace GEOMETRY::index
} // namespace GEOMETRY

#endif // GEOS_IDX_BINTREE_KEY_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/22 16:01:33  strk
 * indexBintree.h header split, classes renamed to match JTS
 *
 **********************************************************************/

