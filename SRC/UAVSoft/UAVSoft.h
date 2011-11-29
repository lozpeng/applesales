// UAVSoft.h : main header file for the UAVSoft application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CUAVSoftApp:
// See UAVSoft.cpp for the implementation of this class
//

class CUAVSoftApp : public CWinApp,
							public CBCGPWorkspace
{
public:
	CUAVSoftApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CUAVSoftApp theApp;