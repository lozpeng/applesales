#ifndef GEOMETRY_GEOS_ITRANSFORM_H
#define GEOMETRY_GEOS_ITRANSFORM_H

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
 * ITransForm提供了平移、缩放、旋转等改变几何图形的接口,大部分图形将实现
 * 
 * 这些接口
 *
 * 
 */
class ITransForm 
{

public:
	ITransForm(){};

	virtual ~ITransForm() {};

public:
    //平移
	virtual void Move(double dx,double dy) {} 

	//镜像
	virtual void Mirror(const Coordinate &p1,const Coordinate &p2){}

	/**
	* 缩放
	* @param OriginPt 缩放时相对的原点，原点将在缩放后保持不变
	* @param dx X轴缩放的比例, dx =newX/oldX
    * @param dy Y轴缩放的比例, dy =newY/oldY
	*/
	virtual void Scale(const Coordinate &OriginPt,double dx,double dy) {}

	/**
	* 旋转
	* @param OriginPt 旋转时相对的原点，原点将在旋转后保持不变
	* @param angle 旋转的角度，单位是弧度，逆时针方向为正
	*/
	virtual void Rotate(const Coordinate &OriginPt,double angle) {}

	/**
	* 将Geometry调整到合适的范围
	* @param destEnv 目标范围
	*/
	virtual void FitEnvelope(const Envelope &destEnv){}
    


};

} // namespace GEOMETRY::geom
} // namespace GEOMETRY


#endif
