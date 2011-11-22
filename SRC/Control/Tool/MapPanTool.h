//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  leo
// 时间：  2010.12
// 描述：  地图漫游工具
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