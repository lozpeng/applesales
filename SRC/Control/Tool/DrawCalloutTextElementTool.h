#ifndef _DRAW_CALLOUT_TEXT_ELEMENT_TOOL_H
#define _DRAW_CALLOUT_TEXT_ELEMENT_TOOL_H

#include "IDrawElementTool.h"
#include "CalloutTextElement.h"

namespace Control
{

class  CDrawCalloutTextElementTool : public IDrawElementTool
{
public:
	CDrawCalloutTextElementTool();
	~CDrawCalloutTextElementTool();

public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);

protected:
	void UpdateStartPoint(CPoint pt);
	void UpdateEndPoint(CPoint pt);

private:
	Element::CCalloutTextElementPtr m_pText;
	BOOL m_bLBtnDown;
	GEOMETRY::geom::Coordinate m_startCoord, m_endCoord;
};

}


#endif