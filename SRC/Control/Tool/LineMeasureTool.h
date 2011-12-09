//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  leo
// 时间：  2011.11
// 描述：  线量测工具
//////////////////////////////////////////////////////////////////////
#ifndef _LINEMEASURETool_H
#define _LINEMEASURETool_H

#include "IDrawElementTool.h"
#include "PolylineMeasureElement.h"

namespace Control
{

	class  CLineMeasureTool: public Control::IDrawElementTool
	{
	public:
		CLineMeasureTool();
		~CLineMeasureTool();

		void Initialize(Framework::IUIObject *pTargetControl);

		void LButtonDownEvent (UINT nFlags, CPoint point);
		void MouseMoveEvent (UINT nFlags, CPoint point);
		void LButtonUpEvent (UINT nFlags, CPoint point);
		void LButtonDblClkEvent (UINT nFlags, CPoint point);

	private:
		Element::CPolylineMeasureElementPtr m_pPolyline;
		int m_nLastVertixId;

		HCURSOR m_hHandCursor;
		bool b_CanDelete;
		bool b_InSketch;
		Element::CPolylineMeasureElementPtr m_DelPolyline; 

	};

}


#endif