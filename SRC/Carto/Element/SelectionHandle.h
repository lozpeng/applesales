//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/12
// 描述：  标绘要素选择 
//////////////////////////////////////////////////////////////////////

#ifndef CSELECTION_HANDLE_H
#define CSELECTION_HANDLE_H

#include "ISelectionTracker.h"
#include "SimpleFillSymbol.h"
#include "SimpleMarkerSymbol.h"


namespace Element{

class CARTO_DLL CSelectionHandle :public ISelectionTracker
{
public:
	CSelectionHandle(const GEOMETRY::geom::Envelope& envlope, HANDLE_TYPE handleType = HT_NONE);
	~CSelectionHandle(void);

	SYSTEM::CSmartPtr<CSelectionHandle> Clone();

	void Draw(const Display::IDisplayPtr pDisplay);

	void DrawBorderLine(const Display::IDisplayPtr pDisplay);

	void DrawHandlePoint(const Display::IDisplayPtr pDisplay);

	void SetOutlineColor(COLORREF color);

	/**
	* 功能描述：击中判断
	* @param double x 给定点的x坐标
	* @param  double y 给定点的y坐标
	* @param bool dbTolerance 容忍距离
	* @return void
	*/
	HIT_HANDLE HitTest( GEOMETRY::geom::Coordinate coord, double dbTolerance=0); 

	/**
	* 功能描述：移动Handle
	* @param HIT_HANDLE nHandle 移动的handle
	* @param GEOMETRY::geom::Coordinate coord handle将被移动到的位置
	* @return void
	*/
	void MoveHandleTo(HIT_HANDLE nHandle,GEOMETRY::geom::Coordinate coord);

	void SetEnvelope(const GEOMETRY::geom::Envelope& envlope);

	GEOMETRY::geom::Envelope GetEnvelope(){return m_envelope;};

	HANDLE_TYPE GetHandleType(){return m_handleType;};


protected:


protected:
	HANDLE_TYPE m_handleType; //
	Display::CSimpleMarkerSymbolPtr m_pMarkerSymbol; //绘制handle的简单点符号
	GEOMETRY::geom::MultiPoint* m_pHandlePoints;    //handle
	GEOMETRY::geom::Envelope m_envelope;
	COLORREF m_color;

};

typedef SYSTEM::CSmartPtr<CSelectionHandle> CSelectionHandlePtr;
}
#endif
