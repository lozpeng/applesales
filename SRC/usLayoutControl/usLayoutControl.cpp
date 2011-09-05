// usLayoutControl.cpp : CusLayoutControlApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "usLayoutControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CusLayoutControlApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x118B851, 0x9465, 0x48C9, { 0xBB, 0x8C, 0x9B, 0x9B, 0xA6, 0x3D, 0x28, 0x45 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CusLayoutControlApp::InitInstance - DLL 初始化

BOOL CusLayoutControlApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CusLayoutControlApp::ExitInstance - DLL 终止

int CusLayoutControlApp::ExitInstance()
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
