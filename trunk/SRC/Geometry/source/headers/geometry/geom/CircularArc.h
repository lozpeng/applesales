#ifndef GEOMETRY_GEOM_CIRCULARARC_H
#define GEOMETRY_GEOM_CIRCULARARC_H

#include <Geometry/platform.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/CoordinateSequence.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Envelope.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Dimension.h> // for Dimension::DimensionType
#include <Geometry/geom/ISegment.h>
#include <geometry/geom/Coordinate.h>

#include <string>
#include <vector>
#include <memory> // for auto_ptr

namespace GEOMETRY {
namespace geom { 


/******************************************************************************
*Բ�λ��μ̳���ISegment��������Ϊһ��������ͼ��ʹ�ã�Ҳ������Ϊ�����Ȧ��һ����
*
******************************************************************************/
class CircularArc: public ISegment
{

public:

	CircularArc();

	/**
	* ͨ��Բ�����ꡢ�뾶�Լ�Բ���ĽǶ�������
	* @param Center Բ������
	* @param radius �뾶
	* @param startAngle ��ʼ�Ƕȣ������X����
	* @param centerAngle Բ��ת���ĽǶ�
	*/
	CircularArc(const Coordinate &Center,double radius,double startAngle,double centerAngle);
	

	virtual ~CircularArc();
public:


	/******************************************************************
	*ʵ��Geometry�ĺ���
	******************************************************************/
public:

	std::string getGeometryType() const {return "CircularArc";}; 

	GeometryTypeId getGeometryTypeId() const {return GEOM_CIRCULARARC;};
	Geometry* clone() const;

	bool equalsExact(const Geometry *other, double tolerance=0) const;


    virtual Envelope::AutoPtr computeEnvelopeInternal() const;
	/******************************************************************
	*����Ϊʵ��ISegment�Ľӿ�
	******************************************************************/
public:


	//���߶εĳ���
	double Length() const;

	void CloestLinePoint(const Coordinate &pt, Coordinate &ret) const;

	//�߶ε��е�
	void MidPoint(Coordinate &ret) const;

	virtual void SegMove(double dx,double dy);

	virtual void SegScale(const Coordinate &OriginPt,double dx,double dy);

	virtual void SegRotate(const Coordinate &OriginPt,double angle);

	/******************************************************************
	*����Ϊʵ��ITransform�Ľӿ�
	******************************************************************/
public:
	void Move(double dx,double dy);

	void Scale(const Coordinate &OriginPt,double dx,double dy);

	void Rotate(const Coordinate &OriginPt,double angle); 

	/******************************************************************
	*����ΪCircle��һЩ����
	******************************************************************/
public:
	
	/**
	* �õ�Բ������Բ�ĵ������
	* @return Բ������
	*/
	Coordinate GetCenterPoint() const{return m_CenterPt;};


	/**
	* ����Բ������Բ�ĵ������
	*/
	void SetCenterPoint(const Coordinate &coord) {m_CenterPt =coord;}


	/**
	* �õ�Բ���뾶
	* @return Բ�İ뾶
	*/
	double GetRadius() const {return m_radius;};


	/**
	* ����Բ���뾶
	*/
	void   SetRadius(double r){m_radius =r;};


	/**
	* �õ�Բ�������ĽǶȣ�Ҳ������ֹ�Ƕȼ�ȥ��ʼ�Ƕ�
	* @return ���ȵ�λ����Χ��-2PI��2PI֮��
	*/
	double GetCenterAngle() const{return m_centerAngle;};

	void   SetCenterAngle(double angle);

	double GetStartAngle() const {return m_startAngle;}

	void   SetStartAngle(double angle);

	/**
	* �ж�Բ���Ƿ�����ʱ��
	* @return trueΪ��ʱ�룬falseΪ˳ʱ��
	*/
	bool   IsCounterClock() const;

	/**
	* �ж�Բ���Ƿ���һ��Բ
	* @return trueΪԲ��falseΪԲ��
	*/
	virtual bool IsCircle();

private:
	//������֪�ĽǶȣ�������ʼ�����ֹ������
	void ComputeStartEndPt();
protected:
	//Բ������
    Coordinate m_CenterPt;

	//Բ���뾶
	double m_radius;

	double m_startAngle;

	//���ĽǶȣ�������ʾ˳ʱ�룬������ʾ��ʱ��
	double m_centerAngle;



};





} // GEOMETRY::geom
} //GEOMETRY







#endif
