// otMapTreeControl.cpp : CotMapTreeControlApp �� DLL ע���ʵ�֡�

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



// CotMapTreeControlApp::InitInstance - DLL ��ʼ��

BOOL CotMapTreeControlApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CotMapTreeControlApp::ExitInstance - DLL ��ֹ

int CotMapTreeControlApp::ExitInstance()
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
