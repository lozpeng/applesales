// otGradientFillSymbol.h : CotGradientFillSymbol 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcDisplay.h"
#include "GradientFillSymbol.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotGradientFillSymbol

class ATL_NO_VTABLE CotGradientFillSymbol :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotGradientFillSymbol, &CLSID_otGradientFillSymbol>,
	public IotGradientFillSymbol,
	public IOriginData
{
public:
	CotGradientFillSymbol();
	~CotGradientFillSymbol();
	

	DECLARE_REGISTRY_RESOURCEID(IDR_OTGRADIENTFILLSYMBOL)


	BEGIN_COM_MAP(CotGradientFillSymbol)
		COM_INTERFACE_ENTRY(IotGradientFillSymbol)
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
	

	// IotSymbol Methods
public:
	STDMETHOD(get_Type)( otSymbolType * pVal);

	STDMETHOD(get_Unit)( otSymbolUnit * pVal);

	STDMETHOD(put_Unit)( otSymbolUnit newVal);

	STDMETHOD(get_FillColor)( IotColor * * pVal);

	STDMETHOD(put_FillColor)( IotColor * newVal);

	//IotGradientFillSymbol Methods
public:
	STDMETHOD(get_BeginColor)( IotColor** pVal );

	STDMETHOD(put_BeginColor)( IotColor* pVal );
	
	STDMETHOD(get_EndColor)(  IotColor** pVal );
	
	STDMETHOD(put_EndColor)(  IotColor* pVal );
	
	STDMETHOD(get_SegmentCounts)( LONG * pVal );
	
	STDMETHOD(put_SegmentCounts)( LONG pVal );
	
	STDMETHOD(get_Percent)( LONG * pVal);
	
	STDMETHOD(put_Percent)( LONG pVal);
	
	STDMETHOD(get_Angle)( FLOAT * pVal );
	
	STDMETHOD(put_Angle)( FLOAT pVal );
	
	STDMETHOD(get_GradientFillType)( otGradientFillType * pVal );
	
	STDMETHOD(put_GradientFillType)( otGradientFillType pVal );
	
private:
	bool CheckPointer();
private:
	Display::ISymbolPtr *m_ppSymbol;
	Display::CGradientFillSymbol *m_pFillSymbol;

	bool m_bAutoDestroy;

};

OBJECT_ENTRY_AUTO(__uuidof(otGradientFillSymbol), CotGradientFillSymbol)
