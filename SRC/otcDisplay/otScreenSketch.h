// otScreenSketch.h : CotScreenSketch 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcDisplay.h"
#include "ScreenSketch.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotScreenSketch

class ATL_NO_VTABLE CotScreenSketch :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotScreenSketch, &CLSID_otScreenSketch>,
	public IotScreenSketch
{
public:
	CotScreenSketch();
	~CotScreenSketch();


DECLARE_REGISTRY_RESOURCEID(IDR_OTSCREENSKETCH)


BEGIN_COM_MAP(CotScreenSketch)
	COM_INTERFACE_ENTRY(IotScreenSketch)
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

	STDMETHOD(Create)(otGeometryType type);
	STDMETHOD(put_ScreenCanvas)(IotCanvas* newVal);
	STDMETHOD(put_Symbol)(IotSymbol* newVal);
	STDMETHOD(Start)(void);
	STDMETHOD(Stop)(IotGeometry** retGeometry);
	STDMETHOD(AddPoint)(IotPoint* point);
	STDMETHOD(SetMousePoint)(IotPoint* point);

private:
	Display::CScreenSketch *m_pSketch;
public:
	STDMETHOD(SetCircleCenter)(IotPoint* point);
	STDMETHOD(SetEllipseTopLeft)(IotPoint* point);
	STDMETHOD(SetRectTopLeft)(IotPoint* point);
};

OBJECT_ENTRY_AUTO(__uuidof(otScreenSketch), CotScreenSketch)
