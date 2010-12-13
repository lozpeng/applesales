//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  leo
// 时间：  2010.12
// 描述：  地图放大工具
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