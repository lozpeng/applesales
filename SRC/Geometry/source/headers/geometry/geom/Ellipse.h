#ifndef GEOMETRY_GEOM_ELLIPSE_H
#define GEOMETRY_GEOM_ELLIPSE_H

#include <Geometry/platform.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/CoordinateSequence.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Envelope.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Dimension.h> // for Dimension::DimensionType
#include <Geometry/geom/EllipticArc.h>
#include <geometry/geom/Coordinate.h>

#include <string>
#include <vector>
#include <memory> // for auto_ptr

namespace GEOMETRY {
namespace geom { 


/******************************************************************************
*��Բ��һ���������Բ��
*
******************************************************************************/
class Ellipse: public EllipticArc
{

public:

	Ellipse();

	/**
	* ͨ����Բ��Ӿ���������
	* @param envelope ��Բ��Ӿ���
	*/
	Ellipse(const Envelope& envelope);


	virtual ~Ellipse();
public:


	/******************************************************************
	*ʵ��Geometry�ĺ���
	******************************************************************/
public:

	std::string getGeometryType() const {return "Ellipse";}; 

	GeometryTypeId getGeometryTypeId() const {return GEOM_ELLIPSE;};
	Geometry* clone() const;

	bool equalsExact(const Geometry *other, double tolerance=0) const;


	virtual Envelope::AutoPtr computeEnvelopeInternal() const;

	///�Ƿ���Ҫ���
	bool isScatter() const { return true; }

	//�������ɢ
	Geometry* scatter() const;


	/******************************************************************
	*����ΪEllipticArc��һЩ����
	******************************************************************/
public:

	/**
	* �ж�Բ���Ƿ���һ����Բ
	* @return trueΪԲ��falseΪ��Բ
	*/
	bool IsEllipse(){return true;}


};





} // GEOMETRY::geom
} //GEOMETRY







#endif
