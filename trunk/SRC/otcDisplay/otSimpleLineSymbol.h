// otSimpleLineSymbol.h : CotSimpleLineSymbol ������

#pragma once
#include "resource.h"       // ������

#include "otcDisplay.h"
#include "SimpleLineSymbol.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotSimpleLineSymbol

class ATL_NO_VTABLE CotSimpleLineSymbol :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotSimpleLineSymbol, &CLSID_otSimpleLineSymbol>,
	public IotSimpleLineSymbol,
	public IOriginData
{
public:
	CotSimpleLineSymbol();
	~CotSimpleLineSymbol();


	DECLARE_REGISTRY_RESOURCEID(IDR_OTSIMPLELINESYMBOL)


	BEGIN_COM_MAP(CotSimpleLineSymbol)
		COM_INTERFACE_ENTRY(IotSimpleLineSymbol)
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

	STDMETHOD(get_LineStyle)(otSimpleLineStyle* pVal);
	STDMETHOD(put_LineStyle)(otSimpleLineStyle newVal);

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
	Display::CSimpleLineSymbol *m_pLineSymbol;

	bool m_bAutoDestroy;


};

OBJECT_ENTRY_AUTO(__uuidof(otSimpleLineSymbol), CotSimpleLineSymbol)