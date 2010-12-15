/************************************************************************/
/*       描述：序列化Geometry
/*	     创建日期:2010-9-19
/*		 创建者:hhzhao
/************************************************************************/

#ifndef GEOS_IO_GEOMETRYSERIALIZOR_H
#define GEOS_IO_GEOMETRYSERIALIZOR_H

#include <string>
#include <vector>
#include "SystemDefine.h"
#include "ISerialization.h"


// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class Coordinate;
		class ISegment;
		class CoordinateSequence;
		class Geometry;
		class GeometryCollection;
		class Point;
		class LineString;
		class LinearRing;
		class Polygon;
		class MultiPoint;
		class MultiLineString;
		class MultiPolygon;
		class Circle;
		class Ellipse;
		class BezierSpline;
	} 
} 
using namespace std;
using namespace GEOMETRY::geom;

namespace GEOMETRY { // NameSpace GEOMETRY
	namespace io {			//NameSpace  io

class GeometySerializor 
{
public:
	GeometySerializor();
	GeometySerializor( Geometry *pGeometry );
	~GeometySerializor();

	 Geometry* serialization( SYSTEM::IArchive &ar );

	void SetGeometry( Geometry *pGeometry );
protected:
	void RWPoint( SYSTEM::IArchive &ar );

	void RWLineString( SYSTEM::IArchive &ar );

	void RWLinearRing( SYSTEM::IArchive &ar );

	void RWPolygon( SYSTEM::IArchive &ar );

	void RWMultiPoint( SYSTEM::IArchive &ar );

	void RWMultiLineString( SYSTEM::IArchive &ar );

	void RWMultiPolygon( SYSTEM::IArchive &ar );

	void RWGeometryCollection( SYSTEM::IArchive &ar );

	void RWCircle( SYSTEM::IArchive &ar );

	void RWEllipse( SYSTEM::IArchive &ar );

	void RWBezierSpline( SYSTEM::IArchive &ar );

	Coordinate * RWCoordinate( SYSTEM::IArchive &ar, Coordinate *pCoord );
	void RWCoordinate( SYSTEM::IArchive &ar, Coordinate &Coord );

	CoordinateSequence * RWCoordinateSequence( SYSTEM::IArchive &ar, CoordinateSequence *pCoordSeq );
	void RWCoordinateSequence( SYSTEM::IArchive &ar, CoordinateSequence &CoordSeq );

	LinearRing * RWLinearRing( SYSTEM::IArchive &ar, LinearRing *pLr );
	void RWLinearRing( SYSTEM::IArchive &ar, LinearRing &lr );

	LineString * RWLineString( SYSTEM::IArchive &ar, LineString *pLs );
	void RWLineString( SYSTEM::IArchive &ar, LineString &ls );

	GEOMETRY::geom::Polygon * RWPolygon( SYSTEM::IArchive &ar, GEOMETRY::geom::Polygon *pPolygon );
	void RWPolygon( SYSTEM::IArchive &ar, GEOMETRY::geom::Polygon &polygon );
	
	GEOMETRY::geom::ISegment * RWSegment( SYSTEM::IArchive &ar, GEOMETRY::geom::ISegment *pSegment );
		
private:
	Geometry *m_pGeometry;
};

} // namespace GEOMETRY::io
} // namespace GEOMETRY


#endif