// Editor.h : Editor DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEditorApp
// �йش���ʵ�ֵ���Ϣ������� Editor.cpp
//

class CEditorApp : public CWinApp
{
public:
	CEditorApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
