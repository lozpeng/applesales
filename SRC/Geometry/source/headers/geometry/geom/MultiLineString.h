/**********************************************************************
 * $Id: MultiLineString.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_GEOS_MULTILINESTRING_H
#define GEOS_GEOS_MULTILINESTRING_H

#include <Geometry/geom/GeometryCollection.h> // for inheritance
//#include <Geometry/platform.h> 
#include <Geometry/geom/Dimension.h>

#include <string>
#include <vector>

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

/// Basic implementation of MultiLineString objects.
class MultiLineString: public GeometryCollection {

public:

	friend class GeometryFactory;

	virtual ~MultiLineString();

	/// Returns line dimension (1)
	Dimension::DimensionType getDimension() const;

	/**
	 * \brief
	 * Returns Dimension::False if all LineStrings in the collection
	 * are closed, 0 otherwise.
	 */
	int getBoundaryDimension() const;

	/// Returns a (possibly empty) MultiPoint 
	Geometry* getBoundary() const;

	std::string getGeometryType() const;

	virtual GeometryTypeId getGeometryTypeId() const;

	bool isClosed() const;

	bool isSimple() const;

	bool equalsExact(const Geometry *other, double tolerance=0) const;

	Geometry *clone() const;

	/**
	 * Creates a MultiLineString in the reverse
	 * order to this object.
	 * Both the order of the component LineStrings
	 * and the order of their coordinate sequences
	 * are reversed.
	 *
	 * @return a MultiLineString in the reverse order
	 */
	MultiLineString* reverse() const;

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

	//以下为ITransForm接口
public:
	virtual void Move(double dx,double dy);

	virtual void Mirror(const Coordinate &p1,const Coordinate &p2);

	virtual void Scale(const Coordinate &OriginPt,double dx,double dy);

	virtual void Rotate(const Coordinate &OriginPt,double angle);
    
protected:

	/**
	 * \brief Constructs a <code>MultiLineString</code>.
	 *
	 * @param  newLines
	 *	The <code>LineStrings</code>s for this
	 *	<code>MultiLineString</code>, or <code>null</code>
	 *	or an empty array to create the empty geometry.
	 *	Elements may be empty <code>LineString</code>s,
	 *	but not <code>null</code>s.
	 *
	 *	Constructed object will take ownership of
	 *	the vector and its elements.
	 *
	 * @param newFactory
	 * 	The GeometryFactory used to create this geometry.
	 *	Caller must keep the factory alive for the life-time
	 *	of the constructed MultiLineString.
	 * 	
	 */
	MultiLineString(std::vector<Geometry *> *newLines,
			const GeometryFactory *newFactory);

	MultiLineString(const MultiLineString &mp);
};

} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#ifdef GEOS_INLINE
# include "Geometry/geom/MultiLineString.inl"
#endif

#endif // ndef GEOS_GEOS_MULTILINESTRING_H

/**********************************************************************
 * $Log$
 * Revision 1.5  2006/05/04 15:49:39  strk
 * updated all Geometry::getDimension() methods to return Dimension::DimensionType (closes bug#93)
 *
 * Revision 1.4  2006/04/28 10:55:39  strk
 * Geometry constructors made protected, to ensure all constructions use GeometryFactory,
 * which has been made friend of all Geometry derivates. getNumPoints() changed to return
 * size_t.
 *
 * Revision 1.3  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.2  2006/03/23 12:12:01  strk
 * Fixes to allow build with -DGEOS_INLINE
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/
