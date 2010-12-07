// TDApp.h : main header file for the TDApp application
//
#pragma once
#define TD_APPLICATION "TD_APPLICATION"
#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CTDAppApp:
// See TDApp.cpp for the implementation of this class
//

class CTDAppApp : public CWinApp,
							public CBCGPWorkspace
{
public:
	CTDAppApp();

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

extern CTDAppApp theApp;