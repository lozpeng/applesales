#include <Geometry/geom/BezierSpline.h>
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/geom/CoordinateArraySequence.h>
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/algorithm/CGAlgorithms.h>

using namespace GEOMETRY::algorithm;

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

BezierSpline::BezierSpline(const std::vector<Coordinate>& knots): Geometry(GeometryFactory::getDefaultInstance())
{
	m_knots.clear();
	m_firstControlPoints.clear();
	m_secondControlPoints.clear();

	if(knots.size()<2)
		return;

	m_knots = knots;

	//
	GetControlPoints();
}

BezierSpline::~BezierSpline()
{
	m_knots.clear();
	m_firstControlPoints.clear();
	m_secondControlPoints.clear();
}

void BezierSpline::GetPolyBezier(std::vector<Coordinate>& polyBezier) const
{
	long lPtCount;

	lPtCount = (m_knots.size()-1)*3+1;
	polyBezier.resize(lPtCount);
	polyBezier[0] = m_knots[0];

	for(int i=1; i<m_knots.size(); i++)
	{
		polyBezier[3*(i-1)+1] = m_firstControlPoints[i-1];
		polyBezier[3*(i-1)+2] = m_secondControlPoints[i-1];
		polyBezier[3*(i-1)+3] = m_knots[i];
	}
}

void BezierSpline::Getknots(std::vector<Coordinate>& knots) const
{
	long lPtCount;

	lPtCount = m_knots.size();
	knots.resize(lPtCount);

	for(int i=0; i<lPtCount; i++)
	{
		knots[i] = m_knots[i];
	}
}

void BezierSpline::GetControlPoints()
{
	int n = m_knots.size()-1;

	if (n == 1)
	{ 
		// Special case: Bezier curve should be a straight line.
		m_firstControlPoints.resize(1);

		// 3P1 = 2P0 + P3
		m_firstControlPoints[0].x = (2 * m_knots[0].x + m_knots[1].x) / 3;
		m_firstControlPoints[0].y = (2 * m_knots[0].y + m_knots[1].y) / 3;

		m_secondControlPoints.resize(1);
		// P2 = 2P1 – P0
		m_secondControlPoints[0].x = 2 * m_firstControlPoints[0].x - m_knots[0].x;
		m_secondControlPoints[0].y = 2 * m_firstControlPoints[0].y - m_knots[0].y;
		return;
	}

	// Calculate first Bezier control points
	// Right hand side vector
	std::vector<double> rhs;
	rhs.resize(n);

	// Set right hand side X values
	for (int i = 1; i < n - 1; ++i)
		rhs[i] = 4 * m_knots[i].x + 2 * m_knots[i + 1].x;

	rhs[0] = m_knots[0].x + 2 * m_knots[1].x;

	rhs[n - 1] = (8 * m_knots[n - 1].x + m_knots[n].x) / 2.0;

	// Get first control points X-values
	std::vector<double> x;
	GetFirstControlPoints(rhs, x);

	// Set right hand side Y values
	for (int i = 1; i < n - 1; ++i)
		rhs[i] = 4 * m_knots[i].y + 2 * m_knots[i + 1].y;

	rhs[0] = m_knots[0].y + 2 * m_knots[1].y;

	rhs[n - 1] = (8 * m_knots[n - 1].y + m_knots[n].y) / 2.0;

	// Get first control points Y-values
	std::vector<double> y;
	GetFirstControlPoints(rhs,y);

	// Fill output arrays.
	m_firstControlPoints.resize(n);
	m_secondControlPoints.resize(n);

	for (int i = 0; i < n; ++i)
	{
		// First control point
		m_firstControlPoints[i].x = x[i];
		m_firstControlPoints[i].y = y[i];

		// Second control point
		if (i < n - 1)
		{
			m_secondControlPoints[i].x = 2 * m_knots[i + 1].x - x[i + 1];
			m_secondControlPoints[i].y = 2 * m_knots[i + 1].y - y[i + 1];
		}
		else
		{
			m_secondControlPoints[i].x = (m_knots[n].x + x[n - 1]) / 2;
			m_secondControlPoints[i].y = (m_knots[n].y + y[n - 1]) / 2;
		}
	}
}

void BezierSpline::GetFirstControlPoints(std::vector<double> rhs, std::vector<double> &slv)
{
	int n = rhs.size();
	std::vector<double> tmp;

	slv.resize(n);
	tmp.resize(n);

	double b = 2.0;
	slv[0] = rhs[0] / b;

	for (int i = 1; i < n; i++) // Decomposition and forward substitution.
	{
		tmp[i] = 1 / b;
		b = (i < n - 1 ? 4.0 : 3.5) - tmp[i];
		slv[i] = (rhs[i] - slv[i - 1]) / b;
	}
	for (int i = 1; i < n; i++)
		slv[n - i - 1] -= tmp[n - i] * slv[n - i]; // Backsubstitution.

}


Geometry* BezierSpline::clone() const
{
	return new BezierSpline(m_knots);
}

//是否在一个误差范围内，两个图形相等
bool BezierSpline::equalsExact(const Geometry *other, double tolerance) const
{
	return true;

}

/******************************************************************************************************
*以下实现了IPointCollection接口
*
******************************************************************************************************/
long BezierSpline::PointCount() const
{
	return (long)getNumPoints();
}


void BezierSpline::AddPoint(GEOMETRY::geom::Coordinate &coord)
{
	m_knots.push_back(coord);

	OnPointChanged();
}

void BezierSpline::InsertPoint(int index, GEOMETRY::geom::Coordinate &newpoint)
{
	if(index<0 || index>=getNumPoints())
	{
		return;
	}

	m_knots.insert(m_knots.begin()+index,newpoint);

	//
	OnPointChanged();

}

void BezierSpline::OnPointChanged()
{
	m_firstControlPoints.clear();
	m_secondControlPoints.clear();

	//
	GetControlPoints();
}

void BezierSpline::ReplacePoint(int index, GEOMETRY::geom::Coordinate &newpoint)
{
	if(index<0 || index>=getNumPoints())
	{
		return;
	}
	m_knots[index] = newpoint;

	OnPointChanged();
}

void BezierSpline::RemovePoint(int index)
{
	if(index<0 || index>=getNumPoints())
	{
		return;
	}
	m_knots.erase(m_knots.begin()+index);

	//删除一个节点时，相应的线段数组也要发生变化
	OnPointChanged();
}

Coordinate BezierSpline::GetPoint(int index)
{
	if(index<0 || index>=getNumPoints())
	{
		return Coordinate();
	}

	return m_knots[index];


}

Envelope::AutoPtr BezierSpline::computeEnvelopeInternal() const
{
	GEOMETRY::geom::Envelope *pEnv =new Envelope();
	double minx,maxx,miny,maxy;

	minx = maxx = m_knots[0].x;
	miny = maxy = m_knots[0].y;

	//
	for(int i=0; i<m_knots.size(); i++)
	{
		if(minx > m_knots[i].x)
			minx = m_knots[i].x;

		if(maxx < m_knots[i].x)
			maxx = m_knots[i].x;

		if(miny > m_knots[i].y)
			miny = m_knots[i].y;

		if(maxy < m_knots[i].y)
			maxy = m_knots[i].y;
	}

	//
	for(int i=0; i<m_firstControlPoints.size(); i++)
	{
		if(minx > m_firstControlPoints[i].x)
			minx = m_firstControlPoints[i].x;

		if(maxx < m_firstControlPoints[i].x)
			maxx = m_firstControlPoints[i].x;

		if(miny > m_firstControlPoints[i].y)
			miny = m_firstControlPoints[i].y;

		if(maxy < m_firstControlPoints[i].y)
			maxy = m_firstControlPoints[i].y;
	}

	//
	for(int i=0; i<m_secondControlPoints.size(); i++)
	{
		if(minx > m_secondControlPoints[i].x)
			minx = m_secondControlPoints[i].x;

		if(maxx < m_secondControlPoints[i].x)
			maxx = m_secondControlPoints[i].x;

		if(miny > m_secondControlPoints[i].y)
			miny = m_secondControlPoints[i].y;

		if(maxy < m_secondControlPoints[i].y)
			maxy = m_secondControlPoints[i].y;
	}

	//
	pEnv->init(minx,maxx,miny,maxy);

	return Envelope::AutoPtr(pEnv);
}

Geometry* BezierSpline::scatter() const
{
	CoordinateArraySequence cds;
	Coordinate cd,p0,p1,p2,p3;
	double t;

	for(int i=0; i<m_firstControlPoints.size(); i++)
	{
		p0 = m_knots[i];
		p1 = m_firstControlPoints[i];
		p2 = m_secondControlPoints[i];
		p3 = m_knots[i+1];

		for(int j=0; j<=10; j++)
		{
			t = j*0.1;
			cd.x = (1-t)*(1-t)*(1-t)*p0.x + 3*(1-t)*(1-t)*t*p1.x + 3*(1-t)*t*t*p2.x + t*t*t*p3.x;
			cd.y = (1-t)*(1-t)*(1-t)*p0.y + 3*(1-t)*(1-t)*t*p1.y + 3*(1-t)*t*t*p2.y + t*t*t*p3.y;

			cds.add(cd);
		}
	}

	LineString* pString = GeometryFactory::getDefaultInstance()->createLineString(cds);

	return (Geometry*)pString;
}

/******************************************************************
*以下为实现ITransform的接口
******************************************************************/
void BezierSpline::Move(double dx,double dy)
{

	for(int i=0; i<m_knots.size(); i++)
	{
		m_knots[i].x += dx;
		m_knots[i].y += dy;
	}

	OnPointChanged();

	geometryChangedAction();
}

void BezierSpline::Rotate(const GEOMETRY::geom::Coordinate &OriginPt, double angle)
{
	for(int i=0; i<m_knots.size(); i++)
	{
		m_knots[i].Rotate(OriginPt,angle);
	}

	OnPointChanged();

	geometryChangedAction();
}
void BezierSpline::Mirror(const Coordinate &p1,const Coordinate &p2)
{
	double a,b,c;
	double x,y;
	CGAlgorithms::LineEquation(p1,p2,a,b,c);

	for(size_t i=0;i<m_knots.size();i++)
	{
		Coordinate &pt =m_knots[i];

		x =pt.x;
		y =pt.y;

		//求对称点
		pt.x=((b*b-a*a)*x-2*a*b*y-2*a*c)/(a*a+b*b); 
		pt.y=((a*a-b*b)*y-2*a*b*x-2*b*c)/(a*a+b*b); 

	}

	OnPointChanged();

	geometryChangedAction();
}

void BezierSpline::Scale(const Coordinate &OriginPt,double dx,double dy)
{
	for(size_t i=0;i<m_knots.size();i++)
	{
		m_knots[i].Scale(OriginPt,dx,dy);
	}

	OnPointChanged();

	geometryChangedAction();
}

/******************************************************************************************************
*以下实现了ISnap接口
*
******************************************************************************************************/
bool BezierSpline::SnapVertex(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plvertexIndex)
{
	long lnum = getNumPoints();
	if(lnum<=0)
	{
		return false;
	}
	Coordinate vertex,temppt;


	double mindis =1e38,distance;

	bool bfind =false;
	for(long i=0;i<lnum;i++)
	{
		vertex =m_knots[i];
		distance =sqrt((vertex.x-pPoint->x)*(vertex.x-pPoint->x) +(vertex.y-pPoint->y)*(vertex.y-pPoint->y));

		if(distance>tolerance)
		{
			continue;
		}
		if(distance<mindis)
		{
			bfind =true;
			mindis = distance;
			temppt =vertex;

			//节点的序号
			*plvertexIndex =i;

		}
	}

	if(!bfind)
	{
		return false;
	}

	*poutPt =temppt;


	*searchDis =mindis;

	*plpartIndex =0;

	return true;
}
}//GEOMETRY::geom

}//GEOMETRY

