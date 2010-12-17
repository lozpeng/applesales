#ifndef _Draw_SimpleMarker_Element_TOOL_h
#define _Draw_SimpleMarker_Element_TOOL_h

#pragma once
#include "IDrawElementTool.h"
#include "SimpleMarkerElement.h"

namespace Control
{
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

}
#endif