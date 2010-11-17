#include <Geometry/geom/EllipticArc.h>
#include <math.h>
namespace GEOMETRY {
namespace geom { // GEOMETRY::geom


#define EllipticAngleTolerance 0.001

EllipticArc::EllipticArc()
{
	m_semiMajor =m_semiMinor =0.0;
	m_centerAngle =0.0;
	m_startAngle =0.0;
	m_rotAngle =0.0;
}


EllipticArc::EllipticArc(const Coordinate &Center,double semiMajor,double semiMinor,double rotationAngle,
						 const Coordinate &FromPt,const Coordinate &ToPt,bool bCounterClock)
						 :ISegment(FromPt,ToPt)
                         
{
	m_CenterPt =Center;
	
	m_semiMajor =semiMajor;
	m_semiMinor =semiMinor;

	m_rotAngle =rotationAngle;

	m_bCounterClock =bCounterClock;

	//������ʼ����ֹ������
	ComputeAngle();

}

EllipticArc:: ~EllipticArc()
{

}

/******************************************************************
*ʵ��Geometry�ĺ���
******************************************************************/
Geometry* EllipticArc::clone() const
{
	if(m_pFromPt==NULL || m_pToPt==NULL)
	{
		return (Geometry*)(new EllipticArc());
	}
	else
	{
		return (Geometry*)(new EllipticArc(m_CenterPt,m_semiMajor,m_semiMinor,m_rotAngle,*m_pFromPt,*m_pToPt,m_bCounterClock));
	}
}

//�Ƿ���һ����Χ�ڣ�����ͼ�����
bool EllipticArc::equalsExact(const Geometry *other, double tolerance) const
{
	if (!isEquivalentClass(other)) 
	{
		return false;
	}

	if ( isEmpty() ) return other->isEmpty();
	else if ( other->isEmpty() ) return false;

	EllipticArc *pArc =dynamic_cast<EllipticArc*>(const_cast<Geometry*>(other));
	//�Ƚ�Բ������
	if(!equal(m_CenterPt,pArc->GetCenterPoint(), tolerance))
	{
		return false;
	}
	
	return true;

}

Envelope::AutoPtr EllipticArc::computeEnvelopeInternal() const
{
	return Envelope::AutoPtr(new Envelope(m_CenterPt.x-m_semiMajor,
		m_CenterPt.x+m_semiMajor, m_CenterPt.y-m_semiMinor,
		m_CenterPt.y+m_semiMinor));
}

/******************************************************************
*ʵ��ISegment�ĺ���
******************************************************************/
double EllipticArc::Length() const
{
	if(isEmpty())
	{
		return 0.0;
	}

	//���㻡�γ���
	return 0.0;
}

//�õ���������ϵ�
void EllipticArc::CloestLinePoint(const Coordinate &pt, Coordinate &ret) const
{

} 

void EllipticArc::MidPoint(Coordinate &ret) const
{

}

void EllipticArc::SegMove(double dx, double dy)
{
	m_CenterPt.x +=dx;
	m_CenterPt.y +=dy;
}

void EllipticArc::SegRotate(const GEOMETRY::geom::Coordinate &OriginPt, double angle)
{
	if(OriginPt==m_CenterPt)
	{
		//��Բ����ת
		m_rotAngle+=angle;
	}
	else
	{
		//��Բ����ת�����Ƚ�Բ����ת
		m_CenterPt.Rotate(OriginPt,angle);
	}
}

void EllipticArc::SegScale(const GEOMETRY::geom::Coordinate &OriginPt, double dx, double dy)
{
	//����Բ��
	m_CenterPt.Scale(OriginPt,dx,dy);

	//�������������Բ������ʱ��Y������Ϊ����
	if(m_rotAngle!=0.0)
	{
		m_semiMajor*=dy;
		m_semiMinor*=dx;
	}
	else
	{
		m_semiMajor*=dx;
		m_semiMinor*=dy;
	}
}

/******************************************************************
*����Ϊʵ��ITransform�Ľӿ�
******************************************************************/
void EllipticArc::Move(double dx,double dy)
{
	m_CenterPt.x +=dx;
	m_CenterPt.y +=dy;

	this->geometryChangedAction();
}

void EllipticArc::Scale(const Coordinate &OriginPt,double dx,double dy)
{
	//����Բ��
	m_CenterPt.Scale(OriginPt,dx,dy);

	//�������������Բ������ʱ��Y������Ϊ����
	if(m_rotAngle!=0.0)
	{
		m_semiMajor*=dy;
		m_semiMinor*=dx;
	}
	else
	{
		m_semiMajor*=dx;
		m_semiMinor*=dy;
	}

	
}

void EllipticArc::Rotate(const Coordinate &OriginPt,double angle)
{
	if(OriginPt==m_CenterPt)
	{
        //��Բ����ת
        m_rotAngle+=angle;
	}
	else
	{
       //��Բ����ת�����Ƚ�Բ����ת
        m_CenterPt.Rotate(OriginPt,angle);
	}
	
}
/******************************************************************
*ʵ��EllipticArc�ĺ���
******************************************************************/

bool EllipticArc::IsEllipse()
{
	return fabs(fabs(m_centerAngle)-2*M_PI)<=EllipticAngleTolerance;
}

bool EllipticArc::IsCounterClock() const
{
	return m_bCounterClock;

}

void EllipticArc::ComputeAngle()
{
	

}


} // namespace GEOMETRY::geom
} // namespace GEOMETRY