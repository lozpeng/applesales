#include "StdAfx.h"
#include "DllResource.h"
#include "Control.h"

extern CControlApp theApp;

namespace Control
{

CDllResource::CDllResource(void)
{
	m_hOldInst = AfxGetResourceHandle ();
	AfxSetResourceHandle (theApp.m_hInstance);
}

CDllResource::~CDllResource(void)
{
	AfxSetResourceHandle (m_hOldInst);
}

}//namespace Control