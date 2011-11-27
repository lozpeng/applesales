#include "stdafx.h"
#include "DllResource.h"
#include "Controls.h"

extern CControlsApp theApp;

namespace Control
{

CDllResource::CDllResource(void)
{
	m_hOldInst = AfxGetResourceHandle ();
	AfxSetResourceHandle(theApp.m_hInstance);
}

CDllResource::~CDllResource(void)
{
	AfxSetResourceHandle (m_hOldInst);
}

}//namespace Control