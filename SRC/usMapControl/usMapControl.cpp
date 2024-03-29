// usMapControl.cpp : CusMapControlApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "usMapControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CusMapControlApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xE2C24107, 0x110E, 0x4076, { 0x9B, 0x0, 0x85, 0x9C, 0x57, 0x64, 0x63, 0xB4 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CusMapControlApp::InitInstance - DLL 初始化

BOOL CusMapControlApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CusMapControlApp::ExitInstance - DLL 终止

int CusMapControlApp::ExitInstance()
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
