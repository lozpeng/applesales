// otMarkerLineSymbol.h : CotMarkerLineSymbol ������

#pragma once
#include "resource.h"       // ������

#include "otcDisplay.h"
#include "MarkerLineSymbol.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotMarkerLineSymbol

class ATL_NO_VTABLE CotMarkerLineSymbol :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotMarkerLineSymbol, &CLSID_otMarkerLineSymbol>,
	public IotMarkerLineSymbol,
	public IOriginData
{
public:
	CotMarkerLineSymbol();
	~CotMarkerLineSymbol();


DECLARE_REGISTRY_RESOURCEID(IDR_OTMARKERLINESYMBOL)


BEGIN_COM_MAP(CotMarkerLineSymbol)
	COM_INTERFACE_ENTRY(IotMarkerLineSymbol)
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

public:
	STDMETHOD(get_MarkerSymbol)(IotMarkerSymbol** pVal);
	STDMETHOD(put_MarkerSymbol)(IotMarkerSymbol* newVal);

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
	Display::CMarkerLineSymbol *m_pLineSymbol;

	bool m_bAutoDestroy;



};

OBJECT_ENTRY_AUTO(__uuidof(otMarkerLineSymbol), CotMarkerLineSymbol)
