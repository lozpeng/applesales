// otSpatialReference.h : CotSpatialReference 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcGeodataModel.h"
#include "SpatialReference.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotSpatialReference

class ATL_NO_VTABLE CotSpatialReference :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotSpatialReference, &CLSID_otSpatialReference>,
	public IotSpatialReference,
	public IOriginData
{
public:
	CotSpatialReference();
	~CotSpatialReference();


DECLARE_REGISTRY_RESOURCEID(IDR_OTSPATIALREFERENCE)


BEGIN_COM_MAP(CotSpatialReference)
	COM_INTERFACE_ENTRY(IotSpatialReference)
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

	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);
public:


	STDMETHOD(Clone)(IotSpatialReference** spatialReference);
	STDMETHOD(ImportFromWkt)(BSTR wkt, VARIANT_BOOL* bSuccess);
	STDMETHOD(ImportFromESRI)(BSTR wkt, VARIANT_BOOL* bSuccess);
	STDMETHOD(ExportToWkt)(BSTR* wkt);
	STDMETHOD(IsGeographic)(VARIANT_BOOL* bRet);
	STDMETHOD(IsProjected)(VARIANT_BOOL* bRet);
	STDMETHOD(IsSame)(IotSpatialReference* other, VARIANT_BOOL* bSame);
	STDMETHOD(GetGeogName)(BSTR* name);
	STDMETHOD(GetProjName)(BSTR* name);

private:
	//检查内部指针是否有效
	bool CheckPointer();

private:
	Geodatabase::CSpatialReferencePtr* m_ppSR;
	bool m_bAutoDestroy;
};

OBJECT_ENTRY_AUTO(__uuidof(otSpatialReference), CotSpatialReference)
