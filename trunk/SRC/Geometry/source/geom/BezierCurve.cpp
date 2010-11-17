#include <Geometry/geom/BezierCurve.h>
#include <math.h>
namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

BezierCurve::BezierCurve()
{

}

BezierCurve::BezierCurve(const GEOMETRY::geom::Coordinate &pt1, const GEOMETRY::geom::Coordinate &pt2, const GEOMETRY::geom::Coordinate &pt3, const GEOMETRY::geom::Coordinate &pt4)
                :ISegment(pt1,pt4)
{
    m_FirstCtrlPt =pt2;
	m_SecondCtrlPt =pt3;
}

BezierCurve::BezierCurve(const GEOMETRY::geom::BezierCurve &other):ISegment(other.GetFromPoint(),other.GetToPoint())
{
   
	m_FirstCtrlPt =other.GetFirstCtrlPoint();
	m_SecondCtrlPt =other.GetSecondCtrlPoint();
}

BezierCurve::~BezierCurve()
{

}

/******************************************************************
*ʵ��Geometry�ĺ���
******************************************************************/
Geometry* BezierCurve::clone() const
{
	
	return (Geometry*)(new BezierCurve(*this));
	
}

//�Ƿ���һ����Χ�ڣ�����ͼ�����
bool BezierCurve::equalsExact(const Geometry *other, double tolerance) const
{
	if (!isEquivalentClass(other)) 
	{
		return false;
	}

	BezierCurve *pother =(BezierCurve*)other;
	//����������������û�ж���
	if(m_pFromPt==NULL || m_pToPt==NULL)
	{
        return (pother->m_pFromPt==NULL || pother->m_pToPt==NULL);
	}
	else if(pother->m_pFromPt==NULL || pother->m_pToPt==NULL)
	{
		return false;
	}
    
	return (*m_pFromPt==*(pother->m_pFromPt))
		    &&(*m_pToPt==*(pother->m_pToPt))
			&&(m_FirstCtrlPt ==pother->m_FirstCtrlPt)
			&&(m_SecondCtrlPt ==pother->m_SecondCtrlPt);
	


}

Envelope::AutoPtr BezierCurve::computeEnvelopeInternal() const
{
	if(m_pFromPt==NULL || m_pToPt==NULL)
	{
		return Envelope::AutoPtr(NULL);
	}

	GEOMETRY::geom::Envelope *pEnv =new Envelope();
	double minx,maxx,miny,maxy;

	minx = maxx = m_pFromPt->x;
	miny = maxy = m_pFromPt->y;

	//�Ƚϵ�һ����
	
	if(minx > m_pToPt->x)
		minx =  m_pToPt->x;

	if(maxx <  m_pToPt->x)
		maxx =  m_pToPt->x;

	if(miny >  m_pToPt->y)
		miny =m_pToPt->y;

	if(maxy < m_pToPt->y)
		maxy =m_pToPt->y;
	

	//�Ƚϵڶ�����
	
	if(minx > m_FirstCtrlPt.x)
		minx = m_FirstCtrlPt.x;

	if(maxx < m_FirstCtrlPt.x)
		maxx = m_FirstCtrlPt.x;

	if(miny > m_FirstCtrlPt.y)
		miny = m_FirstCtrlPt.y;

	if(maxy < m_FirstCtrlPt.y)
		maxy = m_FirstCtrlPt.y;

	//�Ƚϵ�������
	if(minx > m_SecondCtrlPt.x)
		minx = m_SecondCtrlPt.x;

	if(maxx < m_SecondCtrlPt.x)
		maxx = m_SecondCtrlPt.x;

	if(miny > m_SecondCtrlPt.y)
		miny = m_SecondCtrlPt.y;

	if(maxy < m_SecondCtrlPt.y)
		maxy = m_SecondCtrlPt.y;

	//
	pEnv->init(minx,maxx,miny,maxy);

	return Envelope::AutoPtr(pEnv);
}

/******************************************************************
*ʵ��ISegment�ĺ���
******************************************************************/
double BezierCurve::Length() const
{
	if(isEmpty())
	{
		return 0.0;
	}

	//���㻡�γ���
	return 0.0;
}

//�õ���������ϵ�
void BezierCurve::CloestLinePoint(const Coordinate &pt, Coordinate &ret) const
{

} 

void BezierCurve::MidPoint(Coordinate &ret) const
{

}

void BezierCurve::SegMove(double dx, double dy)
{
	m_FirstCtrlPt.x +=dx;
	m_FirstCtrlPt.y +=dy;
	m_SecondCtrlPt.x +=dx;
	m_SecondCtrlPt.y +=dy;
}

void BezierCurve::SegRotate(const GEOMETRY::geom::Coordinate &OriginPt, double angle)
{
	m_FirstCtrlPt.Rotate(OriginPt,angle);

    m_SecondCtrlPt.Rotate(OriginPt,angle);
}

void BezierCurve::SegScale(const GEOMETRY::geom::Coordinate &OriginPt, double dx, double dy)
{
	
	m_FirstCtrlPt.Scale(OriginPt,dx,dy);

	m_SecondCtrlPt.Scale(OriginPt,dx,dy);

	
}




}//GEOMETRY::geom
}

