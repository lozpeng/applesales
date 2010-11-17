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
*圆形弧段继承了ISegment，可以作为一个单独的图形使用，也可以作为组成线圈的一部分
*
******************************************************************************/
class CircularArc: public ISegment
{

public:

	CircularArc();

	/**
	* 通过圆心坐标、半径以及圆弧的角度来构造
	* @param Center 圆心坐标
	* @param radius 半径
	* @param startAngle 起始角度，相对于X坐标
	* @param centerAngle 圆弧转过的角度
	*/
	CircularArc(const Coordinate &Center,double radius,double startAngle,double centerAngle);
	

	virtual ~CircularArc();
public:


	/******************************************************************
	*实现Geometry的函数
	******************************************************************/
public:

	std::string getGeometryType() const {return "CircularArc";}; 

	GeometryTypeId getGeometryTypeId() const {return GEOM_CIRCULARARC;};
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
	*以下为实现ITransform的接口
	******************************************************************/
public:
	void Move(double dx,double dy);

	void Scale(const Coordinate &OriginPt,double dx,double dy);

	void Rotate(const Coordinate &OriginPt,double angle); 

	/******************************************************************
	*以下为Circle的一些操作
	******************************************************************/
public:
	
	/**
	* 得到圆弧所在圆心点的坐标
	* @return 圆心坐标
	*/
	Coordinate GetCenterPoint() const{return m_CenterPt;};


	/**
	* 设置圆弧所在圆心点的坐标
	*/
	void SetCenterPoint(const Coordinate &coord) {m_CenterPt =coord;}


	/**
	* 得到圆弧半径
	* @return 圆的半径
	*/
	double GetRadius() const {return m_radius;};


	/**
	* 设置圆弧半径
	*/
	void   SetRadius(double r){m_radius =r;};


	/**
	* 得到圆弧的中心角度，也就是终止角度减去起始角度
	* @return 弧度单位，范围在-2PI到2PI之间
	*/
	double GetCenterAngle() const{return m_centerAngle;};

	void   SetCenterAngle(double angle);

	double GetStartAngle() const {return m_startAngle;}

	void   SetStartAngle(double angle);

	/**
	* 判断圆弧是否是逆时针
	* @return true为逆时针，false为顺时针
	*/
	bool   IsCounterClock() const;

	/**
	* 判断圆弧是否是一个圆
	* @return true为圆，false为圆弧
	*/
	virtual bool IsCircle();

private:
	//根据已知的角度，计算起始点和终止点坐标
	void ComputeStartEndPt();
protected:
	//圆心坐标
    Coordinate m_CenterPt;

	//圆弧半径
	double m_radius;

	double m_startAngle;

	//中心角度，负数表示顺时针，正数表示逆时针
	double m_centerAngle;



};





} // GEOMETRY::geom
} //GEOMETRY







#endif
