#include "stdafx.h"
#include "DisplayTransformation.h"
#include "CDC.h"
//#include <geometry/geom/BezierCurve.h>

//#define _SHOWCLIP
namespace Display
{

static boost::signal<void (VIEW_POSITION)> gCallbackChangeViewPos;


VIEW_POSITION::VIEW_POSITION()
{
	m_dScale=1.0;
	m_dMapScale=1.0;
	m_dGeoCenterX=m_dGeoCenterY=0.0;
	memset(&m_displayBound,0,sizeof(RECT));
}

VIEW_POSITION* VIEW_POSITION::operator =(const VIEW_POSITION& pos)
{
	m_dMapScale = pos.m_dMapScale;
	m_dScale = pos.m_dScale;
	m_dGeoCenterX = pos.m_dGeoCenterX;
	m_dGeoCenterY = pos.m_dGeoCenterY;
	m_displayBound = pos.m_displayBound;

	return this;
}

GEOMETRY::geom::Envelope VIEW_POSITION::GetViewExtent()
{
    GEOMETRY::geom::Envelope extent;

	double lHeight = m_displayBound.bottom-m_displayBound.top;
	double lWidth = m_displayBound.right-m_displayBound.left;
	
	double minx,miny,maxx,maxy;
	minx =m_dGeoCenterX-lWidth/2*m_dScale;
	maxx =m_dGeoCenterX+lWidth/2*m_dScale;
	miny =m_dGeoCenterY-lHeight/2*m_dScale;
	maxy =m_dGeoCenterY+lHeight/2*m_dScale;

	extent.init(minx,maxx,miny,maxy);

	return extent;
}

//////////////////////////////////////////////////////////////////////////

CDisplayTransformation::CDisplayTransformation()
{
	m_referenceScale = 0;
	m_unit = SYSTEM::SYS_UNIT_METER;
	m_curpos =-1;
}


CDisplayTransformation::~CDisplayTransformation()
{

}

double CDisplayTransformation::GetScale()
{
	return m_viewPositon.m_dScale;
}

double CDisplayTransformation::GetMapScale()
{
	return m_viewPositon.m_dMapScale;
}

double CDisplayTransformation::GetGeoCenterX()
{
	return m_viewPositon.m_dGeoCenterX;
}

void CDisplayTransformation::SetGeoCenterX(double x)
{
	 m_viewPositon.m_dGeoCenterX = x;

	 gCallbackChangeViewPos(m_viewPositon);
}


double CDisplayTransformation::GetGeoCenterY()
{
	return  m_viewPositon.m_dGeoCenterY;
}

void CDisplayTransformation::SetGeoCenterY(double y)
{
	m_viewPositon.m_dGeoCenterY = y;

	gCallbackChangeViewPos(m_viewPositon);
}


DIS_BOUND CDisplayTransformation::GetViewBound()
{
	return m_viewPositon.m_displayBound;
}

void CDisplayTransformation::SetViewBound(DIS_BOUND bound)
{
	m_viewPositon.m_displayBound = bound;

	gCallbackChangeViewPos(m_viewPositon);
}



void CDisplayTransformation::SetViewBound(const long left, const long right, const long top, const long bottom )
{
	m_viewPositon.m_displayBound.top = top;
	m_viewPositon.m_displayBound.bottom = bottom;
	m_viewPositon.m_displayBound.left = left;
	m_viewPositon.m_displayBound.right = right;

	gCallbackChangeViewPos(m_viewPositon);
}

void CDisplayTransformation::SetReferenceScale(double refScale)
{
	m_referenceScale = refScale;
}
double CDisplayTransformation::GetReferenceScale()
{
	return m_referenceScale;
}

void CDisplayTransformation::SetMapScale(double mapScale)
{
	// 更新视图位置
	VIEW_POSITION &viewPos = m_viewPositon;

	viewPos.m_dMapScale = mapScale;

	double val = SYSTEM::UnitConverter::ConvertUnits(1, m_unit, SYSTEM::SYS_UNIT_MILLIMETER);
	viewPos.m_dScale = viewPos.m_dMapScale * CDC::GetCreateDCsRateOfPixelAndMillimeter() / val;	

	gCallbackChangeViewPos(m_viewPositon);
}

void CDisplayTransformation::SetScale(double scale)
{
	// 更新视图位置
	VIEW_POSITION &viewPos = m_viewPositon;

	viewPos.m_dScale = scale;

	double val = SYSTEM::UnitConverter::ConvertUnits(1, m_unit, SYSTEM::SYS_UNIT_MILLIMETER);
	viewPos.m_dMapScale = viewPos.m_dScale / CDC::GetCreateDCsRateOfPixelAndMillimeter() * val;	

	gCallbackChangeViewPos(m_viewPositon);
}

void CDisplayTransformation::MoveViewBound(double OffsetX, double OffsetY)
{
	m_viewPositon.m_dGeoCenterX -= OffsetX;
	m_viewPositon.m_dGeoCenterY -= OffsetY;

	gCallbackChangeViewPos(m_viewPositon);
}



void CDisplayTransformation::GetGeoBound(GEOMETRY::geom::Envelope &bound)
{
	register double displayHalfSizeX = (m_viewPositon.m_displayBound.right - m_viewPositon.m_displayBound.left) / 2.0;
	register double displayHalfSizeY = (m_viewPositon.m_displayBound.bottom - m_viewPositon.m_displayBound.top) / 2.0;
	register double geoHalfSizeX = displayHalfSizeX * m_viewPositon.m_dScale ;
	register double geoHalfSizeY = displayHalfSizeY * m_viewPositon.m_dScale ;

	bound.init(m_viewPositon.m_dGeoCenterX - geoHalfSizeX,
				m_viewPositon.m_dGeoCenterX + geoHalfSizeX,
				m_viewPositon.m_dGeoCenterY - geoHalfSizeY,
				m_viewPositon.m_dGeoCenterY + geoHalfSizeY);
}

VIEW_POSITION& CDisplayTransformation::GetViewPosition()
{
	return m_viewPositon;
}

void CDisplayTransformation::SetViewPosition(VIEW_POSITION pos)
{
	m_viewPositon = pos;
	gCallbackChangeViewPos(m_viewPositon);
}

boost::signals::connection CDisplayTransformation::RegisterChangeViewPos(boost::function<void (VIEW_POSITION)> fun)
{
	return gCallbackChangeViewPos.connect(fun);
}

struct _DBSEGMENT
{
	GEOMETRY::geom::Coordinate pStart,pEnd;
};

// 函数名称 	: _gOpDBPointToDBSegmentDistance2
// 函数描述	    : 内部函数，计算点到线段的距离，返回平方值
// 返回类型		: inline double 
// 参数         :  const _DBPOINT &point
// 参数         : const _DBSEGMENT &seg
inline double _gOpDBPointToDBSegmentDistance2( const GEOMETRY::geom::Coordinate &point , const _DBSEGMENT &seg)
{
	//以已知点为坐标原点，平移坐标系：
	_DBSEGMENT segT;
	segT.pStart.x = seg.pStart.x - point.x;
	segT.pStart.y = seg.pStart.y - point.y;
	segT.pEnd.x = seg.pEnd.x - point.x;
	segT.pEnd.y = seg.pEnd.y - point.y;

	if((segT.pStart.x == segT.pEnd.x) && 
		(segT.pStart.y == segT.pEnd.y))
		return segT.pStart.x * segT.pStart.x + segT.pStart.y * segT.pStart.y;
	//
	register double a = segT.pStart.x * segT.pEnd.y - segT.pEnd.x * segT.pStart.y;
	a *= a;
	register double chaX = segT.pEnd.x - segT.pStart.x;
	register double chaY = segT.pEnd.y - segT.pStart.y;
	register double b = chaX * chaX + chaY * chaY;

	register double temp = a/b;

	register double StartWithOrigin = 
		segT.pStart.x * segT.pStart.x + segT.pStart.y * segT.pStart.y;
	register double EndWithOrigin = 
		segT.pEnd.x * segT.pEnd.x + segT.pEnd.y * segT.pEnd.y;
	if(b + StartWithOrigin - EndWithOrigin <-0.001) 
		return StartWithOrigin;
	else if(b + EndWithOrigin - StartWithOrigin < -0.001)
		return EndWithOrigin;
	else
		return  temp;		
}


// 函数名称 	: _gOpGeralizeDBLine
// 函数描述	    : 内部函数，综合线的递归函数,
//                后发现不需要，应该在数据编辑的基础上已经完善了的，显示时动态使用则速度比不用慢了3倍
// 返回类型		: inline GVOID 
// 参数         : long Start
// 参数         : long End
// 参数         : _DBPOINT* points
// 参数         : bool *pSign
// 参数         : double toler2
inline void _gOpGeralizeDBLine(long Start, long End, const GEOMETRY::geom::Coordinate *points, bool *pSign, double toler2)
{
	if( Start == End || Start+1 == End ) return;

	_DBSEGMENT seg;
	seg.pStart = points[Start];
	seg.pEnd   = points[End];

	long mid;
	double tmp,offtoler2 = 0.0;
	// 寻找偏离最大的点
	for(long i = Start+1 ; i < End-1 ; i++ )
	{
		tmp = _gOpDBPointToDBSegmentDistance2( points[i] , seg );
		if( tmp > offtoler2 )
		{
			offtoler2 = tmp;
			mid = i;
		}
	}

	if( toler2 > offtoler2 )
	{
		// 如果小于要求偏差，放弃期间所有的点
		return;
	}
	else
	{
		pSign[mid] = true;
		_gOpGeralizeDBLine( Start , mid , points , pSign , toler2 );
		_gOpGeralizeDBLine( mid   , End , points , pSign , toler2 );
	}
}

// 函数名称 	: gOpGeralizeDBLine
// 函数描述	    : 线综合算法，返回综合后的点数
// 返回类型		: GAPI long 
// 参数         : long numPoint
// 参数         : _DBPOINT* points
// 参数         : _DBPOINT* out_ptrs
inline long gOpGeralizeDBLine( const GEOMETRY::geom::CoordinateSequence *pincs, GEOMETRY::geom::CoordinateSequence *poutcs, double toler)
{
	size_t numPoint = pincs->getSize();
	bool *pSign = (bool*)malloc(numPoint*sizeof(bool));

	memset(pSign,0,numPoint*sizeof(bool));

	pSign[0] = true;
	pSign[numPoint-1] = true;
	double toler2 = toler * toler;

	const GEOMETRY::geom::Coordinate *pcds = &(pincs->getAt(0));
	_gOpGeralizeDBLine( 0 , (long)numPoint-1 , pcds , pSign , toler2 );

	for(size_t i = 0,outNumPoint = 0 ; i < numPoint ; i++)
	{
		if( pSign[i] )
			poutcs->add( pcds[i] );
	}

	free(pSign);
	return (long)poutcs->getSize();
}

void Display::CDisplayTransformation::GeralizeFromScale( const GEOMETRY::geom::CoordinateSequence *pcs, GEOMETRY::geom::CoordinateSequence *poutcs )
{
	// 根据当前屏幕的分辨率，综合数据，不少于4个点
	gOpGeralizeDBLine( pcs , poutcs , m_viewPositon.m_dScale );
}

enum GPWHERETYPE
{
	G_PLEFT = 0,
	G_PRIGHT= 1
};


// 函数名称 	: gOpPointInSegWhere
// 函数描述	    : 判断点在线的左右端
// 返回类型		: G_PWHERETYPE 
// 参数         : _DBSEGMENT &seg
// 参数         : _DBPOINT &point
inline GPWHERETYPE gOpPointInSegWhere(_DBSEGMENT &seg, const GEOMETRY::geom::Coordinate &point)
{
	return (seg.pStart.x-point.x)*(seg.pEnd.y-point.y)-
		(seg.pStart.y-point.y)*(seg.pEnd.x-point.x)>0.? G_PLEFT:G_PRIGHT;
}

// 函数名称 	: gOpGetCrossPointOf2Seg
// 函数描述	    : 计算两直线交点，交点可能在延长线上
// 返回类型		: GGAPI _DBPOINT 
// 参数         : _DBSEGMENT &seg
// 参数         : _DBSEGMENT &seg2
inline GEOMETRY::geom::Coordinate gOpGetCrossPointOf2Seg(_DBSEGMENT &seg, _DBSEGMENT &seg2)
{
	double a1 = seg.pEnd.x-seg.pStart.x;
	double b1 = seg.pEnd.y-seg.pStart.y;
	double a2 = seg2.pEnd.x-seg2.pStart.x;
	double b2 = seg2.pEnd.y-seg2.pStart.y;
	GEOMETRY::geom::Coordinate p;
	double t = (b2 * (seg2.pStart.x - seg.pStart.x) + a2 * (seg.pStart.y - seg2.pStart.y) ) 
		/ (b2*a1 - a2*b1) ;
	p.x = seg.pStart.x + a1 * t;
	p.y = seg.pStart.y + b1 * t;
	return p;
}


// 函数名称 	: gOpGetCrossPointOf2Seg
// 函数描述	    : 计算两直线交点，交点可能在延长线上
// 返回类型		: GEOMETRY::geom::Coordinate 
// 参数         : GEOMETRY::geom::Coordinate &p1
// 参数         : GEOMETRY::geom::Coordinate &p2
// 参数         : GEOMETRY::geom::Coordinate &p3
// 参数         : GEOMETRY::geom::Coordinate &p4
inline GEOMETRY::geom::Coordinate gOpGetCrossPointOf2Seg(const GEOMETRY::geom::Coordinate &p1,const GEOMETRY::geom::Coordinate &p2,const GEOMETRY::geom::Coordinate &p3,const GEOMETRY::geom::Coordinate &p4)
{
	double a1 = p2.x-p1.x;
	double b1 = p2.y-p1.y;
	double a2 = p4.x-p3.x;
	double b2 = p4.y-p3.y;
	GEOMETRY::geom::Coordinate p;
	double t = (b2 * (p3.x - p1.x) + a2 * (p1.y - p3.y) ) 
		/ (b2*a1 - a2*b1) ;
	p.x = p1.x + a1 * t;
	p.y = p1.y + b1 * t;
	return p;
}

typedef std::list<GEOMETRY::geom::Coordinate> DBPOINTLIST;

void Display::CDisplayTransformation::GetGeoWideOfCurrentView( double &minX , double &minY , double &maxX , double &maxY )
{
	long Width = m_viewPositon.GetViewBound().Width()-1;
	long Height= m_viewPositon.GetViewBound().Height()-1;
	register double geoHalfXWidth = Width  * m_viewPositon.m_dScale / 2;
	register double geoHalfYHeight= Height * m_viewPositon.m_dScale / 2;

	minX = m_viewPositon.GetGeoCenterX() - geoHalfXWidth;
	minY = m_viewPositon.GetGeoCenterY() - geoHalfYHeight;
	maxX = m_viewPositon.GetGeoCenterX() + geoHalfXWidth;
	maxY = m_viewPositon.GetGeoCenterY() + geoHalfYHeight;
}


BOOL Display::CDisplayTransformation::DisplayClip(GEOMETRY::geom::Envelope &env, const GEOMETRY::geom::CoordinateSequence *pcs, std::vector<GEOMETRY::geom::Coordinate> &cs_out , BOOL bPolygon)
{
	// 根据显示范围进行快速矩形裁减

	double minX, minY , maxX , maxY;
	GetGeoWideOfCurrentView( minX, minY , maxX , maxY );
	GEOMETRY::geom::Envelope mbr;
	mbr.init( minX ,maxX , minY ,maxY );
	const GEOMETRY::geom::Coordinate *points = &(pcs->getAt(0));

	int Size = pcs->getSize();
	minX = maxX = points[0].x;
	minY = maxY = points[0].y;
	size_t i;
	for ( i = 0 ; i < Size ; i++ )
	{
		if( minX > points[i].x ) minX = points[i].x;
		if( maxX < points[i].x ) maxX = points[i].x;
		if( minY > points[i].y ) minY = points[i].y;
		if( maxY < points[i].y ) maxY = points[i].y;
	}
	env.init( minX , maxX , minY , maxY );
	//包含
	if( mbr.getMinX() <= env.getMinX() && mbr.getMaxX() >= env.getMaxX() \
		&& mbr.getMinY() <= env.getMinY() && mbr.getMaxY() >= env.getMaxY() )
	{
		cs_out.resize( pcs->size() );
		memcpy( &(cs_out[0]) , points , sizeof(GEOMETRY::geom::Coordinate)*pcs->size() );
		return TRUE; // 直接返回，不进行裁剪
	}
	//相离
	if( mbr.getMaxX() < env.getMinX() || mbr.getMinX() > env.getMaxX() \
		|| mbr.getMaxY() < env.getMinY() || mbr.getMinY() > env.getMaxY() )
	{
		return FALSE;
	}


	DBPOINTLIST pointlist;
	_DBSEGMENT seg;

	size_t NumPoint = pcs->getSize();
	// 过滤上限
	seg.pStart.x = mbr.getMinX();
	seg.pEnd.x   = mbr.getMaxX();
	seg.pStart.y = mbr.getMaxY();
	seg.pEnd.y   = mbr.getMaxY();
	GPWHERETYPE where;
	where = gOpPointInSegWhere( seg , points[0] );
	for( i = 0 ; i < NumPoint-1 ; i++ )
	{
		if( where == G_PRIGHT )
		{
			pointlist.push_back( points[i] );
			where = gOpPointInSegWhere( seg , points[i+1] );
			if( where == G_PLEFT ) // 当前点在内,下一点在外,增加交点
				pointlist.push_back( gOpGetCrossPointOf2Seg( seg , *(_DBSEGMENT*)(points+i) ) );
		}
		else
		{
			where = gOpPointInSegWhere( seg , points[i+1] );
			if( where == G_PRIGHT )// 当前点在外,下一点在内,增加交点
				pointlist.push_back( gOpGetCrossPointOf2Seg( seg , *(_DBSEGMENT*)(points+i) ) );
		}
	}
	if( where == G_PRIGHT ) // 判断最后一个点
		pointlist.push_back( points[i] );

	DBPOINTLIST::iterator iter;
	GEOMETRY::geom::Coordinate ptEnd, ptBegin;
	if(bPolygon)
	{
		iter = pointlist.end();
		iter--;
		ptEnd = *iter;
		iter = pointlist.begin();
		ptBegin = *iter;

		if(abs(ptEnd.x - ptBegin.x)>0.000001 || abs(ptEnd.y - ptBegin.y)>0.000001)
			pointlist.push_back(ptBegin);
	}
	
	DBPOINTLIST::iterator ptr;
	DBPOINTLIST::iterator ptrNext = pointlist.begin();

	// 过滤下限
	if( env.getMinY() < mbr.getMinY() )
	{
		seg.pStart.x = mbr.getMaxX();
		seg.pEnd.x   = mbr.getMinX();
		seg.pStart.y = mbr.getMinY();
		seg.pEnd.y   = mbr.getMinY();
		where = gOpPointInSegWhere( seg , *ptrNext );
		ptr = ptrNext;
		for(ptrNext++ ; ; ptrNext++ )
		{
			if( ptrNext == pointlist.end() ) break;

			if( where == G_PRIGHT )
			{
				where = gOpPointInSegWhere( seg , *ptrNext );
				if( where == G_PLEFT ) // 当前点在内,下一点在外,增加交点
					ptrNext = ++pointlist.insert( ptrNext , gOpGetCrossPointOf2Seg( seg.pStart , seg.pEnd , *ptr , *ptrNext ) );
			}
			else
			{
				where = gOpPointInSegWhere( seg , *ptrNext );
				if( where == G_PRIGHT )// 当前点在外,下一点在内,增加交点
					ptrNext = ++pointlist.insert( ptrNext, gOpGetCrossPointOf2Seg( seg.pStart , seg.pEnd , *ptr , *ptrNext ) );
				pointlist.erase( ptr );
			}
			ptr=ptrNext;
			if( ptrNext == pointlist.end() ) break;
			if( pointlist.size() <= 1 ) return FALSE;
		}
		if( where != G_PRIGHT ) // 判断最后一个点
			pointlist.erase( ptr );
	}

	if(bPolygon)
	{
		iter = pointlist.end();
		iter--;
		ptEnd = *iter;
		iter = pointlist.begin();
		ptBegin = *iter;

		if(abs(ptEnd.x - ptBegin.x)>0.000001 || abs(ptEnd.y - ptBegin.y)>0.000001)
			pointlist.push_back(ptBegin);
	}

	// 过滤左限
	if( env.getMinX() < mbr.getMinX() )
	{
		seg.pStart.x = mbr.getMinX();
		seg.pEnd.x   = mbr.getMinX();
		seg.pStart.y = mbr.getMinY();
		seg.pEnd.y   = mbr.getMaxY();
		ptrNext = pointlist.begin();
		where = gOpPointInSegWhere( seg , *ptrNext );
		ptr = ptrNext;
		for(ptrNext++ ; ; ptrNext++ )
		{
			if( ptrNext == pointlist.end() ) break;
			if( where == G_PRIGHT )
			{
				where = gOpPointInSegWhere( seg , *ptrNext );
				if( where == G_PLEFT ) // 当前点在内,下一点在外,增加交点
					ptrNext = ++pointlist.insert( ptrNext , gOpGetCrossPointOf2Seg( seg.pStart , seg.pEnd , *ptr , *ptrNext ) );
			}
			else
			{
				where = gOpPointInSegWhere( seg , *ptrNext );
				if( where == G_PRIGHT )// 当前点在外,下一点在内,增加交点
					ptrNext = ++pointlist.insert( ptrNext, gOpGetCrossPointOf2Seg( seg.pStart , seg.pEnd , *ptr , *ptrNext ) );
				pointlist.erase( ptr );
			}
			ptr=ptrNext;
			if( ptrNext == pointlist.end() ) break;
			if( pointlist.size() <= 1 ) return FALSE;
		}
		if( where != G_PRIGHT ) // 判断最后一个点
			pointlist.erase( ptr );
	}

	if(bPolygon)
	{
		iter = pointlist.end();
		iter--;
		ptEnd = *iter;
		iter = pointlist.begin();
		ptBegin = *iter;

		if(abs(ptEnd.x - ptBegin.x)>0.000001 || abs(ptEnd.y - ptBegin.y)>0.000001)
			pointlist.push_back(ptBegin);
	}


	// 过滤右限
	if( env.getMaxX() > mbr.getMaxX() )
	{
		seg.pStart.x = mbr.getMaxX();
		seg.pEnd.x   = mbr.getMaxX();
		seg.pStart.y = mbr.getMaxY();
		seg.pEnd.y   = mbr.getMinY();
		ptrNext = pointlist.begin();
		where = gOpPointInSegWhere( seg , *ptrNext );
		ptr = ptrNext;
		for(ptrNext++ ; ; ptrNext++ )
		{
			if( ptrNext == pointlist.end() ) break;
			if( where == G_PRIGHT )
			{
				where = gOpPointInSegWhere( seg , *ptrNext );
				if( where == G_PLEFT ) // 当前点在内,下一点在外,增加交点
					ptrNext = ++pointlist.insert( ptrNext , gOpGetCrossPointOf2Seg( seg.pStart , seg.pEnd , *ptr , *ptrNext ) );
			}
			else
			{
				where = gOpPointInSegWhere( seg , *ptrNext );
				if( where == G_PRIGHT )// 当前点在外,下一点在内,增加交点
					ptrNext = ++pointlist.insert( ptrNext, gOpGetCrossPointOf2Seg( seg.pStart , seg.pEnd , *ptr , *ptrNext ) );
				pointlist.erase( ptr );
			}
			ptr=ptrNext;
			if( ptrNext == pointlist.end() ) break;
			if( pointlist.size() <= 1 ) return FALSE;
		}
		if( where != G_PRIGHT ) // 判断最后一个点
			pointlist.erase( ptr );
	}


	if(bPolygon)
	{
		iter = pointlist.end();
		iter--;
		ptEnd = *iter;
		iter = pointlist.begin();
		ptBegin = *iter;

		if(abs(ptEnd.x - ptBegin.x)>0.000001 || abs(ptEnd.y - ptBegin.y)>0.000001)
			pointlist.push_back(ptBegin);
	}

	// 记录所有点
	for(ptrNext = pointlist.begin(); ptrNext != pointlist.end(); ptrNext++ )
		cs_out.push_back( (*ptrNext) );

	return TRUE;
}

DIS_TEXT* CDisplayTransformation::TransformToDisplay(const GEOMETRY::geom::Envelope* pEnvelope,  const std::string strText)
{
	DIS_TEXT* pText;

	CreateDisplayText(pText, strText.size());

	DIS_RECT *rect = TransformToDisplay(pEnvelope);

	pText->textPos = *rect;

	strcpy(pText->cText, strText.c_str());

	FreeDisplayObj(rect);

	return pText;
}

DIS_POINT* CDisplayTransformation::TransformToDisplay(const GEOMETRY::geom::Point *pPoint)
{
	double minX , maxX , minY , maxY;
	GEOMETRY::geom::Envelope env_view;
	GetGeoWideOfCurrentView( minX , minY , maxX , maxY );
	env_view.init( minX , maxX , minY , maxY );

	const GEOMETRY::geom::Coordinate* coord = pPoint->getCoordinate();
	if(coord->x > maxX || coord->x<minX ||coord->y > maxY || coord->y<minY)
		return NULL;

	DIS_POINT* pt;

	CreateDisplayPoint(pt);

	ConvertGeoToDisplay(pPoint->getX(),pPoint->getY(),pt->p.x,pt->p.y);

	return pt;
}

DIS_LINE* CDisplayTransformation::TransformToDisplay(const GEOMETRY::geom::LineString* pLine)
{
	DIS_LINE* pDisLine;

	const GEOMETRY::geom::CoordinateSequence *pCoors = pLine->getCoordinatesRO();//getCoordinates();

#ifndef _SHOWCLIP
	CreateDisplayLine( pDisLine , (long)pCoors->getSize() );

	ConvertGeoToDisplay( pCoors , pDisLine->ps , pDisLine->Count );

#else


	double minX , maxX , minY , maxY;
	GEOMETRY::geom::Envelope env_view;
	GetGeoWideOfCurrentView( minX , minY , maxX , maxY );
	env_view.init( minX , maxX , minY , maxY );

	unsigned long totalPtCount = 0;
	std::vector<GEOMETRY::geom::Coordinate> cs;
	DisplayClip( env_view , pCoors , cs , FALSE);
	if( cs.size() == 0 ) return NULL;

	CreateDisplayLine( pDisLine , (long)cs.size() );

	ConvertGeoToDisplay( cs , pDisLine->ps);
	

#endif
	

	

	return pDisLine;

}

DIS_POLYGON* CDisplayTransformation::TransformToDisplay(const GEOMETRY::geom::Polygon* pPolygon)
{
	if( pPolygon == NULL ) 
		return NULL;

	//判断多边形是否包含弧段
	if(pPolygon->IsContainArc())
	{
		return (DIS_POLYGON*)TransformArcPolygon(pPolygon);
	}

	DIS_POLYGON *pDIS_POLYGON;
	size_t i,lNumRings = pPolygon->getNumInteriorRing();//内环面的个数						

	const GEOMETRY::geom::LineString *pExtLine = pPolygon->getExteriorRing();
	unsigned long lExtPtCount = (unsigned long)pExtLine->getNumPoints();			//储存点个数
	size_t totlePtCount = lExtPtCount;
	for( i = 0 ; i < lNumRings ; i++ )
	{
		const GEOMETRY::geom::LineString* pRingLineString = pPolygon->getInteriorRingN(i);
		totlePtCount += pRingLineString->getNumPoints();
	}

	
#ifndef _SHOWCLIP
	CreateDisplayPolygon( pDIS_POLYGON , (unsigned long)lNumRings + 1 , (unsigned long)totlePtCount );

	// 外环
	INT_POINT *pAdr = pDIS_POLYGON->GetPointAdr();
	ConvertGeoToDisplay( pExtLine->getCoordinatesRO() , pAdr, lExtPtCount );
	pAdr += lExtPtCount;
	pDIS_POLYGON->RingCount[0] = lExtPtCount;

	unsigned long rpPoint;
	// 内环
	for( i = 0 ; i < lNumRings ; i++ )
	{
		const GEOMETRY::geom::LineString* pRingLineString = pPolygon->getInteriorRingN(i);
		ConvertGeoToDisplay( pRingLineString->getCoordinatesRO() , pAdr, rpPoint  );
		pDIS_POLYGON->RingCount[i+1] = rpPoint;
		pAdr += pDIS_POLYGON->RingCount[i+1];
	}


#else

	// 显示裁减
	GEOMETRY::geom::Envelope env_view;
	std::vector<GEOMETRY::geom::Coordinate> csExt, csInner;
	std::vector<INT_POINT *> innerPts;
	std::vector<unsigned long> innerRingPtCount;
	double minX , maxX , minY , maxY;
	GetGeoWideOfCurrentView( minX , minY , maxX , maxY );
	env_view.init( minX , maxX , minY , maxY );

	unsigned long totalPtCount = 0;
	DisplayClip( env_view , pExtLine->getCoordinatesRO() , csExt , TRUE);
	if( csExt.size() == 0 ) return NULL;
	totalPtCount+=csExt.size();


	unsigned long rpPoint;
	long lNewNumRing = lNumRings;
	// 内环
	for( i = 0 ; i < lNumRings ; i++ )
	{
		const GEOMETRY::geom::LineString* pRingLineString = pPolygon->getInteriorRingN(i);
		DisplayClip( env_view , pRingLineString->getCoordinatesRO() , csInner , TRUE);

		if(csInner.size()==0)
		{
			lNewNumRing--;
			continue;
		}

		INT_POINT* pts = new INT_POINT[csInner.size()];
		ConvertGeoToDisplay( csInner , pts);
		innerPts.push_back(pts);
		innerRingPtCount.push_back(csInner.size());
		totalPtCount+=csInner.size();
		csInner.clear();
	}

	
	CreateDisplayPolygon( pDIS_POLYGON , (unsigned long)lNewNumRing + 1 , totalPtCount );
	INT_POINT *pAdr = pDIS_POLYGON->GetPointAdr();

	ConvertGeoToDisplay( csExt , pAdr , lExtPtCount );
	pAdr += lExtPtCount;
	pDIS_POLYGON->RingCount[0] = lExtPtCount;
	csExt.clear();

	for(int i=0; i<lNewNumRing; i++)
	{
		INT_POINT* pts = innerPts[i];

		for(int j=0; j<innerRingPtCount[i]; j++)
		{
			*pAdr = pts[i];
			pAdr++;
		}
		pDIS_POLYGON->RingCount[i+1] = innerRingPtCount[i];
		delete pts;
		pts = NULL;
		//pAdr += pDIS_POLYGON->RingCount[i+1];
	}
	

#endif
	return pDIS_POLYGON;
}

DIS_ARCPOLYGON* CDisplayTransformation::TransformArcPolygon(const GEOMETRY::geom::Polygon* pPolygon)
{
	if( pPolygon == NULL ) 
		return NULL;

    GEOMETRY::geom::Polygon* pPoly =(GEOMETRY::geom::Polygon*)pPolygon;
    DIS_ARCPOLYGON *pArcPolygon;
    int i,j,nNumRings = pPolygon->getNumInteriorRing()+1;//环的个数
    int nTotalSegment=0; //线段数目
    GEOMETRY::geom::LineString *pRing =NULL;
    for(i=0;i<nNumRings;i++)
	{
		pRing =(GEOMETRY::geom::LineString*)pPoly->GetGeometry(i);
		nTotalSegment+=pRing->SegmentCount();
	}

	CreateDisplayArcPolygon( pArcPolygon , nNumRings ,nTotalSegment);

	int nSegment;
	int index =0;
	GEOMETRY::geom::ISegment *pSeg =NULL;
	GEOMETRY::geom::Coordinate coord;
	DIS_SEGMENT *pds =NULL;

	for(i=0;i<nNumRings;i++)
	{
		pRing =(GEOMETRY::geom::LineString*)pPoly->GetGeometry(i);

		nSegment =pRing->SegmentCount();

		pArcPolygon->pRingIndex[i] =nSegment;

		for(j=0;j<nSegment;j++)
		{
            pSeg =pRing->GetSegment(j);
            switch(pSeg->getGeometryTypeId())
			{
			case GEOMETRY::geom::GEOM_LINE:
				{
					pArcPolygon->pSegments[index].type =ST_LINE;
                    
					//获得起始点，终止点
					coord =pSeg->GetFromPoint();
					ConvertGeoToDisplay(coord.x,coord.y,pArcPolygon->pSegments[index].points[0].x,pArcPolygon->pSegments[index].points[0].y);
                    
					coord =pSeg->GetToPoint();
					ConvertGeoToDisplay(coord.x,coord.y,pArcPolygon->pSegments[index].points[1].x,pArcPolygon->pSegments[index].points[1].y);

					break;
				}
			case GEOMETRY::geom::GEOM_CIRCULARARC:
				{

                    pArcPolygon->pSegments[index].type =ST_CIRCULARARC;
					pds =&(pArcPolygon->pSegments[index]);

					break;
				}
			case GEOMETRY::geom::GEOM_ELLIPTICARC:
				{
                    pArcPolygon->pSegments[index].type =ST_ELLIPTICARC;
					break;
				}
			case GEOMETRY::geom::GEOM_BEZIERCURVE:
				{
					/*pds =&(pArcPolygon->pSegments[index]);
					pds->type =ST_BEZIERCURVE;

					coord =pSeg->GetFromPoint();
					ConvertGeoToDisplay(coord.x,coord.y,pds->points[0].x,pds->points[0].y);

					coord =((GEOMETRY::geom::BezierCurve*)pSeg)->GetFirstCtrlPoint();
                    ConvertGeoToDisplay(coord.x,coord.y,pds->points[1].x,pds->points[1].y);

					coord =((GEOMETRY::geom::BezierCurve*)pSeg)->GetSecondCtrlPoint();
					ConvertGeoToDisplay(coord.x,coord.y,pds->points[2].x,pds->points[2].y);

					coord =pSeg->GetToPoint();
					ConvertGeoToDisplay(coord.x,coord.y,pds->points[3].x,pds->points[3].y);*/
					break;
				}
			default:
				break;
			}
			index++;
		}

		
	}

	return pArcPolygon;

}

DIS_RECT* CDisplayTransformation::TransformToDisplay(const GEOMETRY::geom::Envelope* pRect)
{
#ifndef _SHOWCLIP

	DIS_RECT* pDisRect;

	CreateDisplayRect(pDisRect);

	ConvertGeoToDisplay(pRect->getMinX(),pRect->getMinY(),pDisRect->left,pDisRect->bottom);

	ConvertGeoToDisplay(pRect->getMaxX(),pRect->getMaxY(),pDisRect->right,pDisRect->top);

	return pDisRect;

	

#else
	
	double minX , maxX , minY , maxY;
	GEOMETRY::geom::Envelope env_view;
	GetGeoWideOfCurrentView( minX , minY , maxX , maxY );
	env_view.init( minX , maxX , minY , maxY );

	GEOMETRY::geom::Envelope env_clip;
	env_view.intersection(*pRect, env_clip);

	DIS_RECT* pDisRect;

	CreateDisplayRect(pDisRect);

	ConvertGeoToDisplay(env_clip.getMinX(),env_clip.getMinY(),pDisRect->left,pDisRect->bottom);

	ConvertGeoToDisplay(env_clip.getMaxX(),env_clip.getMaxY(),pDisRect->right,pDisRect->top);

	return pDisRect;

#endif	
	
}

DIS_BOUND* CDisplayTransformation::TransformToDisplayBound(const GEOMETRY::geom::Envelope* pBound)
{

#ifndef _SHOWCLIP

	DIS_BOUND* pDisBound;
	CreateDisplayBound(pDisBound);

	pDisBound->left = (pBound->getMinX() - m_viewPositon.m_dGeoCenterX)/m_viewPositon.m_dScale + (m_viewPositon.m_displayBound.right+m_viewPositon.m_displayBound.left)/2.0;

	pDisBound->bottom = (m_viewPositon.m_dGeoCenterY-pBound->getMinY())/m_viewPositon.m_dScale + (m_viewPositon.m_displayBound.bottom+m_viewPositon.m_displayBound.top)/2.0;

	pDisBound->right = (pBound->getMaxX() - m_viewPositon.m_dGeoCenterX)/m_viewPositon.m_dScale + (m_viewPositon.m_displayBound.right+m_viewPositon.m_displayBound.left)/2.0;

	pDisBound->top = (m_viewPositon.m_dGeoCenterY-pBound->getMaxY())/m_viewPositon.m_dScale + (m_viewPositon.m_displayBound.bottom+m_viewPositon.m_displayBound.top)/2.0;

	return pDisBound;

#else

	double minX , maxX , minY , maxY;
	GEOMETRY::geom::Envelope env_view;
	GetGeoWideOfCurrentView( minX , minY , maxX , maxY );
	env_view.init( minX , maxX , minY , maxY );

	GEOMETRY::geom::Envelope env_clip;
	env_view.intersection(*pBound, env_clip);

	DIS_BOUND* pDisBound;
	CreateDisplayBound(pDisBound);

	pDisBound->left = (env_clip.getMinX() - m_viewPositon.m_dGeoCenterX)/m_viewPositon.m_dScale + (m_viewPositon.m_displayBound.right+m_viewPositon.m_displayBound.left)/2.0;
	
	pDisBound->bottom = (m_viewPositon.m_dGeoCenterY-env_clip.getMinY())/m_viewPositon.m_dScale + (m_viewPositon.m_displayBound.bottom+m_viewPositon.m_displayBound.top)/2.0;

	pDisBound->right = (env_clip.getMaxX() - m_viewPositon.m_dGeoCenterX)/m_viewPositon.m_dScale + (m_viewPositon.m_displayBound.right+m_viewPositon.m_displayBound.left)/2.0;
	
	pDisBound->top = (m_viewPositon.m_dGeoCenterY-env_clip.getMaxY())/m_viewPositon.m_dScale + (m_viewPositon.m_displayBound.bottom+m_viewPositon.m_displayBound.top)/2.0;

	return pDisBound;

#endif

}

DIS_CIRCLE* CDisplayTransformation::TransformToDisplay(const GEOMETRY::geom::Circle *pCircle)
{

#ifndef _SHOWCLIP

	DIS_CIRCLE *pC =NULL;
	CreateDisplayCircle(pC);

	GEOMETRY::geom::Coordinate coord =pCircle->GetCenterPoint();

	ConvertGeoToDisplay(coord.x,coord.y,pC->center.x,pC->center.y);

	pC->Radio =(long)((pCircle->GetRadius())/m_viewPositon.m_dScale);

	return pC;

#else

	double minX , maxX , minY , maxY;
	GEOMETRY::geom::Envelope env_view;
	GetGeoWideOfCurrentView( minX , minY , maxX , maxY );
	env_view.init( minX , maxX , minY , maxY );

	GEOMETRY::geom::Envelope envCircle = *pCircle->getEnvelopeInternal();
	if(env_view.intersects(envCircle))
	{
		GEOMETRY::geom::Geometry* pEnvView = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&env_view);

		return (DIS_CIRCLE*)TransformToDisplay((GEOMETRY::geom::Polygon*)pEnvView->intersection(pCircle));
	}

   DIS_CIRCLE *pC =NULL;
   CreateDisplayCircle(pC);

   GEOMETRY::geom::Coordinate coord =pCircle->GetCenterPoint();

   ConvertGeoToDisplay(coord.x,coord.y,pC->center.x,pC->center.y);

   pC->Radio =(long)((pCircle->GetRadius())/m_viewPositon.m_dScale);

   return pC;

#endif
}

DIS_ELLIPSE* CDisplayTransformation::TransformToDisplay(const GEOMETRY::geom::Ellipse *pEllipse)
{
#ifndef _SHOWCLIP


	DIS_ELLIPSE *pC =NULL;
	CreateDisplayEllipse(pC);

	GEOMETRY::geom::Coordinate coord =pEllipse->GetCenterPoint();

	long cenx,ceny,lmajar,lminor;
	//转换圆心
	ConvertGeoToDisplay(coord.x,coord.y,cenx,ceny);

	double majar,minor;

	pEllipse->GetAxes(&majar,&minor);

	lmajar =(long)(majar/m_viewPositon.m_dScale);

	lminor =(long)(minor/m_viewPositon.m_dScale);

	//如果没有旋转，现在只考虑横，竖两种椭圆，没有考虑旋转
	if(pEllipse->GetRotAngle()==0.0)
	{
		pC->left =cenx -lmajar;
		pC->right =cenx +lmajar;

		pC->top =ceny-lminor;
		pC->bottom =ceny+lminor;
	}
	else
	{
		pC->left =cenx -lminor;
		pC->right =cenx +lminor;

		pC->top =ceny-lmajar;
		pC->bottom =ceny+lmajar;
	}


	return pC;

#else

	double minX , maxX , minY , maxY;
	GEOMETRY::geom::Envelope env_view;
	GetGeoWideOfCurrentView( minX , minY , maxX , maxY );
	env_view.init( minX , maxX , minY , maxY );

	GEOMETRY::geom::Envelope envCircle = *pEllipse->getEnvelopeInternal();
	if(env_view.intersects(envCircle))
	{
		GEOMETRY::geom::Geometry* pEnvView = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&env_view);

		return (DIS_ELLIPSE*)TransformToDisplay((GEOMETRY::geom::Polygon*)pEnvView->intersection(pEllipse));
	}


	DIS_ELLIPSE *pC =NULL;
	CreateDisplayEllipse(pC);

	GEOMETRY::geom::Coordinate coord =pEllipse->GetCenterPoint();

	long cenx,ceny,lmajar,lminor;
	//转换圆心
	ConvertGeoToDisplay(coord.x,coord.y,cenx,ceny);

	double majar,minor;

	pEllipse->GetAxes(&majar,&minor);

	lmajar =(long)(majar/m_viewPositon.m_dScale);

	lminor =(long)(minor/m_viewPositon.m_dScale);

	//如果没有旋转，现在只考虑横，竖两种椭圆，没有考虑旋转
	if(pEllipse->GetRotAngle()==0.0)
	{
		pC->left =cenx -lmajar;
		pC->right =cenx +lmajar;

		pC->top =ceny-lminor;
		pC->bottom =ceny+lminor;
	}
	else
	{
		pC->left =cenx -lminor;
		pC->right =cenx +lminor;

		pC->top =ceny-lmajar;
		pC->bottom =ceny+lmajar;
	}


	return pC;

#endif
}

DIS_BEZIER* CDisplayTransformation::TransformToDisplay(const GEOMETRY::geom::BezierSpline* pBezier)
{
	DIS_BEZIER *pB =NULL;
	long ptCount;

	ptCount = (pBezier->getNumPoints()-1)*3+1;

	CreateDisplayBezier(pB,ptCount);

	//
	std::vector<GEOMETRY::geom::Coordinate> polyBezier;

	pBezier->GetPolyBezier(polyBezier);

	ConvertGeoToDisplay(polyBezier, pB->ps);

	polyBezier.clear();

	return pB;

}

double CDisplayTransformation::TransformToDisplay(double dblDistance)
{
   return (dblDistance)/m_viewPositon.m_dScale;

}

void CDisplayTransformation::ConvertGeoToDisplay( const GEOMETRY::geom::CoordinateSequence *pcs , INT_POINT *pts )
{
	// 地理坐标转换为显示坐标
	size_t i,Size = pcs->getSize();
	GEOMETRY::geom::Coordinate coordinate;

	//
	for( i = 0 ; i < Size ; i++ )
	{
		pcs->getAt(i,coordinate);
		ConvertGeoToDisplay(coordinate.x,coordinate.y,pts[i].x,pts[i].y);
	}
}

void CDisplayTransformation::ConvertGeoToDisplay( const std::vector<GEOMETRY::geom::Coordinate> &cs , INT_POINT *pts )
{
	// 地理坐标转换为显示坐标
	size_t i,Size = cs.size();

	//
	for( i = 0 ; i < Size ; i++ )
	{
		ConvertGeoToDisplay(cs[i].x,cs[i].y,pts[i].x,pts[i].y);
	}
}


inline void CDisplayTransformation::ConvertGeoToDisplay( const GEOMETRY::geom::CoordinateSequence *pcs , INT_POINT *pts , unsigned long &UseCount)
{
	// 地理坐标转换为显示坐标， 同时消除重复坐标
	GEOMETRY::geom::Coordinate coordinate;
	size_t i,Index = 0,Size = pcs->getSize();

	INT_POINT *ptsUse = pts;
	register INT_POINT pt;

	// First Point
	pcs->getAt(0,coordinate);
	ConvertGeoToDisplay(coordinate.x,coordinate.y,ptsUse->x,ptsUse->y);

	//
	for( i = 1 ; i < Size ; i++ )
	{
		pcs->getAt(i,coordinate);
		ConvertGeoToDisplay(coordinate.x,coordinate.y,pt.x,pt.y);

		if( ptsUse->x != pt.x || ptsUse->y != pt.y )
		{
			ptsUse++;
			*ptsUse = pt;
		}
	}
	UseCount = ptsUse - pts + 1;

	if( UseCount < 3 )
	{
		for( ; UseCount < 3 && UseCount < Size ; UseCount++ )
		{
			pts[UseCount] = pts[UseCount-1];
		}
	}
}


inline void CDisplayTransformation::ConvertGeoToDisplay( const std::vector<GEOMETRY::geom::Coordinate> &cs , INT_POINT *pts , unsigned long &UseCount )
{
	// 地理坐标转换为显示坐标， 同时消除重复坐标
	size_t i,Index = 0,Size = cs.size();

	INT_POINT *ptsUse = pts;
	register INT_POINT pt;

	// First Point
	ConvertGeoToDisplay(cs[0].x,cs[0].y,ptsUse->x,ptsUse->y);

	//
	for( i = 1 ; i < Size ; i++ )
	{
		ConvertGeoToDisplay(cs[i].x,cs[i].y,pt.x,pt.y);

		if( ptsUse->x != pt.x || ptsUse->y != pt.y )
		{
			ptsUse++;
			*ptsUse = pt;
		}
	}

	UseCount = ptsUse - pts + 1;
	if( UseCount < 3 )
	{
		for( ; UseCount < 3 && UseCount < Size ; UseCount++ )
		{
			pts[UseCount] = pts[UseCount-1];
		}
	}
}

void CDisplayTransformation::FitViewBound(const GEOMETRY::geom::Envelope &env, bool bFullFill)
{
	// 更新视图位置
	VIEW_POSITION &viewPos = m_viewPositon;
	viewPos.m_dGeoCenterX = ( env.getMinX() + env.getMaxX() ) / 2;
	viewPos.m_dGeoCenterY = ( env.getMinY() + env.getMaxY() ) / 2;
	double lHeight = viewPos.m_displayBound.bottom-viewPos.m_displayBound.top;
	double lWidth = viewPos.m_displayBound.right-viewPos.m_displayBound.left;
	if( lHeight == 0 || lWidth == 0 )
		viewPos.m_dScale = 1.f;
	else
	{
		double XSacle = abs(env.getMaxX() - env.getMinX() ) / lWidth;
		double YScale = abs(env.getMaxY() - env.getMinY() ) / lHeight;
		if( bFullFill )
			viewPos.m_dScale = XSacle<YScale ? XSacle:YScale; // 全屏
		else
			viewPos.m_dScale = XSacle>YScale ? XSacle:YScale; // 适合客户区大小
	}

	double val = SYSTEM::UnitConverter::ConvertUnits(1, m_unit, SYSTEM::SYS_UNIT_MILLIMETER);
	viewPos.m_dMapScale = viewPos.m_dScale * val / CDC::GetCreateDCsRateOfPixelAndMillimeter();

	gCallbackChangeViewPos(viewPos);
}



void CDisplayTransformation::TransformToGeo(const DIS_RECT &rect, GEOMETRY::geom::Envelope *pExtent)
{
    double dleft,dtop,dright,dbottom;
	ConvertDisplayToGeo(rect.left,rect.bottom,dleft,dbottom);
	ConvertDisplayToGeo(rect.right,rect.top,dright,dtop);
	pExtent->init(dleft,dright,dtop,dbottom);
}

double CDisplayTransformation::TransformToGeo(double dblDistance)
{
	return(dblDistance)*m_viewPositon.m_dScale;
}

void CDisplayTransformation::SetUnit(SYSTEM::SYS_UNIT_TYPE unit)
{
	m_unit = unit;
}

SYSTEM::SYS_UNIT_TYPE CDisplayTransformation::GetUnit()
{
	return m_unit;
}
void CDisplayTransformation::MillimeterToDisplay(double mmVal, long& disVal)
{
	double geoVal = SYSTEM::UnitConverter::ConvertUnits(mmVal, SYSTEM::SYS_UNIT_MILLIMETER, m_unit);
	ConvertGeoToDisplay( geoVal, disVal );
}

double CDisplayTransformation::MillimeterToGeo( double dmil )
{
	double dGeo = SYSTEM::UnitConverter::ConvertUnits( dmil, SYSTEM::SYS_UNIT_MILLIMETER, m_unit );

	return dGeo;
}

void CDisplayTransformation::ZoomViewPosScale(double ratio)
{
	m_viewPositon.m_dScale *= ratio;

	m_viewPositon.m_dMapScale *= ratio;

	gCallbackChangeViewPos(m_viewPositon);
}

void CDisplayTransformation::ZoomToFixScale(double scale)
{
	m_viewPositon.m_dMapScale *= scale/m_viewPositon.m_dScale;
	m_viewPositon.m_dScale = scale;
	gCallbackChangeViewPos(m_viewPositon);
}

void CDisplayTransformation::UpdateViewPosScale(double dblScale)
{
	m_viewPositon.m_dScale = dblScale;

	gCallbackChangeViewPos(m_viewPositon);
}

bool CDisplayTransformation::HasPreExtent()
{
   if(m_ViewStack.empty())
   {
	   return false;
   }
   if(m_curpos<=0)
   {
	   return false;
   }
   return true;

}

bool CDisplayTransformation::HasNextExtent()
{
	if(m_ViewStack.empty())
	{
		return false;
	}
	long num =m_ViewStack.size();

	return (m_curpos<(num-1));
}

void CDisplayTransformation::RemoveStack()
{
	if(m_curpos!=(m_ViewStack.size()-1))
	{
		int lstart =(m_curpos>=-1) ?(m_curpos+1) :0;

		m_ViewStack.erase(m_ViewStack.begin()+lstart,m_ViewStack.end());
	}
}

void CDisplayTransformation::SetPreExtent()
{
    if(!HasPreExtent())
	{
		return;
	}
	m_curpos--;
	FitViewBound(m_ViewStack[m_curpos]);
	
}

void CDisplayTransformation::SetNextExtent()
{
	if(!HasNextExtent())
	{
		return;
	}
	m_curpos++;
	FitViewBound(m_ViewStack[m_curpos]);

}

void CDisplayTransformation::RecordCurExtent(GEOMETRY::geom::Envelope& extent)
{
    RemoveStack();
	if(m_ViewStack.size()>19)
	{
		while(m_ViewStack.size()>19)
		{
            m_ViewStack.erase(m_ViewStack.begin());
		}
		m_curpos =m_ViewStack.size()-1;
	}

	//如果是第一条记录，则将之前的范围加入
    m_ViewStack.push_back(extent);
    m_curpos =m_ViewStack.size()-1;
}


}