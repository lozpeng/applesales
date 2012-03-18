// otPicFillSymbol.h : CotPicFillSymbol 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcDisplay.h"
#include "PicFillSymbol.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotPicFillSymbol

class ATL_NO_VTABLE CotPicFillSymbol :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotPicFillSymbol, &CLSID_otPicFillSymbol>,
	public IotPicFillSymbol,
	public IOriginData
{
public:
	CotPicFillSymbol();
	~CotPicFillSymbol();


DECLARE_REGISTRY_RESOURCEID(IDR_OTPICFILLSYMBOL)


BEGIN_COM_MAP(CotPicFillSymbol)
	COM_INTERFACE_ENTRY(IotPicFillSymbol)
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

public:
	STDMETHOD(get_PictureFile)(BSTR* pVal);
	STDMETHOD(put_PictureFile)(BSTR newVal);
	STDMETHOD(get_BackgroundColor)(IotColor** pVal);
	STDMETHOD(put_BackgroundColor)(IotColor* newVal);
	STDMETHOD(get_TransparentColor)(IotColor** pVal);
	STDMETHOD(put_TransparentColor)(IotColor* newVal);

private:
	bool CheckPointer();
private:
	Display::ISymbolPtr *m_ppSymbol;
	Display::CPicFillSymbol *m_pFillSymbol;

	bool m_bAutoDestroy;


};

OBJECT_ENTRY_AUTO(__uuidof(otPicFillSymbol), CotPicFillSymbol)
