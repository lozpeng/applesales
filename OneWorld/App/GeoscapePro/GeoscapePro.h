// GeoscapePro.h : main header file for the GeoscapePro application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CGeoscapeProApp:
// See GeoscapePro.cpp for the implementation of this class
//

class CGeoscapeProApp : public CWinApp,
							public CBCGPWorkspace
{
public:
	CGeoscapeProApp();

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

extern CGeoscapeProApp theApp;