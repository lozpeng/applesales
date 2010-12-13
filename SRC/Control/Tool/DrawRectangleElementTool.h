//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/11/25
// 描述：  标绘工具——矩形
//////////////////////////////////////////////////////////////////////

#ifndef _Draw_Rectangle_Element_h
#define _Draw_Rectangle_Element_h

#include "IDrawElementTool.h"
#include "RectangleElement.h"

namespace Control
{

	class CDrawRectangleElementTool : public IDrawElementTool
	{
	public:
		CDrawRectangleElementTool();
		~CDrawRectangleElementTool();

	public:
		void Initialize(Framework::IUIObject *pTargetControl);
		void LButtonDownEvent (UINT nFlags, CPoint point);
		void MouseMoveEvent (UINT nFlags, CPoint point);
		void LButtonUpEvent (UINT nFlags, CPoint point);


	private:
		Element::CRectangleElementPtr m_pRectangle;
	};

}


#endif