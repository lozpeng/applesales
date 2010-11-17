/************************************************************************/
/*       描述：序列化Geometry
/*	     创建日期:2010-9-19
/*		 创建者:zhm
/************************************************************************/

#ifndef GEOS_IO_GEOMETRYSERIALIZOR_H
#define GEOS_IO_GEOMETRYSERIALIZOR_H

#include <string>
#include <vector>
#include "Preprocess.h"
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

	 Geometry* serialization( otSystem::IArchive &ar );

	void SetGeometry( Geometry *pGeometry );
protected:
	void RWPoint( otSystem::IArchive &ar );

	void RWLineString( otSystem::IArchive &ar );

	void RWLinearRing( otSystem::IArchive &ar );

	void RWPolygon( otSystem::IArchive &ar );

	void RWMultiPoint( otSystem::IArchive &ar );

	void RWMultiLineString( otSystem::IArchive &ar );

	void RWMultiPolygon( otSystem::IArchive &ar );

	void RWGeometryCollection( otSystem::IArchive &ar );

	void RWCircle( otSystem::IArchive &ar );

	void RWEllipse( otSystem::IArchive &ar );

	void RWBezierSpline( otSystem::IArchive &ar );

	Coordinate * RWCoordinate( otSystem::IArchive &ar, Coordinate *pCoord );
	void RWCoordinate( otSystem::IArchive &ar, Coordinate &Coord );

	CoordinateSequence * RWCoordinateSequence( otSystem::IArchive &ar, CoordinateSequence *pCoordSeq );
	void RWCoordinateSequence( otSystem::IArchive &ar, CoordinateSequence &CoordSeq );

	LinearRing * RWLinearRing( otSystem::IArchive &ar, LinearRing *pLr );
	void RWLinearRing( otSystem::IArchive &ar, LinearRing &lr );

	LineString * RWLineString( otSystem::IArchive &ar, LineString *pLs );
	void RWLineString( otSystem::IArchive &ar, LineString &ls );

	GEOMETRY::geom::Polygon * RWPolygon( otSystem::IArchive &ar, GEOMETRY::geom::Polygon *pPolygon );
	void RWPolygon( otSystem::IArchive &ar, GEOMETRY::geom::Polygon &polygon );
	
	GEOMETRY::geom::ISegment * RWSegment( otSystem::IArchive &ar, GEOMETRY::geom::ISegment *pSegment );
		
private:
	Geometry *m_pGeometry;
};

} // namespace GEOMETRY::io
} // namespace GEOMETRY


#endif