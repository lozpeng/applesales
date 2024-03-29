/**********************************************************************
 * $Id: SortedPackedIntervalRTree.cpp 2161 2008-08-18 16:29:09Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#include <Geometry/index/intervalrtree/SortedPackedIntervalRTree.h>
#include <Geometry/index/intervalrtree/IntervalRTreeNode.h>
#include <Geometry/index/intervalrtree/IntervalRTreeLeafNode.h>
#include <Geometry/index/intervalrtree/IntervalRTreeBranchNode.h>
#include <Geometry/index/ItemVisitor.h>
#include <Geometry/util/UnsupportedOperationException.h>

#include <algorithm>

namespace GEOMETRY {
namespace index {
namespace intervalrtree {
//
// private:
//
void 
SortedPackedIntervalRTree::init()
{
	if (root != NULL) return;

	root = buildTree();
}

const IntervalRTreeNode * 
SortedPackedIntervalRTree::buildTree()
{
	// sort the leaf nodes
	std::sort( leaves->begin(), leaves->end(), IntervalRTreeNode::compare );

	// now group nodes into blocks of two and build tree up recursively
	IntervalRTreeNode::ConstVect * src = leaves;
	IntervalRTreeNode::ConstVect * dest = new IntervalRTreeNode::ConstVect();

	while (true) 
	{
		buildLevel( src, dest);
	
		if (dest->size() == 1)
		{
			const IntervalRTreeNode * r = (*dest)[ 0 ];
			delete src;
			delete dest;
			//delete leaves; // don't need anymore
			return r;
		}

		IntervalRTreeNode::ConstVect * temp = src;
		src = dest;
		dest = temp;
	}
}

void 
SortedPackedIntervalRTree::buildLevel( IntervalRTreeNode::ConstVect * src, IntervalRTreeNode::ConstVect * dest) 
{
	level++;

	dest->clear();
	
	for (size_t i = 0, ni = src->size(); i < ni; i += 2) 
	{
		const IntervalRTreeNode * n1 = (*src)[ i ];

		if ( i + 1 < ni )
		{
			const IntervalRTreeNode * n2 = (*src)[ i + 1 ];

			const IntervalRTreeNode * node = new IntervalRTreeBranchNode( n1, n2 );

			dest->push_back( node);
		}
		else
		{
			dest->push_back( n1);
		}
	}
}

//
// protected:
//

//
// public:
//
SortedPackedIntervalRTree::SortedPackedIntervalRTree()
:	root( NULL),
	leaves( new IntervalRTreeNode::ConstVect()),
	level( 0)
{ }

SortedPackedIntervalRTree::~SortedPackedIntervalRTree()
{
	if ( root != NULL )
	{
		// deleting root cascades to all IntervalRTreeNode's
		delete root;
	}
	else // possibly IntervalRTreeNode's in leaves to delete
	{
		for ( size_t i = 0, ni = leaves->size(); i < ni; i++ )
			delete (*leaves)[i];

		delete leaves;
	}
}


void 
SortedPackedIntervalRTree::insert( double min, double max, void * item)
{
	if (root != NULL)
		throw new util::UnsupportedOperationException( "Index cannot be added to once it has been queried");

	leaves->push_back( new IntervalRTreeLeafNode( min, max, item));
}

void 
SortedPackedIntervalRTree::query( double min, double max, index::ItemVisitor * visitor)
{
	init();

	root->query( min, max, visitor);
}

} // geos::intervalrtree
} // GEOMETRY::index
} // geos

/**********************************************************************
 * $Log$
 *
 **********************************************************************/
