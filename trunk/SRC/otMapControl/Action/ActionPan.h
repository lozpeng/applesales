#pragma once

#include "IAction.h"

class CActionPan : public IAction
{
public:
	CActionPan();
	~CActionPan();

public:
	void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);

private:
	CPoint cPt0,cPt1,cPt2;
};