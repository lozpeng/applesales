/**********************************************************************
 * $Id: LinearRing.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_GEOS_LINEARRING_H
#define GEOS_GEOS_LINEARRING_H

#include <string>
#include <vector>
#include <Geometry/platform.h>
#include <Geometry/geom/LineString.h>

#include <Geometry/inline.h>

// Forward declarations
namespace GEOMETRY {
	namespace geom { // GEOMETRY::geom
		class Coordinate;
		class CoordinateArraySequence;
	}
}

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

/**
 *
 * \brief Basic implementation of <code>LinearRing</code>.
 *
 * The first and last point in the coordinate sequence must be equal.
 * Either orientation of the ring is allowed.
 * A valid ring must not self-intersect.
 *
 */
class LinearRing : public LineString {

public:

	LinearRing(const LinearRing &lr);

	/**
	 * \brief Constructs a <code>LinearRing</code> with the given points.
	 *
	 * @param  points  points forming a closed and simple linestring, or
	 *      <code>null</code> or an empty array to create the empty
	 *      geometry.
	 *      This array must not contain <code>null</code> elements.
	 *	If not null LinearRing will take ownership of points.
	 *
	 * @param newFactory the GeometryFactory used to create this geometry
	 *
	 */
	LinearRing(CoordinateSequence* points,
			const GeometryFactory *newFactory);

	/// Hopefully cleaner version of the above
	LinearRing(CoordinateSequence::AutoPtr points,
			const GeometryFactory *newFactory);

	virtual Geometry *clone() const { return new LinearRing(*this); }
	virtual ~LinearRing();
	bool isSimple() const;
	std::string getGeometryType() const;
	virtual GeometryTypeId getGeometryTypeId() const;
	bool isClosed() const;
	void setPoints(CoordinateSequence* cl);

	virtual void SetEmpty();

	//以下为IPointCollection接口
public:
	//virtual long PointCount() const;
 //   
	////在图形的最后添加一个节点
	//virtual void AddPoint(Coordinate &coord);

	////插入一个点
	//virtual void InsertPoint(int index,Coordinate &newpoint);

	//替换一个点
    virtual void ReplacePoint(int index,Coordinate &newpoint);

 //   virtual void RemovePoint(int index);

 //   virtual Coordinate GetPoint(int index); 
private:
	void validateConstruction();
};


} // namespace GEOMETRY::geom
} // namespace GEOMETRY

//#ifdef GEOS_INLINE
//# include "Geometry/geom/LinearRing.inl"
//#endif

#endif // ndef GEOS_GEOS_LINEARRING_H

/**********************************************************************
 * $Log$
 * Revision 1.4  2006/04/11 11:16:25  strk
 * Added LineString and LinearRing constructors by auto_ptr
 *
 * Revision 1.3  2006/04/10 17:35:44  strk
 * Changed LineString::points and Point::coordinates to be wrapped
 * in an auto_ptr<>. This should close bugs #86 and #89
 *
 * Revision 1.2  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/
