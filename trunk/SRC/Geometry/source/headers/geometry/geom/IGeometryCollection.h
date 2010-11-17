#ifndef GEOMETRY_GEOS_IGEOMETRYCOLLECTION_H
#define GEOMETRY_GEOS_IGEOMETRYCOLLECTION_H

#include <Geometry/geom/Geometry.h> 
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
	}
}

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

/**
 * IGeometryCollection是所有包含多个几何体的图形的基类，如MultiPoint,MultiLineString,Polygon,multiPolygon
 * 
 * 不同于GeometryCollection,它对集合中几何图形的操作全由子类来实现，本身并不存储几何对象，只是提供访问集合中
 * 几何对象的公共接口
 *
 *
 * 
 * 
 */
class IGeometryCollection 
{

public:
	IGeometryCollection(){};

	virtual ~IGeometryCollection() {};

public:
	//几何图形的数量
	virtual long GeometryCount() {return 0;}
    //添加一个几何图形
	virtual void AddGeometry(Geometry* pGeometry) {}

	virtual Geometry* GetGeometry(size_t i) {return NULL;}




};

} // namespace GEOMETRY::geom
} // namespace GEOMETRY


#endif
