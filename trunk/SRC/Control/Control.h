// Control.h : Control DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "TreePropSheetEx.h"
#include <vector>

// CControlApp
// 有关此类实现的信息，请参阅 Control.cpp
//

class CControlApp : public CWinApp
{
public:
	CControlApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
public:
	std::vector<TreePropSheet::CTreePropSheetEx*> m_manageSheet;
	std::vector<CResizablePage*>  m_manageSheetPage;
};
extern CControlApp theApp;