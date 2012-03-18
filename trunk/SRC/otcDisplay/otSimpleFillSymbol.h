// otSimpleFillSymbol.h : CotSimpleFillSymbol ������

#pragma once
#include "resource.h"       // ������

#include "otcDisplay.h"
#include "SimpleFillSymbol.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotSimpleFillSymbol

class ATL_NO_VTABLE CotSimpleFillSymbol :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotSimpleFillSymbol, &CLSID_otSimpleFillSymbol>,
	public IotSimpleFillSymbol,
	public IOriginData
{
public:
	CotSimpleFillSymbol();
	~CotSimpleFillSymbol();
	

	DECLARE_REGISTRY_RESOURCEID(IDR_OTSIMPLEFILLSYMBOL)


	BEGIN_COM_MAP(CotSimpleFillSymbol)
		COM_INTERFACE_ENTRY(IotSimpleFillSymbol)
		COM_INTERFACE_ENTRY(IOriginData)
		COM_INTERFACE_ENTRY(IotFillSymbol)
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


	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);

	// IotFillSymbol Methods
public:
	STDMETHOD(get_DrawOutLine)( VARIANT_BOOL * pVal);

	STDMETHOD(put_DrawOutLine)( VARIANT_BOOL newVal);
	
	STDMETHOD(get_OutLine)( IotSymbol * * pVal);
	
	STDMETHOD(put_OutLine)( IotSymbol * newVal);
	
	STDMETHOD(get_FillColor)( IotColor * * pVal);
	
	STDMETHOD(put_FillColor)( IotColor * newVal);
	

	// IotSymbol Methods
public:
	STDMETHOD(get_Type)( otSymbolType * pVal);

	STDMETHOD(get_Unit)( otSymbolUnit * pVal);

	STDMETHOD(put_Unit)( otSymbolUnit newVal);

private:
	bool CheckPointer();
private:
	Display::ISymbolPtr *m_ppSymbol;
	Display::CSimpleFillSymbol *m_pFillSymbol;

	bool m_bAutoDestroy;

};

OBJECT_ENTRY_AUTO(__uuidof(otSimpleFillSymbol), CotSimpleFillSymbol)
