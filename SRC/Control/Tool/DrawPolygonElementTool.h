#ifndef _ACTION_DRAW_POLYGON_ELEMENT_h
#define _ACTION_DRAW_POLYGON_ELEMENT_h

#include "IDrawElementTool.h"
#include "PolygonElement.h"


class  CDrawPolygonElementTool : public IDrawElementTool
{
public:
	CDrawPolygonElementTool();
	~CDrawPolygonElementTool();

public:
	void Initialize(Framework::IUIObject *pTargetControl);

	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);
	void LButtonDblClkEvent (UINT nFlags, CPoint point);


private:
	Element::CPolygonElementPtr m_pPolygon;
	int m_nLastVertixId;
};




#endif