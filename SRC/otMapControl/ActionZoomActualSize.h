
#ifndef _ActionZoomActualSize_h
#define _ActionZoomActualSize_h

#pragma once
#include "iaction.h"

class CActionZoomActualSize :
	public IAction
{
public:
	CActionZoomActualSize(void);
	~CActionZoomActualSize(void);

	
public:
	void Triger();
	void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);
};

#endif