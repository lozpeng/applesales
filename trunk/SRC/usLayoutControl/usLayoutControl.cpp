// usLayoutControl.cpp : CusLayoutControlApp �� DLL ע���ʵ�֡�

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



// CusLayoutControlApp::InitInstance - DLL ��ʼ��

BOOL CusLayoutControlApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CusLayoutControlApp::ExitInstance - DLL ��ֹ

int CusLayoutControlApp::ExitInstance()
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
