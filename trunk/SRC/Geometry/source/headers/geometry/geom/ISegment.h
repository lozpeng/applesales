/**********************************************************************
 * ISegment为所有分段几何模型的基类，如线段、弧段、贝塞尔曲线
 * 
 *  它包含两个点的引用，起点和终点，而实际的点坐标存储在相应的高级图形的
 *  点数组中，如LineString,LineRing,Polygon
 *   
 *  ISegment提供访问和修改起点和终点的函数，相应也会修改包含该Segment的
 *  高级图形的点
 *
 * 
 * 
 * 
 * 
 *
 **********************************************************************/


#ifndef GEOMETRY_GEOM_ISEGMENT_H
#define GEOMETRY_GEOM_ISEGMENT_H

#include <Geometry/platform.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/CoordinateSequence.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Envelope.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Dimension.h> // for Dimension::DimensionType

#include <Geometry/inline.h>

#include <string>
#include <vector>
#include <memory> // for auto_ptr

namespace GEOMETRY {
namespace geom { 

class Coordinate;  

class ISegment: public Geometry
{
	//ISegment对象并不被外部的函数构建，主要由它的继承对象构建
protected:

	ISegment();
    
	//该构造函数会实例化起点和终点对象，并赋值
	ISegment(const Coordinate &p0,const Coordinate &p1);
    //该构造函数只会将起点和终点的指针地址赋给成员函数，
	//ISegment将只保存起点和终点的引用
	ISegment(Coordinate *pFromPt,Coordinate *pToPt );
public:
     
	//析构函数不释放起点和终点的内存，因为起点和终点保存在高级图形的坐标数组中
	virtual ~ISegment();

/******************************************************************
*实现Geometry的函数
******************************************************************/
public:

	virtual const Coordinate* getCoordinate() const;


    virtual CoordinateSequence* getCoordinates() const;

	virtual size_t getNumPoints() const {return 2;};

	virtual bool isSimple() const {return true;};


    virtual void SetEmpty();

	virtual bool isEmpty() const;

	virtual Dimension::DimensionType getDimension() const {return Dimension::L;}


	virtual Geometry* getBoundary() const{return NULL ;};

	virtual int getBoundaryDimension() const {return 0;};

	virtual void apply_rw(const CoordinateFilter *filter) { }; 
	virtual void apply_ro(CoordinateFilter *filter) const { };

	virtual void normalize() {};
protected:

	virtual Envelope::AutoPtr computeEnvelopeInternal() const {return Envelope::AutoPtr(NULL);}; //Abstract

	virtual int compareToSameClass(const Geometry *geom) const{return 0;}; //Abstract

/******************************************************************
*以下为ISegment本身的操作
******************************************************************/
public:
   //得到起始点和终止点
   Coordinate GetFromPoint() const;

   Coordinate GetToPoint() const;

   //设置起始点和终止点

   void setFromPoint(const Coordinate &pt);

   void setToPoint(const Coordinate &pt);

   //设置起点和终点的指针
   void setFromPtr(Coordinate *pPt);

   void setToPtr(Coordinate  *pPt);

   
   //该段的长度
   virtual double Length() const =0;

   //得到最近的线上点
   virtual void CloestLinePoint(const Coordinate &pt, Coordinate &ret) const=0;

   //线段的中点
   virtual void MidPoint(Coordinate &ret) const =0;

public:

	/******************************************************************
	*特殊的变换函数,由Segment所在的高级图形在ITransform中来调用，
	*用来移动，缩放，旋转Segment除了端点以外独有的参数
	******************************************************************/
	//
	virtual void SegMove(double dx,double dy){}

	virtual void SegMirror(const Coordinate &p1,const Coordinate &p2){}

	virtual void SegScale(const Coordinate &OriginPt,double dx,double dy){}

	virtual void SegRotate(const Coordinate &OriginPt,double angle){}
protected:


protected:
     
	//起点和终点的指针
     Coordinate *m_pFromPt;

     Coordinate *m_pToPt;

	 //是否需要删除起始终止点指针
	 bool m_bAutoDestroy;
    


};





} // GEOMETRY::geom
} //GEOMETRY







#endif
