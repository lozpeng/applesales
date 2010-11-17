#include <Geometry/geom/CircularArc.h>
#include <math.h>
namespace GEOMETRY {
namespace geom { // GEOMETRY::geom


#define CirAngleTolerance 0.001

CircularArc::CircularArc()
{
    m_radius =0.0;
	m_centerAngle =0.0;
	m_startAngle =0.0;
}


CircularArc::CircularArc(const Coordinate &Center,double radius,double startAngle,double centerAngle):
            ISegment(Coordinate(),Coordinate())
{
	m_CenterPt =Center;
    m_radius =radius;
	m_startAngle =startAngle;
	m_centerAngle =centerAngle;

	//计算起始和终止点坐标
    ComputeStartEndPt();

}

CircularArc:: ~CircularArc()
{

}

/******************************************************************
*实现Geometry的函数
******************************************************************/
Geometry* CircularArc::clone() const
{
	if(m_pFromPt==NULL || m_pToPt==NULL)
	{
		return (Geometry*)(new CircularArc());
	}
	else
	{
		return (Geometry*)(new CircularArc(m_CenterPt,m_radius,m_startAngle,m_centerAngle));
	}
}

//是否在一个误差范围内，两个图形相等
bool CircularArc::equalsExact(const Geometry *other, double tolerance) const
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

Envelope::AutoPtr CircularArc::computeEnvelopeInternal() const
{
	return Envelope::AutoPtr(NULL);
}

/******************************************************************
*实现ISegment的函数
******************************************************************/
double CircularArc::Length() const
{
	if(isEmpty())
	{
		return 0.0;
	}

	//计算弧段长度
	return 0.0;
}

//得到最近的线上点
void CircularArc::CloestLinePoint(const Coordinate &pt, Coordinate &ret) const
{
	
} 

void CircularArc::MidPoint(Coordinate &ret) const
{
	
}

void CircularArc::SegMove(double dx, double dy)
{
	m_CenterPt.x +=dx;
	m_CenterPt.y +=dy;
}

void CircularArc::SegRotate(const GEOMETRY::geom::Coordinate &OriginPt, double angle)
{
   m_CenterPt.Rotate(OriginPt,angle);
}

void CircularArc::SegScale(const GEOMETRY::geom::Coordinate &OriginPt, double dx, double dy)
{
	//缩放圆心
	m_CenterPt.Scale(OriginPt,dx,dy);

	if(dx!=1.0)
	{
		m_radius*=dx;
	}
	else
	{
		m_radius*=dy;
	}
}

/******************************************************************
*以下为实现ITransform的接口
******************************************************************/
void CircularArc::Move(double dx,double dy)
{
	m_CenterPt.x +=dx;
	m_CenterPt.y +=dy;

	this->geometryChangedAction();
}

void CircularArc::Scale(const Coordinate &OriginPt,double dx,double dy)
{
	//缩放圆心
    m_CenterPt.Scale(OriginPt,dx,dy);

	if(dx!=1.0)
	{
		m_radius*=dx;
	}
	else
	{
		m_radius*=dy;
	}
}

void CircularArc::Rotate(const GEOMETRY::geom::Coordinate &OriginPt, double angle)
{
     m_CenterPt.Rotate(OriginPt,angle);
}

/******************************************************************
*实现CircularArc的函数
******************************************************************/

bool CircularArc::IsCircle()
{
	return fabs(fabs(m_centerAngle)-2*M_PI)<=CirAngleTolerance;
}

bool CircularArc::IsCounterClock() const
{
	return m_centerAngle>=0.0;

}

void CircularArc::ComputeStartEndPt()
{
	m_pFromPt->x =m_CenterPt.x+cos(m_startAngle)*m_radius;
	m_pFromPt->y =m_CenterPt.y+sin(m_startAngle)*m_radius;

	double endAngle =m_startAngle+m_centerAngle;

	m_pToPt->x =m_CenterPt.x+cos(endAngle)*m_radius;
	m_pToPt->y =m_CenterPt.y+sin(endAngle)*m_radius;


}

void CircularArc::SetStartAngle(double angle)
{
	m_startAngle =angle;
    ComputeStartEndPt();
}

void CircularArc::SetCenterAngle(double angle)
{
	m_centerAngle =angle;
	ComputeStartEndPt();
}

} // namespace GEOMETRY::geom
} // namespace GEOMETRY