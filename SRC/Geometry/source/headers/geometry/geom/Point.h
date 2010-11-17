/**********************************************************************
 * $Id: Point.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_GEOS_POINT_H
#define GEOS_GEOS_POINT_H

#include <Geometry/platform.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/CoordinateSequence.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Envelope.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Dimension.h> // for Dimension::DimensionType

#include <Geometry/inline.h>

#include <string>
#include <vector>
#include <memory> // for auto_ptr

// Forward declarations
namespace GEOMETRY {
	namespace geom { // GEOMETRY::geom
		class Coordinate;
		class CoordinateArraySequence;
		class CoordinateFilter;
		class GeometryComponentFilter;
		class GeometryFilter;
	}
}

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

/**
 * \class Point geom.h geos.h
 * \brief Basic implementation of Point.
 */
class Point : public Geometry {

public:

	friend class GeometryFactory;

	/// A vector of const Point pointers
	typedef std::vector<const Point *> ConstVect;

	virtual ~Point();

	Geometry *clone() const { return new Point(*this); }

	CoordinateSequence* getCoordinates(void) const;

	const CoordinateSequence* getCoordinatesRO() const;

	size_t getNumPoints() const;
	bool isEmpty() const;
	bool isSimple() const;
	//bool isValid() const;

	/// Returns point dimension (0)
	Dimension::DimensionType getDimension() const;

	/// Returns Dimension::False (Point has no boundary)
	int getBoundaryDimension() const;

	/// Returns an EMPTY Geometry.
	Geometry* getBoundary() const;

	double getX() const;
	double getY() const;
	const Coordinate* getCoordinate() const;
	std::string getGeometryType() const;
	virtual GeometryTypeId getGeometryTypeId() const;
	void apply_ro(CoordinateFilter *filter) const;
	void apply_rw(const CoordinateFilter *filter);
	void apply_ro(GeometryFilter *filter) const;
	void apply_rw(GeometryFilter *filter);
	void apply_rw(GeometryComponentFilter *filter);
	void apply_ro(GeometryComponentFilter *filter) const;

	bool equalsExact(const Geometry *other, double tolerance=0) const;
	void normalize(void) { };

	virtual void SetEmpty();

	//以下为ISnap接口
public:
	virtual bool SnapVertex(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plvertexIndex);



	//以下为IPointCollection接口
public:
	virtual long PointCount() const;
    
	//在图形的最后添加一个节点
	virtual void AddPoint(Coordinate &coord);

	//插入一个点
	virtual void InsertPoint(int index,Coordinate &newpoint);

	//替换一个点
    virtual void ReplacePoint(int index,Coordinate &newpoint);

    virtual void RemovePoint(int index);

    virtual Coordinate GetPoint(int index); 
    
	//以下为ITransForm接口
public:
	void Move(double dx,double dy);

	void Mirror(const Coordinate &p1,const Coordinate &p2);

	void Scale(const Coordinate &OriginPt,double dx,double dy); 

	void Rotate(const Coordinate &OriginPt,double angle);  


protected:

	/**
	 * \brief
	 * Creates a Point taking ownership of the given CoordinateSequence
	 * (must have 1 element)
	 *
	 * @param  newCoords
	 *	contains the single coordinate on which to base this
	 *	<code>Point</code> or <code>null</code> to create
	 *	the empty geometry.
	 *
	 * @param newFactory the GeometryFactory used to create this geometry
	 */  
	Point(CoordinateSequence *newCoords, const GeometryFactory *newFactory);

	Point(const Point &p); 

	Envelope::AutoPtr computeEnvelopeInternal() const;

	int compareToSameClass(const Geometry *p) const;

private:

	/**
	 *  The <code>Coordinate</code> wrapped by this <code>Point</code>.
	 */
	std::auto_ptr<CoordinateSequence> coordinates;
};

} // namespace GEOMETRY::geom
} // namespace GEOMETRY

//#ifdef GEOS_INLINE
//# include "Geometry/geom/Point.inl"
//#endif

#endif // ndef GEOS_GEOS_POINT_H

/**********************************************************************
 * $Log$
 * Revision 1.6  2006/05/04 15:49:39  strk
 * updated all Geometry::getDimension() methods to return Dimension::DimensionType (closes bug#93)
 *
 * Revision 1.5  2006/04/28 10:55:39  strk
 * Geometry constructors made protected, to ensure all constructions use GeometryFactory,
 * which has been made friend of all Geometry derivates. getNumPoints() changed to return
 * size_t.
 *
 * Revision 1.4  2006/04/10 18:15:09  strk
 * Changed Geometry::envelope member to be of type auto_ptr<Envelope>.
 * Changed computeEnvelopeInternal() signater to return auto_ptr<Envelope>
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
