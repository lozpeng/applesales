// otColor.h : CotColor 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcDisplay.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotColor

class ATL_NO_VTABLE CotColor :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotColor, &CLSID_otColor>,
	public IotColor
{
public:
	CotColor()
	{
		m_red =m_green =m_blue =0;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_OTCOLOR)


BEGIN_COM_MAP(CotColor)
	COM_INTERFACE_ENTRY(IotColor)
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

	STDMETHOD(get_Red)(LONG* pVal);
	STDMETHOD(put_Red)(LONG newVal);
	STDMETHOD(get_Green)(LONG* pVal);
	STDMETHOD(put_Green)(LONG newVal);
	STDMETHOD(get_Blue)(LONG* pVal);
	STDMETHOD(put_Blue)(LONG newVal);

private:
	long m_red;
	long m_green;
	long m_blue;
};

OBJECT_ENTRY_AUTO(__uuidof(otColor), CotColor)
