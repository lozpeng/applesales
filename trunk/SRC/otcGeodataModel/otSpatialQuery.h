// otSpatialQuery.h : CotSpatialQuery 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcGeodataModel.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotSpatialQuery

class ATL_NO_VTABLE CotSpatialQuery :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotSpatialQuery, &CLSID_otSpatialQuery>,
	public IotSpatialQuery,
	public IotSimpleQuery
{
public:
	CotSpatialQuery();

	~CotSpatialQuery();


	DECLARE_REGISTRY_RESOURCEID(IDR_OTSPATIALQUERY)


	BEGIN_COM_MAP(CotSpatialQuery)
		COM_INTERFACE_ENTRY(IotSpatialQuery)
		COM_INTERFACE_ENTRY(IotSimpleQuery)
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


	// IotSimpleQuery Methods
public:
	STDMETHOD(get_Fields)( BSTR * pVal);

	STDMETHOD(put_Fields)( BSTR newVal);

	STDMETHOD(get_WhereString)( BSTR * pVal);

	STDMETHOD(put_WhereString)( BSTR newVal);

	STDMETHOD(AddField)( BSTR fieldname);
private:
	_bstr_t  m_strFields;

	_bstr_t  m_strWhere;
    
	otSpatialRel m_spatialRel;

	IotGeometry *m_pGeometry;
public:
	STDMETHOD(get_SpatialRelation)(otSpatialRel* pVal);
	STDMETHOD(put_SpatialRelation)(otSpatialRel newVal);
	STDMETHOD(get_Geometry)(IotGeometry** pVal);
	STDMETHOD(put_Geometry)(IotGeometry* newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(otSpatialQuery), CotSpatialQuery)
