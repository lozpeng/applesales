/**********************************************************************
 * $Id: LineString.cpp 2091 2007-12-21 22:49:03Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2005-2006 Refractions Research Inc.
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#include <Geometry/util/IllegalArgumentException.h> 
#include <Geometry/algorithm/CGAlgorithms.h>
#include <Geometry/operation/IsSimpleOp.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/CoordinateSequenceFactory.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/CoordinateFilter.h>
#include <Geometry/geom/Dimension.h>
#include <Geometry/geom/GeometryFilter.h>
#include <Geometry/geom/GeometryComponentFilter.h>
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/geom/LineString.h>
#include <Geometry/geom/Point.h>
#include <Geometry/geom/MultiPoint.h> // for getBoundary
#include <Geometry/geom/Envelope.h>
#include <Geometry/geom/Line.h>

#include <algorithm>
#include <typeinfo>
#include <memory>
#include <cassert>

using namespace std;
using namespace GEOMETRY::algorithm;

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

/*protected*/
LineString::LineString(const LineString &ls)
	:
	Geometry(ls.getFactory()),
	points(ls.points->clone())
{
	//拷贝m_segments
	if(ls.SegmentCount()>0)
	{
	   m_Segments.reserve(ls.m_Segments.size());

	   ISegment *pSeg =NULL;
	   
	   for(int i=0;i<ls.m_Segments.size();i++)
	   {
		   pSeg =dynamic_cast<ISegment*>(ls.m_Segments[i]->clone());
		 
		   pSeg->ISegment::SetEmpty();

		   pSeg->setFromPtr(points->GetPtPointer(i));

		   pSeg->setToPtr(points->GetPtPointer(i+1));
           
		   m_Segments.push_back(pSeg);

	   }

	}

	//设置是否有Z或M值
	this->SetbZ(ls.HasZ());
	this->SetbM(ls.HasM());
}

LineString*
LineString::reverse() const
{
	assert(points.get());
	CoordinateSequence* seq = points->clone();
	CoordinateSequence::reverse(seq);
	assert(getFactory());
	return getFactory()->createLineString(seq);
}


/*private*/
void
LineString::validateConstruction()
{
	if (points.get()==NULL)
	{
		points.reset(getFactory()->getCoordinateSequenceFactory()->create(NULL));
		return;
	}

	if (points->size()==1)
	{
		throw util::IllegalArgumentException("point array must contain 0 or >1 elements\n");
	}
    //构造m_segments
	if(points->size()>1)
	{
	   
       
	   Line *pline =NULL;
	   //用点来构造segment，默认类型为Line
	   for(int i=0;i<points->size()-1;i++)
	   {
		   pline =new Line(points->GetPtPointer(i),points->GetPtPointer(i+1));
  
		   m_Segments.push_back(pline);

	   }

	}

}

/*protected*/
LineString::LineString(CoordinateSequence *newCoords,
		const GeometryFactory *factory)
	:
	Geometry(factory),
	points(newCoords)
{
	validateConstruction();
}

/*public*/
LineString::LineString(CoordinateSequence::AutoPtr newCoords,
		const GeometryFactory *factory)
	:
	Geometry(factory),
	points(newCoords)
{
	validateConstruction();
}


LineString::~LineString()
{
	//delete points;
}

CoordinateSequence*
LineString::getCoordinates() const
{
	assert(points.get());
	return points->clone();
	//return points;
}

const CoordinateSequence*
LineString::getCoordinatesRO() const
{
	assert(0 != points.get());
	return points.get();
}

const Coordinate&
LineString::getCoordinateN(int n) const
{
	assert(points.get());
	return points->getAt(n);
}

Dimension::DimensionType
LineString::getDimension() const
{
	return Dimension::L; // line
}

int
LineString::getBoundaryDimension() const
{
	if (isClosed()) {
		return Dimension::False;
	}
	return 0;
}

bool
LineString::isEmpty() const
{
	assert(points.get());
	return points->getSize()==0;
}

size_t
LineString::getNumPoints() const
{
	assert(points.get());
	return points->getSize();
}

Point*
LineString::getPointN(size_t n) const
{
	assert(getFactory());
	assert(points.get());
	return getFactory()->createPoint(points->getAt(n));
}

Point*
LineString::getStartPoint() const
{
	if (isEmpty()) {
		return NULL;
		//return new Point(NULL,NULL);
	}
	return getPointN(0);
}

Point*
LineString::getEndPoint() const
{
	if (isEmpty()) {
		return NULL;
		//return new Point(NULL,NULL);
	}
	return getPointN(getNumPoints() - 1);
}

bool
LineString::isClosed() const
{
	if (isEmpty()) {
		return false;
	}
	return getCoordinateN(0).equals2D(getCoordinateN(getNumPoints()-1));
}

bool
LineString::isRing() const
{
	return isClosed() && isSimple();
}

string
LineString::getGeometryType() const
{
	return "LineString";
}

bool
LineString::isSimple() const
{
	operation::IsSimpleOp iso;
	return iso.isSimple(this); 
}

Geometry*
LineString::getBoundary() const
{
	if (isEmpty()) {
		return getFactory()->createEmptyGeometry();
	}
	if (isClosed()) {
		return getFactory()->createMultiPoint();
	}
	vector<Geometry*> *pts=new vector<Geometry*>();
	pts->push_back(getStartPoint());
	pts->push_back(getEndPoint());
	MultiPoint *mp = getFactory()->createMultiPoint(pts);
	return mp;
}

bool
LineString::isCoordinate(Coordinate& pt) const
{
	assert(points.get());
	int npts=points->getSize();
	for (int i = 0; i<npts; i++) {
		if (points->getAt(i)==pt) {
			return true;
		}
	}
	return false;
}

/*protected*/
Envelope::AutoPtr
LineString::computeEnvelopeInternal() const
{
	if (isEmpty()) {
		// We don't return NULL here
		// as it would indicate "unknown"
		// envelope. In this case we
		// *know* the envelope is EMPTY.
		return Envelope::AutoPtr(new Envelope());
	}

	assert(points.get());
	const Coordinate& c=points->getAt(0);
	double minx = c.x;
	double miny = c.y;
	double maxx = c.x;
	double maxy = c.y;
	int npts=points->getSize();
	for (int i=1; i<npts; i++) {
		const Coordinate &c=points->getAt(i);
		minx = minx < c.x ? minx : c.x;
		maxx = maxx > c.x ? maxx : c.x;
		miny = miny < c.y ? miny : c.y;
		maxy = maxy > c.y ? maxy : c.y;
	}

	Envelope *pEnv =new Envelope(minx, maxx, miny, maxy);
	//判断是否包含弧段
	for(size_t i=0;i<m_Segments.size();i++)
	{
		if(m_Segments[i]->getGeometryTypeId()!=GEOM_LINE)
		{
			//边界扩展以包含这个弧段的边界
			pEnv->expandToInclude(m_Segments[i]->getEnvelopeInternal());
		}
	}	


	// caller expects a newly allocated Envelope.
	// this function won't be called twice, unless
	// cached Envelope is invalidated (set to NULL)
	return Envelope::AutoPtr(pEnv);
}

bool
LineString::equalsExact(const Geometry *other, double tolerance) const
{
	if (!isEquivalentClass(other)) {
		return false;
	}

	const LineString *otherLineString=dynamic_cast<const LineString*>(other);
	assert(otherLineString);
	size_t npts=points->getSize();
	if (npts!=otherLineString->points->getSize()) {
		return false;
	}
	for (size_t i=0; i<npts; ++i) {
		if (!equal(points->getAt(i),otherLineString->points->getAt(i),tolerance)) {
			return false;
		}
	}
	return true;
}

void
LineString::apply_rw(const CoordinateFilter *filter)
{
	assert(points.get());
	points->apply_rw(filter);
}

void
LineString::apply_ro(CoordinateFilter *filter) const
{
	assert(points.get());
	points->apply_ro(filter);
}

void LineString::apply_rw(GeometryFilter *filter)
{
	assert(filter);
	filter->filter_rw(this);
}

void LineString::apply_ro(GeometryFilter *filter) const
{
	assert(filter);
	filter->filter_ro(this);
}

/*public*/
void
LineString::normalize()
{
	assert(points.get());
	int npts=points->getSize();
	int n=npts/2;
	for (int i=0; i<n; i++) {
		int j = npts - 1 - i;
		if (!(points->getAt(i)==points->getAt(j))) {
			if (points->getAt(i).compareTo(points->getAt(j)) > 0) {
				CoordinateSequence::reverse(points.get());
			}
			return;
		}
	}
}

int
LineString::compareToSameClass(const Geometry *ls) const
{
	assert(dynamic_cast<const LineString*>(ls));
	const LineString *line=static_cast<const LineString*>(ls);
	// MD - optimized implementation
	int mynpts=points->getSize();
	int othnpts=line->points->getSize();
	if ( mynpts > othnpts ) return 1;
	if ( mynpts < othnpts ) return -1;
	for (int i=0; i<mynpts; i++)
	{
		int cmp=points->getAt(i).compareTo(line->points->getAt(i));
		if (cmp) return cmp;
	}
	return 0;
}

const Coordinate*
LineString::getCoordinate() const
{
	if (isEmpty()) return NULL; 
	return &(points->getAt(0));
}

double
LineString::getLength() const
{
	return CGAlgorithms::length(points.get());
}

void
LineString::apply_rw(GeometryComponentFilter *filter)
{
	assert(filter);
	filter->filter_rw(this);
}

void
LineString::apply_ro(GeometryComponentFilter *filter) const
{
	assert(filter);
	filter->filter_ro(this);
}

GeometryTypeId
LineString::getGeometryTypeId() const
{
	return GEOS_LINESTRING;
}

void LineString::SetEmpty()
{
	points->ClearAll();
	//清空SegmentCollection
	for(size_t i=0;i<m_Segments.size();i++)
	{
		delete m_Segments[i];
	}
	m_Segments.clear();
}

/******************************************************************************************************
*以下实现了ISnap接口
*
******************************************************************************************************/
bool LineString::SnapVertex(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plvertexIndex)
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
		vertex =points->getAt(i);
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

//捕捉线上点
bool LineString::SnapEdgePoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plSegIndex)
{
	long lnum = this->SegmentCount();
	if(lnum<=0)
	{
		return false;
	}
	Coordinate ret,temppt;


	double mindis =1e38,distance;
    
	bool bfind =false;
    for(long i=0;i<lnum;i++)
	{
		m_Segments[i]->CloestLinePoint(*pPoint,ret);
		distance =sqrt((ret.x-pPoint->x)*(ret.x-pPoint->x) +(ret.y-pPoint->y)*(ret.y-pPoint->y));

		if(distance>tolerance)
		{
			continue;
		}
        if(distance<mindis)
		{
			bfind =true;
            mindis = distance;
			temppt.x =ret.x;
			temppt.y = ret.y;
            //线段的序号
			*plSegIndex =i;

			//当得到一个最邻近点时，返回，这样速度会快一些
			break;

		}
	}

	if(!bfind)
	{
		return false;
	}

	poutPt->x =temppt.x;
	poutPt->y =temppt.y;

    *searchDis =mindis;

    *plpartIndex =0;

    return true;
}

bool LineString::SnapMidPoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plSegIndex)
{
    long lnum = this->SegmentCount();
	if(lnum<=0)
	{
		return false;
	}
	Coordinate ret,temppt;


	double mindis =1e38,distance;
    
	bool bfind =false;
    for(long i=0;i<lnum;i++)
	{
		m_Segments[i]->MidPoint(ret);
		distance =sqrt((ret.x-pPoint->x)*(ret.x-pPoint->x) +(ret.y-pPoint->y)*(ret.y-pPoint->y));

		if(distance>tolerance)
		{
			continue;
		}
        if(distance<mindis)
		{
			bfind =true;
            mindis = distance;
			temppt.x =ret.x;
			temppt.y = ret.y;
            //线段的序号
			*plSegIndex =i;

			//当得到一个最邻近点时，返回，这样速度会快一些
			break;

		}
	}

	if(!bfind)
	{
		return false;
	}

	poutPt->x =temppt.x;
	poutPt->y =temppt.y;

    *searchDis =mindis;

    *plpartIndex =0;

    return true;
}

//捕捉端点
bool LineString::SnapEndPoint(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plvertexIndex)
{
    long lnum = getNumPoints();
	if(lnum<=1)
	{
		return false;
	}
	Coordinate vertex,temppt;


	double mindis =1e38,distance;
    
	bool bfind =false;
   
	//计算起始点
	vertex =points->getAt(0);
	distance =sqrt((vertex.x-pPoint->x)*(vertex.x-pPoint->x) +(vertex.y-pPoint->y)*(vertex.y-pPoint->y));

	
	if(distance <= tolerance && distance<mindis)
	{
		bfind =true;
		mindis = distance;
		temppt.x =vertex.x;
		temppt.y = vertex.y;
		//节点的序号
		*plvertexIndex =0;

	}

	//计算终止点
	vertex =points->getAt(lnum-1);
	distance =sqrt((vertex.x-pPoint->x)*(vertex.x-pPoint->x) +(vertex.y-pPoint->y)*(vertex.y-pPoint->y));

	
	if(distance <= tolerance && distance<mindis)
	{
		bfind =true;
		mindis = distance;
		temppt.x =vertex.x;
		temppt.y = vertex.y;
		//节点的序号
		*plvertexIndex =0;

	}


	if(!bfind)
	{
		return false;
	}

	poutPt->x =temppt.x;
	poutPt->y =temppt.y;

    *searchDis =mindis;

    *plpartIndex =0;

    return true;
}

/******************************************************************************************************
*以下实现了IPointCollection接口
*
******************************************************************************************************/
long LineString::PointCount() const
{
	return (long)getNumPoints();
}


void LineString::AddPoint(GEOMETRY::geom::Coordinate &coord)
{
	 points->add(coord);

	 //如果该点不是第一个点，添加一个线段
	 if(points->getSize()>1)
	 {
		 size_t count =points->getSize();

		
         Line* pnewline = new Line(points->GetPtPointer(count-2),points->GetPtPointer(count-1));
         
		 m_Segments.push_back(pnewline);

	 }
}

void LineString::InsertPoint(int index, GEOMETRY::geom::Coordinate &newpoint)
{
	if(index<0 || index>=getNumPoints())
	{
		return;
	}
    
	points->insert(index,newpoint);

	//插入一个节点时，相应的线段数组也要发生变化
    OnPointChanged();


   
}

void LineString::ReplacePoint(int index, GEOMETRY::geom::Coordinate &newpoint)
{
    if(index<0 || index>=getNumPoints())
	{
		return;
	}
	points->setAt(newpoint,index);
}

void LineString::RemovePoint(int index)
{
    if(index<0 || index>=getNumPoints())
	{
		return;
	}
	points->deleteAt(index);

	//删除一个节点时，相应的线段数组也要发生变化
    OnPointChanged();
}

Coordinate LineString::GetPoint(int index)
{
     if(index<0 || index>=getNumPoints())
	{
		return Coordinate();
	}
 
	return points->getAt(index);


}
/******************************************************************************************************
*以下实现了ITransForm接口
*
******************************************************************************************************/
void LineString::Move(double dx, double dy)
{
	for(size_t i=0;i<points->getSize();i++)
	{
		points->getAt(i).x+=dx;
		points->getAt(i).y +=dy;
	}

	//对每一个段进行额外的操作
	for(size_t i=0;i<m_Segments.size();i++)
	{
		m_Segments[i]->SegMove(dx,dy);
	}
	this->geometryChangedAction();

}

void LineString::Mirror(const Coordinate &p1,const Coordinate &p2)
{
   
    
	double a,b,c;
	double x,y;
	CGAlgorithms::LineEquation(p1,p2,a,b,c);

	for(size_t i=0;i<points->getSize();i++)
	{
		Coordinate &pt =points->getAt(i);

		x =pt.x;
		y =pt.y;

		//求对称点
		pt.x=((b*b-a*a)*x-2*a*b*y-2*a*c)/(a*a+b*b); 
		pt.y=((a*a-b*b)*y-2*a*b*x-2*b*c)/(a*a+b*b); 

	}
	for(size_t i=0;i<m_Segments.size();i++)
	{
		m_Segments[i]->SegMirror(p1,p2);
	}
}

void LineString::Scale(const GEOMETRY::geom::Coordinate &OriginPt, double dx, double dy)
{
	for(size_t i=0;i<points->getSize();i++)
	{
		points->getAt(i).Scale(OriginPt,dx,dy);


	}

	for(size_t i=0;i<m_Segments.size();i++)
	{
		m_Segments[i]->SegScale(OriginPt,dx,dy);
	}
}

void LineString::Rotate(const GEOMETRY::geom::Coordinate &OriginPt, double angle)
{
	for(size_t i=0;i<points->getSize();i++)
	{
		points->getAt(i).Rotate(OriginPt,angle);


	}

	for(size_t i=0;i<m_Segments.size();i++)
	{
		m_Segments[i]->SegRotate(OriginPt,angle);
	}
}

/******************************************************************************************************
*以下实现了ISegmentCollection接口
*
******************************************************************************************************/

void LineString::AddSegment(GEOMETRY::geom::ISegment *pSeg)
{
   if(!pSeg)
   {
	   return;
   }
   //判断这个是否是第一个线段
   if(points->getSize()==0)
   {
       points->add(pSeg->GetFromPoint());
	   points->add(pSeg->GetToPoint());

	   pSeg->ISegment::SetEmpty();
	   pSeg->setFromPtr(points->GetPtPointer(0));
	   pSeg->setToPtr(points->GetPtPointer(1));
   }
   else
   {
	   //判断这个段的起始点是否和当前线圈的最后一个点相同
	   if(pSeg->GetFromPoint()!=points->getAt(points->getSize()-1))
	   {
		   return;
	   }

	   Coordinate coord;
	   coord.x = pSeg->GetToPoint().x;
	   coord.y = pSeg->GetToPoint().y;

	    points->add(coord);
		long size =points->getSize();
		pSeg->ISegment::SetEmpty();
		pSeg->setFromPtr(points->GetPtPointer(size-2));
		pSeg->setToPtr(points->GetPtPointer(size-1));

        ReCreateSegments();
   }
   
   m_Segments.push_back(pSeg);
   
}

void LineString::ReCreateSegments()
{
	ISegment *pSeg =NULL;

	for(int i=0;i<m_Segments.size();i++)
	{
		pSeg =m_Segments[i];

		pSeg->setFromPtr(points->GetPtPointer(i));

		pSeg->setToPtr(points->GetPtPointer(i+1));

	}
}

void LineString::setPoints(CoordinateSequence* cl){
	const vector<Coordinate> *v=cl->toVector();
	points->setPoints(*(v));
	//delete v;
}

void LineString::OnPointChanged()
{
	for(int i=0; i<m_Segments.size(); i++)
	{
		delete m_Segments[i];
	}
	m_Segments.clear();
    
   //重新建立线段数组
	 //构造m_segments
	if(points->size()>1)
	{
	   
       
	   Line *pline =NULL;
	   //用点来构造segment，默认类型为Line
	   for(int i=0;i<points->size()-1;i++)
	   {
		   pline =new Line(points->GetPtPointer(i),points->GetPtPointer(i+1));
  
		   m_Segments.push_back(pline);
	   }

	}
}

} // namespace GEOMETRY::geom
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.71  2006/06/12 10:49:43  strk
 * unsigned int => size_t
 *
 * Revision 1.70  2006/06/12 10:10:39  strk
 * Fixed getGeometryN() to take size_t rather then int, changed unsigned int parameters to size_t.
 *
 * Revision 1.69  2006/05/04 15:49:39  strk
 * updated all Geometry::getDimension() methods to return Dimension::DimensionType (closes bug#93)
 *
 * Revision 1.68  2006/04/28 10:55:39  strk
 * Geometry constructors made protected, to ensure all constructions use GeometryFactory,
 * which has been made friend of all Geometry derivates. getNumPoints() changed to return
 * size_t.
 *
 * Revision 1.67  2006/04/11 11:16:25  strk
 * Added LineString and LinearRing constructors by auto_ptr
 *
 * Revision 1.66  2006/04/10 18:15:09  strk
 * Changed Geometry::envelope member to be of type auto_ptr<Envelope>.
 * Changed computeEnvelopeInternal() signater to return auto_ptr<Envelope>
 *
 * Revision 1.65  2006/04/10 17:35:44  strk
 * Changed LineString::points and Point::coordinates to be wrapped
 * in an auto_ptr<>. This should close bugs #86 and #89
 *
 * Revision 1.64  2006/04/05 10:25:20  strk
 * Fixed LineString constructor to ensure deletion of CoordinateSequence
 * argument on exception throw
 *
 * Revision 1.63  2006/03/31 16:55:17  strk
 * Added many assertions checking in LineString implementation.
 * Changed ::getCoordinate() to return NULL on empty geom.
 * Changed ::get{Start,End}Point() to return NULL on empty geom.
 *
 **********************************************************************/

