//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  leo
// ʱ�䣺  2011.11
// ������  �����⹤��
//////////////////////////////////////////////////////////////////////
#ifndef _LINEMEASURETool_H
#define _LINEMEASURETool_H

#include "IDrawElementTool.h"
#include "PolygonMeasureElement.h"

namespace Control
{

	class  CAreaMeasureTool: public Control::IDrawElementTool
	{
	public:
		CAreaMeasureTool();
		~CAreaMeasureTool();

		void Initialize(Framework::IUIObject *pTargetControl);

		void LButtonDownEvent (UINT nFlags, CPoint point);
		void MouseMoveEvent (UINT nFlags, CPoint point);
		void LButtonUpEvent (UINT nFlags, CPoint point);
		void LButtonDblClkEvent (UINT nFlags, CPoint point);

	private:
		Element::CPolygonMeasureElementPtr m_pPolygon;
		int m_nLastVertixId;

		HCURSOR m_hHandCursor;
		bool b_CanDelete;
		bool b_InSketch;
		Element::CPolygonMeasureElementPtr m_DelPolygon; 
	};

}


#endif