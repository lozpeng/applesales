/**********************************************************************
 * $Id: LineString.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_GEOS_LINESTRING_H
#define GEOS_GEOS_LINESTRING_H

#include <Geometry/platform.h> // do we need this ?
#include <Geometry/geom/Geometry.h> // for inheritance
#include <Geometry/geom/CoordinateSequence.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Envelope.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Dimension.h> // for Dimension::DimensionType
#include <Geometry/geom/SegmentCollection.h>
#include <Geometry/geom/Line.h>
#include <string>
#include <vector>
#include <memory> // for auto_ptr

#include <Geometry/inline.h>

namespace GEOMETRY {
	namespace geom {
		class Coordinate;
		class CoordinateArraySequence;
	}
}

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

/**
 * \class LineString geom.h geos.h
 * \brief Basic implementation of LineString.
 */
class LineString: public Geometry,
	              public ISegmentCollection
{

public:

	friend class GeometryFactory;

	/// A vector of const LineString pointers
	typedef std::vector<const LineString *> ConstVect;

	virtual ~LineString();

	virtual Geometry *clone() const;

	virtual CoordinateSequence* getCoordinates() const;

	/// Returns a read-only pointer to internal CoordinateSequence
	const CoordinateSequence* getCoordinatesRO() const;

	virtual const Coordinate& getCoordinateN(int n) const;

	/// Returns line dimension (1)
	virtual Dimension::DimensionType getDimension() const;

	/**
	 * \brief
	 * Returns Dimension::False for a closed LineString,
	 * 0 otherwise (LineString boundary is a MultiPoint)
	 */
	virtual int getBoundaryDimension() const;

	/**
	 * \brief
	 * Returns a MultiPoint.
	 * Empty for closed LineString, a Point for each vertex otherwise.
	 */
	virtual Geometry* getBoundary() const;

	virtual bool isEmpty() const;

	virtual size_t getNumPoints() const;

	virtual Point* getPointN(size_t n) const;

	/// \brief
	/// Return the start point of the LineString
	/// or NULL if this is an EMPTY LineString.
	///
	virtual Point* getStartPoint() const;

	/// \brief
	/// Return the end point of the LineString
	/// or NULL if this is an EMPTY LineString.
	///
	virtual Point* getEndPoint() const;

	virtual bool isClosed() const;

	virtual bool isRing() const;

	virtual std::string getGeometryType() const;

	virtual GeometryTypeId getGeometryTypeId() const;

	virtual bool isSimple() const;

	virtual bool isCoordinate(Coordinate& pt) const;

	virtual bool equalsExact(const Geometry *other, double tolerance=0)
		const;

	virtual void apply_rw(const CoordinateFilter *filter);

	virtual void apply_ro(CoordinateFilter *filter) const;

	virtual void apply_rw(GeometryFilter *filter);

	virtual void apply_ro(GeometryFilter *filter) const;

	virtual void apply_rw(GeometryComponentFilter *filter);

	virtual void apply_ro(GeometryComponentFilter *filter) const;

	/** \brief
	 * Normalizes a LineString. 
	 *
	 * A normalized linestring
	 * has the first point which is not equal to it's reflected point
	 * less than the reflected point.
	 */
	virtual void normalize();

	//was protected
	virtual int compareToSameClass(const Geometry *ls) const;

	virtual const Coordinate* getCoordinate() const;

	virtual double getLength() const;

	/**
	 * Creates a LineString whose coordinates are in the reverse
	 * order of this objects
	 *
	 * @return a LineString with coordinates in the reverse order
	 */
  	LineString* reverse() const;

	virtual void SetEmpty();

	//以下为ISnap接口
public:
	virtual bool SnapVertex(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plvertexIndex);

    //捕捉线上点
	virtual bool SnapEdgePoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plSegIndex);

	//捕捉线的中点
	virtual bool SnapMidPoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plSegIndex);

	//捕捉线的端点
	virtual bool SnapEndPoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plvertexIndex);

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

	void setPoints(CoordinateSequence* cl);

	//以下为ITransForm接口
public:
	virtual void Move(double dx,double dy);

	virtual void Mirror(const Coordinate &p1,const Coordinate &p2);

	virtual void Scale(const Coordinate &OriginPt,double dx,double dy);

	virtual void Rotate(const Coordinate &OriginPt,double angle);

    //以下为ISegmentCollection接口
public:
	virtual void AddSegment(ISegment *pSeg);

protected:
    //当数组中点发生变化时，如删除、添加等
	virtual void OnPointChanged();

	void ReCreateSegments();

protected:

	LineString(const LineString &ls);

	/// \brief
	/// Constructs a LineString taking ownership the
	/// given CoordinateSequence.
	LineString(CoordinateSequence *pts, const GeometryFactory *newFactory);

	/// Hopefully cleaner version of the above
	LineString(CoordinateSequence::AutoPtr pts,
			const GeometryFactory *newFactory);

	Envelope::AutoPtr computeEnvelopeInternal() const;

	CoordinateSequence::AutoPtr points;

private:

	void validateConstruction();

};

struct LineStringLT {
	bool operator()(const LineString *ls1, const LineString *ls2) const {
		return ls1->compareTo(ls2)<0;
	}
};


inline Geometry*
LineString::clone() const {
	return new LineString(*this);
}

} // namespace GEOMETRY::geom
} // namespace GEOMETRY

//#ifdef GEOS_INLINE
//# include "Geometry/geom/LineString.inl"
//#endif

#endif // ndef GEOS_GEOS_LINESTRING_H

/**********************************************************************
 * $Log$
 * Revision 1.10  2006/06/12 10:49:43  strk
 * unsigned int => size_t
 *
 * Revision 1.9  2006/05/04 15:49:39  strk
 * updated all Geometry::getDimension() methods to return Dimension::DimensionType (closes bug#93)
 *
 * Revision 1.8  2006/04/28 10:55:39  strk
 * Geometry constructors made protected, to ensure all constructions use GeometryFactory,
 * which has been made friend of all Geometry derivates. getNumPoints() changed to return
 * size_t.
 *
 * Revision 1.7  2006/04/11 11:16:25  strk
 * Added LineString and LinearRing constructors by auto_ptr
 *
 * Revision 1.6  2006/04/10 18:15:09  strk
 * Changed Geometry::envelope member to be of type auto_ptr<Envelope>.
 * Changed computeEnvelopeInternal() signater to return auto_ptr<Envelope>
 *
 * Revision 1.5  2006/04/10 17:35:44  strk
 * Changed LineString::points and Point::coordinates to be wrapped
 * in an auto_ptr<>. This should close bugs #86 and #89
 *
 * Revision 1.4  2006/04/05 10:25:21  strk
 * Fixed LineString constructor to ensure deletion of CoordinateSequence
 * argument on exception throw
 *
 * Revision 1.3  2006/03/31 16:55:17  strk
 * Added many assertions checking in LineString implementation.
 * Changed ::getCoordinate() to return NULL on empty geom.
 * Changed ::get{Start,End}Point() to return NULL on empty geom.
 *
 * Revision 1.2  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/
