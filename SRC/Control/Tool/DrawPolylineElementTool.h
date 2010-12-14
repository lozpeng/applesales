#ifndef _ACTION_DRAW_POLYLINE_ELEMENT_H
#define _ACTION_DRAW_POLYLINE_ELEMENT_H

#include "IDrawElementTool.h"
#include "PolylineElement.h"


class CDrawPolylineElementTool : public IDrawElementTool
{
public:
	CDrawPolylineElementTool();
	~CDrawPolylineElementTool();

public:
	void Initialize(Framework::IUIObject *pTargetControl);

	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);
	void LButtonDblClkEvent (UINT nFlags, CPoint point);


private:
	Element::CPolylineElementPtr m_pPolyline;
	int m_nLastVertixId;
};



#endif