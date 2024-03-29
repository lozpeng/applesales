/**********************************************************************
 * $Id: LinearComponentExtracter.h 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#ifndef GEOMETRY_GEOM_UTIL_LINEARCOMPONENTEXTRACTER_H
#define GEOMETRY_GEOM_UTIL_LINEARCOMPONENTEXTRACTER_H

#include <vector>

#include <Geometry/geom/GeometryComponentFilter.h>
#include <Geometry/geom/Geometry.h> // to be removed when we have the .inl
#include <Geometry/geom/LineString.h> // to be removed when we have the .inl
//#include <Geometry/platform.h>

namespace GEOMETRY {
namespace geom { // geos.geom
namespace util { // geos.geom.util

/**
 * Extracts all the 1-dimensional (LineString) components from a Geometry.
 */
class LinearComponentExtracter: public GeometryComponentFilter {

private:

	LineString::ConstVect &comps;

public:
	/**
	 * Push the linear components from a single geometry into
	 * the provided vector.
	 * If more than one geometry is to be processed, it is more
	 * efficient to create a single LinearComponentExtracterFilter instance
	 * and pass it to multiple geometries.
	 */
	static void getLines(const Geometry &geom, std::vector<const LineString*> &ret)
	{
		LinearComponentExtracter lce(ret);
		geom.apply_ro(&lce);
	}

	/**
	 * Constructs a LinearComponentExtracterFilter with a list in which
	 * to store LineStrings found.
	 */
	LinearComponentExtracter(std::vector<const LineString*> &newComps)
		:
		comps(newComps)
		{}

	void filter_rw(Geometry *geom)
	{
if ( const LineString *ls=dynamic_cast<const LineString *>(geom) )
		comps.push_back(ls);
	}

	void filter_ro(const Geometry *geom)
	{
if ( const LineString *ls=dynamic_cast<const LineString *>(geom) )
		comps.push_back(ls);
	}

};

} // namespace GEOMETRY.geom.util
} // namespace GEOMETRY.geom
} // namespace GEOMETRY

#endif

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/
