#ifndef _DISTILL_TOOL_H
#define _DISTILL_TOOL_H

#pragma once

#include "IDrawElementTool.h"
#include "PolygonElement.h"

namespace Control
{

	class CDitillTool: public IDrawElementTool
	{
	public:
		CDitillTool();
		~CDitillTool();

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
}


#endif //_DISTILL_TOOL_H
