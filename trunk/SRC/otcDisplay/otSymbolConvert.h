// otSymbolConvert.h : CotSymbolConvert ������

#pragma once
#include "resource.h"       // ������

#include "otcDisplay.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotSymbolConvert

class ATL_NO_VTABLE CotSymbolConvert :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotSymbolConvert, &CLSID_otSymbolConvert>,
	public IotSymbolConvert
{
public:
	CotSymbolConvert()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_OTSYMBOLCONVERT)


BEGIN_COM_MAP(CotSymbolConvert)
	COM_INTERFACE_ENTRY(IotSymbolConvert)
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

	STDMETHOD(ConvertSymbol)(LONG ldata, VARIANT_BOOL bown, IotSymbol** retSymbol);
};

OBJECT_ENTRY_AUTO(__uuidof(otSymbolConvert), CotSymbolConvert)
