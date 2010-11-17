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
 * ITransForm�ṩ��ƽ�ơ����š���ת�ȸı伸��ͼ�εĽӿ�,�󲿷�ͼ�ν�ʵ��
 * 
 * ��Щ�ӿ�
 *
 * 
 */
class ITransForm 
{

public:
	ITransForm(){};

	virtual ~ITransForm() {};

public:
    //ƽ��
	virtual void Move(double dx,double dy) {} 

	//����
	virtual void Mirror(const Coordinate &p1,const Coordinate &p2){}

	/**
	* ����
	* @param OriginPt ����ʱ��Ե�ԭ�㣬ԭ�㽫�����ź󱣳ֲ���
	* @param dx X�����ŵı���, dx =newX/oldX
    * @param dy Y�����ŵı���, dy =newY/oldY
	*/
	virtual void Scale(const Coordinate &OriginPt,double dx,double dy) {}

	/**
	* ��ת
	* @param OriginPt ��תʱ��Ե�ԭ�㣬ԭ�㽫����ת�󱣳ֲ���
	* @param angle ��ת�ĽǶȣ���λ�ǻ��ȣ���ʱ�뷽��Ϊ��
	*/
	virtual void Rotate(const Coordinate &OriginPt,double angle) {}

	/**
	* ��Geometry���������ʵķ�Χ
	* @param destEnv Ŀ�귶Χ
	*/
	virtual void FitEnvelope(const Envelope &destEnv){}
    


};

} // namespace GEOMETRY::geom
} // namespace GEOMETRY


#endif
