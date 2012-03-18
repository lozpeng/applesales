// otGeoConvert.h : CotGeoConvert 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotGeoConvert

class ATL_NO_VTABLE CotGeoConvert :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotGeoConvert, &CLSID_otGeoConvert>,
	public IotGeoConvert
{
public:
	CotGeoConvert()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_OTGEOCONVERT)


BEGIN_COM_MAP(CotGeoConvert)
	COM_INTERFACE_ENTRY(IotGeoConvert)
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
    //将C++Geometry指针转换为IotGeometry
	STDMETHOD(ConvertGeo)(LONG p, VARIANT_BOOL bown, IotGeometry** retGeo);
	//将IotGeometry转换为C++ Geometry指针
	STDMETHOD(ConvertIGeo)(IotGeometry* geometry, LONG* ret);
};

OBJECT_ENTRY_AUTO(__uuidof(otGeoConvert), CotGeoConvert)
