// otCMap.h : GeoMap 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcCarto.h"
#include "_IGeoMapEvents_CP.h"
#include "Map.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// GeoMap

class ATL_NO_VTABLE GeoMap :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<GeoMap, &CLSID_GeoMap>,
	public IConnectionPointContainerImpl<GeoMap>,
	public CProxy_IGeoMapEvents<GeoMap>,
	public IDispatchImpl<IGeoMap, &IID_IGeoMap, &LIBID_otcCarto, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IOriginData
{
public:
	GeoMap();
	~GeoMap();

	DECLARE_REGISTRY_RESOURCEID(IDR_GEOMAP)


	BEGIN_COM_MAP(GeoMap)
		COM_INTERFACE_ENTRY(IGeoMap)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(IOriginData)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(GeoMap)
		CONNECTION_POINT_ENTRY(__uuidof(_IGeoMapEvents))
	END_CONNECTION_POINT_MAP()


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


	
public:
	//图层数目
	STDMETHOD(LayerCount)(LONG* Count);

	//得到地图单位
	STDMETHOD(get_MapUnit)(otUnits* pVal);
	STDMETHOD(get_GraphicLayer)(IotGraphicLayer** pVal);
	STDMETHOD(get_Name)(BSTR* pVal);
	STDMETHOD(put_Name)(BSTR newVal);

	//添加图层
	STDMETHOD(AddLayer)(IotLayer* layer);
	//得到图层
	STDMETHOD(GetLayer)(LONG index, IotLayer** retLayer);
	STDMETHOD(RemoveLayers)(void);
	STDMETHOD(DeleteLayer)(LONG index);
	STDMETHOD(FindLayer)(IotLayer* layer, LONG* index);
	STDMETHOD(MoveLayer)(IotLayer* layer, LONG ToIndex);
	STDMETHOD(get_SpatialReference)(IotSpatialReference** pVal);
	STDMETHOD(put_SpatialReference)(IotSpatialReference* newVal);


private:

	bool CheckPointer();

	//图元删除时的回调函数
	void OnElementDeleted(Element::IElementPtr pElement);

private:
	Carto::CMapPtr *m_ppMap;
	BOOL m_bAutoDestroy;

	boost::signals::connection m_ConnectionDeleteElement;
public:
	STDMETHOD(ZoomActualSize)(void);
	STDMETHOD(ZoomFullExtent)(void);
};

OBJECT_ENTRY_AUTO(__uuidof(GeoMap), GeoMap)
