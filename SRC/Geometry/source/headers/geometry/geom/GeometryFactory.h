/**********************************************************************
 * $Id: GeometryFactory.h 1820 2006-09-06 16:54:23Z mloskot $
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
 **********************************************************************
 *
 * Last port: geom/GeometryFactory.java rev. 1.48
 *
 **********************************************************************/

#ifndef GEOMETRY_GEOM_GEOMETRYFACTORY_H
#define GEOMETRY_GEOM_GEOMETRYFACTORY_H

//#include <Geometry/geom/CoordinateSequence.h>
//#include <Geometry/geom/Geometry.h>
#include <Geometry/inline.h>
#include <geometry/geom/Coordinate.h>
#include <vector>
#include <memory>

namespace GEOMETRY {
	namespace geom { 
		class CoordinateSequenceFactory;
		class Coordinate;
		class CoordinateSequence;
		class Envelope;
		class Geometry;
		class GeometryCollection;
		class LineString;
		class LinearRing;
		class MultiLineString;
		class MultiPoint;
		class MultiPolygon;
		class Point;
		class Polygon;
		class PrecisionModel;
		class CircularArc;
		class EllipticArc;
		class Circle;
		class Ellipse;
		class BezierSpline;
	}
}

//通过工厂类来构建几何对象
namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

/**
 * \brief
 * Supplies a set of utility methods for building Geometry objects
 * from CoordinateSequence or other Geometry objects.
 *
 * Note that the factory constructor methods do <b>not</b> change the input
 * coordinates in any way.
 * In particular, they are not rounded to the supplied <tt>PrecisionModel</tt>.
 * It is assumed that input Coordinates meet the given precision.
 */
class GeometryFactory {
public:
	/**
	 * \brief 
	 * Constructs a GeometryFactory that generates Geometries having a
	 * floating PrecisionModel and a spatial-reference ID of 0.
	 */
	GeometryFactory();

	/**
	 * \brief
	 * Constructs a GeometryFactory that generates Geometries having
	 * the given PrecisionModel, spatial-reference ID, and
	 * CoordinateSequence implementation.
	 *
	 * NOTES:
	 * (1) the given PrecisionModel is COPIED
	 * (2) the CoordinateSequenceFactory is NOT COPIED
	 *     and must be available for the whole lifetime
	 *     of the GeometryFactory
	 */
	GeometryFactory(const PrecisionModel *pm, int newSRID,
		CoordinateSequenceFactory *nCoordinateSequenceFactory);

	/**
	 * \brief
	 * Constructs a GeometryFactory that generates Geometries having the
	 * given CoordinateSequence implementation, a double-precision floating
	 * PrecisionModel and a spatial-reference ID of 0.
	 */
	GeometryFactory(CoordinateSequenceFactory *nCoordinateSequenceFactory);

	/**
	 * \brief
	 * Constructs a GeometryFactory that generates Geometries having
	 * the given PrecisionModel and the default CoordinateSequence
	 * implementation.
	 *
	 * @param pm the PrecisionModel to use
	 */
	GeometryFactory(const PrecisionModel *pm);

	/**
	 * \brief
	 * Constructs a GeometryFactory that generates Geometries having
	 * the given {@link PrecisionModel} and spatial-reference ID,
	 * and the default CoordinateSequence implementation.
	 *
	 * @param pm the PrecisionModel to use
	 * @param newSRID the SRID to use
	 */
	GeometryFactory(const PrecisionModel* pm, int newSRID);

	/**
	 * \brief Copy constructor
	 *
	 * @param gf the GeometryFactory to clone from
	 */
	GeometryFactory(const GeometryFactory &gf);

	/**
	 * \brief 
	 * Return a pointer to the default GeometryFactory.
	 * This is a global shared object instantiated
	 * using default constructor.
	 */
	static const GeometryFactory*
	getDefaultInstance();

	/// Destructor
	virtual ~GeometryFactory();

//Skipped a lot of list to array convertors

	Point* createPointFromInternalCoord(const Coordinate* coord,
			const Geometry *exemplar) const;

	/// Converts an Envelope to a Geometry.
	//
	/// Returned Geometry can be a Point, a Polygon or an EMPTY geom.
	///
	Geometry* toGeometry(const Envelope* envelope) const;

	/// \brief
	/// Returns the PrecisionModel that Geometries created by this
	/// factory will be associated with.
	const PrecisionModel* getPrecisionModel() const;

	/// Creates an EMPTY Point
	Point* createPoint() const;

	/// Creates a Point using the given Coordinate
	Point* createPoint(const Coordinate& coordinate) const;

	/// Creates a Point taking ownership of the given CoordinateSequence
	Point* createPoint(CoordinateSequence *coordinates) const;

	/// Creates a Point with a deep-copy of the given CoordinateSequence.
	Point* createPoint(const CoordinateSequence &coordinates) const;

	/// Construct an EMPTY GeometryCollection
	GeometryCollection* createGeometryCollection() const;

	/// Construct the EMPTY Geometry
	Geometry* createEmptyGeometry() const;

	/// Construct a GeometryCollection taking ownership of given arguments
	GeometryCollection* createGeometryCollection(
			std::vector<Geometry *> *newGeoms) const;

	/// Constructs a GeometryCollection with a deep-copy of args
	GeometryCollection* createGeometryCollection(
			const std::vector<Geometry *> &newGeoms) const;

	/// Construct an EMPTY MultiLineString 
	MultiLineString* createMultiLineString() const;

	/// Construct a MultiLineString taking ownership of given arguments
	MultiLineString* createMultiLineString(
			std::vector<Geometry *> *newLines) const;

	/// Construct a MultiLineString with a deep-copy of given arguments
	MultiLineString* createMultiLineString(
			const std::vector<Geometry *> &fromLines) const;

	/// Construct an EMPTY MultiPolygon 
	MultiPolygon* createMultiPolygon() const;

	/// Construct a MultiPolygon taking ownership of given arguments
	MultiPolygon* createMultiPolygon(std::vector<Geometry *> *newPolys) const;

	/// Construct a MultiPolygon with a deep-copy of given arguments
	MultiPolygon* createMultiPolygon(
			const std::vector<Geometry *> &fromPolys) const;

	/// Construct an EMPTY LinearRing 
	LinearRing* createLinearRing() const;

	/// Construct a LinearRing taking ownership of given arguments
	LinearRing* createLinearRing(CoordinateSequence* newCoords) const;

	std::auto_ptr<Geometry> createLinearRing(
			std::auto_ptr<CoordinateSequence> newCoords) const;

	/// Construct a LinearRing with a deep-copy of given arguments
	LinearRing* createLinearRing(
			const CoordinateSequence& coordinates) const;

	/// Constructs an EMPTY <code>MultiPoint</code>.
	MultiPoint* createMultiPoint() const;

	/// Construct a MultiPoint taking ownership of given arguments
	MultiPoint* createMultiPoint(std::vector<Geometry *> *newPoints) const;

	/// Construct a MultiPoint with a deep-copy of given arguments
	MultiPoint* createMultiPoint(
			const std::vector<Geometry *> &fromPoints) const;

	/// \brief
	/// Construct a MultiPoint containing a Point geometry
	/// for each Coordinate in the given list.
	MultiPoint* createMultiPoint(
			const CoordinateSequence &fromCoords) const;

	/// Construct an EMPTY Polygon 
	Polygon* createPolygon() const;

	/// Construct a Polygon taking ownership of given arguments
	Polygon* createPolygon(LinearRing *shell,
			std::vector<Geometry *> *holes) const;

	/// Construct a Polygon with a deep-copy of given arguments
	Polygon* createPolygon(const LinearRing &shell,
			const std::vector<Geometry *> &holes) const;

	/// Construct an EMPTY LineString 
	LineString* createLineString() const;

	/// Copy a LineString
	std::auto_ptr<LineString> createLineString(const LineString& ls) const;

	/// Construct a LineString taking ownership of given argument
	LineString* createLineString(CoordinateSequence* coordinates) const;

	std::auto_ptr<Geometry> createLineString(
			std::auto_ptr<CoordinateSequence> coordinates) const;

	/// Construct a LineString with a deep-copy of given argument
	LineString* createLineString(
			const CoordinateSequence& coordinates) const;

	/**
	* 通过圆心坐标、半径以及圆弧的角度来构造圆弧
	* @param Center 圆心坐标
	* @param radius 半径
	* @param startAngle 起始角度，相对于X坐标
	* @param centerAngle 圆弧转过的角度
	*/
	CircularArc* createCircularArc(const Coordinate &Center,double radius,double startAngle,double centerAngle) const;

	/**
	* 通过圆心坐标、半径构造圆
	* @param Center 圆心坐标
	* @param radius 半径
	*/
	Circle* createCircle(const Coordinate &Center,double radius) const;

	/**
	* 创建一个空圆
	*/
    Circle* createCircle() const;

	/**
	* 通过椭圆圆心坐标、长短轴以及起始点坐标来构造
	* @param Center 椭圆圆心坐标
	* @param semiMajor 长轴半径
	* @param semiMinor 短轴半径
	* @param rotationAngle 椭圆旋转角度，相对于X轴正方向
	* @param FromPt 椭圆弧的起始点
	* @param ToPt 椭圆弧的终止点
	* @param bCounterClock 椭圆弧是否是逆时针方向 
	*/
	EllipticArc* createEllipticArc(const Coordinate &Center,double semiMajor,double semiMinor,double rotationAngle,
		const Coordinate &FromPt,const Coordinate &ToPt,bool bCounterClock) const;

	
	BezierSpline* createBezierSpline(const std::vector<Coordinate>& knots) const;

    
	/**
	* 通过外接矩形创建椭圆
	* @param envelop 椭圆的外接矩形
	*/
	Ellipse* createEllipse(const Envelope& envelop) const;

	/**
	* 创建一个空椭圆
	*/
	Ellipse* createEllipse() const;

	/**
	 *  Build an appropriate <code>Geometry</code>, <code>MultiGeometry</code>, or
	 *  <code>GeometryCollection</code> to contain the <code>Geometry</code>s in
	 *  it.
	 *
	 *  For example:
	 *
	 *    - If <code>geomList</code> contains a single <code>Polygon</code>,
	 *      the <code>Polygon</code> is returned.
	 *    - If <code>geomList</code> contains several <code>Polygon</code>s, a
	 *      <code>MultiPolygon</code> is returned.
	 *    - If <code>geomList</code> contains some <code>Polygon</code>s and
	 *      some <code>LineString</code>s, a <code>GeometryCollection</code> is
	 *      returned.
	 *    - If <code>geomList</code> is empty, an empty
	 *      <code>GeometryCollection</code> is returned
	 *    .
	 *
	 * Note that this method does not "flatten" Geometries in the input,
	 * and hence if any MultiGeometries are contained in the input a
	 * GeometryCollection containing them will be returned.
	 *
	 * @param  newGeoms  the <code>Geometry</code>s to combine
	 *
	 * @return
	 *	A <code>Geometry</code> of the "smallest", "most type-specific"
	 *	class that can contain the elements of <code>geomList</code>.
	 *
	 * NOTE: the returned Geometry will take ownership of the
	 * 	given vector AND its elements 
	 */
	Geometry* buildGeometry(std::vector<Geometry *> *geoms) const;

	/** \brief
	 * This function does the same thing of the omonimouse function
	 * taking vector pointer instead of reference. 
	 *
	 * The difference is that this version will copy needed data
	 * leaving ownership to the caller.
	 */
	Geometry* buildGeometry(const std::vector<Geometry *> &geoms) const;
	
	int getSRID() const;

	/// \brief
	/// Returns the CoordinateSequenceFactory associated
	/// with this GeometryFactory
	const CoordinateSequenceFactory* getCoordinateSequenceFactory() const;

	/// Returns a clone of given Geometry.
	Geometry* createGeometry(const Geometry *g) const;

	/// Destroy a Geometry, or release it
	void destroyGeometry(Geometry *g) const;

private:
	const PrecisionModel* precisionModel;
	int SRID;
	const CoordinateSequenceFactory *coordinateListFactory;
};

} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#ifdef GEOS_INLINE
# include "Geometry/geom/GeometryFactory.inl"
#endif

#endif // ndef GEOS_GEOM_GEOMETRYFACTORY_H

/**********************************************************************
 * $Log$
 * Revision 1.11  2006/07/08 00:33:55  strk
 *         * configure.in: incremented CAPI minor version, to avoid                        falling behind any future version from the 2.2. branch.
 *         * source/geom/Geometry.cpp, source/geom/GeometryFactory.cpp,
 *         source/geomgraph/EdgeRing.cpp,
 *         source/headers/geos/geom/Geometry.h,
 *         source/headers/geos/geom/GeometryFactory.h,
 *         source/headers/geos/geom/GeometryFactory.inl,
 *         source/headers/geos/geomgraph/EdgeRing.h:
 *         updated doxygen comments (sync with JTS head).
 *         * source/headers/geos/platform.h.in: include <inttypes.h>
 *         rather then <stdint.h>
 *
 * Revision 1.10  2006/06/19 21:17:24  strk
 * port info and doxygen dox.
 *
 * Revision 1.9  2006/04/28 11:56:52  strk
 * * source/geom/GeometryFactory.cpp, source/headers/geos/geom/GeometryFactory.h: added LineString copy constructor.
 * * source/geom/Polygon.cpp: fixed getBoundary method to always return a geometry composed by LineStrings (not LinearRings)
 *
 * Revision 1.8  2006/04/12 11:39:34  strk
 * Removed Geometry.h and CoordinateSequence.h includes.
 * The former created a circular dependency.
 *
 * Revision 1.7  2006/04/11 11:16:25  strk
 * Added LineString and LinearRing constructors by auto_ptr
 *
 * Revision 1.6  2006/04/10 13:09:49  strk
 * Added GeometryFactory::defaultInstance()
 * Made Geometry::INTERNAL_GEOMETRY_FACTORY an alias for it
 * removed last deletion from Unload::Release class
 *
 * Revision 1.5  2006/03/31 17:51:26  strk
 * A few assertion checking, comments cleanup, use of initialization lists
 * in constructors, handled NULL parameters.
 *
 * Revision 1.4  2006/03/28 16:33:14  strk
 * Added note about args responsibility in GeometryFactory constructor
 *
 * Revision 1.3  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.2  2006/03/20 17:27:03  strk
 * Bug #72 - Missing <vector> header
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/

