#ifndef _DRAW_SIMPLE_TEXT_ELEMENT_TOOL_H
#define _DRAW_SIMPLE_TEXT_ELEMENT_TOOL_H

#include "IDrawElementTool.h"
#include "SimpleTextElement.h"

namespace Control
{
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


}

#endif