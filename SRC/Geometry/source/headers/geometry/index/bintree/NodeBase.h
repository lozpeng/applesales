/**********************************************************************
 * $Id: NodeBase.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_IDX_BINTREE_NODEBASE_H
#define GEOS_IDX_BINTREE_NODEBASE_H

#include <vector>

// Forward declarations
namespace GEOMETRY {
	namespace index { 
		namespace bintree { 
			class Node;
			class Interval;
		}
	}
}

namespace GEOMETRY {
namespace index { // GEOMETRY::index
namespace bintree { // GEOMETRY::index::bintree

/// The base class for nodes in a Bintree.
class NodeBase {

public:

	static int getSubnodeIndex(Interval *interval, double centre);

	NodeBase();

	virtual ~NodeBase();

	virtual std::vector<void*> *getItems();

	virtual void add(void* item);

	virtual std::vector<void*>* addAllItems(std::vector<void*> *newItems);

	virtual std::vector<void*>* addAllItemsFromOverlapping(Interval *interval,
			std::vector<void*> *resultItems);

	virtual int depth();

	virtual int size();

	virtual int nodeSize();

protected:	

	std::vector<void*>* items;

	/**
	 * subnodes are numbered as follows:
	 *
	 *  0 | 1
	 */
	Node* subnode[2];

	virtual bool isSearchMatch(Interval *interval)=0;
};

} // namespace GEOMETRY::index::bintree
} // namespace GEOMETRY::index
} // namespace GEOMETRY

#endif // GEOS_IDX_BINTREE_NODEBASE_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/22 16:01:33  strk
 * indexBintree.h header split, classes renamed to match JTS
 *
 **********************************************************************/

