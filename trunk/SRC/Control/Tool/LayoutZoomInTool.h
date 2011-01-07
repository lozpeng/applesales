//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  leo
// 时间：  2010.12.20
// 描述：  制图放大工具
//////////////////////////////////////////////////////////////////////
#ifndef _LAYOUT_ZOOMIN_TOOL_H_
#define _LAYOUT_ZOOMIN_TOOL_H_


#include "ITool.h"
#include "ILayoutCtrl.h"

class CLayoutZoominTool : public Framework::ITool
{
public:
	CLayoutZoominTool(void);
	virtual ~CLayoutZoominTool(void);

public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);
private:
	Framework::ILayoutCtrl *m_pLayoutCtrl;

	HCURSOR m_hCursor;
};



#endif
