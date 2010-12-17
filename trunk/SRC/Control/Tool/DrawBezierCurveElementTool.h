

#ifndef _DRAW_BezierCurve_ELEMENT_TOOL_H
#define _DRAW_BezierCurve_ELEMENT_TOOL_H
#pragma once
#include "IDrawElementTool.h"
#include "BezierCurveElement.h"

namespace Control
{
	class CDrawBezierCurveElementTool :
		public IDrawElementTool
	{
	public:
		CDrawBezierCurveElementTool(void);
		~CDrawBezierCurveElementTool(void);


	public:
		void Initialize(Framework::IUIObject *pTargetControl);
		void LButtonDownEvent (UINT nFlags, CPoint point);
		void MouseMoveEvent (UINT nFlags, CPoint point);
		void LButtonUpEvent (UINT nFlags, CPoint point);
		void LButtonDblClkEvent (UINT nFlags, CPoint point);


	private:
		Element::CBezierCurveElementPtr m_pBezier;
		int m_nLastVertixId;
	};

}
#endif