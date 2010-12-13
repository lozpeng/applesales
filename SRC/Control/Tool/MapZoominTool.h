//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  leo
// ʱ�䣺  2010.12
// ������  ��ͼ�Ŵ󹤾�
//////////////////////////////////////////////////////////////////////
#ifndef _MapZoominTool_H
#define _MapZoominTool_H

#include "ITool.h"
#include "IMapCtrl.h"

namespace Control
{

class  CToolMapZoomin: public Framework::ITool
{
public:
	CToolMapZoomin();
	~CToolMapZoomin();

public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);

private:
	HCURSOR m_hCursor;

    Framework::IMapCtrl *m_pMapCtrl;

};

}


#endif