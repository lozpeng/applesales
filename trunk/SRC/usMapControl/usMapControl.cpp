// usMapControl.cpp : CusMapControlApp �� DLL ע���ʵ�֡�

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



// CusMapControlApp::InitInstance - DLL ��ʼ��

BOOL CusMapControlApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CusMapControlApp::ExitInstance - DLL ��ֹ

int CusMapControlApp::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
