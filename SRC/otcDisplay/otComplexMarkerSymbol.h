// otComplexMarkerSymbol.h : CotComplexMarkerSymbol ������

#pragma once
#include "resource.h"       // ������

#include "otcDisplay.h"
#include "ComplexMarkerSymbol.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotComplexMarkerSymbol

class ATL_NO_VTABLE CotComplexMarkerSymbol :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotComplexMarkerSymbol, &CLSID_otComplexMarkerSymbol>,
	public IotComplexMarkerSymbol,
	public IOriginData
{
public:
	CotComplexMarkerSymbol();
	~CotComplexMarkerSymbol();


DECLARE_REGISTRY_RESOURCEID(IDR_OTCOMPLEXMARKERSYMBOL)


BEGIN_COM_MAP(CotComplexMarkerSymbol)
	COM_INTERFACE_ENTRY(IotComplexMarkerSymbol)
	COM_INTERFACE_ENTRY(IOriginData)
	COM_INTERFACE_ENTRY(IotMarkerSymbol)
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


	// IotMarkerSymbol Methods
public:
	STDMETHOD(get_Color)( IotColor * * pVal);

	STDMETHOD(put_Color)( IotColor * newVal);

	STDMETHOD(get_OffsetX)( DOUBLE * pVal);

	STDMETHOD(put_OffsetX)( DOUBLE newVal);

	STDMETHOD(get_OffsetY)( DOUBLE * pVal);

	STDMETHOD(put_OffsetY)( DOUBLE newVal);

	STDMETHOD(get_Angle)( DOUBLE * pVal);

	STDMETHOD(put_Angle)( DOUBLE newVal);

	STDMETHOD(get_Size)( DOUBLE * pVal);

	STDMETHOD(put_Size)( DOUBLE newVal);


	// IotSymbol Methods
public:
	STDMETHOD(get_Type)( otSymbolType * pVal);

	STDMETHOD(get_Unit)( otSymbolUnit * pVal);

	STDMETHOD(put_Unit)( otSymbolUnit newVal);

private:
	bool CheckPointer();
private:
	Display::ISymbolPtr *m_ppSymbol;
	Display::CComplexMarkerSymbol *m_pMarkerSymbol;

	bool m_bAutoDestroy;

};

OBJECT_ENTRY_AUTO(__uuidof(otComplexMarkerSymbol), CotComplexMarkerSymbol)
