// otMapControl.cpp : CotMapControlApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "otMapControl.h"
#include "CursorMgr.h"
#include "IAction.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CotMapControlApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x83832279, 0x48EB, 0x4E01, { 0xA8, 0x42, 0x7A, 0x17, 0xDA, 0xBE, 0x20, 0xA5 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

extern CCursorMgr *g_pCursorMgr;

// CotMapControlApp::InitInstance - DLL 初始化

BOOL CotMapControlApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		g_pCursorMgr =new CCursorMgr(theApp.m_hInstance);
		CoInitialize(0);
		IAction::RegisterAll();
	}

	return bInit;
}



// CotMapControlApp::ExitInstance - DLL 终止

int CotMapControlApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。

	CoUninitialize();
	IAction::UnRegisterAll();
	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
