/**********************************************************************
 * $Id: BasicPreparedGeometry.h 2159 2008-08-18 16:27:02Z mloskot $
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

#ifndef GEOMETRY_GEOM_PREP_BASICPREPAREDGEOMETRY_H
#define GEOMETRY_GEOM_PREP_BASICPREPAREDGEOMETRY_H

#include <Geometry/geom/prep/PreparedGeometry.h> // for inheritance
//#include <Geometry/algorithm/PointLocator.h> 
//#include <Geometry/geom/util/ComponentCoordinateExtracter.h> 
#include <Geometry/geom/Coordinate.h> 
//#include <Geometry/geom/Location.h>

#include <vector>
#include <string>

namespace GEOMETRY {
	namespace geom {
		class Geometry;
		class Coordinate;
	}
}


namespace GEOMETRY {
namespace geom { // GEOMETRY::geom
namespace prep { // GEOMETRY::geom::prep

// * \class BasicPreparedGeometry

/**
 * 
 * \brief
 * A base class for {@link PreparedGeometry} subclasses.
 * 
 * Contains default implementations for methods, which simply delegate
 * to the equivalent {@link Geometry} methods.
 * This class may be used as a "no-op" class for Geometry types
 * which do not have a corresponding {@link PreparedGeometry} implementation.
 * 
 * @author Martin Davis
 *
 */
class BasicPreparedGeometry: public PreparedGeometry 
{
private:
	const geom::Geometry * baseGeom;
	Coordinate::ConstVect representativePts;

protected:
	/**
	 * Sets the original {@link Geometry} which will be prepared.
	 */
	void setGeometry( const geom::Geometry * geom );
	
	/**
	 * Determines whether a Geometry g interacts with 
	 * this geometry by testing the geometry envelopes.
	 *  
	 * @param g a Geometry
	 * @return true if the envelopes intersect
	 */
	bool envelopesIntersect(const geom::Geometry* g) const;

	/**
	 * Determines whether the envelope of 
	 * this geometry covers the Geometry g.
	 * 
	 *  
	 * @param g a Geometry
	 * @return true if g is contained in this envelope
	 */
	bool envelopeCovers(const geom::Geometry* g) const;

public:
	BasicPreparedGeometry( const Geometry * geom);

	~BasicPreparedGeometry( );

	const geom::Geometry & getGeometry() const
	{
		return *baseGeom;
	}

	/**
	 * Gets the list of representative points for this geometry.
	 * One vertex is included for every component of the geometry
	 * (i.e. including one for every ring of polygonal geometries) 
	 * 
	 * @return a List of Coordinate
	 */
	const Coordinate::ConstVect * getRepresentativePoints()  const
	{
		return &representativePts;
	}

	/**
	 * Tests whether any representative of the target geometry 
	 * intersects the test geometry.
	 * This is useful in A/A, A/L, A/P, L/P, and P/P cases.
	 * 
	 * @param geom the test geometry
	 * @param repPts the representative points of the target geometry
	 * @return true if any component intersects the areal test geometry
	 */
	bool isAnyTargetComponentInTest(const geom::Geometry * testGeom) const;

	/**
	 * Default implementation.
	 */
	bool contains(const geom::Geometry * g) const;

	/**
	 * Default implementation.
	 */
	bool containsProperly(const geom::Geometry * g)	const;

	/**
	 * Default implementation.
	 */
	bool coveredBy(const geom::Geometry * g) const;

	/**
	 * Default implementation.
	 */
	bool covers(const geom::Geometry * g) const;

	/**
	 * Default implementation.
	 */
	bool crosses(const geom::Geometry * g) const;

	bool disjoint(const geom::Geometry * g)	const;

	/**
	 * Default implementation.
	 */
	bool intersects(const geom::Geometry * g) const;

	/**
	 * Default implementation.
	 */
	bool overlaps(const geom::Geometry * g)	const;

	/**
	 * Default implementation.
	 */
	bool touches(const geom::Geometry * g) const;

	/**
	 * Default implementation.
	 */
	bool within(const geom::Geometry * g) const;

	std::string toString();

};

} // namespace GEOMETRY::geom::prep
} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#endif // GEOS_GEOM_PREP_BASICPREPAREDGEOMETRY_H
/**********************************************************************
 * $Log$
 **********************************************************************/

