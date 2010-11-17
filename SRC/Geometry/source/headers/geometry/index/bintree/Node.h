/**********************************************************************
 * $Id: Node.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_IDX_BINTREE_NODE_H
#define GEOS_IDX_BINTREE_NODE_H

#include <Geometry/index/bintree/NodeBase.h> // for inheritance

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

/// A node of a Bintree.
class Node: public NodeBase {

public:

	static Node* createNode(Interval *itemInterval);

	static Node* createExpanded(Node *node,Interval *addInterval);

	Node(Interval *newInterval,int newLevel);

	~Node();

	Interval* getInterval();

	Node* getNode(Interval *searchInterval);

	NodeBase* find(Interval *searchInterval);

	void insert(Node *node);

private:

	Interval *interval;

	double centre;

	int level;

	Node* getSubnode(int index);

	Node* createSubnode(int index);

protected:

	bool isSearchMatch(Interval *itemInterval);
};

} // namespace GEOMETRY::index::bintree
} // namespace GEOMETRY::index
} // namespace GEOMETRY

#endif // GEOS_IDX_BINTREE_NODE_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/22 16:01:33  strk
 * indexBintree.h header split, classes renamed to match JTS
 *
 **********************************************************************/

