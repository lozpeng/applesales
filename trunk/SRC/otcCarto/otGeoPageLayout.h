// otGeoPageLayout.h : CotGeoPageLayout 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcCarto.h"
#include "PageLayout.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotGeoPageLayout

class ATL_NO_VTABLE CotGeoPageLayout :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotGeoPageLayout, &CLSID_otGeoPageLayout>,
	public IotGeoPageLayout,
	public IOriginData
{
public:
	CotGeoPageLayout();
	~CotGeoPageLayout();


DECLARE_REGISTRY_RESOURCEID(IDR_OTGEOPAGELAYOUT)


BEGIN_COM_MAP(CotGeoPageLayout)
	COM_INTERFACE_ENTRY(IotGeoPageLayout)
	COM_INTERFACE_ENTRY(IOriginData)
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

	STDMETHOD(get_GraphicLayer)(IotGraphicLayer** pVal);

	STDMETHOD(get_Page)(IotPage** pVal);

	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);
private:
	bool CheckPointer();

private:
	Carto::CPageLayoutPtr *m_ppLayout;

	bool m_bAutoDestroy;

	
};

OBJECT_ENTRY_AUTO(__uuidof(otGeoPageLayout), CotGeoPageLayout)
