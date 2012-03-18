// otEnvelope.h : otEnvelope 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// otEnvelope

class ATL_NO_VTABLE otEnvelope :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<otEnvelope, &CLSID_otEnvelope>,
	public IotEnvelope
{
public:
	otEnvelope();


DECLARE_REGISTRY_RESOURCEID(IDR_ENVELOPE)


BEGIN_COM_MAP(otEnvelope)
	COM_INTERFACE_ENTRY(IotEnvelope)
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

	STDMETHOD(get_MinX)(double* pVal);
	STDMETHOD(put_MinX)(double newVal);
	STDMETHOD(get_MinY)(double* pVal);
	STDMETHOD(put_MinY)(double newVal);
	STDMETHOD(get_MaxX)(double* pVal);
	STDMETHOD(put_MaxX)(double newVal);
	STDMETHOD(get_MaxY)(double* pVal);
	STDMETHOD(put_MaxY)(double newVal);
private:
	double  m_minx;
	double  m_miny;
	double  m_maxx;
	double  m_maxy;


};

OBJECT_ENTRY_AUTO(__uuidof(otEnvelope), otEnvelope)
