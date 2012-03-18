// otPage.h : CotPage ������

#pragma once
#include "resource.h"       // ������

#include "otcCarto.h"
#include "Page.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotPage

class ATL_NO_VTABLE CotPage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotPage, &CLSID_otPage>,
	public IotPage,
	public IOriginData
{
public:
	CotPage();
	~CotPage();
	

DECLARE_REGISTRY_RESOURCEID(IDR_OTPAGE)


BEGIN_COM_MAP(CotPage)
	COM_INTERFACE_ENTRY(IotPage)
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

	STDMETHOD(get_PageEnvelope)(IotEnvelope** pVal);

	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);


private:
	bool CheckPointer();
private:

	Element::CPagePtr *m_ppPage;

	bool m_bAutoDestroy;
};

OBJECT_ENTRY_AUTO(__uuidof(otPage), CotPage)
