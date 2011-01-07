//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  leo
// ʱ�䣺  2010.12.20
// ������  ��ͼ�Ŵ󹤾�
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
