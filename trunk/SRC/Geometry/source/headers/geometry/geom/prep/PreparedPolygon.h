/**********************************************************************
 * $Id: PreparedPolygon.h 2159 2008-08-18 16:27:02Z mloskot $
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

#ifndef GEOMETRY_GEOM_PREP_PREPAREDPOLYGON_H
#define GEOMETRY_GEOM_PREP_PREPAREDPOLYGON_H

#include <Geometry/geom/prep/BasicPreparedGeometry.h> // for inheritance
#include <Geometry/noding/SegmentString.h> 

namespace GEOMETRY {
	namespace noding {
		class FastSegmentSetIntersectionFinder;
	}
	namespace algorithm {
		namespace locate {
			class PointOnGeometryLocator;
		}
	}
}

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom
namespace prep { // GEOMETRY::geom::prep

/**
 * \brief
 * A prepared version of {@link Polygon} or {@link MultiPolygon} geometries.
 * 
 * @author mbdavis
 *
 */
class PreparedPolygon : public BasicPreparedGeometry 
{
private:
	bool isRectangle;
	mutable noding::FastSegmentSetIntersectionFinder * segIntFinder;
	mutable algorithm::locate::PointOnGeometryLocator * ptOnGeomLoc;
	mutable noding::SegmentString::ConstVect segStrings;

protected:
public:
	PreparedPolygon( const geom::Geometry * geom);
	~PreparedPolygon( );
  
	noding::FastSegmentSetIntersectionFinder * getIntersectionFinder() const;
	algorithm::locate::PointOnGeometryLocator * getPointLocator() const;
	
	bool contains( const geom::Geometry* g) const;
	bool containsProperly( const geom::Geometry* g) const;
	bool covers( const geom::Geometry* g) const;
	bool intersects( const geom::Geometry* g) const;

};

} // namespace GEOMETRY::geom::prep
} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#endif // GEOS_GEOM_PREP_PREPAREDPOLYGON_H
/**********************************************************************
 * $Log$
 **********************************************************************/

