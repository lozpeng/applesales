#pragma once
#include "IMapCtrl.h"

class CInternalControl:public Framework::IMapCtrl
{
public:
	CInternalControl(void);
	~CInternalControl(void);
public:
    void CreateAss(std::string Name);

	//�����ؼ������г�ʼ��
	bool Create(CWnd *pWnd);
};
