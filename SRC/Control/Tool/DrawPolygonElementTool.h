#ifndef _DRAW_POLYGON_ELEMENT_TOOL_h
#define _DRAW_POLYGON_ELEMENT_TOOL_h

#include "IDrawElementTool.h"
#include "PolygonElement.h"

namespace Control
{
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


}

#endif