
//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  leo
// 时间：  2010.12.20
// 描述：  制图漫游工具
//////////////////////////////////////////////////////////////////////

#ifndef _LayoutPanTool_h
#define _LayoutPanTool_h

#include "ITool.h"
#include "ILayoutCtrl.h"

class  CLayoutPanTool : public Framework::ITool
{
public:
	CLayoutPanTool();
	~CLayoutPanTool();

public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);

private:
	CPoint cPt0,cPt1,cPt2;
	Framework::ILayoutCtrl *m_pLayoutCtrl;
	
	HCURSOR m_hCursor;

};




#endif