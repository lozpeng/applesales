// otTextSymbol.h : CotTextSymbol 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcDisplay.h"
#include  "TextSymbol.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotTextSymbol

class ATL_NO_VTABLE CotTextSymbol :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotTextSymbol, &CLSID_otTextSymbol>,
	public IotTextSymbol,
	public IOriginData
{
public:
	CotTextSymbol();
	~CotTextSymbol();


DECLARE_REGISTRY_RESOURCEID(IDR_OTTEXTSYMBOL)


BEGIN_COM_MAP(CotTextSymbol)
	COM_INTERFACE_ENTRY(IotTextSymbol)
	COM_INTERFACE_ENTRY(IOriginData)
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

	STDMETHOD(get_Size)(DOUBLE* pVal);
	STDMETHOD(put_Size)(DOUBLE newVal);
	STDMETHOD(get_Angle)(DOUBLE* pVal);
	STDMETHOD(put_Angle)(DOUBLE newVal);
	STDMETHOD(get_TextColor)(IotColor** pVal);
	STDMETHOD(put_TextColor)(IotColor* newVal);
	STDMETHOD(get_Font)(IFontDisp** pVal);
	STDMETHOD(put_Font)(IFontDisp* newVal);

	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);


	// IotSymbol Methods
public:
	STDMETHOD(get_Type)( otSymbolType * pVal);

	STDMETHOD(get_Unit)( otSymbolUnit * pVal);

	STDMETHOD(put_Unit)( otSymbolUnit newVal);
private:
	bool CheckPointer();
private:
	Display::ISymbolPtr *m_ppSymbol;
	Display::CTextSymbol *m_pTextSymbol;

	bool m_bAutoDestroy;
};

OBJECT_ENTRY_AUTO(__uuidof(otTextSymbol), CotTextSymbol)
