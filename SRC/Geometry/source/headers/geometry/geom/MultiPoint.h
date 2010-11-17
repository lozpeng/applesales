/**********************************************************************
 * $Id: MultiPoint.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_GEOS_MULTIPOINT_H
#define GEOS_GEOS_MULTIPOINT_H

#include <Geometry/platform.h>
#include <Geometry/geom/GeometryCollection.h>
#include <Geometry/geom/Dimension.h> // for Dimension::DimensionType

#include <Geometry/inline.h>

#include <string>
#include <vector>

namespace GEOMETRY {
	namespace geom { // GEOMETRY::geom
		class Coordinate;
		class CoordinateArraySequence;
	}
}

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

/**
 * \class MultiPoint geom.h geos.h
 * \brief  Models a collection of Point objects.
 */
class MultiPoint: public GeometryCollection {

public:

	friend class GeometryFactory;

	virtual ~MultiPoint();

	/// Returns point dimension (0)
	Dimension::DimensionType getDimension() const;

	/// Returns Dimension::False (Point has no boundary)
	int getBoundaryDimension() const;

	/// Returns an EMPTY Geometry
	Geometry* getBoundary() const;

	std::string getGeometryType() const;

	virtual GeometryTypeId getGeometryTypeId() const;

	//bool isValid() const;

	bool isSimple() const;

	bool equalsExact(const Geometry *other, double tolerance=0) const;

	Geometry *clone() const { return new MultiPoint(*this); };

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
	virtual void Move(double dx,double dy);

	virtual void Mirror(const Coordinate &p1,const Coordinate &p2);

	virtual void Scale(const Coordinate &OriginPt,double dx,double dy);

	void Rotate(const Coordinate &OriginPt,double angle); 

protected:

	/**
	 * \brief Constructs a <code>MultiPoint</code>.
	 *
	 * @param  newPoints
	 *	the <code>Point</code>s for this <code>MultiPoint</code>,
	 *	or <code>null</code> or an empty array to create the empty
	 * 	geometry.
	 *	Elements may be empty <code>Point</code>s,
	 *	but not <code>null</code>s.
	 *
	 *	Constructed object will take ownership of
	 *	the vector and its elements.
	 *
	 * @param newFactory
	 * 	The GeometryFactory used to create this geometry
	 *	Caller must keep the factory alive for the life-time
	 *	of the constructed MultiPoint.
	 */
	MultiPoint(std::vector<Geometry *> *newPoints, const GeometryFactory *newFactory);

	MultiPoint(const MultiPoint &mp): GeometryCollection(mp) 
	{
		//设置是否有Z或M值
		this->SetbZ(mp.HasZ());
		this->SetbM(mp.HasM());
	}

	const Coordinate* getCoordinateN(int n) const;
};

} // namespace GEOMETRY::geom
} // namespace GEOMETRY

//#ifdef GEOS_INLINE
//# include "Geometry/geom/MultiPoint.inl"
//#endif

#endif // ndef GEOS_GEOS_MULTIPOINT_H

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
