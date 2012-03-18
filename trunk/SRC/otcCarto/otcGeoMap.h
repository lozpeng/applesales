// otCMap.h : GeoMap ������

#pragma once
#include "resource.h"       // ������

#include "otcCarto.h"
#include "_IGeoMapEvents_CP.h"
#include "Map.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
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
	//ͼ����Ŀ
	STDMETHOD(LayerCount)(LONG* Count);

	//�õ���ͼ��λ
	STDMETHOD(get_MapUnit)(otUnits* pVal);
	STDMETHOD(get_GraphicLayer)(IotGraphicLayer** pVal);
	STDMETHOD(get_Name)(BSTR* pVal);
	STDMETHOD(put_Name)(BSTR newVal);

	//���ͼ��
	STDMETHOD(AddLayer)(IotLayer* layer);
	//�õ�ͼ��
	STDMETHOD(GetLayer)(LONG index, IotLayer** retLayer);
	STDMETHOD(RemoveLayers)(void);
	STDMETHOD(DeleteLayer)(LONG index);
	STDMETHOD(FindLayer)(IotLayer* layer, LONG* index);
	STDMETHOD(MoveLayer)(IotLayer* layer, LONG ToIndex);
	STDMETHOD(get_SpatialReference)(IotSpatialReference** pVal);
	STDMETHOD(put_SpatialReference)(IotSpatialReference* newVal);


private:

	bool CheckPointer();

	//ͼԪɾ��ʱ�Ļص�����
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
