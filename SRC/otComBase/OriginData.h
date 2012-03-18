// OriginData.h : COriginData ������

#pragma once
#include "resource.h"       // ������

#include "otComBase.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// COriginData

class ATL_NO_VTABLE COriginData :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<COriginData, &CLSID_OriginData>,
	public IOriginData
{
public:
	COriginData()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ORIGINDATA)


BEGIN_COM_MAP(COriginData)
	COM_INTERFACE_ENTRY(IOriginData)
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

	STDMETHOD(get_OriginData)(LONG* pVal);
	STDMETHOD(put_OriginData)(LONG newVal);
	STDMETHOD(get_AutoDestroy)(BOOL* pVal);
	STDMETHOD(put_AutoDestroy)(BOOL newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(OriginData), COriginData)
