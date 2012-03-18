// otWorkspace.h : CotWorkspace 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcGeodataModel.h"
#include "IWorkspace.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotWorkspace

class ATL_NO_VTABLE CotWorkspace :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotWorkspace, &CLSID_otWorkspace>,
	public IotWorkspace,
	public IOriginData
{
public:
	CotWorkspace();


	DECLARE_REGISTRY_RESOURCEID(IDR_OTWORKSPACE)


	BEGIN_COM_MAP(CotWorkspace)
		COM_INTERFACE_ENTRY(IotWorkspace)
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

private:
	Geodatabase::IWorkspace *m_pWorkspace;

public:
	//得到工作空间类型
	STDMETHOD(get_Type)(otWorkspaceType* pVal);

	//得到工作空间路径
	STDMETHOD(get_Path)(BSTR* pVal);

	//打开矢量数据源
	STDMETHOD(OpenFeatureClass)(BSTR filename, IotFeatureClass** FeatureClass);
	STDMETHOD(IsEditing)(VARIANT_BOOL* bret);
	STDMETHOD(StartEdit)(void);
	STDMETHOD(StopEdit)(VARIANT_BOOL save);
	STDMETHOD(StartEditOperation)(void);
	STDMETHOD(StopEditOperation)(void);
	STDMETHOD(UndoEdit)(void);
	STDMETHOD(RedoEdit)(void);
	STDMETHOD(CanUndo)(VARIANT_BOOL* bret);
	STDMETHOD(CanRedo)(VARIANT_BOOL* ret);

	//打开栅格数据源
	STDMETHOD(OpenRasterDataset)(BSTR filename, VARIANT_BOOL ReadOnly, IotRasterDataset** ret);
	STDMETHOD(CreateFeatureClass)(BSTR filename, IotEnvelope* extent, BSTR projWkt, otGeometryType FeatureType, VARIANT_BOOL hasZ, VARIANT_BOOL hasM, LONG numField, SAFEARRAY** fields, IotFeatureClass** retFeatureClass);
};

OBJECT_ENTRY_AUTO(__uuidof(otWorkspace), CotWorkspace)
