// otRasterDataset.h : CotRasterDataset 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcGeodataModel.h"
#include "IRasterDataset.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotRasterDataset

class ATL_NO_VTABLE CotRasterDataset :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotRasterDataset, &CLSID_otRasterDataset>,
	public IotRasterDataset,
	public IOriginData
{
public:
	CotRasterDataset();
	~CotRasterDataset();


DECLARE_REGISTRY_RESOURCEID(IDR_OTRASTERDATASET)


BEGIN_COM_MAP(CotRasterDataset)
	COM_INTERFACE_ENTRY(IotRasterDataset)
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

public:
	STDMETHOD(get_Writable)(VARIANT_BOOL* pVal);
	STDMETHOD(get_ChannelCount)(LONG* pVal);
	STDMETHOD(get_Width)(LONG* pVal);
	STDMETHOD(get_Height)(LONG* pVal);
	STDMETHOD(get_Projection)(BSTR* pVal);
	STDMETHOD(put_Projection)(BSTR newVal);
	STDMETHOD(get_HasPyramid)(VARIANT_BOOL* pVal);
	STDMETHOD(CreateRasterBlock)(LONG BandIndex,LONG width, LONG height,IotRasterBlock **ret);
	STDMETHOD(ReadData)(LONG BandIndex, LONG row, LONG col, IotRasterBlock* RasterBlock);
	STDMETHOD(get_SpatialReference)(IotSpatialReference** pVal);

private:

	Geodatabase::IRasterDatasetPtr *m_ppRasterDataset;
	bool m_bAutoDestroy;

	//内部空间参考系指针
	IotSpatialReference *m_pSR;
};

OBJECT_ENTRY_AUTO(__uuidof(otRasterDataset), CotRasterDataset)
