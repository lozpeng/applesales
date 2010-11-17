#include <Geometry/geom/Line.h>
#include <Geometry/geom/Coordinate.h>

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

Line::Line()
{

}
    
	
Line::Line(Coordinate *pFromPt,Coordinate *pToPt ):
         ISegment(pFromPt,pToPt)
{

}

//该构造函数会实例化起点和终点对象，并赋值
Line::Line(const Coordinate &p0,const Coordinate &p1):
         ISegment(p0,p1)
{

}


//析构函数不释放起点和终点的内存，因为起点和终点保存在高级图形的坐标数组中
Line:: ~Line()
{

}

/******************************************************************
*实现Geometry的函数
******************************************************************/
Geometry* Line::clone() const
{
	if(m_pFromPt==NULL || m_pToPt==NULL)
	{
		return (Geometry*)(new Line());
	}
	else
	{
       return (Geometry*)(new Line(*m_pFromPt,*m_pToPt));
	}
}

//是否在一个误差范围内，两个图形相等
bool Line::equalsExact(const Geometry *other, double tolerance) const
{
    if (!isEquivalentClass(other)) 
	{
		return false;
	}

	if ( isEmpty() ) return other->isEmpty();
	else if ( other->isEmpty() ) return false;

	Coordinate frompt =((Line*)other)->GetFromPoint();
    
	Coordinate topt =((Line*)other)->GetToPoint();

	return equal(*m_pFromPt,frompt, tolerance) && equal(*m_pToPt,topt, tolerance);

}

/******************************************************************
*实现ISegment的函数
******************************************************************/
double Line::Length() const
{
	if(isEmpty())
	{
		return 0.0;
	}

	return m_pFromPt->distance(*m_pToPt);
}

//得到最近的线上点
void Line::CloestLinePoint(const Coordinate &pt, Coordinate &ret) const
{
    double factor=projectionFactor(pt);

	//如果该点在线段中间
	if (factor>0 && factor<1) {
	
		ret.x =m_pFromPt->x +factor*(m_pToPt->x-m_pFromPt->x);
		ret.y = m_pFromPt->y +factor*(m_pToPt->y-m_pFromPt->y);
		return;
	}
	double dist0=m_pFromPt->distance(pt);
	double dist1=m_pToPt->distance(pt);
	if (dist0<dist1)
	{
		ret=*m_pFromPt;
		return;
	}
	ret=*m_pToPt;
} 

void Line::MidPoint(Coordinate &ret) const
{
	ret.x =(m_pFromPt->x +m_pToPt->x)*0.5;
	ret.y = (m_pFromPt->y +m_pToPt->y)*0.5;
}

/******************************************************************
*实现Line的函数
******************************************************************/


//点的垂足相对于线的位置，如果返回结果小于0，则点在线的反向延长线上，
// 大于1，在线的延长线上，0和1之间在线上
double Line::projectionFactor(const GEOMETRY::geom::Coordinate &p) const
{
	if(*m_pFromPt == *m_pToPt) return 0.0;
    if (p==(*m_pFromPt)) return 0.0;
	if (p==(*m_pToPt)) return 1.0;
    // Otherwise, use comp.graphics.algorithms Frequently Asked Questions method
    /*(1)     	      AC dot AB
                   r = ---------
                         ||AB||^2
                r has the following meaning:
                r=0 P = A
                r=1 P = B
                r<0 P is on the backward extension of AB
                r>1 P is on the forward extension of AB
                0<r<1 P is interior to AB
        */
	double dx=m_pToPt->x-m_pFromPt->x;
	double dy=m_pToPt->y-m_pFromPt->y;
	double len2=dx*dx+dy*dy;
	double r=((p.x-m_pFromPt->x)*dx+(p.y-m_pFromPt->y)*dy)/len2;
	return r;
}



} // namespace GEOMETRY::geom
} // namespace GEOMETRY