// otRasterBlock.h : CotRasterBlock 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcGeodataModel.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotRasterBlock

class ATL_NO_VTABLE CotRasterBlock :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotRasterBlock, &CLSID_otRasterBlock>,
	public IotRasterBlock
{
public:
	CotRasterBlock();

	~CotRasterBlock();


DECLARE_REGISTRY_RESOURCEID(IDR_OTRASTERBLOCK)


BEGIN_COM_MAP(CotRasterBlock)
	COM_INTERFACE_ENTRY(IotRasterBlock)
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

	STDMETHOD(get_DataType)(otBandType* pVal);
	STDMETHOD(put_DataType)(otBandType newVal);
	STDMETHOD(get_Width)(LONG* pVal);
	STDMETHOD(put_Width)(LONG newVal);
	STDMETHOD(get_Height)(LONG* pVal);
	STDMETHOD(put_Height)(LONG newVal);
	STDMETHOD(GetValue)(LONG X, LONG Y, VARIANT* value);
	STDMETHOD(get_SafeArray)(VARIANT* pVal);
	STDMETHOD(put_SafeArray)(VARIANT newVal);

private:

	//安全数组
	CComSafeArray<VARIANT> m_sa;

	long m_lwidth;
	long m_lheight;

	otBandType m_type;

};

OBJECT_ENTRY_AUTO(__uuidof(otRasterBlock), CotRasterBlock)
