// otComplexLineSymbol.h : CotComplexLineSymbol 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcDisplay.h"
#include "ComplexLineSymbol.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotComplexLineSymbol

class ATL_NO_VTABLE CotComplexLineSymbol :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotComplexLineSymbol, &CLSID_otComplexLineSymbol>,
	public IotComplexLineSymbol,
	public IOriginData
{
public:
	CotComplexLineSymbol();
	~CotComplexLineSymbol();
	

DECLARE_REGISTRY_RESOURCEID(IDR_OTCOMPLEXLINESYMBOL)


BEGIN_COM_MAP(CotComplexLineSymbol)
	COM_INTERFACE_ENTRY(IotComplexLineSymbol)
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
	Display::CComplexLineSymbol *m_pLineSymbol;

	bool m_bAutoDestroy;

};

OBJECT_ENTRY_AUTO(__uuidof(otComplexLineSymbol), CotComplexLineSymbol)
