/**********************************************************************
 * $Id: Boundable.h 1971 2007-02-07 00:34:26Z strk $
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

#ifndef GEOS_INDEX_STRTREE_BOUNDABLE_H
#define GEOS_INDEX_STRTREE_BOUNDABLE_H

namespace GEOMETRY {
namespace index { // GEOMETRY::index
namespace strtree { // GEOMETRY::index::strtree

/// A spatial object in an AbstractSTRtree.
class Boundable {
public:
	/**
	 * Returns a representation of space that encloses this Boundable,
	 * preferably not much bigger than this Boundable's boundary yet
	 * fast to test for intersection with the bounds of other Boundables.
	 *
	 * The class of object returned depends
	 * on the subclass of AbstractSTRtree.
	 *
	 * @return an Envelope (for STRtrees), an Interval (for SIRtrees),
	 * or other object (for other subclasses of AbstractSTRtree)
	 *
	 * @see AbstractSTRtree::IntersectsOp
	 */
	virtual const void* getBounds() const=0;
	virtual ~Boundable() {};
};


} // namespace GEOMETRY::index::strtree
} // namespace GEOMETRY::index
} // namespace GEOMETRY

#endif // GEOS_INDEX_STRTREE_BOUNDABLE_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/21 10:47:34  strk
 * indexStrtree.h split
 *
 **********************************************************************/

