#ifndef _MapPanTool_H
#define _MapPanTool_H

#include "ITool.h"
#include "IMapCtrl.h"

namespace Control
{

class CONTROL_DLL CToolMapPan: public Framework::ITool
{
public:
	CToolMapPan();
	~CToolMapPan();

public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);

private:
	CPoint cPt0,cPt1,cPt2;

	Framework::IMapCtrl *m_pMapCtrl;

	HCURSOR m_hCursor;


};

}


#endif