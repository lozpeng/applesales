// otField.h : CotField 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcGeodataModel.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotField

class ATL_NO_VTABLE CotField :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotField, &CLSID_otField>,
	public IotField
{
public:
	CotField()
	{

		m_length =0;
		m_precision =0;
		m_type =FTYPE_UNKNOWN;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_OTFIELD)


BEGIN_COM_MAP(CotField)
	COM_INTERFACE_ENTRY(IotField)
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

	STDMETHOD(get_Name)(BSTR* pVal);
	STDMETHOD(put_Name)(BSTR newVal);
	STDMETHOD(get_Length)(LONG* pVal);
	STDMETHOD(put_Length)(LONG newVal);
	STDMETHOD(get_Type)(otFieldType* pVal);
	STDMETHOD(put_Type)(otFieldType newVal);
	STDMETHOD(get_Precision)(LONG* pVal);
	STDMETHOD(put_Precision)(LONG newVal);

private:

	_bstr_t m_name;

	long m_length;

	long m_precision;

	otFieldType m_type;
};

OBJECT_ENTRY_AUTO(__uuidof(otField), CotField)
