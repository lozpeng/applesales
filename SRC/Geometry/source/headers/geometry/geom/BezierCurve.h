#ifndef GEOMETRY_GEOM_BEZIERCURVE_H
#define GEOMETRY_GEOM_BEZIERCURVE_H

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
*���������߶μ̳���ISegment������һ����㣬һ���յ㣬���������Ƶ�
*
******************************************************************************/
class BezierCurve: public ISegment
{

	friend class BezierCurve;
public:

	BezierCurve();

	/**
	* ͨ���ĸ���������һ�����������߶�
	* @param pt1 ��ʼ��
	* @param pt2 ���Ƶ�1
	* @param pt3 ���Ƶ�2
	* @param pt4 ��ֹ��
	*/
	BezierCurve(const Coordinate &pt1,const Coordinate &pt2,const Coordinate &pt3,const Coordinate &pt4);

	BezierCurve(const BezierCurve &other);


	virtual ~BezierCurve();
public:


	/******************************************************************
	*ʵ��Geometry�ĺ���
	******************************************************************/
public:

	std::string getGeometryType() const {return "BezierCurve";}; 

	GeometryTypeId getGeometryTypeId() const {return GEOM_BEZIERCURVE;};
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
	*����ΪBezierCurve��һЩ����
	******************************************************************/
public:

	/**
	* �õ���һ�����Ƶ�
	* @return Բ������
	*/
	Coordinate GetFirstCtrlPoint() const{return m_FirstCtrlPt;};

	/**
	* ���õ�һ�����Ƶ�
	*/
	void SetFirstCtrlPoint(const Coordinate &coord) {m_FirstCtrlPt =coord;}

	/**
	* �õ��ڶ������Ƶ�
	* @return Բ������
	*/
	Coordinate GetSecondCtrlPoint() const{return m_SecondCtrlPt;};

	/**
	* ���õڶ������Ƶ�
	*/
	void SetSecondCtrlPoint(const Coordinate &coord) {m_SecondCtrlPt =coord;}



protected:
	//��һ�����Ƶ�
	Coordinate m_FirstCtrlPt;

	//�ڶ������Ƶ�
	Coordinate m_SecondCtrlPt;

	

};





} // GEOMETRY::geom
} //GEOMETRY







#endif
