// otFeatureLayer.h : CotFeatureLayer 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcCarto.h"
#include "ILayer.h"
#include "FeatureLayer.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotFeatureLayer

class ATL_NO_VTABLE CotFeatureLayer :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotFeatureLayer, &CLSID_otFeatureLayer>,
	public IotFeatureLayer,
	public IOriginData

{
public:
	CotFeatureLayer();

	virtual ~CotFeatureLayer();


	DECLARE_REGISTRY_RESOURCEID(IDR_OTFEATURELAYER)


	BEGIN_COM_MAP(CotFeatureLayer)
		COM_INTERFACE_ENTRY(IotFeatureLayer)
		COM_INTERFACE_ENTRY(IotLayer)
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
    STDMETHOD(get_SelectionSet)(IotSelectionSet** pVal);

	STDMETHOD(put_SelectionSet)(IotSelectionSet* newVal);

	STDMETHOD(ClearSelection)(void);
	STDMETHOD(Select)(IotSimpleQuery* queryFilter, otSelectOption option);

	STDMETHOD(get_Render)(IotFeatureRender** pVal);
	STDMETHOD(put_Render)(IotFeatureRender* newVal);


	// IotLayer Methods
public:
	STDMETHOD(get_Name)( BSTR * pVal);

	STDMETHOD(put_Name)( BSTR newVal);

	STDMETHOD(get_LayerDesciption)( BSTR * pVal);

	STDMETHOD(put_LayerDesciption)( BSTR newVal);

	STDMETHOD(get_Visible)( VARIANT_BOOL * pVal);

	STDMETHOD(put_Visible)( VARIANT_BOOL newVal);

	STDMETHOD(get_ScaleRangeValid)( VARIANT_BOOL * pVal);

	STDMETHOD(put_ScaleRangeValid)( VARIANT_BOOL newVal);

	STDMETHOD(get_ScaleRangeMin)( DOUBLE * pVal);

	STDMETHOD(put_ScaleRangeMin)( DOUBLE newVal);

	STDMETHOD(get_ScaleRangeMax)( DOUBLE * pVal);

	STDMETHOD(put_ScaleRangeMax)( DOUBLE newVal);

	STDMETHOD(get_LayerType)( otLayerType * pVal);

	STDMETHOD(get_DataObject)( IotDataObject * * pVal);

	STDMETHOD(put_DataObject)( IotDataObject * newVal);



	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);

private:
	bool CheckPointer();
private:
	Carto::IFeatureLayerPtr *m_ppLayer;
	bool m_bAutoDestroy;


	
};

OBJECT_ENTRY_AUTO(__uuidof(otFeatureLayer), CotFeatureLayer)
