// otSymbolLibLoader.h : CotSymbolLibLoader ������

#pragma once
#include "resource.h"       // ������

#include "otcDisplay.h"
#include "SymbolLibAccess.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotSymbolLibLoader

class ATL_NO_VTABLE CotSymbolLibLoader :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotSymbolLibLoader, &CLSID_otSymbolLibLoader>,
	public IotSymbolLibLoader
{
public:
	CotSymbolLibLoader();
	~CotSymbolLibLoader();


DECLARE_REGISTRY_RESOURCEID(IDR_OTSYMBOLLIBLOADER)


BEGIN_COM_MAP(CotSymbolLibLoader)
	COM_INTERFACE_ENTRY(IotSymbolLibLoader)
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

	STDMETHOD(Open)(BSTR libName, VARIANT_BOOL* ret);
	STDMETHOD(GetSymbol)(BSTR name,IotSymbol** retSymbol);

private:
	otComUI::CSymbolLibAccess *m_lib;

};

OBJECT_ENTRY_AUTO(__uuidof(otSymbolLibLoader), CotSymbolLibLoader)
