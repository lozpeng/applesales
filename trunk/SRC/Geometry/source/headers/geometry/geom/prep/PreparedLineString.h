/**********************************************************************
 * $Id: PreparedLineString.h 2159 2008-08-18 16:27:02Z mloskot $
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
 *
 **********************************************************************/

#ifndef GEOMETRY_GEOM_PREP_PREPAREDLINESTRING_H
#define GEOMETRY_GEOM_PREP_PREPAREDLINESTRING_H

#include <Geometry/geom/prep/BasicPreparedGeometry.h> // for inheritance
#include <Geometry/noding/SegmentString.h> 

namespace GEOMETRY {
	namespace noding {
		class FastSegmentSetIntersectionFinder;
	}
}

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom
namespace prep { // GEOMETRY::geom::prep

/**
 * \brief
 * A prepared version of {@link LinearRing}, {@link LineString} or {@link MultiLineString} geometries.
 * 
 * @author mbdavis
 *
 */
class PreparedLineString : public BasicPreparedGeometry 
{
private:
	noding::FastSegmentSetIntersectionFinder * segIntFinder;
	mutable noding::SegmentString::ConstVect segStrings;

protected:
public:
	PreparedLineString(const Geometry * geom) 
		: 
		BasicPreparedGeometry( geom),
		segIntFinder( NULL)
	{ }

	noding::FastSegmentSetIntersectionFinder * getIntersectionFinder();

	bool intersects(const geom::Geometry * g) const;

};

} // namespace GEOMETRY::geom::prep
} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#endif // GEOS_GEOM_PREP_PREPAREDLINESTRING_H
/**********************************************************************
 * $Log$
 **********************************************************************/


