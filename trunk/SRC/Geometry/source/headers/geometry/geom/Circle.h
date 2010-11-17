#ifndef GEOMETRY_GEOM_CIRCLE_H
#define GEOMETRY_GEOM_CIRCLE_H

#include <Geometry/platform.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/CoordinateSequence.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Envelope.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Dimension.h> // for Dimension::DimensionType
#include <Geometry/geom/CircularArc.h>
#include <geometry/geom/Coordinate.h>

#include <string>
#include <vector>
#include <memory> // for auto_ptr

namespace GEOMETRY {
namespace geom { 


/******************************************************************************
* Բ����һ�������Բ��
*
******************************************************************************/
class Circle: public CircularArc
{

public:

	Circle();

	/**
	* ͨ��Բ�����ꡢ�뾶������
	* @param Center Բ������
	* @param radius �뾶
	*/
	Circle(const Coordinate &Center,double radius);


	virtual ~Circle();
public:


	/******************************************************************
	*ʵ��Geometry�ĺ���
	******************************************************************/
public:

	std::string getGeometryType() const {return "Circle";}; 

	GeometryTypeId getGeometryTypeId() const {return GEOM_CIRCLE;};
	Geometry* clone() const;

	Dimension::DimensionType getDimension() const {return Dimension::A;}

	///�Ƿ���Ҫ���
	bool isScatter() const { return true; }

	//�������ɢ
	Geometry* scatter() const;


	bool equalsExact(const Geometry *other, double tolerance=0) const;


	virtual Envelope::AutoPtr computeEnvelopeInternal() const;

	/******************************************************************
	*����ΪCircle��һЩ����
	******************************************************************/
public:

	/**
	* �ж�Բ���Ƿ���һ��Բ
	* @return trueΪԲ��falseΪԲ��
	*/
	bool IsCircle() {return true;}

};

} // GEOMETRY::geom
} //GEOMETRY







#endif
