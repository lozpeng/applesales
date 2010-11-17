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
* 圆形是一种特殊的圆弧
*
******************************************************************************/
class Circle: public CircularArc
{

public:

	Circle();

	/**
	* 通过圆心坐标、半径来构造
	* @param Center 圆心坐标
	* @param radius 半径
	*/
	Circle(const Coordinate &Center,double radius);


	virtual ~Circle();
public:


	/******************************************************************
	*实现Geometry的函数
	******************************************************************/
public:

	std::string getGeometryType() const {return "Circle";}; 

	GeometryTypeId getGeometryTypeId() const {return GEOM_CIRCLE;};
	Geometry* clone() const;

	Dimension::DimensionType getDimension() const {return Dimension::A;}

	///是否需要打断
	bool isScatter() const { return true; }

	//几何体打散
	Geometry* scatter() const;


	bool equalsExact(const Geometry *other, double tolerance=0) const;


	virtual Envelope::AutoPtr computeEnvelopeInternal() const;

	/******************************************************************
	*以下为Circle的一些操作
	******************************************************************/
public:

	/**
	* 判断圆弧是否是一个圆
	* @return true为圆，false为圆弧
	*/
	bool IsCircle() {return true;}

};

} // GEOMETRY::geom
} //GEOMETRY







#endif
