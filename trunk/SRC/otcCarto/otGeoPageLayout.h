// otGeoPageLayout.h : CotGeoPageLayout ������

#pragma once
#include "resource.h"       // ������

#include "otcCarto.h"
#include "PageLayout.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotGeoPageLayout

class ATL_NO_VTABLE CotGeoPageLayout :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotGeoPageLayout, &CLSID_otGeoPageLayout>,
	public IotGeoPageLayout,
	public IOriginData
{
public:
	CotGeoPageLayout();
	~CotGeoPageLayout();


DECLARE_REGISTRY_RESOURCEID(IDR_OTGEOPAGELAYOUT)


BEGIN_COM_MAP(CotGeoPageLayout)
	COM_INTERFACE_ENTRY(IotGeoPageLayout)
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

	STDMETHOD(get_GraphicLayer)(IotGraphicLayer** pVal);

	STDMETHOD(get_Page)(IotPage** pVal);

	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);
private:
	bool CheckPointer();

private:
	Carto::CPageLayoutPtr *m_ppLayout;

	bool m_bAutoDestroy;

	
};

OBJECT_ENTRY_AUTO(__uuidof(otGeoPageLayout), CotGeoPageLayout)
