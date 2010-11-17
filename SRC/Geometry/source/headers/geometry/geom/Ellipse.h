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
*椭圆是一种特殊的椭圆弧
*
******************************************************************************/
class Ellipse: public EllipticArc
{

public:

	Ellipse();

	/**
	* 通过椭圆外接矩形来构造
	* @param envelope 椭圆外接矩形
	*/
	Ellipse(const Envelope& envelope);


	virtual ~Ellipse();
public:


	/******************************************************************
	*实现Geometry的函数
	******************************************************************/
public:

	std::string getGeometryType() const {return "Ellipse";}; 

	GeometryTypeId getGeometryTypeId() const {return GEOM_ELLIPSE;};
	Geometry* clone() const;

	bool equalsExact(const Geometry *other, double tolerance=0) const;


	virtual Envelope::AutoPtr computeEnvelopeInternal() const;

	///是否需要打断
	bool isScatter() const { return true; }

	//几何体打散
	Geometry* scatter() const;


	/******************************************************************
	*以下为EllipticArc的一些操作
	******************************************************************/
public:

	/**
	* 判断圆弧是否是一个椭圆
	* @return true为圆，false为椭圆
	*/
	bool IsEllipse(){return true;}


};





} // GEOMETRY::geom
} //GEOMETRY







#endif
