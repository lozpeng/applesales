#pragma once

#include "IAction.h"

class CActionZoomin : public IAction
{
public:
	CActionZoomin();
	~CActionZoomin();

public:
	void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);
	void LButtonDownEvent (UINT nFlags, CPoint point);

};