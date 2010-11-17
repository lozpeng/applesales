#include <Geometry/geom/Circle.h>
#include <math.h>
#include <Geometry/geom/CoordinateArraySequence.h>
#include <Geometry/geom/GeometryFactory.h>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom


#define CirAngleTolerance 0.001

Circle::Circle()
{
	m_radius =0.0;
	m_centerAngle =0.0;
	m_startAngle =0.0;
}


Circle::Circle(const Coordinate &Center,double radius) :CircularArc(Center,radius,0.0,2*M_PI)
{
   
}

Circle:: ~Circle()
{

}

/******************************************************************
*实现Geometry的函数
******************************************************************/
Geometry* Circle::clone() const
{
	return new Circle(m_CenterPt,m_radius);
}

//是否在一个误差范围内，两个图形相等
bool Circle::equalsExact(const Geometry *other, double tolerance) const
{
	if (!isEquivalentClass(other)) 
	{
		return false;
	}

	if ( isEmpty() ) return other->isEmpty();
	else if ( other->isEmpty() ) return false;

	CircularArc *pArc =dynamic_cast<CircularArc*>(const_cast<Geometry*>(other));
	//比较圆心坐标
	if(!equal(m_CenterPt,pArc->GetCenterPoint(), tolerance))
	{
		return false;
	}
	//比较半径
	if(fabs(m_radius-pArc->GetRadius())>tolerance)
	{
		return false;
	}


	return true;

}

Envelope::AutoPtr Circle::computeEnvelopeInternal() const
{
	Envelope *pEnv =new Envelope();

	pEnv->init(m_CenterPt.x-m_radius,m_CenterPt.x+m_radius,m_CenterPt.y-m_radius,m_CenterPt.y+m_radius);

	return Envelope::AutoPtr(pEnv);
}

Geometry* Circle::scatter() const
{

	CoordinateArraySequence cds;
	Coordinate cd;

	for(int i=0; i<360; i++)
	{
		cd.x = m_CenterPt.x + m_radius*cos(i/180.0*M_PI);
		cd.y = m_CenterPt.y + m_radius*sin(i/180.0*M_PI);
		cds.add(cd);
	}
	cds.add(cds[0]);

	LinearRing* pRing = (GeometryFactory::getDefaultInstance()->createLinearRing(cds));
	Polygon* pPolygon = GeometryFactory::getDefaultInstance()->createPolygon(pRing, NULL);

	return (Geometry*)pPolygon;

}

} // namespace GEOMETRY::geom

} // namespace GEOMETRY