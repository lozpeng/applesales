// TmsWF.h : CTmsWF ������

#pragma once
#include "resource.h"       // ������

#include "otcGeodataModel.h"
//#include "TmsWorkspaceFactory.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CTmsWF

class ATL_NO_VTABLE CTmsWF :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTmsWF, &CLSID_TmsWF>,
	public ITmsWF
{
public:
	CTmsWF();


	DECLARE_REGISTRY_RESOURCEID(IDR_TMSWF)


	BEGIN_COM_MAP(CTmsWF)
		COM_INTERFACE_ENTRY(ITmsWF)
		COM_INTERFACE_ENTRY(IotWorkspaceFactory)

	END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	//CTmsWorkspaceFactory *m_pFactory;


	// IotWorkspaceFactory Methods
public:
	STDMETHOD(OpenFromFile)( BSTR filename,  IotWorkspace **workspace);

	STDMETHOD(OpenFolder)(BSTR name, IotWorkspace** retWorkspace);
};

OBJECT_ENTRY_AUTO(__uuidof(TmsWF), CTmsWF)
