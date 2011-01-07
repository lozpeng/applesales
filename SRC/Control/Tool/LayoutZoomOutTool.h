//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  leo
// ʱ�䣺  2010.12.20
// ������  ��ͼ��С����
//////////////////////////////////////////////////////////////////////

#ifndef _LAYOUT_ZOOMOUT_TOOL_H_
#define _LAYOUT_ZOOMOUT_TOOL_H_

#include "ITool.h"
#include "ILayoutCtrl.h"


class CLayoutZoomoutTool : public Framework::ITool
{
public:
	CLayoutZoomoutTool(void);
	virtual ~CLayoutZoomoutTool(void);

public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);
private:
	Framework::ILayoutCtrl *m_pLayoutCtrl;

	HCURSOR m_hCursor;
};



#endif
