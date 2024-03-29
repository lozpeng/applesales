// otRectElement.h : CotRectElement 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcCarto.h"
#include "RectangleElement.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotRectElement

class ATL_NO_VTABLE CotRectElement :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotRectElement, &CLSID_otRectElement>,
	public IotRectElement,
	public IOriginData
{
public:
	CotRectElement();
	~CotRectElement();


DECLARE_REGISTRY_RESOURCEID(IDR_OTRECTELEMENT)


BEGIN_COM_MAP(CotRectElement)
	COM_INTERFACE_ENTRY(IotRectElement)
	COM_INTERFACE_ENTRY(IOriginData)
	COM_INTERFACE_ENTRY(IElement)
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

	STDMETHOD(get_Symbol)(IotSymbol** pVal);
	STDMETHOD(put_Symbol)(IotSymbol* newVal);

	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);


	// IElement Methods
public:
	STDMETHOD(get_Geometry)( IotGeometry * * pVal);

	STDMETHOD(put_Geometry)( IotGeometry * newVal);

	STDMETHOD(get_Name)( BSTR * pVal);

	STDMETHOD(put_Name)( BSTR newVal);

	STDMETHOD(get_Type)( ElementType * pVal);

private:
	bool CheckPointer();
private:
	Element::IElementPtr *m_ppElement;
	Element::CRectangleElement *m_pRectElement;

	bool m_bAutoDestroy;
};

OBJECT_ENTRY_AUTO(__uuidof(otRectElement), CotRectElement)
