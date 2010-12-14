#ifndef _ACTION_DRAW_SIMPLE_TEXT_ELEMENT_H
#define _ACTION_DRAW_SIMPLE_TEXT_ELEMENT_H

#include "IDrawElementTool.h"
#include "SimpleTextElement.h"


class  CDrawSimpleTextElementTool : public IDrawElementTool
{
public:
	CDrawSimpleTextElementTool();
	~CDrawSimpleTextElementTool();

public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);

private:
	Element::CSimpleTextElementPtr m_pText;
};




#endif