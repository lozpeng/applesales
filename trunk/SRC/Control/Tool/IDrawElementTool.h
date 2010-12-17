//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/11/25
// 描述：  标绘工具的基类-从工具基类派生
//////////////////////////////////////////////////////////////////////

#ifndef _Draw_Element_TOOL_h
#define _Draw_Element_TOOL_h

#include "ITool.h"
#include "IMapCtrl.h"

namespace Control
{
	class IDrawElementTool :public Framework::ITool
	{
	public:
		IDrawElementTool(const char* name);
		~IDrawElementTool(void);

	public:
		virtual void Initialize(Framework::IUIObject *pTargetControl);

		virtual void LButtonDownEvent (UINT nFlags, CPoint point);
		virtual void MouseMoveEvent (UINT nFlags, CPoint point);
		virtual void LButtonUpEvent (UINT nFlags, CPoint point);
		virtual void LButtonDblClkEvent (UINT nFlags, CPoint point);

	protected:
		CPoint cPtStart,cPtEnd;

		Framework::IMapCtrl *m_pMapCtrl;
		Carto::CMapPtr m_pMap;

		HCURSOR m_hCursor;
	};

}
#endif
