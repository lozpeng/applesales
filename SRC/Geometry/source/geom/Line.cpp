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

//�ù��캯����ʵ���������յ���󣬲���ֵ
Line::Line(const Coordinate &p0,const Coordinate &p1):
         ISegment(p0,p1)
{

}


//�����������ͷ������յ���ڴ棬��Ϊ�����յ㱣���ڸ߼�ͼ�ε�����������
Line:: ~Line()
{

}

/******************************************************************
*ʵ��Geometry�ĺ���
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

//�Ƿ���һ����Χ�ڣ�����ͼ�����
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
*ʵ��ISegment�ĺ���
******************************************************************/
double Line::Length() const
{
	if(isEmpty())
	{
		return 0.0;
	}

	return m_pFromPt->distance(*m_pToPt);
}

//�õ���������ϵ�
void Line::CloestLinePoint(const Coordinate &pt, Coordinate &ret) const
{
    double factor=projectionFactor(pt);

	//����õ����߶��м�
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
*ʵ��Line�ĺ���
******************************************************************/


//��Ĵ���������ߵ�λ�ã�������ؽ��С��0��������ߵķ����ӳ����ϣ�
// ����1�����ߵ��ӳ����ϣ�0��1֮��������
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