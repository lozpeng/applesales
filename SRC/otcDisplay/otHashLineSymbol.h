// otHashLineSymbol.h : CotHashLineSymbol ������

#pragma once
#include "resource.h"       // ������

#include "otcDisplay.h"
#include "HashLineSymbol.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotHashLineSymbol

class ATL_NO_VTABLE CotHashLineSymbol :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotHashLineSymbol, &CLSID_otHashLineSymbol>,
	public IotHashLineSymbol,
	public IOriginData
{
public:
	CotHashLineSymbol();
	~CotHashLineSymbol();


DECLARE_REGISTRY_RESOURCEID(IDR_OTHASHLINESYMBOL)


BEGIN_COM_MAP(CotHashLineSymbol)
	COM_INTERFACE_ENTRY(IotHashLineSymbol)
	COM_INTERFACE_ENTRY(IOriginData)
	COM_INTERFACE_ENTRY(IotLineSymbol)
	COM_INTERFACE_ENTRY(IotSymbol)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);

	// IotLineSymbol Methods
public:
	STDMETHOD(get_LineWidth)( DOUBLE * pVal);

	STDMETHOD(put_LineWidth)( DOUBLE newVal);

	STDMETHOD(get_Color)( IotColor * * pVal);

	STDMETHOD(put_Color)( IotColor * newVal);


	// IotSymbol Methods
public:
	STDMETHOD(get_Type)( otSymbolType * pVal);

	STDMETHOD(get_Unit)( otSymbolUnit * pVal);

	STDMETHOD(put_Unit)( otSymbolUnit newVal);
private:
	bool CheckPointer();
private:
	Display::ISymbolPtr *m_ppSymbol;
	Display::CHashLineSymbol *m_pLineSymbol;

	bool m_bAutoDestroy;

};

OBJECT_ENTRY_AUTO(__uuidof(otHashLineSymbol), CotHashLineSymbol)