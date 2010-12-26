//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  leo
// 时间：  2010.12
// 描述：  矢量点选工具
//////////////////////////////////////////////////////////////////////
#ifndef _SelectbyPointTool_H
#define _SelectbyPointTool_H

#include "ISelectFeatureTool.h"

namespace Control
{

class  CSelectbyPointTool: public ISelectFeatureTool
{
public:
	CSelectbyPointTool();
	~CSelectbyPointTool();

public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);

private:
	void Select(Geodatabase::CSimpleQuery *pQuery);

	

};

}


#endif