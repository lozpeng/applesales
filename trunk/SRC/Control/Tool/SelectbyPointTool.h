//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  leo
// ʱ�䣺  2010.12
// ������  ʸ����ѡ����
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