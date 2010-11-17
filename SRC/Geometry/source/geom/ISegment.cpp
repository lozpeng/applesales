#include <Geometry/geom/ISegment.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/GeometryFactory.h>
using namespace std;

//using namespace GEOMETRY::operation;

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom


ISegment::ISegment(): Geometry(GeometryFactory::getDefaultInstance())
{
	m_pFromPt =NULL;
	m_pToPt = NULL;
	m_bAutoDestroy =false;
}

ISegment::ISegment(const GEOMETRY::geom::Coordinate &p0, const GEOMETRY::geom::Coordinate &p1) :Geometry(GeometryFactory::getDefaultInstance())
{
    m_pFromPt =new Coordinate();
    
	m_pToPt =new Coordinate();

	*m_pFromPt =p0;
    *m_pToPt = p1;
	m_bAutoDestroy =true;

}

ISegment::ISegment(GEOMETRY::geom::Coordinate *pFromPt, GEOMETRY::geom::Coordinate *pToPt) :Geometry(GeometryFactory::getDefaultInstance())
{
    m_pFromPt =pFromPt;
    m_pToPt = pToPt;
	m_bAutoDestroy =false;
} 

ISegment::~ISegment()
{
    if(m_bAutoDestroy)
	{
		if(m_pFromPt)
			delete m_pFromPt;
		if(m_pToPt)
			delete m_pToPt;
	}
}

/******************************************************************
*实现Geometry的函数
******************************************************************/
const Coordinate* ISegment::getCoordinate() const
{
	if(m_pFromPt!=NULL)
	{
		return m_pFromPt;
	}
	return NULL;
}

 CoordinateSequence* ISegment::getCoordinates() const
{
	 return NULL;
}

bool ISegment::isEmpty() const
{
	if(m_pFromPt==NULL || m_pToPt==NULL )
	{
		return true;
	}
	return false;
}

void ISegment::SetEmpty()
{
	if(m_bAutoDestroy)
	{
		if(m_pFromPt)
			delete m_pFromPt;
		if(m_pToPt)
			delete m_pToPt;

		m_bAutoDestroy=false;
	}
	m_pFromPt =m_pToPt =NULL;
}

/******************************************************************
*以下为ISegment本身的操作
******************************************************************/

//得到起始点坐标
Coordinate ISegment::GetFromPoint() const
{
   
   if(m_pFromPt!=NULL)
   {
	   return *m_pFromPt;
   }
   else
   {
	   return Coordinate();
   }
}

//得到终点坐标
Coordinate ISegment::GetToPoint() const
{
    if(m_pToPt!=NULL)
   {
	   return *m_pToPt;
   }
   else
   {
	   return Coordinate();
   }
}

//设置起始点和终止点
void ISegment::setFromPoint(const Coordinate &pt)
{
    if(m_pFromPt!=NULL)
   {
	   *m_pFromPt =pt;
   }
	else
	{
        m_pFromPt =new Coordinate(pt);
	    m_bAutoDestroy =true;
	}
}

void ISegment::setToPoint(const Coordinate &pt)
{
     if(m_pToPt!=NULL)
   {
	    *m_pToPt = pt;
   }
	 else
	 {
		 m_pToPt =new Coordinate(pt);
		 m_bAutoDestroy =true;
	 }
}

void ISegment::setFromPtr(GEOMETRY::geom::Coordinate *pPt)
{
    if(m_pFromPt && m_bAutoDestroy)
	{
        delete m_pFromPt;
		m_pFromPt =NULL;

	}
	m_pFromPt =pPt;
	m_bAutoDestroy =false;
}

void ISegment::setToPtr(Coordinate *pPt)
{
	if(m_pToPt && m_bAutoDestroy)
	{
		delete m_pToPt;
		m_pToPt =NULL;
	}
	m_pToPt =pPt;
	m_bAutoDestroy =false;
}


} // namespace GEOMETRY::geom
} // namespace GEOMETRY