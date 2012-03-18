#ifndef _Action_Draw_SimpleMarker_Element_h
#define _Action_Draw_SimpleMarker_Element_h

#pragma once
#include "iactiondrawelement.h"
#include "SimpleMarkerElement.h"
class CActionDrawSimpleMarkerElement :
	public IActionDrawElement
{
public:
	CActionDrawSimpleMarkerElement(void);
	~CActionDrawSimpleMarkerElement(void);

public:
	void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);

private:
	Element::CSimpleMarkerElementPtr m_pMarker;
};
#endif