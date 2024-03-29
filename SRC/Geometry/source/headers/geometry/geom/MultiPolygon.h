/**********************************************************************
 * $Id: MultiPolygon.h 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 * Copyright (C) 2005 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#ifndef GEOS_GEOS_MULTIPOLYGON_H
#define GEOS_GEOS_MULTIPOLYGON_H

#include <string>
#include <vector>
#include <Geometry/platform.h>
#include <Geometry/geom/GeometryCollection.h>
#include <Geometry/geom/Dimension.h> // for Dimension::DimensionType

#include <Geometry/inline.h>

// Forward declarations
namespace GEOMETRY {
	namespace geom { // GEOMETRY::geom
		class Coordinate;
		class CoordinateArraySequence;
		class MultiPoint;
	}
}


namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

/// Basic implementation of <code>MultiPolygon</code>.
class MultiPolygon: public GeometryCollection {

public:

	friend class GeometryFactory;

	virtual ~MultiPolygon();

	/// Returns surface dimension (2)
	Dimension::DimensionType getDimension() const;

	/// Returns 1 (MultiPolygon boundary is MultiLineString)
	int getBoundaryDimension() const;

	/**
	 * \brief
	 * Returns a MultiLineString composed of one LineString for
	 * each of the composing Polygon's shells and holes.
	 */
	Geometry* getBoundary() const;

	std::string getGeometryType() const;

	virtual GeometryTypeId getGeometryTypeId() const;

	bool isSimple() const;

	bool equalsExact(const Geometry *other, double tolerance=0) const;

	Geometry *clone() const;

	//是否包含弧段
	bool IsContainArc() const;

	//以下为IPointCollection接口
public:
	virtual long PointCount() const;

	//以下为ITransForm接口
public:
	virtual void Move(double dx,double dy);

	virtual void Mirror(const Coordinate &p1,const Coordinate &p2);

	virtual void Scale(const Coordinate &OriginPt,double dx,double dy);

	virtual void Rotate(const Coordinate &OriginPt,double angle);

protected:

	/**
	 * \brief Construct a MultiPolygon
	 *
	 * @param newPolys
	 *	the <code>Polygon</code>s for this <code>MultiPolygon</code>,
	 *	or <code>null</code> or an empty array to create the empty
	 *	geometry. Elements may be empty <code>Polygon</code>s, but
	 *	not <code>null</code>s.
	 *	The polygons must conform to the assertions specified in the
	 *	<A HREF="http://www.opengis.org/techno/specs.htm">
	 *	OpenGIS Simple Features Specification for SQL
	 *	</A>.
	 *
	 *	Constructed object will take ownership of
	 *	the vector and its elements.
	 *
	 * @param newFactory
	 * 	The GeometryFactory used to create this geometry
	 *	Caller must keep the factory alive for the life-time
	 *	of the constructed MultiPolygon.
	 */
	MultiPolygon(std::vector<Geometry *> *newPolys, const GeometryFactory *newFactory);

	MultiPolygon(const MultiPolygon &mp);


};


} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#ifdef GEOS_INLINE
# include "Geometry/geom/MultiPolygon.inl"
#endif

#endif // ndef GEOS_GEOS_MULTIPOLYGON_H

/**********************************************************************
 * $Log$
 * Revision 1.4  2006/05/04 15:49:39  strk
 * updated all Geometry::getDimension() methods to return Dimension::DimensionType (closes bug#93)
 *
 * Revision 1.3  2006/04/28 10:55:39  strk
 * Geometry constructors made protected, to ensure all constructions use GeometryFactory,
 * which has been made friend of all Geometry derivates. getNumPoints() changed to return
 * size_t.
 *
 * Revision 1.2  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/
