//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/4/14
// 描述：  标绘对象选择
//////////////////////////////////////////////////////////////////////


#ifndef ISELECTION_TRACKER_H
#define ISELECTION_TRACKER_H

#include "SimpleFillSymbol.h"
#include "ElementDefine.h"
#include "SimpleMarkerSymbol.h"

namespace Element{
class CARTO_DLL ISelectionTracker
{
public:
	ISelectionTracker();
	virtual~ISelectionTracker(void);

	virtual void Draw(Display::IDisplayPtr pDisplay);
	
	//virtual GEOMETRY::geom::Geometry*	GetGeometry();

	virtual void SetGeometry(const GEOMETRY::geom::Geometry& geometry);

	virtual GEOMETRY::geom::Envelope GetEnvelope();

	virtual HIT_HANDLE HitTest( GEOMETRY::geom::Coordinate coord, double dbTolerance=0); 

	virtual void MoveHandleTo(HIT_HANDLE nHandle,GEOMETRY::geom::Coordinate coord);

	HANDLE_TYPE GetHandleType(){return m_handleType;};

protected:
	HANDLE_TYPE m_handleType; 
	GEOMETRY::geom::Geometry* m_pGeometry;
	GEOMETRY::geom::Geometry* m_pHandlePoints;
	Display::CSimpleFillSymbolPtr m_pFillSymbol;
	Display::CSimpleMarkerSymbolPtr m_pMarkerSymbol; 
};

typedef SYSTEM::CSmartPtr<ISelectionTracker> ISelectionTrackerPtr;

}

#endif;
