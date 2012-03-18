// otMapTreeControl.cpp : CotMapTreeControlApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "otMapTreeControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CotMapTreeControlApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xB9D879EE, 0xBBA9, 0x4150, { 0x9A, 0xB9, 0xBF, 0x62, 0xA, 0x2B, 0x9, 0xC8 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CotMapTreeControlApp::InitInstance - DLL 初始化

BOOL CotMapTreeControlApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CotMapTreeControlApp::ExitInstance - DLL 终止

int CotMapTreeControlApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。

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
