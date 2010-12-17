#ifndef _Draw_Ellipse_Element_TOOL_h
#define _Draw_Ellipse_Element_TOOL_h

#include "IDrawElementTool.h"
#include "EllipseElement.h"

namespace Control
{

class  CDrawEllipseElementTool : public IDrawElementTool
{
public:
	CDrawEllipseElementTool();
	~CDrawEllipseElementTool();

public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);


private:
	Element::CEllipseElementPtr m_pEllipse;
};

}


#endif