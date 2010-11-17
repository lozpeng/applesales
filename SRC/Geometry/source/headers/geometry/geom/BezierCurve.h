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
*贝塞尔曲线段继承了ISegment，包括一个起点，一个终点，和两个控制点
*
******************************************************************************/
class BezierCurve: public ISegment
{

	friend class BezierCurve;
public:

	BezierCurve();

	/**
	* 通过四个点来构造一个贝塞尔曲线段
	* @param pt1 起始点
	* @param pt2 控制点1
	* @param pt3 控制点2
	* @param pt4 终止点
	*/
	BezierCurve(const Coordinate &pt1,const Coordinate &pt2,const Coordinate &pt3,const Coordinate &pt4);

	BezierCurve(const BezierCurve &other);


	virtual ~BezierCurve();
public:


	/******************************************************************
	*实现Geometry的函数
	******************************************************************/
public:

	std::string getGeometryType() const {return "BezierCurve";}; 

	GeometryTypeId getGeometryTypeId() const {return GEOM_BEZIERCURVE;};
	Geometry* clone() const;

	bool equalsExact(const Geometry *other, double tolerance=0) const;


	virtual Envelope::AutoPtr computeEnvelopeInternal() const;
	/******************************************************************
	*以下为实现ISegment的接口
	******************************************************************/
public:


	//该线段的长度
	double Length() const;

	void CloestLinePoint(const Coordinate &pt, Coordinate &ret) const;

	//线段的中点
	void MidPoint(Coordinate &ret) const;

	virtual void SegMove(double dx,double dy);

	virtual void SegScale(const Coordinate &OriginPt,double dx,double dy);

	virtual void SegRotate(const Coordinate &OriginPt,double angle);


	/******************************************************************
	*以下为BezierCurve的一些操作
	******************************************************************/
public:

	/**
	* 得到第一个控制点
	* @return 圆心坐标
	*/
	Coordinate GetFirstCtrlPoint() const{return m_FirstCtrlPt;};

	/**
	* 设置第一个控制点
	*/
	void SetFirstCtrlPoint(const Coordinate &coord) {m_FirstCtrlPt =coord;}

	/**
	* 得到第二个控制点
	* @return 圆心坐标
	*/
	Coordinate GetSecondCtrlPoint() const{return m_SecondCtrlPt;};

	/**
	* 设置第二个控制点
	*/
	void SetSecondCtrlPoint(const Coordinate &coord) {m_SecondCtrlPt =coord;}



protected:
	//第一个控制点
	Coordinate m_FirstCtrlPt;

	//第二个控制点
	Coordinate m_SecondCtrlPt;

	

};





} // GEOMETRY::geom
} //GEOMETRY







#endif
