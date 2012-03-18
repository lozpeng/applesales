// otFeatureCursor.h : CotFeatureCursor 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcGeodataModel.h"
#include "IFeatureCursor.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotFeatureCursor

class ATL_NO_VTABLE CotFeatureCursor :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotFeatureCursor, &CLSID_otFeatureCursor>,
	public IotFeatureCursor,
	public IOriginData
{
public:
	CotFeatureCursor();

    virtual ~CotFeatureCursor();

	DECLARE_REGISTRY_RESOURCEID(IDR_OTFEATURECURSOR)


	BEGIN_COM_MAP(CotFeatureCursor)
		COM_INTERFACE_ENTRY(IotFeatureCursor)
		COM_INTERFACE_ENTRY(IOriginData)
		COM_INTERFACE_ENTRY(IotCursor)
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

	STDMETHOD(NextFeature)(IotFeature** retFeature);

	// IotCursor Methods
public:
	STDMETHOD(get_Table)( IotTable * * pVal);

	STDMETHOD(NextRow)( IotRow * * row);

	STDMETHOD(IsEOF)( VARIANT_BOOL * ret);


	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);

private:
	//检查内部指针是否有效
	bool CheckPointer();

private:
	Geodatabase::IFeatureCursorPtr* m_ppCursor;
	bool m_bAutoDestroy;

};

OBJECT_ENTRY_AUTO(__uuidof(otFeatureCursor), CotFeatureCursor)
