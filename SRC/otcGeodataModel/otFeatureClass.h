// otFeatureClass.h : CotFeatureClass 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcGeodataModel.h"
#include "IFeatureClass.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotFeatureClass

class ATL_NO_VTABLE CotFeatureClass :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotFeatureClass, &CLSID_otFeatureClass>,
	public IotFeatureClass,
	public IOriginData
	
{
public:
	CotFeatureClass();
	virtual ~CotFeatureClass();

	DECLARE_REGISTRY_RESOURCEID(IDR_OTFEATURECLASS)


	BEGIN_COM_MAP(CotFeatureClass)
		COM_INTERFACE_ENTRY(IotFeatureClass)
        COM_INTERFACE_ENTRY(IotTable)
		COM_INTERFACE_ENTRY(IotDataObject)
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


	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);



	// IotDataObject Methods
public:
	STDMETHOD(GetType)(otDataType * type);

	STDMETHOD(GetName)( BSTR * name);

	STDMETHOD(GetExtent)( IotEnvelope * * envelope);

	STDMETHOD(get_Workspace)( IotWorkspace * * pVal);

private:
	//检查内部指针是否有效
	bool CheckPointer();

	//IotFeatureClass
public:

	//得到要素数目
	STDMETHOD(get_FeatureCount)(LONG* pVal);

	//图形数据字段的名称
	STDMETHOD(get_ShapeFieldName)(BSTR* pVal);
	STDMETHOD(GetFeature)(LONG index, IotFeature** feature);
	STDMETHOD(get_HasM)(VARIANT_BOOL* pVal);
	STDMETHOD(get_HasZ)(VARIANT_BOOL* pVal);

	STDMETHOD(Query)(IotSimpleQuery* queryFilter, VARIANT_BOOL bReadOnly, IotCursor** retCursor);
	STDMETHOD(get_ShapeType)(otGeometryType* pVal);
	STDMETHOD(CreateFeature)(IotFeature** retFeature);
	STDMETHOD(DeleteFeature)(LONG index);
	STDMETHOD(Select)(IotSimpleQuery* queryFilter, IotSelectionSet** ret);
	STDMETHOD(get_FieldCount)(LONG* pVal);
	STDMETHOD(GetField)(LONG index, IotField** field);
	STDMETHOD(FindField)(BSTR name, LONG* index);
	STDMETHOD(AddFeature)(IotFeature* feature);
	STDMETHOD(get_SpatialReference)(IotSpatialReference** pVal);

private:

	Geodatabase::IFeatureClassPtr *m_ppFeatureClass;
	bool m_bAutoDestroy;

	//内部空间参考系指针
	IotSpatialReference *m_pSR;
};

OBJECT_ENTRY_AUTO(__uuidof(otFeatureClass), CotFeatureClass)
