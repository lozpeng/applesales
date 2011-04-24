#include "StdAfx.h"
#include "DllResource.h"
#include "editor.h"

extern CEditorApp theApp;

namespace Editor
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