#ifndef CEDIT_VERTIX_HANDLE_H
#define CEDIT_VERTIX_HANDLE_H

#include "ISelectionTracker.h"
#include "SimpleFillSymbol.h"
#include "SimpleMarkerSymbol.h"


namespace Element{

class CARTO_DLL CEditVertixHandle :public ISelectionTracker
{
public:
	CEditVertixHandle();
	~CEditVertixHandle(void);

	void Draw(const Display::IDisplayPtr pDisplay, const GEOMETRY::geom::Geometry* pGeometry);

	void SetOutlineColor(COLORREF color);

	/**
	* 功能描述：击中判断
	* @param double x 给定点的x坐标
	* @param  double y 给定点的y坐标
	* @param bool dbTolerance 容忍距离
	* @return void
	*/
	HIT_HANDLE HitTest( GEOMETRY::geom::Coordinate coord, double dbTolerance=0); 

	GEOMETRY::geom::Geometry* GetHandleEnv(const GEOMETRY::geom::Geometry* pHandle, double dbTolerance = 0);


protected:
	void UpdateGeometry(const GEOMETRY::geom::Geometry* pGeometry);

protected:
	Display::CSimpleMarkerSymbolPtr m_pMarkerSymbol; //绘制handle的简单点符号
};

typedef SYSTEM::CSmartPtr<CEditVertixHandle> CEditVertixHandlePtr;
}
#endif
