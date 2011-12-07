//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  leo
// ʱ�䣺  2010.12
// ������  ��ͼ��С����
//////////////////////////////////////////////////////////////////////
#ifndef _MapZoomoutTool_H
#define _MapZoomoutTool_H

#include "ITool.h"
#include "IMapCtrl.h"

namespace Control
{

class  CToolMapZoomout: public Framework::ITool
{
public:
	CToolMapZoomout();
	~CToolMapZoomout();

public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);

	virtual Framework::ITool* Clone();

private:
	HCURSOR m_hCursor;

	Framework::IMapCtrl *m_pMapCtrl;

};

}


#endif