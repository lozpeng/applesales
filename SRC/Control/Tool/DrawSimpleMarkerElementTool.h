#ifndef _Action_Draw_SimpleMarker_Element_h
#define _Action_Draw_SimpleMarker_Element_h

#pragma once
#include "IDrawElementTool.h"
#include "SimpleMarkerElement.h"
class CDrawSimpleMarkerElementTool :
	public IDrawElementTool
{
public:
	CDrawSimpleMarkerElementTool(void);
	~CDrawSimpleMarkerElementTool(void);

public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);

private:
	Element::CSimpleMarkerElementPtr m_pMarker;
};
#endif