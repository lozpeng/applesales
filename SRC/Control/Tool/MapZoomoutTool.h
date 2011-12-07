//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  leo
// 时间：  2010.12
// 描述：  地图缩小工具
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