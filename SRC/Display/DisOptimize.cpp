#include "stdafx.h"
#include "DisOptimize.h"
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <vector>
#include <assert.h>
#include "DisplayHeader.h"
//////////////////////////////////////////////////////////////////////////
//内部类
class SUBPOINT
{
public:
	INT_POINT pt;					// 点
	INT_POINT OffSgment[2];		// 偏移线段
	INT_POINT trueOffSegment[2];	// 真实偏移线
	INT_POINT *pCornerPoints;		// 倒角点
	bool   bIsOutAngle;
	bool   bIsfalseline;
	bool   bInUse;
	short  CornerPointCount;	// 倒角点个数
	double OffSgLength;			// 偏移线长度
	double SourceLength;		// 原始线长
	double OffSetSeg;			// 偏移长度
	SUBPOINT()
	{
			bInUse = true;
			bIsOutAngle = false;
			CornerPointCount= 0;
			bIsfalseline = false;
			OffSgLength = 0.0;
			SourceLength = 0.0;
			OffSetSeg = 0.0;
			memset(OffSgment , 0 , sizeof(INT_POINT)*2 );
			memset(trueOffSegment , 0 , sizeof(INT_POINT)*2 );
			memset(&pt , 0 , sizeof(INT_POINT) );
			pCornerPoints = false;
	};
	~SUBPOINT()
	{
			if( pCornerPoints != false ) 
				delete[] pCornerPoints;
			pCornerPoints = false;
	};
	// 增加的函数，原来线偏移没有，需要补充，（张敏）
	SUBPOINT& operator =(const SUBPOINT &sPoint)
	{
			memcpy(&pt,&sPoint.pt,sizeof(pt));
			memcpy(&OffSgment,&sPoint.OffSgment,sizeof(INT_POINT)*2);
			memcpy(&trueOffSegment,&sPoint.trueOffSegment,sizeof(INT_POINT)*2);
			if( pCornerPoints != false ) delete[]  pCornerPoints;
			CornerPointCount = sPoint.CornerPointCount;
			pCornerPoints = new INT_POINT[CornerPointCount];
			memcpy(pCornerPoints , sPoint.pCornerPoints , sizeof(INT_POINT)*CornerPointCount);

			bIsOutAngle = sPoint.bIsOutAngle;
			bIsfalseline = sPoint.bIsfalseline;
			OffSgLength = sPoint.OffSgLength;
			SourceLength= sPoint.SourceLength;
			OffSetSeg   = sPoint.OffSetSeg;
			bInUse      = sPoint.bInUse;
			return *this;
	};
	void SetCornerPointCount(short PCount)
	{
			if( pCornerPoints != false ) delete[]  pCornerPoints;
			CornerPointCount = PCount;
			pCornerPoints = new INT_POINT[CornerPointCount];
	}
};
typedef std::vector<SUBPOINT> SUBARRAY;
//typedef SYSTEM::CArray<SUBPOINT,SUBPOINT&> SUBARRAY;
typedef long (CALLBACK GETANGLE_FUNC)(INT_POINT Segment1[], INT_POINT Segment2[], INT_POINT &CrossPt, INT_POINT &SourcePoint , long Offset, INT_POINT **pINT_POINTs);


////////////////////////////////////////////////////////////////////////
//内联部分函数
// 函数名	: AngleEx
// 描述	    : 计算角度
// 返回值	: inline double 
// 参数     : POINT Point
// 参数     : POINT Origin
inline double AngleEx(INT_POINT &Point, INT_POINT &Origin)
{
	if(Point.x == Origin.x)
	{
		if(Point.y < Origin.y)
			return (1.5 * PI);
		else if (Point.y == Origin.y)
			return 0.0;
		else
			return (0.5 * PI);
	}
	else if(Point.y == Origin.y)
	{
		if(Point.x < Origin.x)
			return PI;
		else 
			return 0.0;
	}
	else
	{
		double dx = (double)(Point.x - Origin.x);
		double dy = (double)(Point.y - Origin.y);
		double angle = fabs(atan(dy/dx));
		if(dy >0.0)
		{
			if(dx>0.0)  
				return angle;
			else 
				return (PI - angle);
		}
		else 
		{
			if(dx>0.0)  
				return (2*PI - angle);
			else 
				return (PI + angle);
		}
	}
}

inline bool IsPointInSegEx(INT_POINT &point,INT_POINT &p1,INT_POINT &p2)
{
	if( p1.x == p2.x )
	{
		if( point.x != p1.x ) return false;
		if( point.y > p1.y && point.y > p2.y 
			|| point.y < p1.y && point.y < p2.y )
			return false;
		else
			return true;
	}
	else
	{
		if( abs(point.x - p1.x ) <= 40 
			&& abs(point.y - p1.y) <= 40 
			|| abs(point.x - p2.x ) <= 40 
			&& abs(point.y - p2.y) <= 40)
			return true;
		double t;
		if( p2.x == p1.x ) 
			t = 1;
		else
			t = (point.x - p1.x ) / (double)( p2.x - p1.x );
		double t2;
		if( p2.y == p1.y )
			t2 = 1;
		else
			t2 = (point.y - p1.y ) / (double)( p2.y - p1.y );
		if( (t > 1 || t < 0) || (t2 > 1 || t2 < 0) ) 
		{
			return false;
			double d = 5 / (double)(p2.x - p1.x );
			if( fabs(t) < fabs(d) )
				return true;
			else
				return false;
		}
		else 
			return true;
	}
}
// 函数名	: IsPointInSeg
// 描述	    : 点是否在线上
// 返回值	: inline bool 
// 参数     : INT_POINT &point
// 参数     : INT_POINT &p1
// 参数     : INT_POINT &p2
inline bool IsPointInSeg(INT_POINT &point,INT_POINT &p1,INT_POINT &p2)
{
	if( p1.x == p2.x )
	{
		if( point.x != p1.x ) return false;
		if( point.y > p1.y && point.y > p2.y 
			|| point.y < p1.y && point.y < p2.y )
			return false;
		else
			return true;
	}
	else
	{
		if( abs(point.x - p1.x ) <= 2 
			&& abs(point.y - p1.y) <= 2 
			|| abs(point.x - p2.x ) <= 2 
			&& abs(point.y - p2.y) <= 2 )
			return true;
		double t;
		if( p2.x == p1.x ) 
			t = 1;
		else
			t = (point.x - p1.x ) / (double)( p2.x - p1.x );
		double t2;
		if( p2.y == p1.y )
			t2 = 1;
		else
			t2 = (point.y - p1.y ) / (double)( p2.y - p1.y );
		if( (t > 1 || t < 0) || (t2 > 1 || t2 < 0) ) 
		{
			return false;
			double d = 5 / (double)(p2.x - p1.x );
			if( fabs(t) < fabs(d) )
				return true;
			else
				return false;
		}
		else 
			return true;
	}
}

// 函数名	: GetArc
// 描述	    : 离散弧段
// 返回值	: inline long 
// 参数     : INT_POINT &center
// 参数     : long R
// 参数     : INT_POINT &StartPoint
// 参数     : INT_POINT &EnINT_POINT
// 参数     : INT_POINT **pOutINT_POINT
inline long GetArc(INT_POINT &center, long R, INT_POINT &StartPoint,INT_POINT &EndPoint, INT_POINT **pOutDPOINT)
{
	double startPI = AngleEx( StartPoint , center );
	double endPI   = AngleEx( EndPoint , center );
	if( R < 0 )
	{
		if( endPI - startPI - PI > 0.0 )
			endPI = endPI - 2 * PI;
		if ( endPI - startPI + PI <= 1e-6 )
			startPI = startPI - 2 * PI;

	}
	else // if( R > 0 )
	{
		if( startPI - endPI <= -PI )
			endPI = endPI - 2 * PI;
		if ( startPI - endPI > PI )
			startPI = startPI - 2 * PI;
	}
	if( endPI == startPI )
		endPI += 2 * PI;

	long Scale = fabs(2*(fabs(endPI - startPI)/(PI/9.)+0.5)*R/10);
	long Count = Scale < 2.? 2 : long(Scale+0.5);
	if(Count > 25)
		Count = 25;
	double dd;
	if( Count != 1 )
	{
		dd = ( endPI - startPI ) / ( Count - 1 );
		*pOutDPOINT = new INT_POINT[Count+2];
	}
	else
	{
		_ASSERT(false);
		*pOutDPOINT = false;
		return 0;
	}
	long StartPos = 0;
	R = labs(R);
	if( dd > 0 )
	{
		for(double d = startPI ; d <= endPI ; d+= dd )
		{
			(*pOutDPOINT)[StartPos].x = long(center.x + R * cos( d ) + 0.5);
			(*pOutDPOINT)[StartPos].y = long(center.y + R * sin( d ) + 0.5);
			if( StartPos == 0 || !((*pOutDPOINT)[StartPos].x == (*pOutDPOINT)[StartPos-1].x
				&& (*pOutDPOINT)[StartPos].y == (*pOutDPOINT)[StartPos-1].y) )
				StartPos++;
		}
	}
	else
	{
		for(double d = startPI ; d >= endPI ; d+= dd )
		{
			(*pOutDPOINT)[StartPos].x = long(center.x + R * cos( d ) + 0.5);
			(*pOutDPOINT)[StartPos].y = long(center.y + R * sin( d ) + 0.5);
			if( StartPos == 0 || !((*pOutDPOINT)[StartPos].x == (*pOutDPOINT)[StartPos-1].x
				&& (*pOutDPOINT)[StartPos].y == (*pOutDPOINT)[StartPos-1].y) )
				StartPos++;
		}
	}
	(*pOutDPOINT)[StartPos].x = EndPoint.x;
	(*pOutDPOINT)[StartPos].y = EndPoint.y;
	return StartPos+1;
}


// 函数名	: OffsetSeg
// 描述	    : 计算偏移线
// 返回值	: inline void 
// 参数     : INT_POINT out_ps[]
// 参数     : INT_POINT ps[]
// 参数     : long &offset
inline void OffsetSeg(INT_POINT out_ps[],INT_POINT ps[],long &offset)
{
	double tmp,tmpx,tmpy,tmpoffx,tmpoffy;

	tmpx = ps[1].x-ps[0].x;
	tmpy = ps[1].y-ps[0].y;
	if ( abs(tmpx) > 0.001 && abs(tmpy) > 0.001 )
	{
		tmp  = sqrt( tmpx*tmpx + tmpy*tmpy );
		tmpoffx = offset * tmpy / tmp;
		tmpoffy = offset * tmpx / tmp;
		out_ps[0].x = long(ps[0].x - tmpoffx+0.5);
		out_ps[0].y = long(ps[0].y + tmpoffy+0.5);
		out_ps[1].x = long(ps[1].x - tmpoffx+0.5);
		out_ps[1].y = long(ps[1].y + tmpoffy+0.5);
	}
	else
	{
		out_ps[0].x = long(ps[0].x );
		out_ps[0].y = long(ps[0].y + offset );
		out_ps[1].x = long(ps[1].x );
		out_ps[1].y = long(ps[1].y + offset);
	}
};

inline bool GetCrossPointOfLine(INT_POINT Segment1[],INT_POINT Segment2[], INT_POINT &CrossPt)
{
	// 求交
	if( abs(Segment1[1].x - Segment2[0].x) <= 1 &&
		abs(Segment1[1].y - Segment2[0].y) <= 1 ||
		abs(Segment1[1].x - Segment2[1].x) <= 1 &&
		abs(Segment1[1].y - Segment2[1].y) <= 1 )
	{
		CrossPt.x = Segment1[1].x;
		CrossPt.y = Segment1[1].y;
	}
	else if( abs(Segment1[0].x - Segment2[1].x) <= 1 &&
		abs(Segment1[0].y - Segment2[1].y) <= 1 ||
		abs(Segment1[0].x - Segment2[0].x) <= 1 &&
		abs(Segment1[0].y - Segment2[0].y) <= 1 )
	{
		CrossPt.x = Segment1[0].x;
		CrossPt.y = Segment1[0].y;
	}
	else
	{
		if( (Segment1[1].x - Segment2[0].x)*(Segment1[1].x - Segment2[0].x) +
			(Segment1[1].y - Segment2[0].y)*(Segment1[1].y - Segment2[0].y) < 10 )
		{
			CrossPt.x = (Segment1[1].x + Segment2[0].x) / 2 + 0.5;
			CrossPt.y = (Segment1[1].y + Segment2[0].y) / 2 + 0.5;
			return true;
		}
		double DX21 = Segment1[1].x - Segment1[0].x;
		double DY21 = Segment1[1].y - Segment1[0].y;
		double DX43 = Segment2[1].x - Segment2[0].x;
		double DY43 = Segment2[1].y - Segment2[0].y;
		if( DX21*DY43 - DX43*DY21 == 0.0 )
		{
			CrossPt.x = ( Segment1[1].x + Segment2[0].x ) / 2;
			CrossPt.y = ( Segment1[1].y + Segment2[0].y ) / 2;
			return false;
		}
		else
		{
			double t = ( ( Segment2[0].x - Segment1[0].x )*DY43 - ( Segment2[0].y - Segment1[0].y )*DX43 ) / (DX21*DY43 - DX43*DY21 );
			CrossPt.x = (long)(Segment1[0].x + DX21 * t + 0.5);
			CrossPt.y = (long)(Segment1[0].y + DY21 * t + 0.5);
		}
	}
	return true;
}

// 函数名	: _OffsetlineRight
// 描述	    : 偏移线，返回链表,T = CLeftOffset 或者 CRightOffset
// 返回值	: inline  
// 参数     : long numPoint
// 参数     : INT_POINT *ps
// 参数     : SUBLIST &ptlist
inline void _Offsetline(long numPoint, INT_POINT *ps, SUBARRAY &ptArray, long Offset)
{
	INT_POINT Segment1[2],Segment2[2];
	OffsetSeg( Segment1 , ps , Offset );

	SUBPOINT sPt;
	INT_POINT CrossPt;
	INT_POINT *ps_ptr = ps;
	//	memset(&sPt,0,sizeof(SUBPOINT));
	sPt.pt = Segment1[0];
	memcpy(sPt.OffSgment , Segment1 , sizeof(INT_POINT)*2);
	ptArray.push_back( sPt );
	memcpy(Segment2 , Segment1 , sizeof(INT_POINT)*2);

	long i;
	for(i = 1 , ps++ ; i < numPoint-1 ; i++,ps++)
	{
		OffsetSeg( Segment2 , ps , Offset );

		GetCrossPointOfLine( Segment1 , Segment2 , CrossPt );

		sPt.pt = CrossPt;
		memcpy(sPt.OffSgment , Segment2 , sizeof(INT_POINT)*2);
		ptArray.push_back( sPt );
		// exchange
		memcpy(Segment1 , Segment2 , sizeof(INT_POINT)*2);
	}
	if( ps_ptr[0].x == ps[0].x && ps_ptr[0].y == ps[0].y )
	{
		OffsetSeg( Segment2 , ps_ptr , Offset );
		GetCrossPointOfLine( Segment1 , Segment2 , CrossPt );
		sPt.pt = CrossPt;
		memcpy(sPt.OffSgment , Segment2 , sizeof(INT_POINT)*2);
	}
	else
	{
		sPt.pt = Segment2[1];
		memset(sPt.OffSgment,0,sizeof(INT_POINT)*2);
		sPt.bInUse = false;
	}
	ptArray.push_back( sPt );

	for(i = 0 ; i < numPoint ; i++)
		memcpy(ptArray[i].trueOffSegment,ptArray[i].OffSgment,sizeof(INT_POINT)*2);
}

Display::CDisOptimize::CDisOptimize(void)
{
}

Display::CDisOptimize::~CDisOptimize(void)
{
}
///////////////////////////////////////////////////////////////
namespace Display{
template<class T>
class CSetFlagT
{

private:
	UINT    m_numPoint;				//点的个数
	bool*	m_pFlag;				//标记：true　点有效（初值）
	//　　　false：点无效
	T *  m_pDist;				//点到线段的最短距离(临时)
	T *  m_pPoints;				//点集的指针
	T  m_nLength;					//点与线段最短距离的阀值（容差）

public:

	CSetFlagT(T * pPoints, UINT numPoint, T length);
	~CSetFlagT();

	//外调函数
	//线抽稀点，产生新的线（WKBLineString）
	//返回点数
	UINT CreatePoints(T **pRetPoints);

private:
	//递归函数
	//设置m_pFlag 
	void CaleFlag(UINT start, UINT end);

};

}

//内部函数
//////////////////////////////////////////////////////////////////////////


// 函数名	: IsOutAngle
// 描述	    : 判断内外角
// 返回值	: inline bool 
// 参数     : INT_POINT ps[]
// 参数     : long Offset
inline bool IsOutAngle(INT_POINT ps[], long Offset)
{
	double td = ( ps[2].x - ps[0].x ) * ( ps[1].y - ps[0].y );
	double td2 = ( ps[2].y - ps[0].y ) * ( ps[1].x - ps[0].x );

	if( td < td2 )
	{
		if( Offset > 0 ) // 内角
			return false;
		else	// 外角
			return true;
	}
	else if( td == td2 )
		return true;
	else
	{
		if( Offset > 0 ) 
			return true;
		else	// 外角
			return false;
	}
};

inline void ReleaseAngle(INT_POINT *pDPOINTs)
{
	delete[] pDPOINTs;
};

// 不倒角
long CALLBACK GetAnglefalse(INT_POINT Segment1[], INT_POINT Segment2[], INT_POINT &CrossPt, INT_POINT &SourcePoint , long Offset, INT_POINT **pDPOINTs)
{
	*pDPOINTs = new INT_POINT[3];
	memcpy(*pDPOINTs , &(Segment1[1]) , sizeof(INT_POINT) );
	memcpy(*pDPOINTs+1 , &(CrossPt) , sizeof(INT_POINT) );
	memcpy(*pDPOINTs+2 , &(Segment2[0]) , sizeof(INT_POINT) );
	return 3;
};

// 倒圆角
long CALLBACK GetAngleArc(INT_POINT Segment1[], INT_POINT Segment2[], INT_POINT &CrossPt, INT_POINT &SourcePoint , long Offset, INT_POINT **pDPOINTs)
{
	if( Segment1[1].x == Segment2[0].x 
		&& Segment1[1].y == Segment2[0].y )
	{
		*pDPOINTs = new INT_POINT;
		memcpy(*pDPOINTs , &(Segment1[1]) , sizeof(INT_POINT) );
		return 1;
	}
	return GetArc( SourcePoint, Offset, Segment1[1], Segment2[0], pDPOINTs );
};

// 倒切角
long CALLBACK GetAngleCut(INT_POINT Segment1[], INT_POINT Segment2[], INT_POINT &CrossPt, INT_POINT &SourcePoint , long Offset, INT_POINT **pDPOINTs)
{
	*pDPOINTs = new INT_POINT[4];
	INT_POINT *p = *pDPOINTs;
	long Count = 0;
	double t,DX,DY;
	INT_POINT cPt[2],CrossPt2;
	DX = CrossPt.x-SourcePoint.x;
	DY = CrossPt.y-SourcePoint.y;
	t = labs(Offset) / sqrt(DX*DX+DY*DY);
	if( t >= 1. )
	{
		memcpy(*pDPOINTs , &CrossPt , sizeof(INT_POINT) );
		Count = 1;
	}
	else
	{
		_ASSERT( t < 1. );
		cPt[0].x = (long)(SourcePoint.x + t * DX+0.5);
		cPt[0].y = (long)(SourcePoint.y + t * DY+0.5);
		if( DY == 0.0 )
		{
			cPt[1].x = cPt[0].x;
			cPt[1].y = 0.0;
		}
		else
		{
			cPt[1].x = 0;
			cPt[1].y = (long)(cPt[0].y + cPt[0].x * DX / DY+0.5);
		}
		memcpy( p++ , &Segment1[1] , sizeof(INT_POINT) );
		Count++;
		//		if( IsPointInSeg( pSubPoint[0].OffSgment[1] , pSubPoint[0].pt , pSubPoint[1].pt ) )
		{
			GetCrossPointOfLine( Segment1 , cPt ,  CrossPt2 );
			memcpy( p++ , &CrossPt2 , sizeof(INT_POINT) );
			Count++;
		}
		//		if( IsPointInSeg( pSubPoint[1].OffSgment[0] , pSubPoint[1].pt , pSubPoint[2].pt ) )
		{
			::GetCrossPointOfLine( Segment2 , cPt ,  CrossPt2 );
			memcpy( p++ , &CrossPt2 , sizeof(INT_POINT) );
			Count++;
		}
		memcpy( p++ , &Segment2[0] , sizeof(INT_POINT) );
		Count++;
	}
	return Count;
}

// 内外角及有效线判断，同时调用倒角函数
inline void TrimLine(SUBPOINT *pSubPoint,SUBPOINT *pSubPoint2, INT_POINT **pDPOINTs, INT_POINT *pSource , long Offset , GETANGLE_FUNC Func)
{
	// 如果已经没有有效线段

	pSubPoint->bIsOutAngle = IsOutAngle( pSource , Offset );
	if( !pSubPoint->bIsOutAngle ) 
	{
		// 内角
		bool bFirstR = IsPointInSegEx(
			pSubPoint2->pt,pSubPoint->OffSgment[0],pSubPoint->OffSgment[1]);
		bool bSecondR= IsPointInSegEx(
			pSubPoint2->pt,pSubPoint2->OffSgment[0],pSubPoint2->OffSgment[1]);
		if( bFirstR && bSecondR )
		{  // 交点在两条线上正常内角/* /\ */

			// 线段1的有效线段截取末尾
			pSubPoint->trueOffSegment[1] = pSubPoint2->pt;
			// 线段2的有效线段截取头部
			pSubPoint2->trueOffSegment[0] = pSubPoint2->pt;
			return;
		}
		else if( bSecondR )
		{  
			// 交点在第二条线段上
			// 第一条线段没有有效线段，且没有倒角数据
			pSubPoint->trueOffSegment[1] = pSubPoint->trueOffSegment[0];
			pSubPoint->bIsfalseline = true;
			// 第二条截取尾部分
			pSubPoint2->trueOffSegment[0] = pSubPoint2->pt;
		}
		else if( bFirstR )
		{  
			// 交点在第1条线段上
			// 第2条线段没有有效线段，且没有倒角数据
			pSubPoint2->trueOffSegment[1] = pSubPoint2->trueOffSegment[0];
			pSubPoint2->bIsfalseline = true;
			// 第1条截取头部分
			pSubPoint->trueOffSegment[1] = pSubPoint2->pt;
		}
		else
		{
			// 第二条线段上没有交点,交点无效
			// 线段1没有有效线段,退化到起点
			//pSubPoint->trueOffSegment[1] = pSubPoint->trueOffSegment[0];
			pSubPoint->bIsfalseline = true;
			// 线段２没有有效线段,退化到终点
			//pSubPoint2->trueOffSegment[0] = pSubPoint2->trueOffSegment[1];
			pSubPoint2->bIsfalseline = true;
		}
	}
	else
	{
		// 外角倒角
		pSubPoint->CornerPointCount = Func(
			pSubPoint->OffSgment , pSubPoint2->OffSgment , 
			pSubPoint2->pt , pSource[1] , Offset , &pSubPoint->pCornerPoints );
	}
}


// 函数名	: IsSegmentCross
// 描述	    : 判断直线段是否相交
// 返回值	: inline bool 
// 参数     : INT_POINT pt1[]
// 参数     : INT_POINT pt2[]
inline bool IsSegmentCross(INT_POINT pt1[],INT_POINT pt2[],INT_POINT &CrossPt)
{
	if( !GetCrossPointOfLine( pt1, pt2 , CrossPt ) ) 
		return false;

	if( IsPointInSeg( CrossPt,pt1[0],pt1[1] )
		&& IsPointInSeg( CrossPt,pt2[0],pt2[1] ) )
		return true;
	else
		return false;
}

// 函数名	: SetCrossOver
// 描述	    : 判断折线是否相交，如果相交，按照走向截取，并返回true
// 返回值	: inline bool 
// 参数     : INT_POINT pt1[]
// 参数     : long &pt1Count
// 参数     : INT_POINT pt1[]
// 参数     : long &pt1Count
inline bool SetCrossOver(INT_POINT pt1[],short &pt1Count,INT_POINT pt2[],short &pt2Count)
{
	pt1Count--;
	pt2Count--;
	INT_POINT CrossPt;
	for(long i = 0 ; i < pt1Count ; i++ )
		for(long j = 0 ; j < pt2Count ; j++)
		{
			if( IsSegmentCross( &pt1[i] , &pt2[j] , CrossPt ) )
			{
				pt1[i+1] = CrossPt;
				pt1Count = i+1+1;
				pt2[0] = CrossPt;
				j++;
				long k = 1;
				for( ; j < pt2Count+1 ; j++,k++)
					pt2[k] = pt2[j];
				pt2Count = k;
				return true;
			}
		}
		pt1Count++;
		pt2Count++;
		return false;
}


// 函数名	: SetCrossOverEx
// 描述	    : pt1作为直线，求交，并修改pt2
// 返回值	: inline bool 
// 参数     : INT_POINT pt1[]
// 参数     : short &pt1Count
// 参数     : INT_POINT pt2[]
// 参数     : short &pt2Count
inline bool SetCrossOverEx(INT_POINT pt1[],INT_POINT pt2[],short &pt2Count)
{
	pt2Count--;
	INT_POINT CrossPt;
	for(long j = 0 ; j < pt2Count ; j++)
	{
		GetCrossPointOfLine( pt1, &pt2[j] , CrossPt );

		if( IsPointInSeg( CrossPt,pt2[j],pt2[j+1] ) )
		{
			pt2[0] = CrossPt;
			j++;
			long k = 1;
			for( ; j < pt2Count+1 ; j++,k++)
				pt2[k] = pt2[j];
			pt2Count = k;
			return true;
		}
	}
	pt2Count++;
	return false;
}
inline bool SetCrossOverEx2(INT_POINT pt1[],INT_POINT pt2[],short &pt2Count)
{
	pt2Count--;
	INT_POINT CrossPt;
	for(long j = pt2Count-1 ; j >= 0 ; j--)
	{
		GetCrossPointOfLine( pt1, &pt2[j] , CrossPt );

		if( IsPointInSeg( CrossPt,pt2[j],pt2[j+1] ) )
		{
			pt2[j+1] = CrossPt;
			j++;
			pt2Count = j;
			return true;
		}
	}
	pt2Count++;
	return false;
}
// 函数名	: _TrimlineToPOINTS
// 描述	    : 整理倒角
// 返回值	: inline long 
// 参数     :  offset
// 参数     : list
// 参数     : (INT_POINT*)ps
// 参数     : out_p
inline void _TrimlineCorner(long offset ,SUBARRAY &ptArray , INT_POINT* ps , GETANGLE_FUNC Func)
{
	//SUBPOINT* ptArray = ptArray[0];
	long i;
	long Count = ptArray.size();

	for( i = 0 ; i < Count-2 ; i++)
		TrimLine( &ptArray[i] , &ptArray[i+1], &(ptArray[i].pCornerPoints) , &ps[i] , offset , Func );

	if( ptArray[i+1].bInUse )
	{
		INT_POINT TMP[3];
		memcpy( TMP , &ps[i] , sizeof(INT_POINT)*2 );
		memcpy( TMP+2 , &ps[1] , sizeof(INT_POINT) );
		TrimLine( &ptArray[i] , &ptArray[i+1], &(ptArray[i].pCornerPoints) , TMP , offset , Func );
		if( !ptArray[i].bIsOutAngle )
		{
			ptArray[0].trueOffSegment[0] = ptArray[i+1].trueOffSegment[0];
		}
	}
	else
	{
		ptArray[i].bIsOutAngle = true;
	}
	ptArray[i+1].bIsfalseline = true;

	short TMP = 2,TMP2 = 2;
	// 整理外角+无效线+外角的情况，处理间隔外角的相交情况
	for( i = 1 ; i < Count ; i++)
	{
		// 判断&& ptArray[i].bIsOutAngle
		if(  !ptArray[i-1].bIsOutAngle  )
		{
			INT_POINT Offset1[2];
			INT_POINT Offset2[2];
			if( i>=2 )
			{
				memcpy(Offset2,(ptArray[i].OffSgment),sizeof(INT_POINT));
				memcpy(&Offset2[1],&(ptArray[i].trueOffSegment[1]),sizeof(INT_POINT));
				if( SetCrossOver(ptArray[i-2].pCornerPoints,ptArray[i-2].CornerPointCount,
					Offset2 , TMP2 ) )
				{
					ptArray[i].bIsfalseline = false;
					ptArray[i-1].bIsfalseline = true;
					memcpy(ptArray[i].trueOffSegment,Offset2,sizeof(INT_POINT)*2);
					//					continue;
				}
				// 先看看前一个外角的倒角是否相交
				if( ptArray[i-2].bIsOutAngle && i < Count-1 )
				{
					if( SetCrossOver(ptArray[i-2].pCornerPoints,ptArray[i-2].CornerPointCount,
						ptArray[i].pCornerPoints , ptArray[i].CornerPointCount ) )
					{
						ptArray[i-1].bIsfalseline = true;
						ptArray[i].bIsfalseline = true;

						//						continue;
					}
					memcpy(Offset2,(ptArray[i+1].OffSgment),sizeof(INT_POINT));
					memcpy(&Offset2[1],&(ptArray[i+1].trueOffSegment[1]),sizeof(INT_POINT));
					if( SetCrossOver(ptArray[i-2].pCornerPoints,ptArray[i-2].CornerPointCount,
						Offset2 , TMP2 ) )
					{
						memcpy(ptArray[i+1].trueOffSegment,Offset2,sizeof(INT_POINT)*2);
						ptArray[i].bIsfalseline = true;
						ptArray[i-1].bIsfalseline = true;
						delete[] ptArray[i].pCornerPoints;
						ptArray[i].pCornerPoints = false;
						ptArray[i].CornerPointCount = 0;
						delete[] ptArray[i-1].pCornerPoints;
						ptArray[i-1].pCornerPoints = false;
						ptArray[i-1].CornerPointCount = 0;
						ptArray[i+1].bIsfalseline = false;
						//						continue;
					}
					memcpy(Offset1,&(ptArray[i-2].trueOffSegment),sizeof(INT_POINT));
					memcpy(&Offset1[1],&(ptArray[i-2].OffSgment[1]),sizeof(INT_POINT));
					memcpy(Offset2,(ptArray[i].OffSgment),sizeof(INT_POINT));
					memcpy(&Offset2[1],&(ptArray[i].trueOffSegment[1]),sizeof(INT_POINT));
					if( SetCrossOver(Offset1,TMP,
						Offset2 , TMP2 ) )
					{
						memcpy(ptArray[i-2].trueOffSegment,Offset1,sizeof(INT_POINT)*2);
						memcpy(ptArray[i].trueOffSegment,Offset2,sizeof(INT_POINT)*2);
						delete[] ptArray[i-2].pCornerPoints;
						ptArray[i-2].pCornerPoints = false;
						ptArray[i-2].CornerPointCount = 0;
						ptArray[i].bIsfalseline = false;
						//						continue;
					}
				}
			}
			memcpy(Offset1,&(ptArray[i-1].trueOffSegment),sizeof(INT_POINT));
			memcpy(&Offset1[1],&(ptArray[i-1].OffSgment[1]),sizeof(INT_POINT));
			if( i >= 2)
			{
				// 先看看外角的倒角与前的偏移线是否相交
				if( SetCrossOver(Offset1,TMP,
					ptArray[i].pCornerPoints , ptArray[i].CornerPointCount ) )
				{
					ptArray[i-1].bIsfalseline = false;
					ptArray[i].bIsfalseline = true;
					memcpy(ptArray[i-1].trueOffSegment,Offset1,sizeof(INT_POINT)*2);
					//				continue;
				}
			}
			// 前的偏移线与后偏移线段有交点
			if( i!= Count-1 && !ptArray[i+1].bIsfalseline )
			{
				memcpy(Offset2,(ptArray[i+1].OffSgment),sizeof(INT_POINT));
				memcpy(&Offset2[1],&(ptArray[i+1].trueOffSegment[1]),sizeof(INT_POINT));
				if( SetCrossOver( Offset1, TMP,
					Offset2 , TMP2 ) )
				{
					// 放弃倒角，彻底放弃该线
					if( ptArray[i].bIsOutAngle )
					{
						delete[] ptArray[i].pCornerPoints;
						ptArray[i].pCornerPoints = false;
						ptArray[i].CornerPointCount = 0;
						memcpy(ptArray[i-1].trueOffSegment,Offset1,sizeof(INT_POINT)*2);
						ptArray[i-1].bIsfalseline = false;
						memcpy(ptArray[i+1].trueOffSegment,Offset2,sizeof(INT_POINT)*2);
						ptArray[i+1].bIsfalseline = false;
					}
					//					continue;
				}
			}
			// 先看看倒角和下两条偏移线是否相交
			if( i<Count-2 && !ptArray[i+2].bIsfalseline )
			{
				memcpy(Offset2,ptArray[i+2].OffSgment,sizeof(INT_POINT));
				memcpy(&Offset2[1],&(ptArray[i+2].trueOffSegment[1]),sizeof(INT_POINT));
				if( SetCrossOver(ptArray[i].pCornerPoints,ptArray[i].CornerPointCount,
					Offset2 , TMP2 ) )
				{
					memcpy(ptArray[i+2].trueOffSegment,Offset2,sizeof(INT_POINT)*2);
					//					continue;
				}
			}
		}
	}
	// 从前端判断是否有需要切外角
	for( i = 0 ; i < Count ; i++)
	{
		if( !ptArray[i].bIsfalseline ) break;
		if( ptArray[i].bIsOutAngle && ptArray[i].CornerPointCount != 0 )
		{
			// 用前一条线为延长切割线切外角
			_ASSERT( i != 0 );
			if( !SetCrossOverEx( ptArray[i-1].OffSgment ,
				ptArray[i].pCornerPoints , ptArray[i].CornerPointCount ) )
			{
				if( ptArray[i].bIsOutAngle )
				{
					delete[] ptArray[i].pCornerPoints;
					ptArray[i].pCornerPoints = false;
					ptArray[i].CornerPointCount = 0;
					continue;
				}
			}
			if( ptArray[i].CornerPointCount == 1 )
			{
				if( ptArray[i].bIsOutAngle )
				{
					delete[] ptArray[i].pCornerPoints;
					ptArray[i].pCornerPoints = false;
					ptArray[i].CornerPointCount = 0 ;
				}
			}
			break;
		}
	}
	// 从后端判断是否有需要切外角
	for( i = Count-3 ; i >= 0 ; i--)
	{
		if( !ptArray[i+1].bIsfalseline ) break;
		if( ptArray[i].bIsOutAngle && ptArray[i].CornerPointCount != 0 )
		{
			// 用前一条线为延长切割线切外角
			//			ASSERT( i != 0 );
			if( !SetCrossOverEx2( ptArray[i+2].OffSgment ,
				ptArray[i].pCornerPoints , ptArray[i].CornerPointCount ) )
			{
				delete[] ptArray[i].pCornerPoints;
				ptArray[i].pCornerPoints = false;
				ptArray[i].CornerPointCount = 0 ;
				continue;
			}
			if( ptArray[i].CornerPointCount == 1 )
			{
				delete[] ptArray[i].pCornerPoints;
				ptArray[i].pCornerPoints = false;
				ptArray[i].CornerPointCount = 0 ;
			}
			break;
		}
	}
	// 消除无需的外角，条件为前线和后线都为空
	/*	for( i = 0 ; i < Count ; i++)
	{
	if( ptArray[i].bIsfalseline && ptArray[i+1].bIsfalseline 
	&& ptArray[i].CornerPointCount != 0 )
	{
	ptArray[i].CornerPointCount = 0;
	delete[] ptArray[i].pCornerPoints;
	ptArray[i].pCornerPoints = false;
	}
	}*/
}

inline long _GetSoliDIS_LINE(long **out_p , SUBARRAY &ptArray)
{
	long i,PtCount = 0, Count = ptArray.size();
	for( i  = 0 ; i < Count ; i++)
	{
		if( !ptArray[i].bIsfalseline )
			PtCount += 2;
		PtCount += ptArray[i].CornerPointCount;
	}
	*out_p = new long[PtCount*2+4];
	INT_POINT *p = (INT_POINT*)*out_p;

	// Start

	for(i = 0 ; i < Count ; i++)
	{
		if( !ptArray[i].bIsfalseline )
		{
			if( (ULONGLONG)p != (ULONGLONG)*out_p && !(p->x == ptArray[i].trueOffSegment[0].x && 
				p->y == ptArray[i].trueOffSegment[0].y ) )
				p++;
			memcpy(p++ , ptArray[i].trueOffSegment , sizeof(INT_POINT)*2 );

		}
		if( ptArray[i].CornerPointCount != 0 )
		{
			if( (ULONGLONG)p != (ULONGLONG)*out_p && !(p->x == ptArray[i].pCornerPoints[0].x && 
				p->y == ptArray[i].pCornerPoints[0].y ) )
				p++;
			memcpy(p , ptArray[i].pCornerPoints , 
				sizeof(INT_POINT)*ptArray[i].CornerPointCount );
			p+= ptArray[i].CornerPointCount-1;
		}
	}
	PtCount = ((ULONGLONG)p - (ULONGLONG)*out_p) / sizeof(INT_POINT);
	if(PtCount <=0)
	{
		delete [](*out_p);
		*out_p = false;
		return 0;
	}
	else
		return PtCount+1;
}
/*
// 函数名	: OffsetLine
// 描述	    : 连续线偏移
// 返回值	: long 
// 参数     : long numPoint
// 参数     : POINT *ps
// 参数     : long offset , 大于0 为左,小于0 为右
// 参数     : unsigned char AngleType 倒角类型
// 参数     : POINT **out_p
long OffsetSoliDIS_LINE(long numPoint, long *ps,long offset,unsigned char AngleType, long **out_p)
{
ASSERT( *out_p  == false );

SUBARRAY ptArray;
if( offset == 0 )
{
*out_p = new long[numPoint*2];
memcpy(out_p,ps,numPoint*2*sizeof(long));
return numPoint;
}
else
{
// 计算偏移线
_Offsetline( numPoint , (INT_POINT*)ps, ptArray , offset );

// 整理内外角关系以及倒角
_TrimlineCorner( offset , ptArray , (INT_POINT*)ps , 
AngleType == 1? GetAngleCut:GetAngleArc );

// 整理结果，并采样
return _GetSoliDIS_LINE( out_p , ptArray );
}
return -1;
}

*/
//////////////////////////////////////////////////////////////////////////

//内部函数
template <class T>
double calculate_angle(T point1[2],T point2[2])
{
	T dx2 = point2[0] - point1[0];
	T dy2 = point2[1] - point1[1];
	if(dx2 == 0)	//denominator is zero
	{
		if(dy2 < 0)
			return _3PI2;
		else if(dy2 == 0)
			return 0;
		else
			return _PI2;
	}
	else
	{
		double fTmp = atan((double)dy2/(double)dx2);
		if(dy2 < 0)
		{
			if(dx2 < 0)				//quanrant 3
				return (fTmp + _PI);
			else						//quanrant 4
				return (fTmp + _2PI);
		}
		else
		{
			if(dx2 < 0)				//quanrant 2
				return (fTmp + _PI);
			else						//quanrant 1
				return fTmp;
		}
	}	
}


// 内部函数
// 转换直线角度－＞椭圆方程的角度　
double T_Angle(double a,double b,double sAngle)
{
double ret;
if(fabs(sAngle-_PI2) < 0.001 || fabs(sAngle-_3PI2) < 0.001)
ret = sAngle; 
else 
{
ret = atan(a*tan(sAngle)/b );
if(sAngle > _3PI2)
ret += _2PI ;
else if(sAngle > _PI2)
ret += _PI;
}
return ret;
}


//内部函数
void RotatePoint(long& x,long& y,long OrgX,long OrgY,double angle)
{
	double fx,fy,s,c;
	s = sin(-angle);
	c = cos(-angle);
	fx = x - OrgX;
	fy = y - OrgY;
	x = fy * s + fx * c + OrgX + 0.5;
	y = fy * c - fx * s + OrgY + 0.5;
}

//内部函数
bool IsInScope(long pt[2],INT_POINT segment[2])
{
	long minx,miny,maxx,maxy;
	if(segment[0].x < segment[1].x)
	{
		minx = segment[0].x;
		maxx = segment[1].x;
	}
	else
	{
		maxx = segment[0].x;
		minx = segment[1].x;
	}
	if(segment[0].y < segment[1].y)
	{
		miny = segment[0].y;
		maxy = segment[1].y;
	}
	else
	{
		maxy = segment[0].y;
		miny = segment[1].y;
	}
	if(pt[0] < minx-1 || pt[0] > maxx+1 || pt[1] < miny-1 || pt[1] > maxy+1)
		return false;
	return true;
}

//内部函数
void GetPolygonBox(long PointCount,const long* pSourPolygon,long& minxRet, long& minyRet,long& maxxRet,long& maxyRet)
{
	long X,Y;
	long minY  = 10E15; 
	long minX  = 10E15; 
	long maxX = -10E15;
	long maxY = -10E15;
	for(long i=0; i<PointCount; i++)
	{
		X = pSourPolygon[2*i];
		Y = pSourPolygon[2*i+1];
		if(X > maxX)
			maxX = X;
		if(X < minX)
			minX = X;
		if(Y > maxY)
			maxY = Y;
		if(Y < minY)
			minY = Y;
	}
	minxRet =  minX;
	maxxRet =  maxX;
	minyRet =  minY;
	maxyRet =  maxY;
}

//////////////////////////////////////////////////////////////////////////

//1.5.1矩形
void GetRectBoxByRotate(const  long * pData, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	long x,y,ctX,ctY;
	long * p = (long*)pData;
	ctX = (*p + *(p+2))/2;
	ctY = (*(p+1) + *(p+3))/2;
	x = *p;
	y = *(p+1);
	RotatePoint(x,y,ctX,ctY,Angle);
	minx = maxx = x;
	miny = maxy = y;

	for(UINT i= 0;i< 3; i++)
	{
		x = *(p+2);
		y = *(p+1);
		if(i == 2)
			x = *p;
		if(i > 0)
			y = *(p+3);
		RotatePoint(x,y,ctX,ctY,Angle);
		if(minx > x) 
			minx = x;
		if(maxx < x)
			maxx = x;
		if(miny > y) 
			miny = y;
		if(maxy < y)
			maxy = y;
	}
}


//1.5.2椭圆
void GetEllipseBoxByRotate(const  long * pData, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	long * p = (long*)pData;
	long a = fabs((*(p+2) - *p)/2+0.5);
	long b = fabs((*(p+3) - *(p+1))/2+0.5);
	double s = sin(Angle);
	double c = cos(Angle);
	INT_POINT CtPoint;
	CtPoint.x = (*p + *(p+2))/2+0.5;
	CtPoint.y = (*(p+1) + *(p+3))/2+0.5;
	if(fabs(Angle) < 0.001)
	{
		minx = CtPoint.x - a;
		miny = CtPoint.y - b;
		maxx = CtPoint.x + a;
		maxy = CtPoint.y + b;
		return;
	}
	double y1,x2,y3,x4,fx,fy;
	double tanRA = tan(Angle);
	double cosf = a*tanRA/sqrt(b*b+a*a*tanRA*tanRA);
	double Ag = acos( -cosf );
	fx = a * cos(Ag) ;
	fy = b * sin(Ag) ;
	y1 = fy * c - fx * s + CtPoint.y;
	fx = -a * cos(Ag);
	fy = -b * sin(Ag);
	y3 = fy * c - fx * s + CtPoint.y;
	if(y1 < y3)
	{
		miny = y1;
		maxy = y3+1;
	}
	else
	{
		miny = y3;
		maxy = y1+1;
	}
	tanRA = 1/tanRA;
	cosf = a*tanRA/sqrt(b*b+a*a*tanRA*tanRA);
	Ag = acos( cosf );
	fx = a * cos(Ag) ;
	fy = b * sin(Ag) ;
	x2 = fy * s + fx * c + CtPoint.x;
	fx = -a * cos(Ag);
	fy = -b * sin(Ag);
	x4 = fy * s + fx * c + CtPoint.x;
	if(x2 < x4)
	{
		minx = x2;
		maxx = x4+1;
	}
	else
	{
		minx = x4;
		maxx = x2+1;
	}
}

//1.5.3圆角矩形
void GetRoundRectBoxByRotate(const  long * pData, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	long * p = (long*)pData;
	long w = labs((*(p+2) - *p)/2+1);
	long h = labs((*(p+3) - *(p+1))/2+1);
	long a = labs(*(p+4)/2+0.5);
	long b = labs(*(p+5)/2+0.5);
	if(a > w)
		a = w;
	if(b > h)
		b = h;
	double s = sin(Angle);
	double c = cos(Angle);
	INT_POINT CtPoint;
	CtPoint.x = (*p + *(p+2))/2+0.5;
	CtPoint.y = (*(p+1) + *(p+3))/2+0.5;
	if(fabs(Angle) < 0.001)
	{
		minx = CtPoint.x - w;
		miny = CtPoint.y - h;
		maxx = CtPoint.x + w;
		maxy = CtPoint.y + h;
		return;
	}
	long mix,miy,max,may;
	double y1,x2,y3,x4,fx,fy;
	double tanRA = tan(Angle);
	double cosf = a*tanRA/sqrt(b*b+a*a*tanRA*tanRA);
	double Ag = acos( -cosf );
	fx = a * cos(Ag) ;
	fy = b * sin(Ag) ;
	y1 = fy * c - fx * s ;
	fx = -a * cos(Ag);
	fy = -b * sin(Ag);
	y3 = fy * c - fx * s ;
	if(y1 < y3)
	{
		miy = y1;
		may = y3+1;
	}
	else
	{
		miy = y3;
		may = y1+1;
	}
	tanRA = 1/tanRA;
	cosf = a*tanRA/sqrt(b*b+a*a*tanRA*tanRA);
	Ag = acos( cosf );
	fx = a * cos(Ag) ;
	fy = b * sin(Ag) ;
	x2 = fy * s + fx * c ;
	fx = -a * cos(Ag);
	fy = -b * sin(Ag);
	x4 = fy * s + fx * c ;
	if(x2 < x4)
	{
		mix = x2;
		max = x4+1;
	}
	else
	{
		mix = x4;
		max = x2+1;
	}
	/////////////////////
	long dx1,dy1,dx2,dy2;
	dx1 = dx2 = w-a;
	dy1 = dy2 = h-b;
	RotatePoint(dx1,dy1,0,0,Angle);
	RotatePoint(dx2,dy2,0,0,-Angle);
	dx1 = labs(dx1)>labs(dx2)?labs(dx1):labs(dx2);
	dy1 = labs(dy1)>labs(dy2)?labs(dy1):labs(dy2);
	minx = mix + CtPoint.x - dx1;
	maxx = max + CtPoint.x + dx1;
	miny = miy + CtPoint.y - dy1;
	maxy = may + CtPoint.y + dy1;
}

//内部函数
//set max min XY
void SetMMXY(double x,double y,long &minx,long &miny,long &maxx,long &maxy)
{
	if(minx > x)
		minx = x;
	if(maxx < x)
		maxx = x;
	if(miny > y)
		miny = y;
	if(maxy < y)
		maxy = y;
}


//内部函数
void MoveBox(long&  minx,  long& maxx, long& miny, long& maxy , long OrgX,long OrgY,long rotX,long rotY,double angle)
{
	long dltX = rotX;
	long dltY = rotY;
	RotatePoint(dltX,dltY,OrgX,OrgY,angle);
	dltX = rotX - dltX;
	dltY = rotY - dltY;
	minx += dltX;
	maxx += dltX;
	miny += dltY;
	maxy += dltY;
}


//1.5.12椭圆
void GetEllipseBoxByRotateEx(const  long * pData,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	GetEllipseBoxByRotate(pData,Angle , minx, maxx,miny,maxy );
	long OrgX = (*pData + *(pData+2))/2+ 0.5 ;
	long OrgY = (*(pData+1) + *(pData+3))/2+ 0.5 ;
	MoveBox(minx, maxx,miny,maxy,OrgX,OrgY,rotX,rotY,Angle);
}


//内部函数
void GetRealArcBoxByRotate(const  long * pData, double Angle ,long rotX,long rotY, long&  minx,  long& maxx, long& miny, long& maxy )
{
	long a,b;
	if(fabs(Angle)< 0.001)
	{
		Display::CDisOptimize::GetArcBox(pData,false,minx, miny,maxx, maxy);
		return;
	}
	bool b1,b2,b3,b4;
	b1 = b2 = b3 = b4 = false;
	double Ag1,Ag2,Ag;
	minx = miny = 10E16;
	maxx = maxy = -10E16;
	long * p = (long*)pData;
	a = labs((*(p+2) - *p)/2+1);
	b = labs((*(p+3) - *(p+1))/2+1);
	double s = sin(Angle);
	double c = cos(Angle);
	INT_POINT StartPoint,EndPoint,CtPoint;
	CtPoint.x = (*p + *(p+2))/2+0.5;
	CtPoint.y = (*(p+1) + *(p+3))/2+0.5;
	memcpy(&StartPoint,p+4,2*sizeof(long));
	memcpy(&EndPoint,p+6,2*sizeof(long));
	double startAngle = calculate_angle((long*)&CtPoint,(long*)&StartPoint);
	double endAngle = calculate_angle((long*)&CtPoint,(long*)&EndPoint);
	if(fabs(endAngle - startAngle) < 0.001)
	{
		GetEllipseBoxByRotateEx(pData, rotX,rotY,Angle, minx, maxx, miny,maxy);
		return;
	}
	startAngle = T_Angle(a,b,startAngle);
	endAngle = T_Angle(a,b,endAngle);
	long  pRetPoint[4];
	if(Display::CDisOptimize::GetArcAccurateBeingEndPoint(pData, pRetPoint)!=2)
	{
		minx = miny = maxx = maxy = 0;
		return;
	}
	StartPoint.x = pRetPoint[0];
	StartPoint.y = pRetPoint[1];
	EndPoint.x = pRetPoint[2];
	EndPoint.y = pRetPoint[3];

	long fx,fy;
	double tanRA = tan(-Angle);
	double cosf = a*tanRA/sqrt(b*b+a*a*tanRA*tanRA);
	Ag1 = acos( -cosf );
	tanRA = 1/tanRA;
	cosf = a*tanRA/sqrt(b*b+a*a*tanRA*tanRA);
	Ag2 = acos( cosf );
	if(startAngle > endAngle)
	{
		if(Ag1 > startAngle || Ag1 < endAngle)
			b1 = true;
		Ag = fmod(Ag1+_PI,_2PI);
		if(Ag > startAngle || Ag < endAngle)
			b3 = true;
		if(Ag2 > startAngle || Ag2 < endAngle)
			b2 = true;
		Ag = fmod(Ag2+_PI,_2PI);
		if(Ag > startAngle || Ag < endAngle)
			b4 = true;
	}
	else
	{
		if(Ag1 > startAngle && Ag1 < endAngle)
			b1 = true;
		Ag = fmod(Ag1+_PI,_2PI);
		if(Ag > startAngle && Ag < endAngle)
			b3 = true;
		if(Ag2 > startAngle && Ag2 < endAngle)
			b2 = true;
		Ag = fmod(Ag2+_PI,_2PI);
		if(Ag > startAngle && Ag < endAngle)
			b4 = true;
	}
	if(b1)
	{
		fx = a * cos(Ag1) + 0.5 + CtPoint.x;
		fy = b * sin(Ag1) + 0.5 + CtPoint.y;
		RotatePoint((long)fx,(long)fy,rotX,rotY,Angle);
		SetMMXY(fx,fy,minx,miny,maxx,maxy);
	}
	if(b2)
	{
		fx = a * cos(Ag2) + 0.5 + CtPoint.x;
		fy = b * sin(Ag2) + 0.5 + CtPoint.y;
		RotatePoint((long)fx,(long)fy,rotX,rotY,Angle);
		SetMMXY(fx,fy,minx,miny,maxx,maxy);
	}
	if(b3)
	{
		fx = -a * cos(Ag1) + 0.5 + CtPoint.x;
		fy = -b * sin(Ag1) + 0.5 + CtPoint.y;
		RotatePoint((long)fx,(long)fy,rotX,rotY,Angle);
		SetMMXY(fx,fy,minx,miny,maxx,maxy);
	}
	if(b4)
	{
		fx = -a * cos(Ag2) + 0.5 + CtPoint.x;
		fy = -b * sin(Ag2) + 0.5 + CtPoint.y;
		RotatePoint((long)fx,(long)fy,rotX,rotY,Angle);
		SetMMXY(fx,fy,minx,miny,maxx,maxy);
	}
	RotatePoint(StartPoint.x,StartPoint.y,rotX,rotY,Angle);
	RotatePoint(EndPoint.x,EndPoint.y,rotX,rotY,Angle);
	SetMMXY(StartPoint.x,StartPoint.y,minx,miny,maxx,maxy);
	SetMMXY(EndPoint.x,EndPoint.y,minx,miny,maxx,maxy);
}


//内部函数
void MoveTwoBox(long&  minx,  long& maxx, long& miny, long& maxy , long OrgX,long OrgY,long rotXSelf,long rotYSelf,double angleSelf,long rotX,long rotY,double angle)
{
	long dltX = OrgX;
	long dltY = OrgY;
	RotatePoint(dltX,dltY,rotXSelf,rotYSelf,angleSelf);
	RotatePoint(dltX,dltY,rotX,rotY,angle);
	dltX -= OrgX;
	dltY -= OrgY;
	minx += dltX;
	maxx += dltX;
	miny += dltY;
	maxy += dltY;
}

//1.5.4.0椭圆弧
void GetEllipseCCWArcBoxByRotate(const  long * pData, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	Display::CDisOptimize::GetArcBox(pData,false,minx,miny,maxx,maxy );
	if(fabs(Angle) < 0.001)
		return;
	long rotX = (minx+maxx)/2+ 0.5 ;
	long rotY = (miny+maxy)/2+ 0.5 ;
	GetRealArcBoxByRotate(pData, Angle ,rotX,rotY, minx, maxx, miny, maxy );
}


//1.5.4.1顺时针椭圆弧
void GetEllipseCWArcBoxByRotate(const  long * pData, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	long p[8];
	memcpy(p,pData,4*sizeof(long));
	p[4] = *(pData+6);
	p[5] = *(pData+7);
	p[6] = *(pData+4);
	p[7] = *(pData+5);
	GetEllipseCCWArcBoxByRotate(p, Angle ,minx,maxx,miny,maxy );
}


//1.5.5弓形
void GetChordBoxByRotate(const  long * pData, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	GetEllipseCCWArcBoxByRotate(pData, Angle ,minx,maxx,miny,maxy );
}

//1.5.6扇形
void GetPieBoxByRotate(const  long * pData, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	Display::CDisOptimize::GetArcBox(pData,false,minx,miny,maxx,maxy );
	INT_POINT CtPoint;
	CtPoint.x = (*pData + *(pData+2))/2+ 0.5 ;
	CtPoint.y = (*(pData+1) + *(pData+3))/2+ 0.5 ;
	SetMMXY(CtPoint.x,CtPoint.y,minx,miny,maxx,maxy);
	long rotX = (minx+maxx)/2+ 0.5 ;
	long rotY = (miny+maxy)/2+ 0.5 ;
	if(fabs(Angle) > 0.001)
		GetRealArcBoxByRotate(pData, Angle ,rotX,rotY, minx, maxx, miny, maxy );
	RotatePoint(CtPoint.x,CtPoint.y,rotX,rotY,Angle);
	SetMMXY(CtPoint.x,CtPoint.y,minx,miny,maxx,maxy);
}


//1.5.7线（点集）
void GetLineBoxByRotate(long PointCount, const long * pData, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	_ASSERT(PointCount > 1);
	GetPolygonBox(PointCount,pData,minx, miny,maxx,maxy);
	INT_POINT CtPoint;
	CtPoint.x = (minx + maxx)/2+ 0.5 ;
	CtPoint.y = (miny + maxy)/2+ 0.5 ;
	minx = miny = 10E16;
	maxx = maxy = -10E16;
	long x,y;
	long * p = (long *)pData;
	for(long i=0; i< PointCount; i++,p+=2)
	{
		x = *p;
		y = *(p+1);
		RotatePoint(x,y,CtPoint.x,CtPoint.y,Angle);
		SetMMXY(x,y,minx,miny,maxx,maxy);
	}
}


//1.5.11矩形
void GetRectBoxByRotateEx(const  long * pData,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	long x,y,ctX,ctY;
	long * p = (long*)pData;
	ctX = rotX;
	ctY = rotY;
	x = *p;
	y = *(p+1);
	RotatePoint(x,y,ctX,ctY,Angle);
	minx = maxx = x;
	miny = maxy = y;

	for(UINT i= 0;i< 3; i++)
	{
		x = *(p+2);
		y = *(p+1);
		if(i == 2)
			x = *p;
		if(i > 0)
			y = *(p+3);
		RotatePoint(x,y,ctX,ctY,Angle);
		if(minx > x) 
			minx = x;
		if(maxx < x)
			maxx = x;
		if(miny > y) 
			miny = y;
		if(maxy < y)
			maxy = y;
	}
}



//1.5.13圆角矩形
void GetRoundRectBoxByRotateEx(const  long * pData,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	GetRoundRectBoxByRotate(pData,Angle , minx, maxx,miny,maxy );
	long OrgX = (*pData + *(pData+2))/2+ 0.5 ;
	long OrgY = (*(pData+1) + *(pData+3))/2+ 0.5 ;
	MoveBox(minx, maxx,miny,maxy,OrgX,OrgY,rotX,rotY,Angle);
}

//1.5.14.0椭圆弧
void GetEllipseCCWArcBoxByRotateEx(const  long * pData,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	GetRealArcBoxByRotate(pData, Angle ,rotX,rotY, minx, maxx, miny, maxy );
}


//1.5.14.1顺时针椭圆弧
void GetEllipseCWArcBoxByRotateEx(const  long * pData,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	long p[8];
	memcpy(p,pData,4*sizeof(long));
	p[4] = *(pData+6);
	p[5] = *(pData+7);
	p[6] = *(pData+4);
	p[7] = *(pData+5);
	GetEllipseCCWArcBoxByRotateEx(p,rotX,rotY, Angle ,minx,maxx,miny,maxy );
}


//1.5.15弓形
void GetChordBoxByRotateEx(const  long * pData,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	GetEllipseCCWArcBoxByRotateEx(pData,rotX,rotY, Angle ,minx,maxx,miny,maxy );
}

//1.5.16扇形
void GetPieBoxByRotateEx(const  long * pData,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	INT_POINT CtPoint;
	CtPoint.x = (*pData + *(pData+2))/2+ 0.5 ;
	CtPoint.y = (*(pData+1) + *(pData+3))/2+ 0.5 ;
	if(fabs(Angle) > 0.001)
		GetRealArcBoxByRotate(pData, Angle ,rotX,rotY, minx, maxx, miny, maxy );
	else
		Display::CDisOptimize::GetArcBox(pData,false,minx,miny,maxx,maxy );		
	RotatePoint(CtPoint.x,CtPoint.y,rotX,rotY,Angle);
	SetMMXY(CtPoint.x,CtPoint.y,minx,miny,maxx,maxy);
}


//1.5.17线（点集）
void GetLineBoxByRotateEx(long PointCount, const long * pData,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	_ASSERT(PointCount > 1);
	minx = miny = 10E16;
	maxx = maxy = -10E16;
	long x,y;
	long * p = (long *)pData;
	for(long i=0; i< PointCount; i++,p+=2)
	{
		x = *p;
		y = *(p+1);
		RotatePoint(x,y,rotX,rotY,Angle);
		SetMMXY(x,y,minx,miny,maxx,maxy);
	}
}

//////////////////////////////////////////////////////////////////////////

//1.5.21矩形
void GetRectBoxByTwoRotate(const  long * pData,long rotXSelf,long rotYSelf, double AngleSelf ,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	long x,y;
	long * p = (long*)pData;
	x = *p;
	y = *(p+1);
	RotatePoint(x,y,rotXSelf,rotYSelf,AngleSelf);
	RotatePoint(x,y,rotX,rotY,Angle);
	minx = maxx = x;
	miny = maxy = y;

	for(UINT i= 0;i< 3; i++)
	{
		x = *(p+2);
		y = *(p+1);
		if(i == 2)
			x = *p;
		if(i > 0)
			y = *(p+3);
		RotatePoint(x,y,rotXSelf,rotYSelf,AngleSelf);
		RotatePoint(x,y,rotX,rotY,Angle);
		if(minx > x) 
			minx = x;
		if(maxx < x)
			maxx = x;
		if(miny > y) 
			miny = y;
		if(maxy < y)
			maxy = y;
	}
}

//1.5.22椭圆
void GetEllipseBoxByTwoRotate(const  long * pData,long rotXSelf,long rotYSelf, double AngleSelf ,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	double ang = Angle + AngleSelf;
	GetEllipseBoxByRotate(pData,ang, minx, maxx,miny,maxy );
	long OrgX = (*pData + *(pData+2))/2+ 0.5 ;
	long OrgY = (*(pData+1) + *(pData+3))/2+ 0.5 ;
	MoveTwoBox(minx, maxx,miny,maxy,OrgX,OrgY,rotXSelf,rotYSelf,AngleSelf,rotX,rotY,Angle);
}

//1.5.23圆角矩形
void GetRoundRectBoxByTwoRotate(const  long * pData,long rotXSelf,long rotYSelf, double AngleSelf ,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	double ang = Angle + AngleSelf;
	GetRoundRectBoxByRotate(pData,ang , minx, maxx,miny,maxy );
	long OrgX = (*pData + *(pData+2))/2+ 0.5 ;
	long OrgY = (*(pData+1) + *(pData+3))/2+ 0.5 ;
	MoveTwoBox(minx, maxx,miny,maxy,OrgX,OrgY,rotXSelf,rotYSelf,AngleSelf,rotX,rotY,Angle);
}

//1.5.24.0椭圆弧
void GetEllipseCCWArcBoxByTwoRotate(const  long * pData,long rotXSelf,long rotYSelf, double AngleSelf ,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	double ang = Angle + AngleSelf;
	long OrgX = (*pData + *(pData+2))/2+ 0.5 ;
	long OrgY = (*(pData+1) + *(pData+3))/2+ 0.5 ;
	GetRealArcBoxByRotate(pData, ang ,OrgX,OrgY, minx, maxx, miny, maxy );
	MoveTwoBox(minx, maxx,miny,maxy,OrgX,OrgY,rotXSelf,rotYSelf,AngleSelf,rotX,rotY,Angle);
}


//1.5.24.1顺时针椭圆弧
void GetEllipseCWArcBoxByTwoRotate(const  long * pData,long rotXSelf,long rotYSelf, double AngleSelf ,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	long p[8];
	memcpy(p,pData,4*sizeof(long));
	p[4] = *(pData+6);
	p[5] = *(pData+7);
	p[6] = *(pData+4);
	p[7] = *(pData+5);
	GetEllipseCCWArcBoxByTwoRotate(p,rotXSelf,rotYSelf, AngleSelf ,rotX,rotY, Angle ,minx,maxx,miny,maxy );
}


//1.5.25弓形
void GetChordBoxByTwoRotate(const  long * pData,long rotXSelf,long rotYSelf, double AngleSelf ,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	GetEllipseCCWArcBoxByTwoRotate(pData,rotXSelf,rotYSelf, AngleSelf ,rotX,rotY, Angle ,minx,maxx,miny,maxy );
}

//1.5.26扇形
void GetPieBoxByTwoRotate(const  long * pData,long rotXSelf,long rotYSelf, double AngleSelf ,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	long OrgX = (*pData + *(pData+2))/2+ 0.5 ;
	long OrgY = (*(pData+1) + *(pData+3))/2+ 0.5 ;
	GetEllipseCCWArcBoxByTwoRotate(pData,rotXSelf,rotYSelf, AngleSelf ,rotX,rotY, Angle ,minx,maxx,miny,maxy );
	RotatePoint(OrgX,OrgY,rotXSelf,rotYSelf,AngleSelf);
	RotatePoint(OrgX,OrgY,rotX,rotY,Angle);
	SetMMXY(OrgX,OrgY,minx,miny,maxx,maxy);
}


//1.5.27线（点集）
void GetLineBoxByTwoRotate(long PointCount, const long * pData,long rotXSelf,long rotYSelf, double AngleSelf ,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
	_ASSERT(PointCount > 1);
	minx = miny = 10E16;
	maxx = maxy = -10E16;
	long x,y;
	long * p = (long *)pData;
	for(long i=0; i< PointCount; i++,p+=2)
	{
		x = *p;
		y = *(p+1);
		RotatePoint(x,y,rotXSelf,rotYSelf,AngleSelf);
		RotatePoint(x,y,rotX,rotY,Angle);
		SetMMXY(x,y,minx,miny,maxx,maxy);
	}
}

//////////////////////////////////////////////////////////////////////////



//Bezier　光滑

//内部函数
//生成所有的控制点，形成完整的Bezier的控制点
template <class T>
void FeedBezierT(T * pBezier,UINT numPt,double curveRate)
{
	double dist1,dist2,scope;
	T * pb = pBezier;
	UINT sizePt = 2*sizeof(T);
	memcpy(pb,   pb+2,sizePt);
	memcpy(pb+4, pb+2,sizePt);
	pb += 8 ;
	//控制点间距为两点间距的1/4
	for(UINT i=1; i<numPt-1; i++)
	{
		dist1 = sqrt((*(pb-6) - *pb)*1.0*(*(pb-6) - *(pb)) +(*(pb-5) - *(pb+1))*1.0*(*(pb-5) - *(pb+1)));//前后两点间距
		dist2 = sqrt((*(pb) - *(pb+6))*1.0*(*(pb) - *(pb+6)) + (*(pb+1) - *(pb+7))*1.0*(*(pb+1) - *(pb+7)));//前后两点间距
		dist1 *= curveRate;
		dist2 *= curveRate;
		scope = calculate_angle(pb-6, pb+6);
		*(pb-2) = *pb - (T)(dist1 * cos(scope));
		*(pb-1) = *(pb+1) - (T)(dist1 * sin(scope));
		*(pb+2) = *pb + (T)(dist2 * cos(scope));
		*(pb+3) = *(pb+1) + (T)(dist2 * sin(scope));
		pb += 6;
	}
	memcpy(pb-2, pb ,sizePt);
	memcpy(pb+2, pb ,sizePt);
}
double DPointToLineSeg(const INT_POINT& Point, const DIS_LINE& Seg,double tolerance)
{
	INT_POINT StartPoint,EndPoint;
	//以已知点为坐标原点，平移坐标系:
	StartPoint.x = Seg.ps[0].x - Point.x;	StartPoint.y =Seg.ps[0].y - Point.y;
	EndPoint.x = Seg.ps[1].x - Point.x;	EndPoint.y = Seg.ps[1].y - Point.y;

	if(labs(StartPoint.x - EndPoint.x) < tolerance && labs(StartPoint.y - EndPoint.y) < tolerance)
		return (double)StartPoint.x * (double)StartPoint.x + (double)StartPoint.y * (double)StartPoint.y;

	double a = (double)StartPoint.x * (double)EndPoint.y - (double)EndPoint.x * (double)StartPoint.y;
	a = a * a;
	double chaX = (double)EndPoint.x - (double)StartPoint.x;
	double chaY = (double)EndPoint.y - (double)StartPoint.y;
	double b = chaX * chaX + chaY * chaY;
	double temp = a/b;

	double StartWithOrigin = (double)StartPoint.x * (double)StartPoint.x + (double)StartPoint.y * (double)StartPoint.y;
	double EndWithOrigin = (double)EndPoint.x * (double)EndPoint.x + (double)EndPoint.y * (double)EndPoint.y;
	if(b + StartWithOrigin - EndWithOrigin <-tolerance) 
		return StartWithOrigin;
	else if(b + EndWithOrigin - StartWithOrigin < -tolerance)
		return EndWithOrigin;
	else
		return  temp;		
}

//////////////////////////////////////////////////////////////////////////
//类CSetFlag 用于抽稀
template <class T>
Display::CSetFlagT<T>::CSetFlagT(T * pPoints, UINT numPoint, T length)
{
	m_nLength = length*length;
	m_numPoint = numPoint;
	m_pPoints = pPoints ;
	m_pFlag = new bool[m_numPoint];
	m_pDist = new T[m_numPoint];
	for(UINT i=0; i< m_numPoint; i++)
	{
		m_pFlag[i] = true;
		m_pDist[i] = 0;
	}
}

template <class T>
Display::CSetFlagT<T>::~CSetFlagT()
{
	if(m_pFlag != false)
		delete []m_pFlag;
	if(m_pDist != false)
		delete []m_pDist;
}


//内部函数(递归)
//功能：　设置各点的flag值：　　0：点有效（初值）
//								1:点无效
//参数：　pPoints,点集的起始位置
//		　start end为所要考查的点的起、终位置
//		  length  点与线段最短距离的阀值（容差）
template <class T>
void Display::CSetFlagT<T>::CaleFlag(UINT start, UINT end)
{
	if(end - start < 2)
		return;

	UINT i,posMaxD ;

	INT_POINT pt;
	DIS_LINE SegLine;
	SegLine.ps[0].x = (double)*(m_pPoints+2*start);
	SegLine.ps[0].y = (double)*(m_pPoints+2*start+1);
	SegLine.ps[1].x = (double)*(m_pPoints+2*end);
	SegLine.ps[1].y = (double)*(m_pPoints+2*end+1);

	posMaxD = start+1;
	for(i = start+1; i< end ;i++)
	{
		pt.x = (double)*(m_pPoints+2*i);
		pt.y = (double)*(m_pPoints+2*i+1);
		m_pDist[i] =(T)DPointToLineSeg(pt,SegLine,0.0001);
		if(m_pDist[posMaxD] < m_pDist[i])
			posMaxD = i;
	}
	if(m_pDist[posMaxD] > m_nLength)
	{
		CaleFlag(start, posMaxD);
		CaleFlag(posMaxD, end);
	}
	else
	{	//将start -->end 的FLAG全部设为false(无效点)
		for(i = start+1; i< end ;i++)
			m_pFlag[i] = false;
	}
}

//返回点的个数
template <class T>
UINT Display::CSetFlagT<T>::CreatePoints(T **ppRetPoints)
{
	UINT i,retNum=0 ;
	T * pDesc;
	CaleFlag(0,m_numPoint-1);
	*ppRetPoints = new T[2 * m_numPoint];
	pDesc = *ppRetPoints;
	for(i=0; i< m_numPoint; i++)
	{
		if(m_pFlag[i])
		{
			memcpy(pDesc,m_pPoints+2*i,2*sizeof(T));
			pDesc += 2;
			retNum ++;
		}
	}
	return retNum;
}

// end  --  类CSetFlag 
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//外部函数

//释放“底层库函数”
void Display::CDisOptimize::free_Object(unsigned char ** ppObject)
{
	if (*ppObject == false)
		return;
	delete [](*ppObject);
	*ppObject = false;
}
void Display::CDisOptimize::free_Group(long ** ppGroup)
{
	if (*ppGroup == false)
		return;
	delete [](*ppGroup);
	*ppGroup = false;
}
void Display::CDisOptimize::free_Group(double ** ppGroup)
{
	if (*ppGroup == false)
		return;
	delete [](*ppGroup);
	*ppGroup = false;
}
//////////////////////////////////////////////////////////////////////////
//
//功能：将点集进行抽稀处理
//参数：输入参数 iPointNum, 源点集中的点个数
//      		 pPoints　源点集
//				 length  点与线段最短距离的阀值（容差）
//      输出参数 ppRetPoints 抽稀后的点数据（点集）
//返回值：
//		抽稀后的点个数
long Display::CDisOptimize::DilutePoints(long iPointNum, const long * pPoints, long length, long ** ppRetPoints)
{
		if(length <=0)
			length = 0;
		assert(pPoints != false && iPointNum >1);

		CSetFlagT<long> Cale((long*)pPoints,iPointNum,length);
		long lRet = Cale.CreatePoints(ppRetPoints);
		if(lRet < 2)
		{
			delete [](*ppRetPoints);
			*ppRetPoints = false;
			lRet = 0;
		}
		return lRet;

}

template <class T>
UINT CreatePoints(T **ppRetPoints)
{
	UINT i,retNum=0 ;
	T * pDesc;
	CaleFlag(0,m_numPoint-1);
	*ppRetPoints = new T[2 * m_numPoint];
	pDesc = *ppRetPoints;
	for(i=0; i< m_numPoint; i++)
	{
		if(m_pFlag[i])
		{
			memcpy(pDesc,m_pPoints+2*i,2*sizeof(T));
			pDesc += 2;
			retNum ++;
		}
	}
	return retNum;
}


inline double TPointToSegmentDistance2( const dbPoint &point , const dbPoint seg[2])
{
	//以已知点为坐标原点，平移坐标系：
	register double x1, y1, x2, y2;
	x1 = seg[0].x - point.x;
	y1 = seg[0].y - point.y;
	x2 = seg[1].x - point.x;
	y2 = seg[1].y - point.y;

	const double dbEps = 0.000000001;			//	微小量
// 	if( abs(x1 - x2) < dbEps && 
// 		abs(y1 - y2) < dbEps)
// 	if(x1==x2 && y1==y2)
// 	{
// 		return x1 * x1 + y1 * y1;
// 	}
	//
	register double a = x1 * y2 - x2 * y1;
	a *= a;
	register double chaX = x2 - x1;
	register double chaY = y2 - y1;
	register double b = chaX * chaX + chaY * chaY;

	register double temp = a/b;

	register double StartWithOrigin = x1 * x1 + y1 * y1;
	register double EndWithOrigin =   x2 * x2 + y2 * y2;

	if(b + StartWithOrigin - EndWithOrigin <-0.001) 
		return StartWithOrigin;
	else if(b + EndWithOrigin - StartWithOrigin < -0.001)
		return EndWithOrigin;
	else
		return  temp;	
}

inline double PointToSegmentDistance2( const double *point , double *seg)
{
	//以已知点为坐标原点，平移坐标系：
	register double x1, y1, x2, y2;
	x1 = seg[0] - point[0];
	y1 = seg[1] - point[1];
	x2 = seg[2] - point[0];
	y2 = seg[3] - point[1];

	const double dbEps = 0.000000001;			//	微小量
	// 	if( abs(x1 - x2) < dbEps && 
	// 		abs(y1 - y2) < dbEps)
// 	// 	if(x1==x2 && y1==y2)
// 	// 	{
// 	// 		return x1 * x1 + y1 * y1;
// 	// 	}
// 	//
	register double a = x1 * y2 - x2 * y1;
	a *= a;
	register double chaX = x2 - x1;
	register double chaY = y2 - y1;
	register double b = chaX * chaX + chaY * chaY;

	register double temp = a/b;

	register double StartWithOrigin = x1 * x1 + y1 * y1;
	register double EndWithOrigin =   x2 * x2 + y2 * y2;

	if(b + StartWithOrigin - EndWithOrigin <-0.001) 
		return StartWithOrigin;
	else if(b + EndWithOrigin - StartWithOrigin < -0.001)
		return EndWithOrigin;
	else
		return  temp;	
}


inline void _GeralizeDoubleLine(long Start, long End, const double *points, bool *pSign, double toler2)
{
	if( Start == End || Start+1 == End ) return;

	double seg[4];
	seg[0] = points[Start*2];
	seg[1] = points[Start*2+1];
	seg[2] = points[End*2];
	seg[3] = points[End*2+1];

	long mid;
	double tmp,offtoler2 = 0.0;
	// 寻找偏离最大的点
	for(long i = Start+1 ; i < End-1 ; i++ )
	{
		tmp = PointToSegmentDistance2( points+2*i , seg );
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
		pSign[mid] = TRUE;
		_GeralizeDoubleLine( Start , mid , points , pSign , toler2 );
		_GeralizeDoubleLine( mid   , End , points , pSign , toler2 );
	}
}


long GeralizeDoubleLine(long numPoint, const double* points,  double* outPoints, double toler)
{
	long i;
	bool *pSign = new bool[numPoint];
	for( i=0; i<numPoint; i++)
		pSign[i] = false;

	long outNumPoint;

	pSign[0] = true;
	pSign[numPoint-1] = true;
	double toler2 = toler * toler;

	_GeralizeDoubleLine( 0 , numPoint-1 , points , pSign , toler2 );

	for( i = 0,outNumPoint = 0 ; i < numPoint ; i++)
	{
		if( pSign[i] )
		{
			outPoints[2*outNumPoint] = points[i*2];
			outPoints[2*outNumPoint+1] = points[i*2+1];
			outNumPoint++;
		}
	}

	delete []pSign;

	return outNumPoint;
}



//	调用前确保ppRetPoints经过初始化
long Display::CDisOptimize::DiluteDoublePoints(long iPointNum, const double * pPoints, double length, double ** ppRetPoints)
{
	_ASSERT(pPoints != NULL && ppRetPoints != NULL);

	if(*ppRetPoints != NULL)
	{
		delete *ppRetPoints;
	}

	*ppRetPoints = new double[iPointNum*2];
	return GeralizeDoubleLine(iPointNum, pPoints, *ppRetPoints, length);
}



//功能：得到拟和曲线的拟和点个数和拟和点数据
//参数：输入参数 iPointNum, 控制点个数
//      		 pControlPoint, 控制点数据
//				 stepLength 离散化后的点的步长（默认为15）
//				 curveRate 为曲线的弯曲(平滑)程度(0--1) ，默认为0.25
//      输出参数 ppCurvePoint, 拟和点数据
//返回值：拟和点点个数
long  Display::CDisOptimize::GetCurvePoint( long iPointNum, const long * pControlPoint, long ** ppCurvePoint ,long stepLength,double curveRate)
{
		_ASSERT(pControlPoint != false && iPointNum>1);
		if(pControlPoint == false || iPointNum < 2)
		{
			*ppCurvePoint =	false;
			return 0;
		}
		if(stepLength <1)
			stepLength = 1;
		double dLength;
		UINT i, numPt, span,sizePt;
		long * pSour,* pDesc;
		long * pBzHeader , *pBz;
		sizePt = 2*sizeof(long);
		numPt = iPointNum;
		*ppCurvePoint = new long[numPt*2002];

		pSour = (long *)pControlPoint;
		pBzHeader = (long *)malloc(3*numPt*sizePt);
		pBz = pBzHeader+2;
		for(i=0; i< numPt; i++)
		{
			memcpy(pBz,pSour, sizePt);
			pSour +=2 ;
			pBz += 6;
		}
		FeedBezierT(pBzHeader,numPt,curveRate);
		//三次Bezier,&& 组织返回结果
		double t,t1,t2,yt;
		pSour = pBzHeader + 2;
		pDesc = *ppCurvePoint;
		for(i=0; i< numPt-1; i++)
		{
			dLength = sqrt((*pSour - *(pSour+6))*1.0*(*pSour - *(pSour+6)) + (*(pSour+1) - *(pSour+7))*1.0*(*(pSour+1) - *(pSour+7)));
			span = (UINT)(dLength/stepLength);
			if(span < 4)	//span 从5－－1000
				span = 4;
			if(span > 1000)
				span = 1000;
			for(t=0; t<=1 ; t+=1.0/span)
			{
				yt = 1-t;
				t1 = yt *yt;
				t2 = 3*yt * t;
				*pDesc     = (long)(*(pSour  ) * yt *t1 + *(pSour+2) * yt *t2 + *(pSour+4) * t *t2 + *(pSour+6) * t * t * t);
				*(pDesc+1) = (long)(*(pSour+1) * yt *t1 + *(pSour+3) * yt *t2 + *(pSour+5) * t *t2 + *(pSour+7) * t * t * t);
				pDesc += 2;
			}
			pSour += 6;
		}
		free(pBzHeader);
}


//功能：得到任意弧段的外接矩形
//参数：输入参数	iPointNum, 点个数
//					bClockwise (T：顺时针　F：逆时针)
//					pArcPoint, 弧段点数据
//		输出参数	minxRet，maxxRet，minyRet，maxyRet, 弧段的外接矩形
void  Display::CDisOptimize::GetArcBox(const long *  pArcPoint, bool bClockwise, long& minxRet, long& minyRet,long& maxxRet,  long& maxyRet)
{
		bool bminx,bmaxx,bminy,bmaxy;
		bminx=bmaxx=bminy=bmaxy=false;
		long * p = (long*)pArcPoint;
		double a = (*(p+2) - *p)/2;
		double b = (*(p+3) - *(p+1))/2;
		INT_POINT StartPoint,EndPoint,CtPoint;
		CtPoint.x = (*p + *(p+2))/2;
		CtPoint.y = (*(p+1) + *(p+3))/2;
		memcpy(&StartPoint,p+4,2*sizeof(long));
		memcpy(&EndPoint,p+6,2*sizeof(long));
		double startAngle,endAngle;
		startAngle = calculate_angle((long*)&CtPoint,(long*)&StartPoint);
		endAngle = calculate_angle((long*)&CtPoint,(long*)&EndPoint);
		if(fabs(endAngle - startAngle) < 0.001)
		{
			if(pArcPoint[0]<pArcPoint[2])
			{
				minxRet = pArcPoint[0];
				maxxRet = pArcPoint[2];
			}
			else
			{
				minxRet = pArcPoint[2];
				maxxRet = pArcPoint[0];
			}
			if(pArcPoint[1]<pArcPoint[3])
			{
				minyRet = pArcPoint[1];
				maxyRet = pArcPoint[3];
			}
			else
			{
				minyRet = pArcPoint[3];
				maxyRet = pArcPoint[1];
			}
			return;
		}
		startAngle = T_Angle(a,b,startAngle);
		endAngle = T_Angle(a,b,endAngle);
		StartPoint.x =  CtPoint.x + (*(p+2) - *p)*cos(startAngle)/2;
		StartPoint.y =  CtPoint.y + (*(p+3) - *(p+1))*sin(startAngle)/2;
		EndPoint.x =  CtPoint.x + (*(p+2) - *p)*cos(endAngle)/2;
		EndPoint.y =  CtPoint.y + (*(p+3) - *(p+1))*sin(endAngle)/2;

		if(!bClockwise && startAngle > endAngle || bClockwise && startAngle < endAngle)
		{
			bmaxx = true;
			if(bClockwise)
			{
				if(endAngle <= _PI  || startAngle >= _PI )
					bminx = true;
				if(endAngle <= _PI2  || startAngle >= _PI2 )
					bmaxy = true;
				if(endAngle <= _3PI2  || startAngle >= _3PI2 )
					bminy = true;
			}
			else
			{
				if(startAngle <= _PI  || endAngle >= _PI )
					bminx = true;
				if(startAngle <= _PI2  || endAngle >= _PI2 )
					bmaxy = true;
				if(startAngle <= _3PI2  || endAngle >= _3PI2 )
					bminy = true;
			}
		}
		else
		{
			if(startAngle < 0.001 || (_2PI-startAngle) < 0.001 ||
				endAngle < 0.001 || (_2PI-endAngle) < 0.001 )
				bmaxx = true;
			if(bClockwise)
			{
				if(endAngle <= _PI  && startAngle >= _PI )
					bminx = true;
				if(endAngle <= _PI2  && startAngle >= _PI2 )
					bmaxy = true;
				if(endAngle <= _3PI2  && startAngle >= _3PI2 )
					bminy = true;
			}
			else
			{
				if(startAngle <= _PI  && endAngle >= _PI )
					bminx = true;
				if(startAngle <= _PI2  && endAngle >= _PI2 )
					bmaxy = true;
				if(startAngle <= _3PI2  && endAngle >= _3PI2 )
					bminy = true;
			}
		}

		if(bminx)
			minxRet = *p;
		else
			minxRet = StartPoint.x < EndPoint.x? StartPoint.x:EndPoint.x;
		if(bminy)
			minyRet = *(p+1);
		else
			minyRet = StartPoint.y < EndPoint.y? StartPoint.y:EndPoint.y;
		if(bmaxx)
			maxxRet = *(p+2);
		else
			maxxRet = StartPoint.x > EndPoint.x? StartPoint.x:EndPoint.x;
		if(bmaxy)
			maxyRet = *(p+3);
		else
			maxyRet = StartPoint.y > EndPoint.y? StartPoint.y:EndPoint.y;
}


//功能：得到任意弧段的精确的在弧上的起点和终点
//参数：输入参数	iPointNum, 点个数
//	   				pArcPoint, 弧段点数据
//      输出参数	ppRetPoint, 返回的弧段点数据
//返回值：
//		返回的点个数

long  Display::CDisOptimize::GetArcAccurateBeingEndPoint(const long* pArcPoint, long  pRetPoint[4])
{
		long * p = (long*)pArcPoint;
		double a = (*(p+2) - *p)/2;
		double b = (*(p+3) - *(p+1))/2;
		INT_POINT StartPoint,EndPoint,CtPoint;
		CtPoint.x = (*p + *(p+2))/2;
		CtPoint.y = (*(p+1) + *(p+3))/2;
		memcpy(&StartPoint,p+4,2*sizeof(long));
		memcpy(&EndPoint,p+6,2*sizeof(long));
		double startAngle = calculate_angle((long*)&CtPoint,(long*)&StartPoint);
		startAngle = T_Angle(a,b,startAngle);
		pRetPoint[0] = CtPoint.x + a*cos(startAngle);
		pRetPoint[1] = CtPoint.y + b*sin(startAngle);
		if(StartPoint.x==EndPoint.x && StartPoint.y==EndPoint.y)
			return 1;
		double endAngle = calculate_angle((long*)&CtPoint,(long*)&EndPoint);
		endAngle = T_Angle(a,b,endAngle);
		pRetPoint[2] = CtPoint.x + a*cos(endAngle);
		pRetPoint[3] = CtPoint.y + b*sin(endAngle);
}

//// 功能：得到任意弧段的打散的点
////参数：输入参数 iPointNum, 点个数
////				bClockwise (T：顺时针　F：逆时针)
////	   			pPoint, 弧段点数据
////      输出参数 ppDestPoint, 返回的打散的点数据
////返回值：返回的打散的点个数
//long  Display::CDisOptimize::TransArcToPoints(const long pArcPoint[8],bool bClockwise, long ** ppRetPoint, long StepLength)
//{
//	_ASSERT(StepLength >0);
//	if(StepLength <=0) return 0;
//
//	unsigned char objType;
//	double * pRetAngle = false;
//	if(bClockwise)
//		objType = OTArcCW;
//	else
//		objType = OTArcCCW;
//	long lRet = Display::CDisOptimize::OffsetObjectByMarkerLine (pArcPoint,objType,0,1,LJSRound, &StepLength, ppRetPoint,&pRetAngle );
//	delete []pRetAngle;
//	return lRet;
//}

//内部函数
//点都与圆心重合
bool Same3Point(long Data[8])
{
	long ctX = (Data[0]+Data[2])/2; 
	long ctY = (Data[1]+Data[3])/2;
	if(labs(ctX - Data[4]) <= 1 && labs(ctY - Data[5]) <= 1 &&
		labs(ctX - Data[6]) <= 1 && labs(ctY - Data[7]) <= 1)
		return true;
	return false;
}

//功能：得到带旋转角度的矢量点符号的外接矩形
//参数：输入参数 pData, 矢量绘制结构原始值
//				objType 对象的类型
//	   			Angle, 旋转角度
//      输出参数 minx,maxX,minY,maxY, 旋转以后的外接矩形
//返回值：
void Display::CDisOptimize::GetObjectBoxByRotate(long PointCount,const long * pObjData, unsigned char objType, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
		_ASSERT(pObjData != false);
		long Data[8],tmp;

		if(objType>2 && objType<10)
		{
			memcpy(Data,pObjData,8*sizeof(long));
			if(Data[0] > Data[2])
			{
				tmp = Data[0];
				Data[0] = Data[2];
				Data[2] = tmp;
			}
			if(Data[1] > Data[3])
			{
				tmp = Data[1];
				Data[1] = Data[3];
				Data[3] = tmp;
			}
		}

		switch(objType)
		{
		case OTCurve:	//	拟和线	//需求没有明确
		case OTNormal:	//	规则绘制对象
			GetLineBoxByRotate( PointCount,pObjData,Angle ,minx,maxx,miny,maxy );
			break;
		case OTRect	:	//	矩形
			GetRectBoxByRotate( Data, Angle , minx,maxx,miny,maxy );
			break;
		case OTEllipse:	//	椭圆
			GetEllipseBoxByRotate(Data,Angle ,minx,maxx,miny,maxy );
			break;
		case OTRoundRect://	圆角矩形
			GetRoundRectBoxByRotate(  Data,Angle ,minx,maxx,miny,maxy );
			break;
		case OTArcCW:	//	顺时针椭圆弧
			if(Same3Point(Data))
			{
				//minx = miny = maxx = maxy = 0;
				GetEllipseBoxByRotate(Data,Angle ,minx,maxx,miny,maxy );
				return;
			}
			GetEllipseCWArcBoxByRotate( Data,Angle ,minx,maxx,miny,maxy );
			break;
		case OTArcCCW:	//	逆时针椭圆弧
			if(Same3Point(Data))
			{
				//minx = miny = maxx = maxy = 0;
				GetEllipseBoxByRotate(Data,Angle ,minx,maxx,miny,maxy );
				return;
			}
			GetEllipseCCWArcBoxByRotate( Data,Angle ,minx,maxx,miny,maxy );
			break;
		case OTChord:	//	弓形
			if(Same3Point(Data))
			{
				//minx = miny = maxx = maxy = 0;
				GetEllipseBoxByRotate(Data,Angle ,minx,maxx,miny,maxy );
				return;
			}
			GetChordBoxByRotate(  Data,Angle ,minx,maxx,miny,maxy );
			break;
		case OTPie:		//	扇形
			if(Same3Point(Data))
			{
				//minx = miny = maxx = maxy = 0;
				GetEllipseBoxByRotate(Data,Angle ,minx,maxx,miny,maxy );
				return;
			}
			GetPieBoxByRotate( Data,Angle ,minx,maxx,miny,maxy );
			break;
			//	case OTPath:	//	路径，部分之间是连续的，如果传入的不连续，会自动把数据连接起来。
			//		break;
			//	case OTMultiObject:
			//		break;
		default:
			_ASSERT(false);
			minx = miny = maxx = maxy = 0;
			break;
		}
}

//函数扩展：以rotX,rotY为旋转中心进行旋转
void Display::CDisOptimize::GetObjectBoxByRotateEx(long PointCount,const long * pObjData, unsigned char objType, long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
		_ASSERT(pObjData != false);
		long Data[8],tmp;

		if(objType>2 && objType<10)
		{
			memcpy(Data,pObjData,8*sizeof(long));
			if(Data[0] > Data[2])
			{
				tmp = Data[0];
				Data[0] = Data[2];
				Data[2] = tmp;
			}
			if(Data[1] > Data[3])
			{
				tmp = Data[1];
				Data[1] = Data[3];
				Data[3] = tmp;
			}
		}
		switch(objType)
		{
		case OTCurve:	//	拟和线	//需求没有明确
		case OTNormal:	//	规则绘制对象
			GetLineBoxByRotateEx( PointCount,pObjData,rotX,rotY,Angle ,minx,maxx,miny,maxy );
			break;
		case OTRect	:	//	矩形
			GetRectBoxByRotateEx( Data,rotX,rotY, Angle , minx,maxx,miny,maxy );
			break;
		case OTEllipse:	//	椭圆
			GetEllipseBoxByRotateEx(Data,rotX,rotY,Angle ,minx,maxx,miny,maxy );
			break;
		case OTRoundRect://	圆角矩形
			GetRoundRectBoxByRotateEx(  Data,rotX,rotY,Angle ,minx,maxx,miny,maxy );
			break;
		case OTArcCW:	//	顺时针椭圆弧
			if(Same3Point(Data))
			{
				//minx = miny = maxx = maxy = 0;
				GetEllipseBoxByRotateEx(Data,rotX,rotY,Angle ,minx,maxx,miny,maxy );
				return;
			}
			GetEllipseCWArcBoxByRotateEx( Data,rotX,rotY,Angle ,minx,maxx,miny,maxy );
			break;
		case OTArcCCW:	//	逆时针椭圆弧
			if(Same3Point(Data))
			{
				//minx = miny = maxx = maxy = 0;
				GetEllipseBoxByRotateEx(Data,rotX,rotY,Angle ,minx,maxx,miny,maxy );
				return;
			}
			GetEllipseCCWArcBoxByRotateEx( Data,rotX,rotY,Angle ,minx,maxx,miny,maxy );
			break;
		case OTChord:	//	弓形
			if(Same3Point(Data))
			{
				//minx = miny = maxx = maxy = 0;
				GetEllipseBoxByRotateEx(Data,rotX,rotY,Angle ,minx,maxx,miny,maxy );
				return;
			}
			GetChordBoxByRotateEx(  Data,rotX,rotY,Angle ,minx,maxx,miny,maxy );
			break;
		case OTPie:		//	扇形
			if(Same3Point(Data))
			{
				//minx = miny = maxx = maxy = 0;
				GetEllipseBoxByRotateEx(Data,rotX,rotY,Angle ,minx,maxx,miny,maxy );
				return;
			}
			GetPieBoxByRotateEx( Data,rotX,rotY,Angle ,minx,maxx,miny,maxy );
			break;
			//	case OTPath:	//	路径，部分之间是连续的，如果传入的不连续，会自动把数据连接起来。
			//		break;
			//	case OTMultiObject:
			//		break;
		default:
			_ASSERT(false);
			minx = miny = maxx = maxy = 0;
			break;
		}
}


//功能：带两种旋转角度的矢量点符号的外接矩形
//参数：输入参数 pData, 矢量绘制结构原始值
//				objType 对象的类型
//				rotXSelf, rotYSelf 自旋中心
//	   			AngleSelf,	自旋角度
//				rotX, rotY	外旋中心
//	   			Angle,		外旋角度
//      输出参数 minx,maxX,minY,maxY, 旋转以后的外接矩形
//返回值：
void Display::CDisOptimize::GetObjectBoxByTwoRotate(long PointCount,const long * pObjData, unsigned char objType, long rotXSelf,long rotYSelf, double AngleSelf ,long rotX,long rotY, double Angle , long&  minx,  long& maxx, long& miny, long& maxy )
{
		_ASSERT(pObjData != false);
		long Data[8],tmp;

		if(objType>2 && objType<10)
		{
			memcpy(Data,pObjData,8*sizeof(long));
			if(Data[0] > Data[2])
			{
				tmp = Data[0];
				Data[0] = Data[2];
				Data[2] = tmp;
			}
			if(Data[1] > Data[3])
			{
				tmp = Data[1];
				Data[1] = Data[3];
				Data[3] = tmp;
			}
		}
		switch(objType)
		{
		case OTCurve:	//	拟和线	//需求没有明确
		case OTNormal:	//	规则绘制对象
			GetLineBoxByTwoRotate( PointCount,pObjData,rotXSelf,rotYSelf,AngleSelf, rotX,rotY,Angle,minx,maxx,miny,maxy );
			break;
		case OTRect	:	//	矩形
			GetRectBoxByTwoRotate(Data,rotXSelf,rotYSelf,AngleSelf, rotX,rotY,Angle,minx,maxx,miny,maxy );
			break;
		case OTEllipse:	//	椭圆
			GetEllipseBoxByTwoRotate(Data,rotXSelf,rotYSelf,AngleSelf, rotX,rotY,Angle,minx,maxx,miny,maxy );
			break;
		case OTRoundRect://	圆角矩形
			GetRoundRectBoxByTwoRotate(Data,rotXSelf,rotYSelf,AngleSelf, rotX,rotY,Angle,minx,maxx,miny,maxy );
			break;
		case OTArcCW:	//	顺时针椭圆弧
			if(Same3Point(Data))
			{
				//minx = miny = maxx = maxy = 0;
				GetEllipseBoxByTwoRotate(Data,rotXSelf,rotYSelf,AngleSelf, rotX,rotY,Angle,minx,maxx,miny,maxy );
				return;
			}
			GetEllipseCWArcBoxByTwoRotate(Data,rotXSelf,rotYSelf,AngleSelf, rotX,rotY,Angle,minx,maxx,miny,maxy );
			break;
		case OTArcCCW:	//	逆时针椭圆弧
			if(Same3Point(Data))
			{
				//minx = miny = maxx = maxy = 0;
				GetEllipseBoxByTwoRotate(Data,rotXSelf,rotYSelf,AngleSelf, rotX,rotY,Angle,minx,maxx,miny,maxy );
				return;
			}
			GetEllipseCCWArcBoxByTwoRotate(Data,rotXSelf,rotYSelf,AngleSelf, rotX,rotY,Angle,minx,maxx,miny,maxy );
			break;
		case OTChord:	//	弓形
			if(Same3Point(Data))
			{
				//minx = miny = maxx = maxy = 0;
				GetEllipseBoxByTwoRotate(Data,rotXSelf,rotYSelf,AngleSelf, rotX,rotY,Angle,minx,maxx,miny,maxy );
				return;
			}
			GetChordBoxByTwoRotate(Data,rotXSelf,rotYSelf,AngleSelf, rotX,rotY,Angle,minx,maxx,miny,maxy );
			break;
		case OTPie:		//	扇形
			if(Same3Point(Data))
			{
				//minx = miny = maxx = maxy = 0;
				GetEllipseBoxByTwoRotate(Data,rotXSelf,rotYSelf,AngleSelf, rotX,rotY,Angle,minx,maxx,miny,maxy );
				return;
			}
			GetPieBoxByTwoRotate(Data,rotXSelf,rotYSelf,AngleSelf, rotX,rotY,Angle,minx,maxx,miny,maxy );
			break;
			//	case OTPath:	//	路径，部分之间是连续的，如果传入的不连续，会自动把数据连接起来。
			//		break;
			//	case OTMultiObject:
			//		break;
		default:
			_ASSERT(false);
			minx = miny = maxx = maxy = 0;
			break;
		}
}

//////////////////////////////////////////////////////////////////////////
//线符号

//水平偏移
long OffsetLnOX(long numPoint, long * pSour , long nOX, long ** ppRetLine)
{
	_ASSERT(nOX >=0);
	if(nOX == 0)
	{
		*ppRetLine = new long[2*numPoint];
		memcpy(*ppRetLine,pSour,2*numPoint*sizeof(long));
		return numPoint;
	}

	long lCur,length=0,temp=0;//temp为前一次的length,lCur为当关前线长
	long i;
	//处理水平偏移
	for(i=0; i<numPoint-1; i++)
	{
		lCur = sqrt((*(pSour+2*i+2)-*(pSour+2*i))*1.0*(*(pSour+2*i+2)-*(pSour+2*i))+(*(pSour+2*i+3)-*(pSour+2*i+1))*1.0*(*(pSour+2*i+3)-*(pSour+2*i+1)));
		length += lCur;
		if(length > nOX)
			break;
		temp = length;
	}
	if(i==numPoint-1)//线长＜水平偏移
	{
		*ppRetLine = false;
		return DP_NOX_LENGTH_SHORT;
	}
	//正常水平偏移
	*ppRetLine = new long[2*(numPoint -i)];
	length = nOX-temp;		//i段线中需要delete的线长度
	**ppRetLine = *(pSour+2*i)+ length*(*(pSour+2*i+2)-*(pSour+2*i))/lCur;//X
	*(*ppRetLine+1) = *(pSour+2*i+1)+length*(*(pSour+2*i+3)-*(pSour+2*i+1))/lCur;//Y
	memcpy(*ppRetLine+2,pSour+2*i+2,sizeof(long)*(2*(numPoint -i)-2));
	return (numPoint -i);
}



//功能：实线得到偏移后的线数据
//参数：输入参数	pSourLine:原线的点集
//					nOX:水平偏移
//					nOY:垂直偏移(左为负，右为正)
//					JointStyle:拐角样式	
//      输出参数
//					ppRetLine: 新线的点集
//返回值：
//		ppRetLine中点的个数
long Display::CDisOptimize::OffsetLine(long PointCount, const long * pSourLine , long nOX,long nOY, unsigned char JointStyle, long ** ppRetLine)
{
		_ASSERT(pSourLine != false && PointCount > 1 &&  *ppRetLine == false );
		_ASSERT(JointStyle > 0);
		//	ASSERT(nOX >=0);
		if(nOX <0) nOX =0;
		if(labs(nOY) <0) nOY = 0;

		long * pSour = false;
		long numPoint;

		//处理水平偏移
		numPoint = OffsetLnOX(PointCount,(long*)pSourLine,nOX,&pSour);
		if(numPoint<0)
		{
			*ppRetLine = false;
			return numPoint;
		}
		//处理垂直偏移
		SUBARRAY ptArray;
		if( nOY == 0 )
		{
			*ppRetLine = pSour;
			return numPoint;
		}
		else
		{
			//nOY = -nOY;
			// 计算偏移线形成链表结构　ptArray
			_Offsetline( numPoint , (INT_POINT*)pSour, ptArray , nOY );
			// 整理内外角关系以及倒角
			_TrimlineCorner( nOY , ptArray , (INT_POINT*)pSour , 
				JointStyle == LJSRound? GetAngleArc:(JointStyle == LJSMiter? GetAnglefalse:GetAngleCut) );
			// 整理结果，并采样
			long ret = _GetSoliDIS_LINE( ppRetLine , ptArray );
			delete []pSour;
			return ret;
		}
}


// 内部函数
// 计算SUBARRAY结构中的线长度
bool FeedLengthInArray(SUBARRAY& ptArray)
{
	int size = ptArray.size();
	if(size < 1)	//没有内容
		return false;

	for(int i=0 ; i<size; i++)
	{
		if(!ptArray[i].bIsfalseline)	//有重叠边	
		{
			//计算OffSgLength
			ptArray[i].OffSgLength = sqrt((ptArray[i].trueOffSegment[0].x-ptArray[i].trueOffSegment[1].x)*1.0*(ptArray[i].trueOffSegment[0].x-ptArray[i].trueOffSegment[1].x) +
				(ptArray[i].trueOffSegment[0].y-ptArray[i].trueOffSegment[1].y)*1.0*(ptArray[i].trueOffSegment[0].y-ptArray[i].trueOffSegment[1].y));

		}
		else
			ptArray[i].OffSgLength = 0;
		//计算SourceLength
		ptArray[i].SourceLength = sqrt((ptArray[i].OffSgment[0].x-ptArray[i].OffSgment[1].x)*1.0*(ptArray[i].OffSgment[0].x-ptArray[i].OffSgment[1].x) +
			(ptArray[i].OffSgment[0].y-ptArray[i].OffSgment[1].y)*1.0*(ptArray[i].OffSgment[0].y-ptArray[i].OffSgment[1].y));

	}
	return true;
}

//内部函数
//线没有nOY偏移时的“标记线/虚线符号”
//lengthClip为新添加,说明同"GetMarkerLine_Array"
long GetMarkerLine(bool bDashLine,long PointCount, long * pSourLine , long MarkerCount, long * pMarkerSpace,double lengthClip,long ** ppRetLine, double ** ppRetAngle)
{
	double Angle, *pLength;		//for temp
	long  * pby = pSourLine, *pDescLine ;
	double * pDescAngle, dltTX,dltTY;				//dltTX,dltTY for temp
	double  dBaseX,dBaseY,dltX,dltY; 		
	long i,j,k, iStep ;
	long IndexSeg = 0, lRet;								//IndexSeg:上一段中遗留的Marker小段号
	double dLast = 0, MarkerLength = 0;			//dLast > 0 表示“上一段有遗留的线长度”

	for(i= 0; i< MarkerCount; i++)
	{
		MarkerLength += pMarkerSpace[i];
	}
	//计算线段长
	dltTX = 0;			//借用,作为总长
	pLength = new double[PointCount];
	for(i= 0; i< PointCount-1; i++,pby += 2)
	{
		pLength[i] = sqrt((*pby - *(pby+2))*1.0*(*pby - *(pby+2)) 
			+ (*(pby+1) - *(pby+3))*1.0*(*(pby+1) - *(pby+3)));
		dltTX += pLength[i];
	}
	bool bExtenDIS_LINE;//需要延长线
	if(lengthClip > dltTX+TOLER)
	{
		_ASSERT(MarkerCount == 1);
		bExtenDIS_LINE = true;
		lengthClip -= dltTX;
	}
	else
		bExtenDIS_LINE = false;
	//分配了内存
	lRet = ((long)(dltTX/MarkerLength)+1)*(MarkerCount+1);//借用,作为总点数
	if(bExtenDIS_LINE)
		lRet += (lengthClip/pMarkerSpace[0] +1);
	lRet += 2*PointCount;
	*ppRetLine  = new long[2*lRet];
	*ppRetAngle = new double[lRet];
	pDescLine = *ppRetLine;
	pDescAngle = *ppRetAngle;
	//开始
	pby = pSourLine;
	dBaseX = *pSourLine;
	dBaseY = *(pSourLine+1);
	memcpy(pDescLine, pby,2*sizeof(long));	//加入头一点
	Angle = calculate_angle(pby,pby+2);
	*pDescAngle = Angle;
	pDescLine +=2;
	pDescAngle ++;
	lRet =1;
	for(i= 0; i< PointCount-1; i++,pby += 2)
	{
		//计算本线段的Angle
		Angle = calculate_angle(pby,pby+2);
		if(dLast+pLength[i] < pMarkerSpace[IndexSeg])
		{
			dLast += pLength[i];
	//		if(bDashLine && fmod(IndexSeg,2)<0.1)//虚线时
			if(bDashLine && (IndexSeg%2)<0.1)//虚线时
			{
				//*pDescLine = dBaseX;
				//*(pDescLine+1) = dBaseY;
				memcpy(pDescLine,pby+2,16);
				memcpy(pDescLine+2,pby+2,16);
				*pDescAngle = Angle;
				*(pDescAngle+1) = Angle;
				pDescLine +=4;
				pDescAngle +=2;
				lRet +=2;
			}
			continue;
		}
		dltTX = (*(pby+2)-*pby)/pLength[i];		//斜率
		dltTY = (*(pby+3)-*(pby+1))/pLength[i];
		//添加第一个SEG
		if(dLast > 0 || IndexSeg !=0)//上一条线有遗留
		{
			//添加第一点
			dLast = pMarkerSpace[IndexSeg] - dLast;//借用dLast
			dBaseX = *pby + dLast*dltTX;
			dBaseY = *(pby+1) + dLast*dltTY;
			*pDescLine = dBaseX;
			*(pDescLine+1) = dBaseY;
			*pDescAngle = Angle;
			pDescLine +=2;
			pDescAngle ++;
			lRet ++;
		//	IndexSeg = fmod(IndexSeg+1,MarkerCount);
			IndexSeg = ((IndexSeg+1)%MarkerCount);
			if(IndexSeg != 0)
				for(j=IndexSeg; j< MarkerCount; j++)//走完本段Marker
				{
					dLast += pMarkerSpace[j];
					if(dLast > pLength[i])
					{
						//本段Marker没有走完
						//dLast -= pLength[i];	//恢复dLast功能
						dLast = pMarkerSpace[j]-(dLast- pLength[i]);
						IndexSeg = j;
						goto NEXTLOOP;
					}
					dltX = pMarkerSpace[j] * dltTX;
					dltY = pMarkerSpace[j] * dltTY;
					dBaseX += dltX;
					dBaseY += dltY;
					*pDescLine = dBaseX;
					*(pDescLine+1) = dBaseY;
					*pDescAngle = Angle;
					pDescLine +=2;
					pDescAngle ++;
					lRet ++;
				}
		}
		iStep = (pLength[i]-dLast)/MarkerLength;			//大段数
		dLast = pLength[i]-dLast-(MarkerLength*iStep);	//恢复dLast功能
		for(j= 0; j< iStep; j++)
		{
			for(k= 0; k< MarkerCount; k++)//处理大段中的小段
			{
				dltX = pMarkerSpace[k] * dltTX;
				dltY = pMarkerSpace[k] * dltTY;
				dBaseX += dltX;
				dBaseY += dltY;
				*pDescLine = dBaseX;
				*(pDescLine+1) = dBaseY;
				*pDescAngle = Angle;
				pDescLine +=2;
				pDescAngle ++;
				lRet ++;
			}
		}
		//添加last小段
		IndexSeg = 0;
		if(dLast > pMarkerSpace[0])
		{
			for(k= 0; k< MarkerCount-1; k++)//处理大段中的小段
			{
				dltX = pMarkerSpace[k] * dltTX;
				dltY = pMarkerSpace[k] * dltTY;
				dBaseX += dltX;
				dBaseY += dltY;
				*pDescLine = dBaseX;
				*(pDescLine+1) = dBaseY;
				*pDescAngle = Angle;
				pDescLine +=2;
				pDescAngle ++;
				lRet ++;
				dLast -= pMarkerSpace[k];
				if(dLast < pMarkerSpace[k+1])
				{
//					IndexSeg = fmod(k+1,MarkerCount);
					IndexSeg = ((k+1)%MarkerCount);
					break;
				}
			}
		}
NEXTLOOP:	
//		if(bDashLine && fmod(IndexSeg,2)<0.1)//虚线时
		if(bDashLine && (IndexSeg%2)<0.1)//虚线时
		{
			memcpy(pDescLine,pby+2,16);
			memcpy(pDescLine+2,pby+2,16);
			*pDescAngle = Angle;
			*(pDescAngle+1) = Angle;
			pDescLine +=4;
			pDescAngle +=2;
			lRet +=2;
		}
	}//end(i)
	if(bExtenDIS_LINE)//需要延长线
	{
		double dTemp = pMarkerSpace[0];
		if(pby != pSourLine+2*(PointCount-2))//没有定位在最后一段
		{
			pby = pSourLine+2*(PointCount-2);
			Angle = calculate_angle(pby,pby+2);
			dltTX = (*(pby+2)-*pby)/pLength[PointCount-2];		//斜率
			dltTY = (*(pby+3)-*(pby+1))/pLength[PointCount-2];
			dBaseX = *(pby+2) + (dTemp-dLast)*dltTX;
			dBaseY = *(pby+3) + (dTemp-dLast)*dltTY;
		}
		else
		{
			dltX = dTemp * dltTX;
			dltY = dTemp * dltTY;
			dBaseX += dltX;
			dBaseY += dltY;
		}
		*pDescLine = dBaseX;
		*(pDescLine+1) = dBaseY;
		*pDescAngle = Angle;
		pDescLine +=2;
		pDescAngle ++;
		lRet ++;
		//go on
		IndexSeg = 0;
		dLast += (lengthClip-dTemp);
		while(dLast >0)
		{
			dltX = dTemp * dltTX;
			dltY = dTemp * dltTY;
			dBaseX += dltX;
			dBaseY += dltY;
			*pDescLine = dBaseX;
			*(pDescLine+1) = dBaseY;
			*pDescAngle = Angle;
			pDescLine +=2;
			pDescAngle ++;
			lRet ++;
			dLast -= dTemp;
		}
	}
	if(lengthClip > 0 && dLast >pMarkerSpace[0]/2)
	{
		double dTemp = pMarkerSpace[0];
		if(pby != pSourLine+2*(PointCount-2))//没有定位在最后一段
		{
			pby = pSourLine+2*(PointCount-2);
			Angle = calculate_angle(pby,pby+2);
			dltTX = (*(pby+2)-*pby)/pLength[PointCount-2];		//斜率
			dltTY = (*(pby+3)-*(pby+1))/pLength[PointCount-2];
			dBaseX = *(pby+2) + (dTemp-dLast)*dltTX;
			dBaseY = *(pby+3) + (dTemp-dLast)*dltTY;
		}
		else
		{
			dltX = dTemp * dltTX;
			dltY = dTemp * dltTY;
			dBaseX += dltX;
			dBaseY += dltY;
		}
		*pDescLine = dBaseX;
		*(pDescLine+1) = dBaseY;
		*pDescAngle = Angle;
		pDescLine +=2;
		pDescAngle ++;
		lRet ++;
	}


	delete []pLength; 
	if(lRet <= 0)
	{
		delete [](*ppRetLine);
		delete [](*ppRetAngle);
		*ppRetLine = false;
		*ppRetAngle = false;
	}
	return lRet ;
}

//内部函数
//添加双点于　pDesc(Line/Angle)指针中
long AddDashCornerPt(bool bTailer, UINT JointStyle, long nOY, long PointCount, long * pSourLine, SUBARRAY& ptArray,  UINT iCur, double Angle, long * pDIS_LINE, double * pDAngle )
{
	int j;
	long  lRet = 0;
	INT_POINT  * pDPOINTs = false;
	long * pDescLine = pDIS_LINE;
	double * pDescAngle = pDAngle;
	/*	if(JointStyle == LJSMiter)
	{
	if(iCur >= PointCount-2 && (fabs(pSourLine[0]-pSourLine[2*PointCount-2])>2*TOLER || fabs(pSourLine[1]-pSourLine[2*PointCount-1])>2*TOLER ))
	return 0;
	*pDescLine = ptArray[iCur].trueOffSegment[1].x;
	*(pDescLine+1) = ptArray[iCur].trueOffSegment[1].y;
	*pDescAngle = Angle;
	lRet = 1;
	//
	{
	*(pDescLine+2) = ptArray[iCur+1].pt.x;
	*(pDescLine+3) = ptArray[iCur+1].pt.y;
	*(pDescLine+4) = ptArray[iCur+1].pt.x;
	*(pDescLine+5) = ptArray[iCur+1].pt.y;
	*(pDescLine+6) = ptArray[iCur+1].trueOffSegment[0].x;
	*(pDescLine+7) = ptArray[iCur+1].trueOffSegment[0].y;
	*(pDescAngle+1) = Angle;
	*(pDescAngle+2) = Angle;
	*(pDescAngle+3) = Angle;
	lRet += 3;
	}
	}
	else //if(JointStyle == LJSRound)*/
	{
		SUBPOINT * pAry = &ptArray[iCur];
		int numPt =  pAry->CornerPointCount;
		if(numPt <=0)
			return 0;
		for(j=0; j< numPt-1; j++)
		{
			*pDescLine = pAry->pCornerPoints[j].x;
			*(pDescLine+1) = pAry->pCornerPoints[j].y;
			*(pDescLine+2) = pAry->pCornerPoints[j+1].x;
			*(pDescLine+3) = pAry->pCornerPoints[j+1].y;
			*pDescAngle = Angle;
			*(pDescAngle+1) = Angle;
			pDescLine +=4;
			pDescAngle+=2;
			lRet +=2;
		}
		delete []pDPOINTs;
		pDPOINTs = false;

	}
	return lRet;
}


//内部函数
bool IsSameDirt(long seg1[4], long seg2[4])
{
	return ((seg1[0] - seg1[2])*(seg2[0] - seg2[2]) > 0.1 ||
		(seg1[1] - seg1[3])*(seg2[1] - seg2[3]) > 0.1);
}

//内部函数
//有SUBARRAY结构时，计算“标记线符号”位置
//注：如果JointStyle>0 ,表示"虚线＋倒角类型"
//	　否则为实线，不考虑倒角
//	　（JointStyle　、pSourLine仅仅对“虚线＋倒角”有用）
//	 返回的角度值，对虚线不一定有效（因为没有考虑倒角时的角度）。
//  新加入: lengthClip 表示"需要截取的长度",正常情况设置为0,或者负值;当 "lengthClip>线的总长" 时,lengthClip表示需要延长线.
long GetMarkerLine_Array(UINT JointStyle, long nOY, long PointCount, long * pSourLine, SUBARRAY& ptArray, long MarkCount, long * pMarkSpace,double lengthClip, long ** ppRetLine, double ** ppRetAngle)
{
	_ASSERT(PointCount == ptArray.size());
	INT_POINT  * pDPOINTs = false;
	double Angle, *pLength;		//for temp
	long   *pDescLine , *pby ;	
	double * pDescAngle,dltX,dltY,dltTX,dltTY;				//dltTX,dltTY for temp
	double  dBaseX,dBaseY;		//double		
	long i,j, iStep ;
	int k,dT=1;
	long IndexSeg = 0, lRet;						//IndexSeg:上一段中遗留的Mark小段号
	double dLast = 0, dLastTemp, MarkLength = 0;	//dLast > 0 表示“上一段有遗留的线长度” ;dLastTemp为“本段中没有走的部分”
	double dOverLastLgt, dOverOrgLgt;				//重合边离本线段首尾的距离。 

	for(i= 0; i< MarkCount; i++)
	{
		MarkLength += pMarkSpace[i];
		if(pMarkSpace[i]==0)
			dT++;
	}
	//计算线段长
	dltTX = 0;			//借用,作为总长
	pLength = new double[PointCount];
	for(i= 0; i< PointCount-1; i++)
	{
		pLength[i] = ptArray[i].SourceLength;
		dltTX += pLength[i];
	}
	bool bExtenDIS_LINE;//需要延长线
	if(lengthClip > dltTX+TOLER)
	{
		_ASSERT(MarkCount == 1);
		bExtenDIS_LINE = true;
		lengthClip -= dltTX;
	}
	else
		bExtenDIS_LINE = false;

	//分配了内存
	lRet = ((long)(dltTX/MarkLength)+1)*(MarkCount+1);//借用,作为总点数
	if(JointStyle > 0)	//如果是虚线&&有倒角，还要加入倒角上的点
	{
		dT = (lRet+PointCount*72)*dT;
		*ppRetLine  = new long[2*dT];
		*ppRetAngle = new double[dT];
	}
	else
	{	
		if(bExtenDIS_LINE)
			lRet += (lengthClip/pMarkSpace[0] +1);
		*ppRetLine  = new long[2*lRet];
		*ppRetAngle = new double[lRet];
	}

	pDescLine = *ppRetLine;
	pDescAngle = *ppRetAngle;
	//开始
	lRet = 0;
	for(i= 0; i< PointCount-1; i++)
	{
		if(ptArray[i].bIsfalseline || !IsSameDirt((long*)ptArray[i].OffSgment,(long*)ptArray[i].trueOffSegment))
		{
			if(JointStyle > 0 && i > 0  && 
//				(dLast < TOLER || dLast >= TOLER && fmod(IndexSeg,2)<0.1 && !ptArray[i-1].bIsfalseline))
				(dLast < TOLER || dLast >= TOLER && (IndexSeg%2)<0.1 && !ptArray[i-1].bIsfalseline))
			{
				k = AddDashCornerPt(true,JointStyle,nOY,PointCount, pSourLine, ptArray, i-1,Angle, pDescLine, pDescAngle);
				pDescLine += 2*k;
				pDescAngle += k;
				lRet += k;
			}
			dLast += pLength[i];
			if(dLast < pMarkSpace[IndexSeg])
				continue;
			//走完本段Mark
			iStep = dLast/MarkLength;			
			dLast -= MarkLength*iStep;	
			for(k=IndexSeg; k< MarkCount; k++)//处理大段中的小段
			{
				dLast -= pMarkSpace[k];
				if(dLast <0)
				{
					IndexSeg = k;
					//dLast = -dLast;		//恢复dLast功能
					dLast += pMarkSpace[k] ;
					break;
				}
				if(k==MarkCount-1)//for loop
					k=-1;
			}
			continue;
		}	
		pby = (long *)ptArray[i].OffSgment;
		//计算本线段的Angle
		Angle = calculate_angle(pby,pby+2);
		dltTX = (*(pby+2)-*pby)/pLength[i];		//斜率
		dltTY = (*(pby+3)-*(pby+1))/pLength[i];

		dOverOrgLgt = sqrt((ptArray[i].trueOffSegment[0].x-*pby)*1.0*(ptArray[i].trueOffSegment[0].x-*pby)+(ptArray[i].trueOffSegment[0].y-*(pby+1))*1.0*(ptArray[i].trueOffSegment[0].y-*(pby+1)));
		dOverLastLgt = ptArray[i].SourceLength - ptArray[i].OffSgLength - dOverOrgLgt;
		dLastTemp = pMarkSpace[IndexSeg] - dLast;
		//if(dOverOrgLgt < 0) dOverOrgLgt =0;
		//if(dOverLastLgt < 0) dOverLastLgt =0;
		if(dLastTemp < TOLER) dLastTemp =0;
		//加入上一个有效的外角
		if(JointStyle > 0 && i > 0 && dOverOrgLgt <= TOLER &&
//			(fmod(IndexSeg,2)<0.1 || dLast < TOLER ))	//|| fabs(dLast-pMarkSpace[IndexSeg])< TOLER)
			((IndexSeg%2)<0.1 || dLast < TOLER ))	//|| fabs(dLast-pMarkSpace[IndexSeg])< TOLER)
		{
			k = AddDashCornerPt(true,JointStyle,nOY,PointCount, pSourLine, ptArray, i-1,Angle, pDescLine, pDescAngle);
			pDescLine += 2*k;
			pDescAngle += k;
			lRet += k;
		}
		//有“交叠边”
		if(dLast+pLength[i] < pMarkSpace[IndexSeg] + TOLER)//本段长度不够，或者刚好。
		{
			if(JointStyle>0)//处理虚线(实线段)
			{	
//				if(fmod(IndexSeg,2)<0.1)
				if((IndexSeg%2)<0.1)
				{
					//加入2点
					*pDescLine = ptArray[i].trueOffSegment[0].x;
					*(pDescLine+1) = ptArray[i].trueOffSegment[0].y;
					*(pDescLine+2) = ptArray[i].trueOffSegment[1].x;
					*(pDescLine+3) = ptArray[i].trueOffSegment[1].y;
					*pDescAngle = Angle;
					*(pDescAngle+1) = Angle;
					pDescLine +=4;
					pDescAngle +=2;
					lRet +=2;
					k = AddDashCornerPt(true,JointStyle,nOY,PointCount, pSourLine, ptArray, i,Angle, pDescLine, pDescAngle);
					pDescLine += 2*k;
					pDescAngle += k;
					lRet += k;
				}
				else if(dLast+pLength[i] > pMarkSpace[IndexSeg]-TOLER)
				{
					k = AddDashCornerPt(true,JointStyle,nOY,PointCount, pSourLine, ptArray, i,Angle, pDescLine, pDescAngle);
					pDescLine += 2*k;
					pDescAngle += k;
					lRet += k;
				}
			}
			else//标记线
			{
				if(dLast < TOLER && dOverOrgLgt < TOLER)
				{
					*pDescLine = ptArray[i].trueOffSegment[0].x;
					*(pDescLine+1) = ptArray[i].trueOffSegment[0].y;
					*pDescAngle = Angle;
					pDescLine +=2;
					pDescAngle ++;
					lRet ++;
				}
				if(dOverLastLgt < TOLER && 
					(dLast+pLength[i] > pMarkSpace[IndexSeg]-TOLER))//刚好尾点
				{
					*pDescLine = ptArray[i].trueOffSegment[1].x;
					*(pDescLine+1) = ptArray[i].trueOffSegment[1].y;
					*pDescAngle = Angle;
					pDescLine +=2;
					pDescAngle ++;
					lRet ++;
//					IndexSeg = fmod(IndexSeg+1,MarkCount);
					IndexSeg = ((IndexSeg+1)%MarkCount);
					dLast = 0;
					continue;
				}
			}
			dLast += pLength[i];
			continue;
		}

//		if(dLast < TOLER && (JointStyle <= 0 || fmod(IndexSeg,2)<0.1)
		if(dLast < TOLER && (JointStyle <= 0 || (IndexSeg%2)<0.1)
			&& dOverOrgLgt < TOLER)	//标记点在端点时，多加一个点
		{
			dBaseX = (double)ptArray[i].trueOffSegment[0].x;
			dBaseY = (double)ptArray[i].trueOffSegment[0].y;
			*pDescLine = dBaseX;
			*(pDescLine+1) = dBaseY;
			*pDescAngle = Angle;
			pDescLine +=2;
			pDescAngle ++;
			lRet ++;
		}
		//走dOverOrgLgt
		if(dOverOrgLgt > dLastTemp)
		{	
//			IndexSeg = fmod(IndexSeg+1,MarkCount);
			IndexSeg = ((IndexSeg+1)%MarkCount);
			iStep = (dOverOrgLgt-dLastTemp)/MarkLength;			//大段数
			dLastTemp = dOverOrgLgt-dLastTemp-MarkLength*iStep;	
			for(k=IndexSeg; k< MarkCount; k++)//处理大段中的小段
			{
				dLastTemp -= pMarkSpace[k];
				if(dLastTemp < 0)
				{
					IndexSeg = k;
					//dLast = -dLast;		//恢复dLast功能
					dLast = pMarkSpace[k] + dLastTemp;
					dLastTemp = -dLastTemp;
					break;
				}
				if(k==MarkCount-1)//for loop
					k=-1;
			}
		}
		else
		{
			dLast += dOverOrgLgt;
			dLastTemp -= dOverOrgLgt;
		}
		//添加有效头点
//		if(JointStyle>0 && fmod(IndexSeg,2)<0.1 &&
		if(JointStyle>0 && (IndexSeg%2)<0.1 &&
			(dLast >= TOLER || dOverOrgLgt > TOLER))//处理虚线(实线段)
		{	
			*pDescLine = ptArray[i].trueOffSegment[0].x;
			*(pDescLine+1) = ptArray[i].trueOffSegment[0].y;
			*pDescAngle = Angle;
			pDescLine +=2;
			pDescAngle ++;
			lRet ++;
		}
		//正常走大段
		if(ptArray[i].OffSgLength > dLastTemp)
		{	
			//添加第一个点
			dltX = dLastTemp * dltTX;
			dltY = dLastTemp * dltTY;
			dBaseX = (double)ptArray[i].trueOffSegment[0].x + dltX;
			dBaseY = (double)ptArray[i].trueOffSegment[0].y + dltY;
			*pDescLine = dBaseX;				
			*(pDescLine+1) = dBaseY;
			*pDescAngle = Angle;
			pDescLine +=2;
			pDescAngle ++;
			lRet ++;
//			IndexSeg = fmod(IndexSeg+1,MarkCount);
			IndexSeg = ((IndexSeg+1)%MarkCount);
			//大段数
			iStep = (ptArray[i].OffSgLength-dLastTemp)/MarkLength;			
			dLastTemp = ptArray[i].OffSgLength-dLastTemp-MarkLength*iStep;	
			//加入“大段”点
			int numInd;
			for(j= 0; j< iStep; j++)
			{
				for(k= 0; k< MarkCount; k++)//处理大段中的小段
				{
//					numInd = fmod(k+IndexSeg,MarkCount);
					numInd = ((k+IndexSeg)%MarkCount);
					dltX = pMarkSpace[numInd] * dltTX;
					dltY = pMarkSpace[numInd] * dltTY;
					dBaseX += dltX;
					dBaseY += dltY;
					*pDescLine = dBaseX;
					*(pDescLine+1) = dBaseY;
					*pDescAngle = Angle;
					pDescLine +=2;
					pDescAngle ++;
					lRet ++;
				}
			}
			//处理大段中的小段
			for(k=IndexSeg; k< MarkCount; k++)
			{
				dLastTemp -= pMarkSpace[k];
				if(dLastTemp < 0)
				{
					IndexSeg = k;
					//dLast = -dLast;		//恢复dLast功能
					dLast = pMarkSpace[k] + dLastTemp;
					dLastTemp = -dLastTemp;
					break;
				}
				dltX = pMarkSpace[k] * dltTX;
				dltY = pMarkSpace[k] * dltTY;
				dBaseX += dltX;
				dBaseY += dltY;
				*pDescLine = dBaseX;
				*(pDescLine+1) = dBaseY;
				*pDescAngle = Angle;
				pDescLine +=2;
				pDescAngle ++;
				lRet ++;
				if(k==MarkCount-1)//for loop
					k=-1;
			}
		}
		else
		{
			dLast += ptArray[i].OffSgLength;
			dLastTemp -= ptArray[i].OffSgLength;
		}
		//添加有效尾点
		if(JointStyle>0)//处理虚线(实线段)
		{	
//			if(fmod(IndexSeg,2)<0.1)
			if((IndexSeg%2)<0.1)
			{
				*pDescLine = ptArray[i].trueOffSegment[1].x;
				*(pDescLine+1) = ptArray[i].trueOffSegment[1].y;
				*pDescAngle = Angle;
				pDescLine +=2;
				pDescAngle ++;
				lRet ++;
			}
		}
		//走dOverLastLgt段
		if(dOverLastLgt > dLastTemp)
		{	
			IndexSeg = ((IndexSeg+1)%MarkCount);
			iStep = (dOverLastLgt-dLastTemp)/MarkLength;			//大段数
			dLastTemp = dOverLastLgt-dLastTemp-MarkLength*iStep;	
			for(k=IndexSeg; k< MarkCount; k++)//处理大段中的小段
			{
				dLastTemp -= pMarkSpace[k];
				if(dLastTemp < 0)
				{
					IndexSeg = k;
					//dLast = -dLast;		//恢复dLast功能
					dLast = pMarkSpace[k] + dLastTemp;
					dLastTemp = -dLastTemp;
					break;
				}
				if(k==MarkCount-1)//for loop
					k=-1;
			}
		}
		else
		{
			dLast = pMarkSpace[IndexSeg] -(dLastTemp - dOverLastLgt);
		}

		if(dOverLastLgt < TOLER && fabs(pMarkSpace[IndexSeg]-dLast) < TOLER)
		{
			if(JointStyle <= 0)//标记线
			{
				*pDescLine = ptArray[i].trueOffSegment[1].x;
				*(pDescLine+1) = ptArray[i].trueOffSegment[1].y;
				*pDescAngle = Angle;
				pDescLine +=2;
				pDescAngle ++;
				lRet ++;
//				IndexSeg = fmod(IndexSeg+1,MarkCount);
				IndexSeg = ((IndexSeg+1)&MarkCount);
				dLast = 0;
			}
			else//虚线
			{
				k = AddDashCornerPt(true,JointStyle,nOY,PointCount, pSourLine, ptArray, i,Angle, pDescLine, pDescAngle);
				pDescLine += 2*k;
				pDescAngle += k;
				lRet += k;
			}

		}
	}//end(i)
	if(bExtenDIS_LINE)//需要延长线
	{
		double dTemp = pMarkSpace[0];
		if(pby != pSourLine+2*(PointCount-2))//没有定位在最后一段
		{
			pby = pSourLine+2*(PointCount-2);
			Angle = calculate_angle(pby,pby+2);
			dltTX = (*(pby+2)-*pby)/pLength[PointCount-1];		//斜率
			dltTY = (*(pby+3)-*(pby+1))/pLength[PointCount-1];
			dBaseX = *(pby+2) + (dTemp-dLast)*dltTX;
			dBaseY = *(pby+3) + (dTemp-dLast)*dltTY;
		}
		else
		{
			dltX = dTemp * dltTX;
			dltY = dTemp * dltTY;
			dBaseX += dltX;
			dBaseY += dltY;
		}
		*pDescLine = dBaseX;
		*(pDescLine+1) = dBaseY;
		*pDescAngle = Angle;
		pDescLine +=2;
		pDescAngle ++;
		lRet ++;
		//go on
		IndexSeg = 0;
		dLast += (lengthClip-dTemp);
		while(dLast >0)
		{
			dltX = dTemp * dltTX;
			dltY = dTemp * dltTY;
			dBaseX += dltX;
			dBaseY += dltY;
			*pDescLine = dBaseX;
			*(pDescLine+1) = dBaseY;
			*pDescAngle = Angle;
			pDescLine +=2;
			pDescAngle ++;
			lRet ++;
			dLast -= dTemp;
		}
	}
	else if(lRet != 0 && JointStyle <= 0 && dLast > TOLER && dOverLastLgt < TOLER
//		|| (JointStyle>0 && fmod(IndexSeg,2)<0.1))//加上最后一个点
		|| (JointStyle>0 && (IndexSeg%2)<0.1))//加上最后一个点	
	{

		if(JointStyle>0 && labs(*pSourLine - *(pSourLine + 2*PointCount -2)) < TOLER 
			&& labs(*(pSourLine+1) - *(pSourLine + 2*PointCount -1)) < TOLER )//是环
		{
			k = AddDashCornerPt(true,JointStyle,nOY,PointCount, pSourLine, ptArray, PointCount-2 ,Angle, pDescLine, pDescAngle);
			pDescLine += 2*k;
			pDescAngle += k;
			lRet += k;
		}
	}
	if(lengthClip > 0 && dLast >pMarkSpace[0]/2)
	{
		double dTemp = pMarkSpace[0];
		if(pby != pSourLine+2*(PointCount-2))//没有定位在最后一段
		{
			pby = pSourLine+2*(PointCount-2);
			Angle = calculate_angle(pby,pby+2);
			dltTX = (*(pby+2)-*pby)/pLength[PointCount-1];		//斜率
			dltTY = (*(pby+3)-*(pby+1))/pLength[PointCount-1];
			dBaseX = *(pby+2) + (dTemp-dLast)*dltTX;
			dBaseY = *(pby+3) + (dTemp-dLast)*dltTY;
		}
		else
		{
			dltX = dTemp * dltTX;
			dltY = dTemp * dltTY;
			dBaseX += dltX;
			dBaseY += dltY;
		}
		*pDescLine = dBaseX;
		*(pDescLine+1) = dBaseY;
		*pDescAngle = Angle;
		pDescLine +=2;
		pDescAngle ++;
		lRet ++;
	}

	delete []pLength;
	if(lRet <= 0)
	{
		delete [](*ppRetLine);
		delete [](*ppRetAngle);
		*ppRetLine = false;
		*ppRetAngle = false;
	}
	return lRet ;
}

//内部函数：去除头一个数据
template<class T>
void RemoveFirstNote(T* pData, long num,int step)
{
	UINT n = num/step;
	for(UINT i=1; i<n; i++)
	{
		memcpy(&pData[step*(i-1)],&pData[step*i],step*sizeof(T));
	}
}


//功能：标记线符号计算偏移后的线
//参数：输入参数	pSourLine:原线的点集
//					nOX:水平偏移
//					nOY:垂直偏移
//					JointStyle:拐角样式	
//					MarkCount: 样式单元中标记数
//					pMarkSpace:样式单元中每个标记的间隔
//      输出参数
//					ppRetLine: 返回的绘制标记符号的位置集(点集)
//					pRetAngle:返回位置处线的角度（弧度）
//返回值：
//		ppRetLine中点的个数
long Display::CDisOptimize::OffsetLineByMarkLine(long PointCount,const  long * pSourLine , long nOX, long nOY,unsigned char JointStyle, long MarkCount, long * pMarkSpace, long ** ppRetLine, double ** ppRetAngle)
{
		_ASSERT(pSourLine != false && PointCount > 1 &&  *ppRetLine == false );
		_ASSERT(MarkCount>0);
		if(MarkCount<1)
		{
			return DP_MARKCOUNT_ERROR;
		}
		bool bParaError = false;
		bool bAllZero = true;
		for(long i=0; i<MarkCount; i++)
		{
			if(pMarkSpace[i] < 0)
			{
				bParaError = true;
				break;
			}
			if(pMarkSpace[i]>0)
				bAllZero = false;
		}
		if(bParaError || bAllZero)
			return DP_MARKLINE_ERROR;
		_ASSERT(JointStyle > 0);
		//	ASSERT(nOX >=0);
		if(nOX <0) nOX =0;
		if(labs(nOY) <0) nOY = 0;
		long * pSour = false;
		long numPoint, retVal;
		//处理水平偏移
		numPoint = OffsetLnOX(PointCount,(long*)pSourLine,nOX,&pSour);
		if(numPoint<0)
		{
			*ppRetLine = false;
			return numPoint;
		}
		//处理垂直偏移
		if( nOY == 0 )
		{
			//没有垂直偏移
			retVal = GetMarkerLine(false,numPoint,pSour,MarkCount, pMarkSpace,0,ppRetLine, ppRetAngle);
		}
		else
		{
			//nOY = -nOY;
			SUBARRAY ptArray;
			//形成链表结构　ptArray
			_Offsetline( numPoint , (INT_POINT*)pSour, ptArray , nOY );
			// 整理内外角关系以及倒角
			_TrimlineCorner( nOY , ptArray , (INT_POINT*)pSour , 
				JointStyle == LJSRound? GetAngleArc:(JointStyle == LJSMiter? GetAnglefalse:GetAngleCut) );

			if( !FeedLengthInArray(ptArray))
			{
				//ptArray 中没有内容
				delete []pSour;
				*ppRetLine = false; 
				*ppRetAngle = false;
				return -1;
			}
			retVal = GetMarkerLine_Array(0,nOY,numPoint,pSour,ptArray,MarkCount, pMarkSpace,0,ppRetLine, ppRetAngle);
		}
		delete []pSour;
		return retVal;
}


//功能：虚线符号计算偏移后的线
//参数：输入参数	pSourLine:原线的点集
//					nOX:水平偏移
//					nOY:垂直偏移
//					JointStyle:拐角样式	
//					MarkCount虚线样式单元中部分数
//					pMarkSpace每部分的长度集
//      输出参数
//					ppRetLine: 返回的绘制虚线符号的位置集(点集)
//返回值：
//		ppRetLine中点的个数
long Display::CDisOptimize::OffsetLineByDasheDIS_LINE(long PointCount,const long* pSourLine, long nOX, long nOY, unsigned char  JointStyle, long MarkCount, long * pMarkSpace, long **ppRetLine,double **ppRetAngle)
{
		_ASSERT(pSourLine != false && PointCount > 1 &&  *ppRetLine == false );
		_ASSERT(MarkCount>0);
		if(MarkCount<1)
		{
			return DP_MARKCOUNT_ERROR;
		}
		bool bParaError = false;
		bool bAllZero = true;
		for(long i=0; i<MarkCount; i++)
		{
			if(pMarkSpace[i] < 0)
			{
				bParaError = true;
				break;
			}
			if(pMarkSpace[i]>0)
				bAllZero = false;
		}
		if(bParaError || bAllZero)
			return DP_MARKLINE_ERROR;
		_ASSERT(JointStyle > 0);
		//	ASSERT(nOX >=0);
		if(nOX <0) nOX =0;
		if(labs(nOY) <0) nOY = 0;
		long * pSour = false;
		long numPoint, retVal;
		*ppRetAngle = false;

		//处理水平偏移
		numPoint = OffsetLnOX(PointCount,(long*)pSourLine,nOX,&pSour);
		if(numPoint<0)
		{
			*ppRetLine = false;
			return numPoint;
		}
		//处理垂直偏移
		if( nOY == 0 )
		{
			//没有垂直偏移
			retVal = GetMarkerLine(true,numPoint,pSour,MarkCount, pMarkSpace,0,ppRetLine, ppRetAngle);
		}
		else
		{
			//nOY = -nOY;
			SUBARRAY ptArray;
			//形成链表结构　ptArray
			_Offsetline( numPoint , (INT_POINT*)pSour, ptArray , nOY );
			// 整理内外角关系以及倒角
			_TrimlineCorner( nOY , ptArray , (INT_POINT*)pSour , 
				JointStyle == LJSRound? GetAngleArc:(JointStyle == LJSMiter? GetAnglefalse:GetAngleCut) );

			if( !FeedLengthInArray(ptArray))
			{
				//ptArray 中没有内容
				delete []pSour;
				*ppRetLine = false; 
				return -1;
			}
			retVal = GetMarkerLine_Array((UINT)JointStyle,nOY,numPoint,pSour,ptArray,MarkCount, pMarkSpace,0,ppRetLine, ppRetAngle);
		}
		
		delete []pSour;
		return retVal;
}


//功能：得到距离线的首点或尾点一定长度的位置和角度(用于修饰属性)
//参数：输入参数	pSourLine:原线的点集
//					nOY:垂直偏移
//					JointStyle:拐角样式			
//					nDistance:距离值
//					nDirect:方向 =0 指到首点距离  =1到尾点距离
//      输出参数
//					pRetPoint:返回的位置(点)
//					pRetAngle:返回位置处线的角度（弧度）
//返回值：
//		false：　	长度大于线的长度，没有处理而返回
//					nDirect 不为0 或 1
//					nDistance < 0
//					当垂直方向有偏移 && 点不在有效线上。
//需求变更(2005.4.29)：只要点不在第一段或最后一段上，返回F。
bool Display::CDisOptimize::GetPtInLineByDistance(long PointCount,const long * pSourLine, long nOY, unsigned char JointStyle, long nDistance , long nDirect , long * pRetPoint , double* pRetAngle )
{
		_ASSERT(pSourLine != false && PointCount > 1);
		_ASSERT(pRetPoint != false && pRetAngle != false);
		if(!(nDirect ==0 || nDirect ==1) || nDistance < 0)
			return false;
		UINT i;
		double length = 0 , lTotal = 0;
		double dltTX ,dltTY;
		long * pby = (long*)pSourLine;
		/*	
		//2005.4.28需求变更前(Begin)
		if(nDirect == 0)
		{
		for(i=0 ;i< PointCount-1; i++, pby += 2)
		{
		length = sqrt((*(pby+2)-*pby)*1.0*(*(pby+2)-*pby)+(*(pby+3)-*(pby+1))*1.0*(*(pby+3)-*(pby+1)));
		lTotal += length;
		if(lTotal >= nDistance)
		{
		lTotal = length - (lTotal-nDistance); //i段的偏移量
		break;
		}
		}
		}
		else//nDirect == 1
		{
		pby = (long*)pSourLine+2*(PointCount-2);
		for(i=0 ;i< PointCount-1; i++, pby -= 2)
		{
		length = sqrt((*(pby+2)-*pby)*1.0*(*(pby+2)-*pby)+(*(pby+3)-*(pby+1))*1.0*(*(pby+3)-*(pby+1)));
		lTotal += length;
		if(lTotal >= nDistance)
		{
		lTotal = lTotal-nDistance; //i段的偏移量
		break;
		}
		}
		}
		if(i == PointCount-1)
		return false;
		//2005.4.28需求变更前(End)
		*/

		//需求变更后新增加的(Begin)
		if(nDirect == 1)
		{
			i=PointCount-2;
			pby = (long*)pSourLine+2*(PointCount-2);
			length = sqrt((*(pby+2)-*pby)*1.0*(*(pby+2)-*pby)+(*(pby+3)-*(pby+1))*1.0*(*(pby+3)-*(pby+1)));
			lTotal = length - nDistance;
		}
		else
		{
			i =0;
			length = sqrt((*(pby+2)-*pby)*1.0*(*(pby+2)-*pby)+(*(pby+3)-*(pby+1))*1.0*(*(pby+3)-*(pby+1)));
			lTotal = nDistance;
		}
		if(nDistance > length)
			return false;
		//需求变更后新增加的(End)

		//在第i条线上
		*pRetAngle = calculate_angle(pby,pby+2);
		dltTX = (*(pby+2)-*pby)/length;		//斜率
		dltTY = (*(pby+3)-*(pby+1))/length;

		*pRetPoint = *pby + lTotal*dltTX;
		*(pRetPoint+1) = *(pby+1) + lTotal*dltTY;
		if(nOY != 0)
		{
			//nOY = - nOY;
			*pRetPoint -=  nOY *(*(pby+3)-*(pby+1))/length ;
			*(pRetPoint+1) +=  nOY *(*(pby+2)-*pby)/length ;
			SUBARRAY ptArray;
			//形成链表结构　ptArray
			_Offsetline( PointCount , (INT_POINT*)pSourLine, ptArray , nOY );
			// 整理内外角关系以及倒角
			_TrimlineCorner( nOY , ptArray , (INT_POINT*)pSourLine , 
				JointStyle == LJSRound? GetAngleArc:(JointStyle == LJSMiter? GetAnglefalse:GetAngleCut) );
			//		if(nDirect == 1)
			//			i = PointCount-i-2;
			if(ptArray[i].bIsfalseline || 
				!IsInScope(pRetPoint,ptArray[i].trueOffSegment))
				return false;
		}
}


//得到线角度
double Display::CDisOptimize::GetAngleOfLine(long *pStartPoint , long* pEndPoint )
{
	return calculate_angle(pStartPoint,pEndPoint);

}



//功能：取到线上各个节点一定距离的位置集和各位置的角度集（逆时针角度为正）
//参数：输入参数	pSourLine:原线的点集
//					nOY:垂直偏移
//					JointStyle:拐角样式	
//					nDistance:到节点的距离 大于0为线的前向  小于0为线的反向
//      输出参数
//					ppRetPoints: 返回的各位置集合
//					ppRetAngles: 返回的各位置处线的角度集合
//返回值：
//		ppRetPoints中点的个数
long Display::CDisOptimize::GetPtsInLineByNodeDistance(long PointCount,const  long * pSourLine, long nOY, unsigned char  JointStyle,long nDistance , long ** ppRetPoints, double** ppRetAngles )
{
		_ASSERT(pSourLine != false && PointCount > 1);
		_ASSERT(*ppRetPoints == false && *ppRetAngles == false);
		*ppRetPoints = new long[2*PointCount]; 
		*ppRetAngles = new double[PointCount];

		UINT i,nBegin,nEnd;
		bool bFront; 
		double length, dltTX ,dltTY;
		long * pby = (long *)pSourLine;
		long * pDescPt = *ppRetPoints , Ret = 0;
		double * pDescAgl =  *ppRetAngles;

		nBegin = 0;
		nEnd = PointCount-1;
		if(nDistance > 0)
		{
			bFront = true;
			nBegin ++;
			pby += 2;
		}
		else
		{
			bFront = false;
			nDistance = -nDistance;
			nEnd --;
		}

		if(nOY ==0)
		{
			for(i=nBegin ;i< nEnd; i++, pby += 2)
			{
				length = sqrt((*(pby+2)-*pby)*1.0*(*(pby+2)-*pby)+(*(pby+3)-*(pby+1))*1.0*(*(pby+3)-*(pby+1)));
				if(length < nDistance)
					continue;
				*pDescAgl = calculate_angle(pby,pby+2);
				dltTX = (*(pby+2)-*pby)/length;		//斜率
				dltTY = (*(pby+3)-*(pby+1))/length;
				if(bFront)
				{
					*pDescPt = *pby + nDistance*dltTX;
					*(pDescPt+1) = *(pby+1) + nDistance*dltTY;
				}
				else
				{
					*pDescPt = *(pby+2) - nDistance*dltTX;
					*(pDescPt+1) = *(pby+3) - nDistance*dltTY;
				}	
				pDescPt += 2;
				pDescAgl += 1;
				Ret ++;
			}
		}
		else // nOY !=0
		{
			//nOY = - nOY;
			long ptTemp[2];
			SUBARRAY ptArray;
			//形成链表结构　ptArray
			_Offsetline( PointCount , (INT_POINT*)pSourLine, ptArray , nOY );
			// 整理内外角关系以及倒角
			_TrimlineCorner( nOY , ptArray , (INT_POINT*)pSourLine , 
				JointStyle ==LJSRound? GetAngleArc:(JointStyle == LJSMiter? GetAnglefalse:GetAngleCut) );
			for(i=nBegin ;i< nEnd; i++)
			{
				if(ptArray[i].bIsfalseline)
					continue;
				pby = (long *)ptArray[i].OffSgment;
				length = sqrt((*(pby+2)-*pby)*1.0*(*(pby+2)-*pby)+(*(pby+3)-*(pby+1))*1.0*(*(pby+3)-*(pby+1)));
				if(length < nDistance)
					continue;
				*pDescAgl = calculate_angle(pby,pby+2);
				dltTX = (*(pby+2)-*pby)/length;		//斜率
				dltTY = (*(pby+3)-*(pby+1))/length;
				if(bFront)
				{
					ptTemp[0] = *pby + nDistance*dltTX;
					ptTemp[1] = *(pby+1) + nDistance*dltTY;
				}
				else
				{
					ptTemp[0] = *(pby+2) - nDistance*dltTX;
					ptTemp[1] = *(pby+3) - nDistance*dltTY;
				}	
				if(IsInScope(ptTemp,ptArray[i].trueOffSegment))
				{
					*pDescPt = ptTemp[0];
					*(pDescPt+1) = ptTemp[1];
					pDescPt += 2;
					pDescAgl += 1;
					Ret ++;
				}
			}
		}
		if(Ret <=0)
		{
			delete [](*ppRetPoints);
			delete [](*ppRetAngles);
			*ppRetPoints = false;
			*ppRetAngles = false;
		}
		return Ret;
}


//功能：取线中各子线段的中心位置，返回各位置和该位置线的角度（逆时针角度为正）
//参数：输入参数	pSourLine:原线的点集
//					nOY:垂直偏移
//					JointStyle:拐角样式	
//      输出参数
//					ppRetPoints: 返回的各位置集合
//					ppRetAngles: 返回的各位置处线的角度集合
//返回值：
//		ppRetPoints中点的个数
long Display::CDisOptimize::GetPtsInSubLineByCenter(long PointCount,const  long * pSourLine, long nOY, unsigned char  JointStyle, long ** ppRetPoints, double** ppRetAngles)
{
		*ppRetPoints = new long[2*PointCount]; 
		*ppRetAngles = new double[PointCount];

		long i;
		double length;
		long * pby = (long *)pSourLine;
		long * pDescPt = *ppRetPoints , Ret = 0;
		double * pDescAgl =  *ppRetAngles;

		if(nOY ==0)
		{
			for(i=0 ;i< PointCount-1; i++, pby += 2)
			{
				length = sqrt((*(pby+2)-*pby)*1.0*(*(pby+2)-*pby)+(*(pby+3)-*(pby+1))*1.0*(*(pby+3)-*(pby+1)));
				if(length < TOLER)
					continue;
				*pDescAgl = calculate_angle(pby,pby+2);
				*pDescPt = (*pby + *(pby+2))/2;
				*(pDescPt+1) = (*(pby+1) + *(pby+3))/2;
				pDescPt += 2;
				pDescAgl += 1;
				Ret ++;
			}
		}
		else // nOY !=0
		{
			//nOY = - nOY;
			long ptTemp[2];
			SUBARRAY ptArray;
			//形成链表结构　ptArray
			_Offsetline( PointCount , (INT_POINT*)pSourLine, ptArray , nOY );
			// 整理内外角关系以及倒角
			_TrimlineCorner( nOY , ptArray , (INT_POINT*)pSourLine , 
				JointStyle == LJSRound? GetAngleArc:(JointStyle == LJSMiter? GetAnglefalse:GetAngleCut) );
			for(i=0 ;i< PointCount-1; i++)
			{
				if(ptArray[i].bIsfalseline)
					continue;
				pby = (long *)ptArray[i].OffSgment;
				length = sqrt((*(pby+2)-*pby)*1.0*(*(pby+2)-*pby)+(*(pby+3)-*(pby+1))*1.0*(*(pby+3)-*(pby+1)));
				if(length < TOLER)
					continue;
				*pDescAgl = calculate_angle(pby,pby+2);
				ptTemp[0] = (*pby + *(pby+2))/2;
				ptTemp[1] = (*(pby+1) + *(pby+3))/2;
				if(IsInScope(ptTemp,ptArray[i].trueOffSegment))
				{
					*pDescPt = ptTemp[0];
					*(pDescPt+1) = ptTemp[1];
					pDescPt += 2;
					pDescAgl += 1;
					Ret ++;
				}
			}
		}
		if(Ret <=0)
		{
			delete [](*ppRetPoints);
			delete [](*ppRetAngles);
			*ppRetPoints = false;
			*ppRetAngles = false;
		}
		return Ret;
}



//功能：用给定间隔长度平均分割线，返回各分割点位置和该点处线的角度（逆时针角度为正）
//参数：输入参数	pSourLine:原线的点集
//					nOY:垂直偏移
//					JointStyle:拐角样式	
//					nLength::线分割的间隔长度
//      输出参数
//					ppRetPoints: 返回的各位置集合
//					ppRetAngles: 返回的各位置处线的角度集合
//返回值：
//		ppRetPoints中点的个数
//说明：如果有偏移，定位以原线为准
long Display::CDisOptimize::GetPtsInLineByAvgInterval(long PointCount,const  long * pSourLine, long nOY, unsigned char  JointStyle, long nLength , long ** ppRetPoints, double** ppRetAngles)
{
		_ASSERT(pSourLine != false && PointCount > 1);
		_ASSERT(*ppRetPoints == false && *ppRetAngles == false);
		long ret = Display::CDisOptimize::OffsetLineByMarkLine(PointCount,pSourLine , 0, nOY,JointStyle, 1, &nLength, ppRetPoints, ppRetAngles);
		if(ret ==1)
		{
			delete [](*ppRetPoints);
			delete [](*ppRetAngles);
			*ppRetPoints = false;
			*ppRetAngles = false;
			return 0;
		}
		//去除第一点
		RemoveFirstNote(*ppRetPoints, 2*ret,2);
		RemoveFirstNote(*ppRetAngles, ret,1);
	return ret;
}


//功能：用给定段数(中间点数+1)平均分割线，返回各分割点位置和该点处线的角度（逆时针角度为正）
//		要求：首尾点去除
//参数：输入参数	pSourLine:原线的点集
//					nOY:垂直偏移
//					JointStyle:拐角样式	
//					nCount::中间的点个数
//      输出参数
//					ppRetPoints: 返回的各位置集合
//					ppRetAngles: 返回的各位置处线的角度集合
//返回值：
//		ppRetPoints中点的个数
//说明：如果有偏移，定位以原线为准
long Display::CDisOptimize::GetPtsInLineByAvgCount(long PointCount,const  long * pSourLine, long nOY, unsigned char JointStyle, long nCount, long ** ppRetPoints, double** ppRetAngles)
{
		_ASSERT(pSourLine != false && PointCount > 1);
		_ASSERT(*ppRetPoints == false && *ppRetAngles == false);
		if(nCount <= 0)
			return 0;
		long i;
		double length= 0 ;
		long * pby = (long *)pSourLine;
		for(i=0 ;i< PointCount-1; i++, pby += 2)
		{
			length += sqrt((*(pby+2)-*pby)*1.0*(*(pby+2)-*pby)+(*(pby+3)-*(pby+1))*1.0*(*(pby+3)-*(pby+1)));
		}
		length = length/(nCount+1)+1;
		return GetPtsInLineByAvgInterval(PointCount,pSourLine, nOY,JointStyle,length , ppRetPoints, ppRetAngles);
}




//////////////////////////////////////////////////////////////////////////
//面符号

//内部函数
//直线与矩形的交点
//不考虑水平、垂直的情况
//true：返回值两个点
bool GetLineBoxInterPt(double slope,double constant, long minx, long miny, long maxx, long maxy, long pRetPoints[4])
{
	bool b1,b2,b3,b4;
	long Yx1 = slope * minx + constant;
	long Yx2 = slope * maxx + constant;
	long Xy1 = (miny-constant)/slope;
	long Xy2 = (maxy-constant)/slope;
	long dt=0;
BEGIN:
	b1 = (Yx1 <= maxy+dt && Yx1 >= miny-dt);
	b2 = (Yx2 <= maxy+dt && Yx2 >= miny-dt);
	b3 = (Xy1 <= maxx+dt && Xy1 >= minx-dt);
	b4 = (Xy2 <= maxx+dt && Xy2 >= minx-dt);
	if(!(b1 || b2 || b3 ||b4))
		return false;
	if(b1)
	{	
		pRetPoints[0] = minx;
		pRetPoints[1] = Yx1;
		if(b2)
		{
			//包括1.2.3.4全为true
			pRetPoints[2] = maxx;
			pRetPoints[3] = Yx2;
		}
		else if(b3)
		{ 
			if(b4 && slope > 0)
			{
				pRetPoints[2] = Xy2;
				pRetPoints[3] = maxy;
			}
			else
			{
				pRetPoints[2] = Xy1;
				pRetPoints[3] = miny;
			}
		}
		else if(b4)
		{
			pRetPoints[2] = Xy2;
			pRetPoints[3] = maxy;
		}
		else
		{
			dt++;
			goto BEGIN;
		}
	}
	else if(b3)
	{
		pRetPoints[0] = Xy1;
		pRetPoints[1] = miny;
		if(b2)
		{
			pRetPoints[2] = maxx;
			pRetPoints[3] = Yx2;
		}
		else if(b4)
		{
			if(slope>0)
			{
				pRetPoints[2] = Xy2;
				pRetPoints[3] = maxy;
			}
			else
			{	
				pRetPoints[0] = Xy2;
				pRetPoints[1] = maxy;
				pRetPoints[2] = Xy1;
				pRetPoints[3] = miny;
			}
		}
		else
		{
			dt++;
			goto BEGIN;
		}
	}
	else if(b4)
	{
		pRetPoints[0] = Xy2;
		pRetPoints[1] = maxy;
		if(b2)
		{
			pRetPoints[2] = maxx;
			pRetPoints[3] = Yx2;
		}
		else
		{
			dt++;
			goto BEGIN;
		}
	}
	else
	{
		dt++;
		goto BEGIN;
	}
	return true;
}

//水平线与面矩形的求交
long GetIntersection_H(long minx, long miny, long maxx, long maxy, long OrgY, long nOffset, long ** ppRetHorizonLine)
{
	_ASSERT(nOffset >0);
	//OrgY = (long)fmod(OrgY-miny,nOffset);
	OrgY = (long)((OrgY-miny)%nOffset);
	if(OrgY <= 0)
		OrgY += nOffset;
	if(miny + OrgY > maxy)
		return -1;

	//直线与BOX有交点
	*ppRetHorizonLine = new long[4*((long)((maxy-miny)/nOffset)+2)];
	long * pDesc = *ppRetHorizonLine;
	long Ret =0;
	long dlt = maxy-miny;
	*pDesc = minx;
	*(pDesc+1) = miny+OrgY;
	*(pDesc+2) = maxx;
	*(pDesc+3) = miny+OrgY;
	Ret ++;
	pDesc += 4;
	//正向走
	while(OrgY+nOffset < dlt)
	{
		OrgY += nOffset;
		*pDesc = minx;
		*(pDesc+1) = miny+OrgY;
		*(pDesc+2) = maxx;
		*(pDesc+3) = miny+OrgY;
		Ret ++;
		pDesc += 4;
	}
	return Ret;
}

//垂直线与面矩形的求交
long GetIntersection_V(long minx, long miny, long maxx, long maxy, long OrgX, long nOffset, long ** ppRetHorizonLine)
{
	_ASSERT(nOffset >0);
//	OrgX = (long)fmod(OrgX-minx,nOffset);
	OrgX = ((OrgX-minx)%nOffset);
	if(OrgX <= 0)
		OrgX += nOffset;
	if(minx + OrgX > maxx)
		return -1;

	//直线与BOX有交点
	*ppRetHorizonLine = new long[4*((long)((maxx-minx)/nOffset)+2)];
	long * pDesc = *ppRetHorizonLine;
	long Ret =0;
	long dlt = maxx - minx;
	*pDesc = minx+OrgX;
	*(pDesc+1) = miny;
	*(pDesc+2) = minx+OrgX;
	*(pDesc+3) = maxy;
	Ret ++;
	pDesc += 4;
	//正向走
	while(OrgX+nOffset < dlt)
	{
		OrgX += nOffset;
		*pDesc = minx+OrgX;
		*(pDesc+1) = miny;
		*(pDesc+2) = minx+OrgX;
		*(pDesc+3) = maxy;
		Ret ++;
		pDesc += 4;
	}
	return Ret;
}

//函数功能：平行线与面矩形的求交，返回一系列平行线
//输入参数：minx, maxx, miny, maxy 为矩形框
//			bAbsolutedPos  
//				T:   OrgX、Y以原点为参照的绝对坐标
//				F：　OrgX、Y以矩形的（minx,miny）点为参照的相对坐标
//			OrgX 、OrgY平行线上的点坐标
//			nOffset线之间偏移量
//	   		dAngle线的斜角(弧度)
//输出参数：ppRetHorizonLine一系列平行线（点对的集合）
//返回值：	ppRetHorizonLine的线段条数
//			如果==-1 , false;(因为nOffset太大)
long Display::CDisOptimize::GetIntersection(long minx, long miny, long maxx, long maxy, bool bAbsolutedPos,long OrgX, long OrgY, double dAngle, long nOffset, long ** ppRetHorizonLine)
{
		if(nOffset < 1)
			nOffset = 1;
		if(!bAbsolutedPos)
		{
			OrgX += minx;
			OrgY += miny;
		}
		double temp = fmod(dAngle,_PI);
		if(fabs(temp) < 0.0001)//水平
			return GetIntersection_H(minx, miny, maxx, maxy, OrgY, nOffset, ppRetHorizonLine);
		else if(fabs(temp-_PI2) < 0.0001 || fabs(temp+_PI2) < 0.0001 )//垂直
			return GetIntersection_V(minx, miny, maxx, maxy, OrgX, nOffset, ppRetHorizonLine);

		double slope, constant, constBase, dist;
		long	pInterPoints[4],dlt,skip;
		slope = tan(dAngle);
		dlt = fabs(nOffset/cos(dAngle));
		constBase = miny - slope * minx;
		constant = fmod((OrgY - slope * OrgX)-constBase,dlt);
		if(constant <= 0)
			constant += dlt;
		constant += constBase;

		if(!GetLineBoxInterPt(slope,constant, minx, miny, maxx, maxy, pInterPoints))
		{
			dist = fabs( slope*OrgX+constant-OrgY)/sqrt( slope*slope+1);  
			skip = dist/nOffset;
			dist = skip*dlt;//借用dist;
			if(!GetLineBoxInterPt(slope,constant+dist, minx, miny, maxx, maxy, pInterPoints))
			{
				dist = (skip+1)*dlt;
				if(!GetLineBoxInterPt(slope,constant+dist, minx, miny, maxx, maxy, pInterPoints))
				{
					dist = -skip*dlt;
					if(!GetLineBoxInterPt(slope,constant+dist, minx, miny, maxx, maxy, pInterPoints))
					{
						dist = -(skip+1)*dlt;
						if(!GetLineBoxInterPt(slope,constant+dist, minx, miny, maxx, maxy, pInterPoints))
							return -1;
					}
				}
			}
			constant += dist;
		}
		//直线与BOX有交点
		dist = sqrt((minx-maxx)*1.0*(minx-maxx)+(miny-maxy)*1.0*(miny-maxy));
		*ppRetHorizonLine = new long[4*((long)(dist/nOffset)+2)];
		long * pDesc = *ppRetHorizonLine;
		long Ret =0;
		//与平行线垂直的线（基准线）
		double slopeT,constantT,dltXT,dltYT,skX,skY;	
		slopeT = tan(dAngle+_PI2);
		if(slope > 0)
			constantT = miny - slopeT*minx;
		else
			constantT = maxy - slopeT*minx;
		double x1 =  (constantT-constant)/(slope-slopeT);
		double y1 =  x1*slope+constant ;
		dAngle = fmod(dAngle,_2PI);
		if(dAngle<0)
			dAngle += _2PI;
		if(dAngle > _PI2 && dAngle < _3PI2)
		{
			dltXT = nOffset*cos(dAngle-_PI2);
			dltYT = nOffset*sin(dAngle-_PI2);
		}
		else
		{
			dltXT = nOffset*cos(dAngle+_PI2);
			dltYT = nOffset*sin(dAngle+_PI2);
		}
		////////////////////////////////////////////////
		memcpy(pDesc,pInterPoints,4*sizeof(long));
		*pDesc = (long)x1;
		*(pDesc+1) = (long)y1;
		Ret ++;
		pDesc += 4;
		//正向走
		skip = dlt;
		skX = dltXT;
		skY = dltYT;
		while(GetLineBoxInterPt(slope,constant+skip, minx, miny, maxx, maxy, pInterPoints))
		{
			memcpy(pDesc,pInterPoints,4*sizeof(long));
			*(pDesc) = (long)(x1+skX);
			*(pDesc+1) = (long)(y1+skY);
			Ret ++;
			pDesc += 4;
			skip += dlt;
			skX += dltXT;
			skY += dltYT;
		}
		//反向走
		skip = -dlt;
		skX = -dltXT;
		skY = -dltYT;
		while(GetLineBoxInterPt(slope,constant+skip, minx, miny, maxx, maxy, pInterPoints))
		{
			memcpy(pDesc,pInterPoints,4*sizeof(long));
			*(pDesc) = (long)(x1+skX);
			*(pDesc+1) = (long)(y1+skY);
			Ret ++;
			pDesc += 4;
			skip -= dlt;
			skX -= dltXT;
			skY -= dltYT;
		}
	return Ret;
}

//函数功能：求点集没有旋转前的外接矩形
//输入参数： 
//			PointCount 点个数
//			pSourPolygon 点集数据
//			dAngle	旋转角度
//输出参数  minxRet，maxxRet，minyRet，maxyRet, 点集的外接矩形值
void Display::CDisOptimize::GetUnRotateRect(long PointCount,const long* pSourPolygon,double dAngle,long& minxRet, long& minyRet,long& maxxRet,long& maxyRet)
{
		double temp = fmod(dAngle,_PI);
		if(fabs(temp) < 0.0001 || fabs(temp - _PI) < 0.0001)
		{
			GetPolygonBox(PointCount,pSourPolygon,minxRet, minyRet,maxxRet,maxyRet);
			return;
		}
		double dltX,dltY,constX,constY;
		double constMinY  = 10E15; 
		double constMinX  = 10E15; 
		double constMaxX = -10E15;
		double constMaxY = -10E15;
		double slopeX = tan(dAngle);
		double slopeY = tan(_PI2+dAngle);
		for(long i=0; i< PointCount; i++)
		{
			constX = pSourPolygon[2*i+1]-pSourPolygon[2*i]*slopeX;
			constY = pSourPolygon[2*i+1]-pSourPolygon[2*i]*slopeY;
			if(constX > constMaxX)
				constMaxX = constX;
			else if(constX < constMinX)
				constMinX = constX;
			if(constY > constMaxY)
				constMaxY = constY;
			else if(constY < constMinY)
				constMinY = constY;
		}
		dltY = (constMaxX-constMinX)*cos(dAngle)/2;
		dltX= (constMaxY-constMinY)*sin(dAngle)/2;
		constX = ((constMaxY+constMinY)-(constMaxX+constMinX))/(2*(slopeX-slopeY));//借用，为centerX
		constY = slopeX*constX+(constMaxX+constMinX)/2;
		minxRet =  constX - dltX;
		maxxRet =  constX + dltX;
		minyRet =  constY - dltY;
		maxyRet =  constY + dltY;
}



//////////////////////////////////////////////////////////////////////////
//2005-5 线文字算法需求

//内部函数
long LeftClipLine(long PointCount,const  long * pSourLine, double nRebulidLength,long ** ppRetPoints)
{
		double dTmp,length= 0 ;
		long ret;
		long * pby = (long *)pSourLine;
		long i=0;
		for(;i< PointCount-1; i++, pby += 2)
		{
			dTmp = sqrt((*(pby+2)-*pby)*1.0*(*(pby+2)-*pby)+(*(pby+3)-*(pby+1))*1.0*(*(pby+3)-*(pby+1)));
			length += dTmp;
			if(length - nRebulidLength > 0)
				break;
		}
		ret = i+2;
		*ppRetPoints = new long[2*ret];
		if(i==PointCount-1)//需要延长线
		{
			ret --;
			length = nRebulidLength-length;
		}
		else
		{	
			length -= nRebulidLength;
		}
		memcpy(*ppRetPoints,pSourLine,(2*ret)*sizeof(long));
		if(length > TOLER)
		{
			if(i==PointCount-1)
			{
				length += dTmp;
				pby -= 2;
				dTmp = length/dTmp;
			}
			else
				dTmp = (dTmp-length)/dTmp;
			*(*ppRetPoints+2*ret-2) = *pby + (*(pby+2) - *pby)*dTmp; 
			*(*ppRetPoints+2*ret-1) = *(pby+1) + (*(pby+3) - *(pby+1))*dTmp;
		}
		return ret;
}

//内部函数
long RightClipLine(long PointCount,const  long * pSourLine, double nRebulidLength,long ** ppRetPoints)
{
	double dTmp,length= 0 ;
	long ret;
	long * pby = (long *)pSourLine;
	pby += 2*PointCount-2;
	long i= 0;
	for(;i< PointCount-1 ; i++, pby -= 2)
	{
		dTmp = sqrt((*pby-*(pby-2))*1.0*(*pby-*(pby-2))+(*(pby+1)-*(pby-1))*1.0*(*(pby+1)-*(pby-1)));
		length += dTmp;
		if(length - nRebulidLength > 0)
			break;
	}
	ret = i + 2;
	*ppRetPoints = new long[2*ret];

	if(i==PointCount-1)//需要延长线
	{
		//		ret--;
		pby += 2;
	}
	dTmp = (dTmp - length + nRebulidLength)/dTmp;
	*(*ppRetPoints) = *pby + (*(pby-2) - *pby)*dTmp; 
	*(*ppRetPoints+1) = *(pby+1) + (*(pby-1) - *(pby+1))*dTmp;
	memcpy(*ppRetPoints+2,pSourLine+2*(PointCount-i-1),(2*ret-2)*sizeof(long));

	return ret;
}


//功能:返回中点 及其它信息
//输入参数: 
//			PointCount 点个数
//			pSourLine 点的数据
//返回值: T是原线上的顶点(点在pIndex段尾)
//			pIndex为第几段(1-n),中点所在的线段号
//			pMidx,pMidy 中点的XY坐标
//			pdtLeft,pdtRight(当返回为F时有效,为中点距本线段两端点的距离)
bool Display::CDisOptimize::GetMidPointInfo(long PointCount,const  long * pSourLine,long * pIndex,double * pMidx, double * pMidy,double * pdtLeft, double * pdtRight)
{
		long i,j,k;
		double dlMid,tmp;
		long ret = -1;
		double * length = new double[PointCount+1];
		length[0] =0;
		long * pby = (long *)pSourLine;
		for(i=1 ;i< PointCount; i++, pby += 2)
			length[i] = length[i-1] + sqrt((*(pby+2)-*pby)*1.0*(*(pby+2)-*pby)+(*(pby+3)-*(pby+1))*1.0*(*(pby+3)-*(pby+1)));

		dlMid = length[PointCount-1]/2;
		//二分
		i = 0;
		j = PointCount-1;
		while(j-i > 1)
		{
			k = (j+i)/2;
			tmp = length[k];
			if(tmp < dlMid)
				i = k;
			else if(tmp > dlMid)
				j = k;
			else
			{
				*pIndex = k;
				*pMidx = *(pSourLine+2*k);
				*pMidy = *(pSourLine+2*k+1);
				*pdtLeft = 0;
				*pdtRight = 0;
				delete []length;
				return true;
			}
		}
		//
		_ASSERT(j - i == 1);
		*pIndex = j;
		pby = (long *)pSourLine;
		pby += 2*i;
		*pdtLeft = dlMid - length[i];
		*pdtRight = length[j] - dlMid;
		length[0] = *pdtLeft/(length[j]-length[i]);//借用
		*pMidx = *pby + (*(pby+2) - *pby)*length[0]; 
		*pMidy = *(pby+1) + (*(pby+3) - *(pby+1))*length[0];

		delete []length;
	return false;
}

//内部函数
void GetMidSplit_LRLine(long PointCount,const  long * pSourLine,long * pNumPointL, long ** ppLineLeft, long * pNumPointR, long ** ppLineRight)
{
	_ASSERT(*ppLineLeft == false && *ppLineRight == false);

	long numPt1,numPt2;
	long Index;
	double dMidx,dMidy,dtLeft,dtRight;
	if(Display::CDisOptimize::GetMidPointInfo(PointCount,pSourLine,&Index,&dMidx,&dMidy,&dtLeft,&dtRight))
	{
		numPt1 = Index+1;
		*ppLineLeft = new long[2*numPt1];
		memcpy(*ppLineLeft,pSourLine,2*(Index+1)*sizeof(long));

		numPt2 = PointCount-Index;
		*ppLineRight = new long[2*numPt2];
		memcpy(*ppLineRight,pSourLine+Index,2*numPt2*sizeof(long));
	}
	else
	{
		numPt1 = Index+1;
		*ppLineLeft = new long[2*numPt1];
		memcpy(*ppLineLeft,pSourLine,2*(numPt1-1)*sizeof(long));
		*(*ppLineLeft+2*(numPt1-1)) = dMidx;
		*(*ppLineLeft+2*numPt1-1) = dMidy;

		numPt2 = PointCount-Index+1;
		*ppLineRight = new long[2*numPt2];
		*(*ppLineRight) = dMidx;
		*(*ppLineRight+1) = dMidy;
		memcpy(*ppLineRight+2,pSourLine+2*(numPt1-1),2*(numPt2-1)*sizeof(long));
	}
	*pNumPointL = numPt1;
	*pNumPointR = numPt2;
	return;	
}

//内部函数
long CentClipLine(long PointCount,const  long * pSourLine, double nRebulidLength,long ** ppRetPoints)
{
	long numPt1,numPt2;
	long * pLineLeft, * pLineRight;	
	pLineLeft = pLineRight = false;
	GetMidSplit_LRLine(PointCount,pSourLine,&numPt1, &pLineLeft,&numPt2, &pLineRight);

	long nRet1,nRet2;
	long * pRetLeft, * pRetRight;
	pRetLeft = pRetRight = false;
	double length = nRebulidLength/2;
	nRet1 = RightClipLine(numPt1,pLineLeft,length,&pRetLeft);
	nRet2 = LeftClipLine(numPt2,pLineRight,length,&pRetRight);
	//合并	
	*ppRetPoints = new long[2*(nRet1+nRet2-1)];
	memcpy(*ppRetPoints,pRetLeft,2*nRet1*sizeof(long));
	memcpy(*ppRetPoints+(2*nRet1),pRetRight+2,2*(nRet2-1)*sizeof(long));

	//memcpy(*ppRetPoints,pLineRight,2*numPt2*sizeof(long));//debug 

	delete []pRetLeft;
	delete []pRetRight;
	delete []pLineLeft;
	delete []pLineRight;

	//return numPt2;//debug 
	return nRet1+nRet2-1;
}

//内部函数
long GetPt_Count_Interval(long numPoint,const  long * pSourLine, long nOY, unsigned char  JointStyle, long nCount,long nLength ,long ** ppRetPoints, double** ppRetAngles)
{
	long retVal;
	long * pSour = (long*)pSourLine;
	double nClipLength = nCount * nLength;
	//处理垂直偏移
	if( nOY == 0 )
	{
		//没有垂直偏移
		retVal = GetMarkerLine(false,numPoint,pSour,1,&nLength,nClipLength,ppRetPoints, ppRetAngles);
	}
	else
	{
		SUBARRAY ptArray;
		//形成链表结构　ptArray
		_Offsetline( numPoint , (INT_POINT*)pSour, ptArray , nOY );
		// 整理内外角关系以及倒角
		_TrimlineCorner( nOY , ptArray , (INT_POINT*)pSour , 
			JointStyle ==LJSRound? GetAngleArc:(JointStyle == LJSMiter? GetAnglefalse:GetAngleCut) );

		if( !FeedLengthInArray(ptArray))
		{
			//ptArray 中没有内容
			delete []pSour;
			*ppRetPoints = false; 
			*ppRetAngles = false;
			return DP_ARRAY_NULL_ERROR;
		}
		retVal = GetMarkerLine_Array(0,nOY,numPoint,pSour,ptArray,1,&nLength,nClipLength,ppRetPoints, ppRetAngles);
	}
	return retVal;
}

//内部函数
long LeftGetPt_Count_Interval(long PointCount,const  long * pSourLine, long nOY, unsigned char  JointStyle, long nCount,long nLength ,long ** ppRetPoints, double** ppRetAngles)
{
	long * pSour = false;
	long numPoint = LeftClipLine(PointCount,pSourLine,nCount*nLength,&pSour);
	long ret = GetPt_Count_Interval(numPoint,pSour,nOY, JointStyle,nCount,nLength ,ppRetPoints, ppRetAngles);
	delete []pSour;
	return ret;
}

long RightGetPt_Count_Interval(long PointCount,const  long * pSourLine, long nOY, unsigned char  JointStyle, long nCount,long nLength ,long ** ppRetPoints, double** ppRetAngles)
{
	long * pSour = false;
	long numPoint = RightClipLine(PointCount,pSourLine,nCount*nLength,&pSour);
	long ret = GetPt_Count_Interval(numPoint,pSour,nOY, JointStyle,nCount,nLength ,ppRetPoints, ppRetAngles);
	delete []pSour;
	return ret;
}

long CentGetPt_Count_Interval(long PointCount,const  long * pSourLine, long nOY, unsigned char  JointStyle, long nCount,long nLength ,long ** ppRetPoints, double** ppRetAngles)
{
	long numPt1,numPt2;
	long * pLineLeft, * pLineRight;
	pLineLeft = pLineRight = false;
	GetMidSplit_LRLine(PointCount,pSourLine,&numPt1, &pLineLeft,&numPt2, &pLineRight);

	long nRet1,nRet2;
	long * pRetLeft, * pRetRight;
	pRetLeft = pRetRight = false;
	double length = ((double)(nCount*nLength))/2.0;
	nRet1 = RightClipLine(numPt1,pLineLeft,length,&pRetLeft);
	nRet2 = LeftClipLine(numPt2,pLineRight,length,&pRetRight);
	delete []pLineLeft;
	delete []pLineRight;
	//合并	
	long * pLine = new long[2*(nRet1+nRet2)];
	memcpy(pLine,pRetLeft,2*nRet1*sizeof(long));

	pLineLeft = pLine+(2*nRet1-2);//借用pLineLeft
	if(labs(*pLineLeft - *pRetRight) < 0.01 &&
		labs(*(pLineLeft+1) - *(pRetRight+1)) < 0.01)//左线的尾点与右线的头点相等
	{
		memcpy(pLine+(2*nRet1),pRetRight+2,2*(nRet2-1)*sizeof(long));
		numPt1 = nRet1 + nRet2 -1;//借用numPt1
	}
	else
	{
		memcpy(pLine+(2*nRet1),pRetRight,2*nRet2*sizeof(long));
		numPt1 = nRet1 + nRet2;//借用numPt1
	}
	delete []pRetLeft;
	delete []pRetRight;
	//借用numPt2
	numPt2 = LeftGetPt_Count_Interval(numPt1,pLine,nOY, JointStyle,nCount,nLength ,ppRetPoints, ppRetAngles);
	delete []pLine;
	return numPt2;
}

//功能: 给定 间隔&&长度，计算个分布点位置和角度
//
//参数：输入参数	PointCount:	原线的点数
//					pSourLine:	原线的点集
//					nOY:		垂直偏移
//					JointStyle:	拐角样式	
//					nCount:		间隔数(返回的点个数为:nCount+1)
//					nLength:	线分割的间隔长度
//					AlignType :	点集在线上的排列方式（左，右，中）
//      输出参数
//					ppRetPoints: 返回的各位置集合
//					ppRetAngles: 返回的各位置处线的角度集合
//返回值：
//			ppRetPoints中点的个数
//说明：
//		如果有偏移，定位以原线为准
//		左排列从线的起点开始沿线分布（考虑延长线）
//		右排列从线的尾点开始沿线分布（考虑延长线）
//		中排列从线的中间往两侧沿线分布（考虑延长线）

long Display::CDisOptimize::GetPtsInLineByCount_Interval(long PointCount,const  long * pSourLine, long nOY, unsigned char  JointStyle, long nCount,long nLength ,unsigned char AlignType, long ** ppRetPoints, double** ppRetAngles)
{
		_ASSERT(pSourLine != false && PointCount > 1 &&  
			*ppRetPoints== false && *ppRetAngles==false);
		_ASSERT(nCount>0 && nLength > 0);
		_ASSERT(JointStyle > 0);
		if(labs(nOY)<3) nOY = 0;

		if(AlignType ==ATLeft)
			return LeftGetPt_Count_Interval(PointCount,pSourLine,nOY, JointStyle,nCount,nLength ,ppRetPoints, ppRetAngles);
		else if(AlignType == ATRight)
			return RightGetPt_Count_Interval(PointCount,pSourLine,nOY, JointStyle,nCount,nLength ,ppRetPoints, ppRetAngles);
		return CentGetPt_Count_Interval(PointCount,pSourLine,nOY, JointStyle,nCount,nLength ,ppRetPoints, ppRetAngles);
}



//功能: 给定间隔数，计算各个分布点位置和角度（在线上平均分散）(扩展)
//参数：输入参数	PointCount:	原线的点数
//					pSourLine:	原线的点集
//					nOY:		垂直偏移
//					JointStyle:	拐角样式	
//					nCount:		间隔数(返回的点个数为:nCount+1)
//					nMinLength:	点间的最小间隔长度
//      输出参数
//					ppRetPoints: 返回的各位置集合
//					ppRetAngles: 返回的各位置处线的角度集合
//返回值：
//			ppRetPoints中点的个数
//说明：
//			如果线的长度不够，根据左排列方式进行延长。
long Display::CDisOptimize::GetPtsInLineByAvgCountEx(long PointCount,const  long * pSourLine, long nOY, unsigned char  JointStyle, long nCount,long nMinLength , long ** ppRetPoints, double** ppRetAngles)
{
		_ASSERT(pSourLine != false && PointCount > 1);
		_ASSERT(*ppRetPoints == false && *ppRetAngles == false);
		_ASSERT(nCount > 0);

		long i;
		double totalL=0, length ;
		long * pby = (long *)pSourLine;
		for(i=0 ;i< PointCount-1; i++, pby += 2)
		{
			totalL += sqrt((*(pby+2)-*pby)*1.0*(*(pby+2)-*pby)+(*(pby+3)-*(pby+1))*1.0*(*(pby+3)-*(pby+1)));
		}
		length = totalL/nCount;
		if(length < nMinLength)//需要延长线
		{
			return Display::CDisOptimize::GetPtsInLineByCount_Interval(PointCount,pSourLine,nOY, JointStyle,nCount,nMinLength,ATLeft,ppRetPoints, ppRetAngles);
		}
		long ltemp = length;
		long ret = Display::CDisOptimize::OffsetLineByMarkLine(PointCount,pSourLine , 0, nOY,JointStyle, 1, &ltemp, ppRetPoints, ppRetAngles);
		if(ret ==1)
		{
			delete [](*ppRetPoints);
			delete [](*ppRetAngles);
			*ppRetPoints = false;
			*ppRetAngles = false;
			return 0;
		}
	return ret;
}

//功能:	线的截取 重组 , 计算截取下来的线数据
//参数：输入参数	PointCount:	原线的点数
//					pSourLine:	原线的点集
//					nRebulidLength:给定长度（可以超过线的长度，超过则加上延长线）
//					AlignType :	点集在线上的排列方式（左，右，中）
//      输出参数
//					ppRetPoints: 返回的各位置集合
//				
//返回值：
//		ppRetPoints中点的个数
long Display::CDisOptimize::ReBuliDIS_LINE(long PointCount,const  long * pSourLine, long nRebulidLength, unsigned char AlignType,long ** ppRetPoints)
{
		_ASSERT(*ppRetPoints == false && pSourLine != false);
		if(PointCount < 2)
			return 0;
		if(AlignType == ATLeft)
			return LeftClipLine(PointCount,pSourLine,nRebulidLength,ppRetPoints);
		else if(AlignType == ATRight)
			return RightClipLine(PointCount,pSourLine,nRebulidLength,ppRetPoints);
	return CentClipLine(PointCount,pSourLine,nRebulidLength,ppRetPoints);
}
