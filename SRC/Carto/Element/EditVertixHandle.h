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
	* ���������������ж�
	* @param double x �������x����
	* @param  double y �������y����
	* @param bool dbTolerance ���̾���
	* @return void
	*/
	HIT_HANDLE HitTest( GEOMETRY::geom::Coordinate coord, double dbTolerance=0); 

	GEOMETRY::geom::Geometry* GetHandleEnv(const GEOMETRY::geom::Geometry* pHandle, double dbTolerance = 0);


protected:
	void UpdateGeometry(const GEOMETRY::geom::Geometry* pGeometry);

protected:
	Display::CSimpleMarkerSymbolPtr m_pMarkerSymbol; //����handle�ļ򵥵����
};

typedef SYSTEM::CSmartPtr<CEditVertixHandle> CEditVertixHandlePtr;
}
#endif
