//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/11/25
// ������  ��湤�ߡ�������
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