#pragma once

#include "IAction.h"

class CActionZoomOut : public IAction
{
public:
	CActionZoomOut();
	~CActionZoomOut();

public:
	void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);
	void LButtonDownEvent (UINT nFlags, CPoint point);

};