/**********************************************************************
 * $Id: Polygon.h 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2005 2006 Refractions Research Inc.
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: geom/Polygon.java rev. 1.47
 *
 **********************************************************************/

#ifndef GEOMETRY_GEOM_POLYGON_H
#define GEOMETRY_GEOM_POLYGON_H

#include <string>
#include <vector>
#include <Geometry/platform.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/Envelope.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Dimension.h> // for Dimension::DimensionType
#include <Geometry/geom/IGeometryCollection.h>
#include <Geometry/inline.h>

#include <memory> // for auto_ptr

// Forward declarations
namespace GEOMETRY {
	namespace geom { // GEOMETRY::geom
		class Coordinate;
		class CoordinateArraySequence;
		class LinearRing;
		class LineString;
	}
}

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

/**
 * \class Polygon geom.h geos.h
 *
 * \brief Represents a linear polygon, which may include holes.
 *
 * The shell and holes of the polygon are represented by {@link LinearRing}s.
 * In a valid polygon, holes may touch the shell or other holes at a single point.
 * However, no sequence of touching holes may split the polygon into two pieces.
 * The orientation of the rings in the polygon does not matter.
 * <p>
 *  The shell and holes must conform to the assertions specified in the <A
 *  HREF="http://www.opengis.org/techno/specs.htm">OpenGIS Simple Features
 *  Specification for SQL</A> .
 *
 */
class Polygon: public Geometry , public IGeometryCollection
{

public:

	friend class GeometryFactory;

	/// A vector of const Polygon pointers
	typedef std::vector<const Polygon *> ConstVect;

	virtual ~Polygon();

	virtual Geometry *clone() const { return new Polygon(*this); }

	CoordinateSequence* getCoordinates() const;

	size_t getNumPoints() const;

	/// Returns surface dimension (2)
	Dimension::DimensionType getDimension() const;

	/// Returns 1 (Polygon boundary is a MultiLineString)
	int getBoundaryDimension() const;

	/**
	 * \brief
	 * Returns a MultiLineString.
	 * One LineString for the shell and one for each hole.
	 * Empty for an empty Polygon.
	 */
	Geometry* getBoundary() const;

	bool isEmpty() const;

	/** \brief
	 * Tests if a valid polygon is simple.
	 * This method always returns true, since a valid polygon is always simple
	 *
	 * @return <code>true</code>
	 */
	bool isSimple() const;
	
	/// Returns the exterior ring (shell)
	const LineString* getExteriorRing() const;

	void  SetExteriorRing(LinearRing *ring);

	/// Returns number of interior rings (hole)
	size_t getNumInteriorRing() const;

	/// Get nth interior ring (hole)
	const LineString* getInteriorRingN(size_t n) const;

	std::string getGeometryType() const;
	virtual GeometryTypeId getGeometryTypeId() const;
	bool equalsExact(const Geometry *other, double tolerance=0) const;
	void apply_rw(const CoordinateFilter *filter);
	void apply_ro(CoordinateFilter *filter) const;
	void apply_rw(GeometryFilter *filter);
	void apply_ro(GeometryFilter *filter) const;

	Geometry* convexHull() const;

	void normalize();

	int compareToSameClass(const Geometry *p) const; //was protected

	const Coordinate* getCoordinate() const;

	double getArea() const;

 	/// Returns the perimeter of this <code>Polygon</code>
	double getLength() const;

	void apply_rw(GeometryComponentFilter *filter);

	void apply_ro(GeometryComponentFilter *filter) const;

	bool isRectangle() const;

	virtual void SetEmpty();

	/**
	* 规范化多边形，将具有多个外环的多边形转换成一个多多边形	
	* @return 如果是正规多边形，则返回它本身的指针，如果转换成了多多边形，则返回多多边形指针
	*/
	Geometry* OrganizePolygon();

	//是否包含弧段
	bool IsContainArc() const;


	//以下为ISnap接口
public:
	virtual bool SnapVertex(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plvertexIndex);
    
	 //捕捉线上点
	virtual bool SnapEdgePoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plSegIndex);

    //捕捉线的中点
	virtual bool SnapMidPoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plSegIndex);

	//以下为IPointCollection接口
public:
	virtual long PointCount() const;
 //   
	////在图形的最后添加一个节点
	//virtual void AddPoint(Coordinate &coord);

	////插入一个点
	//virtual void InsertPoint(int index,Coordinate &newpoint);

	////替换一个点
 //   virtual void ReplacePoint(int index,Coordinate &newpoint);

 //   virtual void RemovePoint(int index);

 //   virtual Coordinate GetPoint(int index); 

	//以下为ITransForm接口
public:
	virtual void Move(double dx,double dy);

	virtual void Mirror(const Coordinate &p1,const Coordinate &p2);

	virtual void Scale(const Coordinate &OriginPt,double dx,double dy);

	virtual void Rotate(const Coordinate &OriginPt,double angle);

/********************************************************************
*以下为继承的IGeometryCollection的接口
********************************************************************/
public:

	//添加一个多边形
	virtual void AddGeometry(Geometry *pGeometry);

	//几何图形的数量
	virtual long GeometryCount() ;

	virtual Geometry* GetGeometry(size_t i) ;



protected:


	Polygon(const Polygon &p);

	/**
	 * Constructs a <code>Polygon</code> with the given exterior 
	 * and interior boundaries.
	 *
	 * @param  newShell  the outer boundary of the new Polygon,
	 *                   or <code>null</code> or an empty
	 *		     LinearRing if the empty geometry
	 *                   is to be created.
	 *
	 * @param  newHoles  the LinearRings defining the inner
	 *                   boundaries of the new Polygon, or
	 *                   null or empty LinearRing 
	 *                   if the empty  geometry is to be created.
	 *
	 * @param newFactory the GeometryFactory used to create this geometry
	 *
	 * Polygon will take ownership of Shell and Holes LinearRings 
	 */
	Polygon(LinearRing *newShell, std::vector<Geometry *> *newHoles,
		const GeometryFactory *newFactory);

	LinearRing *shell;

	std::vector<Geometry *> *holes; //Actually vector<LinearRing *>

	Envelope::AutoPtr computeEnvelopeInternal() const;

private:

	void normalize(LinearRing *ring, bool clockwise);
};

} // namespace GEOMETRY::geom
} // namespace GEOMETRY

//#ifdef GEOS_INLINE
//# include "Geometry/geom/Polygon.inl"
//#endif

#endif // ndef GEOS_GEOM_POLYGON_H

/**********************************************************************
 * $Log$
 * Revision 1.7  2006/06/08 17:58:57  strk
 * Polygon::getNumInteriorRing() return size_t, Polygon::interiorRingN() takes size_t.
 *
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
 * Revision 1.3  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.2  2006/03/15 09:12:45  strk
 * isSimple doc
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/
