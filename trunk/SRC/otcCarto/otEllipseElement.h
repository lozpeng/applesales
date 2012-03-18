// otEllipseElement.h : CotEllipseElement ������

#pragma once
#include "resource.h"       // ������

#include "otcCarto.h"
#include "EllipseElement.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotEllipseElement

class ATL_NO_VTABLE CotEllipseElement :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotEllipseElement, &CLSID_otEllipseElement>,
	public IotEllipseElement,
	public IOriginData
{
public:
	CotEllipseElement();
	~CotEllipseElement();
	

DECLARE_REGISTRY_RESOURCEID(IDR_OTELLIPSEELEMENT)


BEGIN_COM_MAP(CotEllipseElement)
	COM_INTERFACE_ENTRY(IotEllipseElement)
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
	Element::CEllipseElement *m_pEllipseElement;

	bool m_bAutoDestroy;

};

OBJECT_ENTRY_AUTO(__uuidof(otEllipseElement), CotEllipseElement)
