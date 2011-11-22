//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  leo
// ʱ�䣺  2010.12
// ������  ��ͼ���ι���
//////////////////////////////////////////////////////////////////////
#ifndef _MapPanTool_H
#define _MapPanTool_H

#include "ITool.h"
#include "IMapCtrl.h"

namespace Control
{

class  CToolMapPan: public Framework::ITool
{
public:
	CToolMapPan();
	~CToolMapPan();

public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);

	virtual Framework::ITool* Clone();

private:
	CPoint cPt0,cPt1,cPt2;

	Framework::IMapCtrl *m_pMapCtrl;

	HCURSOR m_hCursor;


};

}


#endif