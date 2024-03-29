/**********************************************************************
 * $Id: NodeBase.cpp 2522 2009-05-27 18:28:23Z pramsey $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2006 Refractions Research Inc.
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#include <Geometry/index/quadtree/NodeBase.h> 
#include <Geometry/index/quadtree/Node.h> 
#include <Geometry/index/ItemVisitor.h> 
#include <Geometry/geom/Envelope.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/util.h>

#include <sstream>
#include <vector>
#include <algorithm>

#ifndef GEOS_DEBUG
#define GEOS_DEBUG 0
#endif

#if GEOS_DEBUG
#include <iostream>
#endif

using namespace std;
using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace index { // geos.index
namespace quadtree { // geos.index.quadtree

int
NodeBase::getSubnodeIndex(const Envelope *env, const Coordinate& centre)
{
	int subnodeIndex=-1;
	if (env->getMinX()>=centre.x) {
		if (env->getMinY()>=centre.y) subnodeIndex=3;
		if (env->getMaxY()<=centre.y) subnodeIndex=1;
	}
	if (env->getMaxX()<=centre.x) {
		if (env->getMinY()>=centre.y) subnodeIndex=2;
		if (env->getMaxY()<=centre.y) subnodeIndex=0;
	}
#if GEOS_DEBUG
	cerr<<"getSubNodeIndex("<<env->toString()<<", "<<centre.toString()<<") returning "<<subnodeIndex<<endl;
#endif
	return subnodeIndex;
}

NodeBase::NodeBase() {
	items=new vector<void*>();
	subnode[0]=NULL;
	subnode[1]=NULL;
	subnode[2]=NULL;
	subnode[3]=NULL;
}

NodeBase::~NodeBase() {
	delete subnode[0];
	delete subnode[1];
	delete subnode[2];
	delete subnode[3];
	subnode[0]=NULL;
	subnode[1]=NULL;
	subnode[2]=NULL;
	subnode[3]=NULL;
	delete items;
}

vector<void*>* NodeBase::getItems() {
	return items;
}

void NodeBase::add(void* item) {
	items->push_back(item);
	//GEOS_DEBUG itemCount++;
	//GEOS_DEBUG System.out.print(itemCount);
}

vector<void*>*
NodeBase::addAllItems(vector<void*> *resultItems)
{
	//<<TODO:ASSERT?>> Can we assert that this node cannot have both items
	//and subnodes? [Jon Aquino]
	resultItems->insert(resultItems->end(),items->begin(),items->end());
	for(int i=0;i<4;i++) {
		if (subnode[i]!=NULL) {
			subnode[i]->addAllItems(resultItems);
		}
	}
	return resultItems;
}

void
NodeBase::addAllItemsFromOverlapping(const Envelope *searchEnv, vector<void*> *resultItems)
{
	if (!isSearchMatch(searchEnv))
		return;

	//<<TODO:ASSERT?>> Can we assert that this node cannot have both items
	//and subnodes? [Jon Aquino]
	resultItems->insert(resultItems->end(),items->begin(),items->end());
	for(int i=0;i<4;i++) {
		if (subnode[i]!=NULL) {
			subnode[i]->addAllItemsFromOverlapping(searchEnv,resultItems);
		}
	}
}

//<<TODO:RENAME?>> In Samet's terminology, I think what we're returning here is
//actually level+1 rather than depth. (See p. 4 of his book) [Jon Aquino]
int NodeBase::depth() {
	int maxSubDepth=0;
	for(int i=0;i<4;i++) {
		if (subnode[i]!=NULL) {
			int sqd=subnode[i]->depth();
			if (sqd>maxSubDepth)
				maxSubDepth=sqd;
		}
	}
	return maxSubDepth+1;
}

//<<TODO:RENAME?>> "size" is a bit generic. How about "itemCount"? [Jon Aquino]
int NodeBase::size() {
	int subSize=0;
	for(int i=0;i<4;i++) {
		if (subnode[i]!=NULL) {
			subSize+=subnode[i]->size();
		}
	}
	return subSize+(int)items->size();
}

//<<TODO:RENAME?>> The Java Language Specification recommends that "Methods to
//get and set an attribute that might be thought of as a variable V should be
//named getV and setV" (6.8.3). Perhaps this and other methods should be
//renamed to "get..."? [Jon Aquino]
int NodeBase::nodeCount() {
	int subSize=0;
	for(int i=0;i<4;i++) {
		if (subnode[i]!=NULL) {
			subSize+=subnode[i]->size();
		}
	}
	return subSize+1;
}

string
NodeBase::toString() const
{
	ostringstream s;
	s<<"ITEMS:"<<items->size()<<endl;
	for (int i=0; i<4; i++)
	{
		s<<"subnode["<<i<<"] ";
		if ( subnode[i] == NULL ) s<<"NULL";
		else s<<subnode[i]->toString();
		s<<endl;
	}
	return s.str();
}

/*public*/
void
NodeBase::visit(const Envelope* searchEnv, ItemVisitor& visitor)
{
	if (! isSearchMatch(searchEnv)) return;

	// this node may have items as well as subnodes (since items may not
	// be wholely contained in any single subnode
	visitItems(searchEnv, visitor);

	for (int i = 0; i < 4; i++) {
		if (subnode[i] != NULL) {
			subnode[i]->visit(searchEnv, visitor);
		}
	}
}

/*private*/
void
NodeBase::visitItems(const Envelope* searchEnv, ItemVisitor& visitor)
{
    UNREFERENCED_PARAMETER(searchEnv);

	// would be nice to filter items based on search envelope, but can't
	// until they contain an envelope
	for (vector<void*>::iterator i=items->begin(), e=items->end();
			i!=e; i++)
	{
		visitor.visitItem(*i);
	}
}

/*public*/
bool
NodeBase::remove(const Envelope* itemEnv, void* item)
{
	// use envelope to restrict nodes scanned
	if (! isSearchMatch(itemEnv)) return false;

	bool found = false;
	for (int i = 0; i < 4; i++) {
		if (subnode[i] != NULL) {
			found = subnode[i]->remove(itemEnv, item);
			if (found) {
				// trim subtree if empty
				if (subnode[i]->isPrunable()) 
				{
					delete subnode[i];
					subnode[i] = NULL;
				}
				break;
			}
		}
	}
	// if item was found lower down, don't need to search for it here
	if (found) return found;

	// otherwise, try and remove the item from the list of items
	// in this node
	vector<void*>::iterator foundIter = 
		find(items->begin(), items->end(), item);
	if ( foundIter != items->end() ) {
		items->erase(foundIter);
		return true;
	} else {
		return false;
	}
}


} // namespace GEOMETRY.index.quadtree
} // namespace GEOMETRY.index
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.2  2006/03/23 13:31:58  strk
 * Fixed to allow build with GEOS_DEBUG
 *
 * Revision 1.1  2006/03/22 14:28:53  strk
 * Filenames renamed to match class names (matching JTS)
 *
 * Revision 1.19  2006/03/22 12:22:50  strk
 * indexQuadtree.h split
 *
 **********************************************************************/

