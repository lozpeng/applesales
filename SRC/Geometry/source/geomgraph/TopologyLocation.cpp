/**********************************************************************
 * $Id: TopologyLocation.cpp 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 * Copyright (C) 2005 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: geomgraph/TopologyLocation.java rev. 1.6 (JTS-1.7)
 *
 **********************************************************************/

#include <Geometry/geomgraph/TopologyLocation.h>
#include <Geometry/geomgraph/Position.h>
#include <Geometry/geom/Location.h>

#include <vector>
#include <sstream>
#include <iostream>
#include <cassert>

using namespace std;
using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace geomgraph { // geos.geomgraph

/*public*/
TopologyLocation::TopologyLocation(const vector<int> &newLocation):
	location(newLocation.size(), Location::UNDEF)
{
}

/*public*/
TopologyLocation::TopologyLocation()
{
}

/*public*/
TopologyLocation::~TopologyLocation()
{
}

/*public*/
TopologyLocation::TopologyLocation(int on, int left, int right):
	location(3)
{
	location[Position::ON]=on;
	location[Position::LEFT]=left;
	location[Position::RIGHT]=right;
}

/*public*/
TopologyLocation::TopologyLocation(int on):
	location(1, on)
{
	//(*location)[Position::ON]=on;
}

/*public*/
TopologyLocation::TopologyLocation(const TopologyLocation &gl):
	location(gl.location)
{
	//location=new vector<int>(gl->location->begin(),gl->location->end());
}

/*public*/
int
TopologyLocation::get(size_t posIndex) const
{
	// should be an assert() instead ?
	if (posIndex<location.size()) return location[posIndex];
	return Location::UNDEF;
}

/*public*/
bool
TopologyLocation::isNull() const
{
	for (size_t i=0, sz=location.size(); i<sz; ++i) {
		if (location[i]!=Location::UNDEF) return false;
	}
	return true;
}

/*public*/
bool
TopologyLocation::isAnyNull() const
{
	for (size_t i=0, sz=location.size(); i<sz; ++i) {
		if (location[i]==Location::UNDEF) return true;
	}
	return false;
}

/*public*/
bool
TopologyLocation::isEqualOnSide(const TopologyLocation &le, int locIndex) const
{
	return location[locIndex]==le.location[locIndex];
}

/*public*/
bool
TopologyLocation::isArea() const
{
	return location.size()>1;
}

/*public*/
bool
TopologyLocation::isLine() const
{
	return location.size()==1;
}

/*public*/
void
TopologyLocation::flip()
{
	if (location.size()<=1) return;
	int temp=location[Position::LEFT];
	location[Position::LEFT]=location[Position::RIGHT];
	location[Position::RIGHT] = temp;
}

/*public*/
void
TopologyLocation::setAllLocations(int locValue)
{
	for (size_t i=0, sz=location.size(); i<sz; ++i) {
		location[i]=locValue;
	}
}

/*public*/
void
TopologyLocation::setAllLocationsIfNull(int locValue)
{
	for (size_t i=0, sz=location.size(); i<sz; ++i) {
		if (location[i]==Location::UNDEF) location[i]=locValue;
	}
}

/*public*/
void
TopologyLocation::setLocation(size_t locIndex, int locValue)
{
	location[locIndex]=locValue;
}

/*public*/
void
TopologyLocation::setLocation(int locValue)
{
	setLocation(Position::ON, locValue);
}

/*public*/
const vector<int> &
TopologyLocation::getLocations() const
{
	return location;
}

/*public*/
void
TopologyLocation::setLocations(int on, int left, int right)
{
	assert(location.size() >= 3);
	location[Position::ON]=on;
	location[Position::LEFT]=left;
	location[Position::RIGHT]=right;
}

/*public*/
bool
TopologyLocation::allPositionsEqual(int loc) const
{
	for (size_t i=0, sz=location.size(); i<sz; ++i) {
		if (location[i]!=loc) return false;
	}
	return true;
}

/*public*/
void
TopologyLocation::merge(const TopologyLocation &gl)
{
	// if the src is an Area label & and the dest is not, increase the dest to be an Area
	size_t sz=location.size();
	size_t glsz=gl.location.size();
	if (glsz>sz) {
		location.resize(3);
		location[Position::LEFT]=Location::UNDEF;
		location[Position::RIGHT]=Location::UNDEF;
	}
	for (size_t i=0; i<sz; ++i) {
		if (location[i]==Location::UNDEF && i<glsz)
			location[i]=gl.location[i];
	}
}

string
TopologyLocation::toString() const
{
	stringstream ss;
	ss << *this;
	return ss.str();
}

std::ostream& operator<< (std::ostream& os, const TopologyLocation& tl)
{
	if (tl.location.size()>1) os << Location::toLocationSymbol(tl.location[Position::LEFT]);
	os << Location::toLocationSymbol(tl.location[Position::ON]);
	if (tl.location.size()>1) os << Location::toLocationSymbol(tl.location[Position::RIGHT]);
	return os;
}

} // namespace GEOMETRY.geomgraph
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.10  2006/06/12 11:29:23  strk
 * unsigned int => size_t
 *
 * Revision 1.9  2006/04/06 09:01:10  strk
 * Doxygen comments, port info, operator<<, assertion checking
 *
 * Revision 1.8  2006/03/15 17:16:29  strk
 * streamlined headers inclusion
 *
 * Revision 1.7  2006/03/03 10:46:21  strk
 * Removed 'using namespace' from headers, added missing headers in .cpp files, removed useless includes in headers (bug#46)
 *
 * Revision 1.6  2006/02/19 19:46:49  strk
 * Packages <-> namespaces mapping for most GEOS internal code (uncomplete, but working). Dir-level libs for index/ subdirs.
 *
 * Revision 1.5  2005/11/29 15:45:39  strk
 * Fixed signedness of TopologyLocation methods, cleanups.
 *
 * Revision 1.4  2005/11/15 18:30:59  strk
 * Removed dead code
 *
 * Revision 1.3  2005/11/14 18:14:04  strk
 * Reduced heap allocations made by TopologyLocation and Label objects.
 * Enforced const-correctness on GraphComponent.
 * Cleanups.
 *
 * Revision 1.2  2004/07/02 13:28:26  strk
 * Fixed all #include lines to reflect headers layout change.
 * Added client application build tips in README.
 *
 * Revision 1.1  2004/03/19 09:48:45  ybychkov
 * "geomgraph" and "geomgraph/indexl" upgraded to JTS 1.4
 *
 * Revision 1.8  2003/11/07 01:23:42  pramsey
 * Add standard CVS headers licence notices and copyrights to all cpp and h
 * files.
 *
 *
 **********************************************************************/

