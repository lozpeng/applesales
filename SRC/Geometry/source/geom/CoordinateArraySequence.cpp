/**********************************************************************
 * $Id: CoordinateArraySequence.cpp 2091 2007-12-21 22:49:03Z mloskot $
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
 **********************************************************************/

#include <Geometry/geom/Envelope.h>
#include <Geometry/geom/CoordinateArraySequence.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/CoordinateFilter.h>

#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

CoordinateArraySequence::CoordinateArraySequence():
	vect(new vector<Coordinate>())
{
}

CoordinateArraySequence::CoordinateArraySequence(size_t n):
	vect(new vector<Coordinate>(n))
{
}

CoordinateArraySequence::CoordinateArraySequence(
	vector<Coordinate> *coords): vect(coords)
{
	if ( ! vect ) vect = new vector<Coordinate>();
}

CoordinateArraySequence::CoordinateArraySequence(
	const CoordinateArraySequence &c)
	:
	CoordinateSequence(c),
	vect(new vector<Coordinate>(*(c.vect)))
{
}

CoordinateSequence *
CoordinateArraySequence::clone() const
{
	return new CoordinateArraySequence(*this);
}

void
CoordinateArraySequence::setPoints(const vector<Coordinate> &v)
{
	vect->assign(v.begin(), v.end());
}

const vector<Coordinate>*
CoordinateArraySequence::toVector() const
{
	return vect; //new vector<Coordinate>(vect->begin(),vect->end());
}

bool
CoordinateArraySequence::isEmpty() const
{
	return vect->empty();
}

void
CoordinateArraySequence::add(const Coordinate& c)
{
	vect->push_back(c);
}

void
CoordinateArraySequence::add(const Coordinate& c, bool allowRepeated)
{
	if (!allowRepeated && ! vect->empty() )
	{
		const Coordinate& last=vect->back();
		if (last.equals2D(c)) return;
	}
	vect->push_back(c);
}

size_t
CoordinateArraySequence::getSize() const
{
	return vect->size();
}

 Coordinate &
CoordinateArraySequence::getAt(size_t pos) const
{
	assert(pos<vect->size());
	return (*vect)[pos];
}

void
CoordinateArraySequence::getAt(size_t pos, Coordinate &c) const
{
	assert(pos<vect->size());
	c=(*vect)[pos];
}

void
CoordinateArraySequence::setAt(const Coordinate& c, size_t pos)
{
	assert(pos<vect->size());
	(*vect)[pos]=c;
}

void
CoordinateArraySequence::deleteAt(size_t pos)
{
	assert(pos<vect->size());
	vect->erase(vect->begin()+pos);
}

string
CoordinateArraySequence::toString() const
{
	string result("(");
	if (getSize()>0) {
		//char buffer[100];
		for (size_t i=0, n=vect->size(); i<n; i++)
		{
			Coordinate& c=(*vect)[i];
			if ( i ) result.append(", ");
			result.append(c.toString());
		}
	}
	result.append(")");

	return result;
}

CoordinateArraySequence::~CoordinateArraySequence()
{
	delete vect;
}

void
CoordinateArraySequence::expandEnvelope(Envelope &env) const
{
	size_t size = vect->size();
	for (size_t i=0; i<size; i++) env.expandToInclude((*vect)[i]);
}

double
CoordinateArraySequence::getOrdinate(size_t index, size_t ordinateIndex) const
{

	assert(index<vect->size());

	switch (ordinateIndex)
	{
		case CoordinateSequence::X:
			return (*vect)[index].x;
		case CoordinateSequence::Y:
			return (*vect)[index].y;
		case CoordinateSequence::Z:
			return (*vect)[index].z;
		default:
			return DoubleNotANumber;
	}
}

void
CoordinateArraySequence::setOrdinate(size_t index, size_t ordinateIndex,
	double value)
{

	assert(index<vect->size());

    assert(ordinateIndex == CoordinateSequence::X
           || ordinateIndex == CoordinateSequence::Y
           || ordinateIndex == CoordinateSequence::Z);

	switch (ordinateIndex)
	{
		case CoordinateSequence::X:
			(*vect)[index].x = value;
			break;
		case CoordinateSequence::Y:
			(*vect)[index].y = value;
			break;
		case CoordinateSequence::Z:
			(*vect)[index].z = value;
			break;
		default:
			break;
	}
}

void
CoordinateArraySequence::apply_rw(const CoordinateFilter *filter)
{
	for (vector<Coordinate>::iterator i=vect->begin(), e=vect->end(); i!=e; ++i)
	{
		filter->filter_rw(&(*i));
	}
}

void
CoordinateArraySequence::apply_ro(CoordinateFilter *filter) const
{
	for (vector<Coordinate>::const_iterator i=vect->begin(), e=vect->end(); i!=e; ++i)
	{
		filter->filter_ro(&(*i));
	}
}

CoordinateSequence&
CoordinateArraySequence::removeRepeatedPoints()
{
	// We use == operator, which is 2D only
	vector<Coordinate>::iterator new_end = \
		std::unique(vect->begin(), vect->end());
	
	vect->erase(new_end, vect->end());

	return *this;
}

void CoordinateArraySequence::insert(size_t pos, const GEOMETRY::geom::Coordinate &c)
{
	if(pos>=vect->size())
	{
		return;
	}
	vect->insert(vect->begin()+pos+1,c);
}

void CoordinateArraySequence::ClearAll()
{
	if(!vect->empty())
	{
		vect->clear();
	}
}
//得到一个点的指针
Coordinate* CoordinateArraySequence::GetPtPointer(size_t i)
{
   if(i>=vect->size())
   {
	   return NULL;
   }

   return &((*vect)[i]);
}

} // namespace GEOMETRY::geom
} //namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.10  2006/06/12 15:07:47  strk
 * explicitly invoked CoordinateSequence (copy) ctor - suggested by GCC warning.
 *
 * Revision 1.9  2006/06/12 10:10:39  strk
 * Fixed getGeometryN() to take size_t rather then int, changed unsigned int parameters to size_t.
 *
 * Revision 1.8  2006/05/03 08:58:34  strk
 * added new non-static CoordinateSequence::removeRepeatedPoints() mutator.
 *
 * Revision 1.7  2006/03/27 09:00:50  strk
 * Bug #79 - Small fix in CoordinateArraySequence::toString()
 *
 * Revision 1.6  2006/03/22 16:58:34  strk
 * Removed (almost) all inclusions of geom.h.
 * Removed obsoleted .cpp files.
 * Fixed a bug in WKTReader not using the provided CoordinateSequence
 * implementation, optimized out some memory allocations.
 *
 **********************************************************************/

