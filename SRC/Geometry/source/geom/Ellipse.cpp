#include <Geometry/geom/Ellipse.h>
#include <math.h>
#include <Geometry/geom/CoordinateArraySequence.h>
#include <Geometry/geom/GeometryFactory.h>
namespace GEOMETRY {
namespace geom { // GEOMETRY::geom


#define EllipticAngleTolerance 0.000001

#define EQ( dblX, dblY ) (fabs(dblX-dblY)<=(1e-9))

Ellipse::Ellipse()
{

}


Ellipse::Ellipse(const Envelope& envelop)

{
	Coordinate center;
	envelop.centre(center);
	double semiMajor =envelop.getWidth()/2;
	double semiMinor =envelop.getHeight()/2;
	double rotangle =(semiMajor<semiMinor)? M_PI/2 : 0.0;
	Coordinate FromPt,ToPt;
	if(semiMajor<semiMinor)
	{
		double temp =semiMajor;
		semiMajor =semiMinor;
		semiMinor =temp;
	}
	FromPt.x =envelop.getMaxX();
	FromPt.y =center.y;
	ToPt =FromPt;

	//EllipticArc::EllipticArc(center,semiMajor,semiMinor,rotangle,FromPt,ToPt,true);
	m_CenterPt =center;

	m_semiMajor =semiMajor;
	m_semiMinor =semiMinor;

	m_rotAngle =rotangle;

	m_bCounterClock =true;

	//������ʼ����ֹ������
	ComputeAngle();

}

Ellipse:: ~Ellipse()
{

}

/******************************************************************
*ʵ��Geometry�ĺ���
******************************************************************/
Geometry* Ellipse::clone() const
{
	return new Ellipse(*getEnvelopeInternal());
}

//�Ƿ���һ����Χ�ڣ�����ͼ�����
bool Ellipse::equalsExact(const Geometry *other, double tolerance) const
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

Envelope::AutoPtr Ellipse::computeEnvelopeInternal() const
{
	//�ж��Ƿ������Բ
	return Envelope::AutoPtr(new Envelope(m_CenterPt.x-m_semiMajor,
		m_CenterPt.x+m_semiMajor, m_CenterPt.y-m_semiMinor,
		m_CenterPt.y+m_semiMinor));
}

Geometry* Ellipse::scatter() const
{
	//�����Բ
	

	long lNumPoints=360;


	double angle;
	double dblDst;
	double x, y;
	CoordinateArraySequence *cds =new CoordinateArraySequence();
	Coordinate cd;

	for (long l = 0; l < lNumPoints-1; l++)
	{
		 angle = M_PI*2*l/lNumPoints;
		 dblDst = 0;
		
		 //Y���ϵĵ�
		if (EQ(angle,M_PI/2.0))
		{
			x = 0.0;
			y = m_semiMinor;
		}
		else if (EQ(angle, M_PI))
		{
			x = -m_semiMajor;
			y = 0.0;
		}
		else if (EQ(angle, 0.0))
		{
			x = m_semiMajor;
			y = 0.0;
		}
		else if (EQ(angle, M_PI*1.5))
		{
			x = 0.0;
			y = -m_semiMinor;
		}
		else
		{
			x = fabs(sqrt( 1.0/( (tan(angle)*tan(angle))/(m_semiMinor*m_semiMinor) + (1.0/(m_semiMajor*m_semiMajor)) )));
			y = fabs( tan(angle)*x );
			if (angle > M_PI/2.0 && angle < M_PI*3.0/2.0)
				x = -x;
			if (angle > M_PI && angle < M_PI*2.0)
				y = -y;
		}
		dblDst = sqrt(x*x+y*y);

		//������Բ����ת
		cd.x = dblDst*cos(m_rotAngle+angle)+m_CenterPt.x;
		cd.y = dblDst*sin(m_rotAngle+angle)+m_CenterPt.y;

		cds->add(cd);

		
	}
	cds->add((*cds)[0]);

	LinearRing* pRing = (GeometryFactory::getDefaultInstance()->createLinearRing(cds));
	Polygon* pPolygon = GeometryFactory::getDefaultInstance()->createPolygon(pRing, NULL);

	return (Geometry*)pPolygon;
	
}

} // namespace GEOMETRY::geom
} // namespace GEOMETRY