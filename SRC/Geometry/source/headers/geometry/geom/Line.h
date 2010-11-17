#ifndef GEOMETRY_GEOM_LINE_H
#define GEOMETRY_GEOM_LINE_H

#include <Geometry/platform.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/CoordinateSequence.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Envelope.h> // for proper use of auto_ptr<>
#include <Geometry/geom/Dimension.h> // for Dimension::DimensionType
#include <Geometry/geom/ISegment.h>


#include <string>
#include <vector>
#include <memory> // for auto_ptr

namespace GEOMETRY {
namespace geom { 

class Coordinate;  

/******************************************************************************
*线段继承了ISegment，为低级图形，它是组成线、线环、多边形等高级图形的元素
*
******************************************************************************/
class Line: public ISegment
{
	
public:

	Line();
    
	//该构造函数会实例化起点和终点对象，并赋值
	Line(const Coordinate &p0,const Coordinate &p1);

	Line(Coordinate *pFromPt,Coordinate *pToPt );

	//析构函数不释放起点和终点的内存，因为起点和终点保存在高级图形的坐标数组中
	virtual ~Line();
public:
     
	

/******************************************************************
*实现Geometry的函数
******************************************************************/
public:

     std::string getGeometryType() const {return "Line";}; 

	 GeometryTypeId getGeometryTypeId() const {return GEOM_LINE;};
	 Geometry* clone() const;

	 bool equalsExact(const Geometry *other, double tolerance=0) const;


protected:



/******************************************************************
*以下为实现ISegment的接口
******************************************************************/
public:

   
   //该线段的长度
    double Length() const;

    void CloestLinePoint(const Coordinate &pt, Coordinate &ret) const;

		//线段的中点
    void MidPoint(Coordinate &ret) const;

/******************************************************************
*以下为Line的一些操作
******************************************************************/
public:

	//判断点的垂足相对于线段的位置
	double projectionFactor(const Coordinate& p) const;

};





} // GEOMETRY::geom
} //GEOMETRY







#endif
