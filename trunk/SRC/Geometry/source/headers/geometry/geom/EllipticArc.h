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
*椭圆弧段继承了ISegment，可以作为一个单独的图形使用，也可以作为组成线圈的一部分
*
******************************************************************************/
class EllipticArc: public ISegment
{

public:

	EllipticArc();

	/**
	* 通过椭圆圆心坐标、长短轴以及起始点坐标来构造
	* @param Center 椭圆圆心坐标
	* @param semiMajor 长轴半径
	* @param semiMinor 短轴半径
	* @param rotationAngle 椭圆旋转角度，相对于X轴正方向
	* @param FromPt 椭圆弧的起始点
	* @param ToPt 椭圆弧的终止点
	* @param bCounterClock 椭圆弧是否是逆时针方向 
	*/
	EllipticArc(const Coordinate &Center,double semiMajor,double semiMinor,double rotationAngle,
		 const Coordinate &FromPt,const Coordinate &ToPt,bool bCounterClock);


	virtual ~EllipticArc();
public:


	/******************************************************************
	*实现Geometry的函数
	******************************************************************/
public:

	std::string getGeometryType() const {return "EllipticArc";}; 

	GeometryTypeId getGeometryTypeId() const {return GEOM_ELLIPTICARC;};
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
	*以下为EllipticArc的一些操作
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
	* 得到椭圆长短轴半径
	* @param semiMajor 获得的长轴半径
	* @param semiMinor 获得的短轴半径
	*/
	void GetAxes(double *semiMajor,double *semiMinor) const 
	{ *semiMajor =m_semiMajor;*semiMinor =m_semiMinor;}


	/**
	* 设置椭圆长短轴半径
	* @param semiMajor 长轴半径
	* @param semiMinor 短轴半径
	*/
	void SetAxes(double semiMajor,double semiMinor) 
	{m_semiMajor =semiMajor;m_semiMinor =semiMinor;}


	/**
	* 得到圆弧的中心角度，也就是终止角度减去起始角度
	* @return 弧度单位，范围在-2PI到2PI之间
	*/
	double GetCenterAngle() const{return m_centerAngle;};

	/**
	* 得到旋转角度，旋转角度是椭圆相对于规则椭圆的旋转
	* @return 弧度单位，范围在-2PI到2PI之间
	*/
	double GetRotAngle() const{return m_rotAngle;}

	/**
	* 判断圆弧是否是逆时针
	* @return true为逆时针，false为顺时针
	*/
	bool   IsCounterClock() const;

	/**
	* 判断圆弧是否是一个椭圆
	* @return true为圆，false为椭圆
	*/
	
	virtual bool IsEllipse();

protected:
	//计算起始终止角度
	void ComputeAngle();
protected:
	//椭圆中心坐标
	Coordinate m_CenterPt;

	//长轴半径
	double m_semiMajor;
    //短轴半径
	double m_semiMinor;

	//旋转角度
	double m_rotAngle;

	//起始角度
	double m_startAngle;

	//中心角度，负数表示顺时针，正数表示逆时针
	double m_centerAngle;

	bool  m_bCounterClock;



};





} // GEOMETRY::geom
} //GEOMETRY







#endif
