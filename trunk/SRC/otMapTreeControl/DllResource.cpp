#include "StdAfx.h"
#include "DllResource.h"
#include "otMapTreeControl.h"

extern CotMapTreeControlApp theApp;


CDllResource::CDllResource(void)
{
	m_hOldInst = AfxGetResourceHandle ();
	AfxSetResourceHandle (theApp.m_hInstance);
}

CDllResource::~CDllResource(void)
{
	AfxSetResourceHandle (m_hOldInst);
}

