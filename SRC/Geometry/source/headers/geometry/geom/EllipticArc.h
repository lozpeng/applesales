#ifndef GEOMETRY_GEOM_ELLIPTICARC_H
#define GEOMETRY_GEOM_ELLIPTICARC_H

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
*��Բ���μ̳���ISegment��������Ϊһ��������ͼ��ʹ�ã�Ҳ������Ϊ�����Ȧ��һ����
*
******************************************************************************/
class EllipticArc: public ISegment
{

public:

	EllipticArc();

	/**
	* ͨ����ԲԲ�����ꡢ�������Լ���ʼ������������
	* @param Center ��ԲԲ������
	* @param semiMajor ����뾶
	* @param semiMinor ����뾶
	* @param rotationAngle ��Բ��ת�Ƕȣ������X��������
	* @param FromPt ��Բ������ʼ��
	* @param ToPt ��Բ������ֹ��
	* @param bCounterClock ��Բ���Ƿ�����ʱ�뷽�� 
	*/
	EllipticArc(const Coordinate &Center,double semiMajor,double semiMinor,double rotationAngle,
		 const Coordinate &FromPt,const Coordinate &ToPt,bool bCounterClock);


	virtual ~EllipticArc();
public:


	/******************************************************************
	*ʵ��Geometry�ĺ���
	******************************************************************/
public:

	std::string getGeometryType() const {return "EllipticArc";}; 

	GeometryTypeId getGeometryTypeId() const {return GEOM_ELLIPTICARC;};
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
	*����ΪEllipticArc��һЩ����
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
	* �õ���Բ������뾶
	* @param semiMajor ��õĳ���뾶
	* @param semiMinor ��õĶ���뾶
	*/
	void GetAxes(double *semiMajor,double *semiMinor) const 
	{ *semiMajor =m_semiMajor;*semiMinor =m_semiMinor;}


	/**
	* ������Բ������뾶
	* @param semiMajor ����뾶
	* @param semiMinor ����뾶
	*/
	void SetAxes(double semiMajor,double semiMinor) 
	{m_semiMajor =semiMajor;m_semiMinor =semiMinor;}


	/**
	* �õ�Բ�������ĽǶȣ�Ҳ������ֹ�Ƕȼ�ȥ��ʼ�Ƕ�
	* @return ���ȵ�λ����Χ��-2PI��2PI֮��
	*/
	double GetCenterAngle() const{return m_centerAngle;};

	/**
	* �õ���ת�Ƕȣ���ת�Ƕ�����Բ����ڹ�����Բ����ת
	* @return ���ȵ�λ����Χ��-2PI��2PI֮��
	*/
	double GetRotAngle() const{return m_rotAngle;}

	/**
	* �ж�Բ���Ƿ�����ʱ��
	* @return trueΪ��ʱ�룬falseΪ˳ʱ��
	*/
	bool   IsCounterClock() const;

	/**
	* �ж�Բ���Ƿ���һ����Բ
	* @return trueΪԲ��falseΪ��Բ
	*/
	
	virtual bool IsEllipse();

protected:
	//������ʼ��ֹ�Ƕ�
	void ComputeAngle();
protected:
	//��Բ��������
	Coordinate m_CenterPt;

	//����뾶
	double m_semiMajor;
    //����뾶
	double m_semiMinor;

	//��ת�Ƕ�
	double m_rotAngle;

	//��ʼ�Ƕ�
	double m_startAngle;

	//���ĽǶȣ�������ʾ˳ʱ�룬������ʾ��ʱ��
	double m_centerAngle;

	bool  m_bCounterClock;



};





} // GEOMETRY::geom
} //GEOMETRY







#endif
