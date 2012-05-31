#ifndef _ActionMapPan_h
#define _ActionMapPan_h

#include "ITool.h"
#include "ILayoutCtrl.h"
namespace Control
{

class  CLayoutMapPan : public Framework::ITool
{
public:
	CLayoutMapPan();
	~CLayoutMapPan();

public:
	
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);

private:
	CPoint cPt0,cPt1,cPt2;

	Framework::ILayoutCtrl *m_pLayoutCtrl;
	
	HCURSOR m_hCursor;
	HDC m_mapBackHDC;
	HBITMAP m_hBitmap, m_hOldBitmap;
	long m_lDCWidth, m_lDCHeight;
};

}


#endif