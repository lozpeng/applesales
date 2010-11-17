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
 * IGeometryCollection�����а�������������ͼ�εĻ��࣬��MultiPoint,MultiLineString,Polygon,multiPolygon
 * 
 * ��ͬ��GeometryCollection,���Լ����м���ͼ�εĲ���ȫ��������ʵ�֣��������洢���ζ���ֻ���ṩ���ʼ�����
 * ���ζ���Ĺ����ӿ�
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
	//����ͼ�ε�����
	virtual long GeometryCount() {return 0;}
    //���һ������ͼ��
	virtual void AddGeometry(Geometry* pGeometry) {}

	virtual Geometry* GetGeometry(size_t i) {return NULL;}




};

} // namespace GEOMETRY::geom
} // namespace GEOMETRY


#endif
