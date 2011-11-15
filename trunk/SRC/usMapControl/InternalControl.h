#pragma once
#include "IMapCtrl.h"

class CInternalControl:public Framework::IMapCtrl
{
public:
	CInternalControl(void);
	~CInternalControl(void);
public:
    void CreateAss(std::string Name);

	//创建控件，进行初始化
	bool Create(CWnd *pWnd);
};
