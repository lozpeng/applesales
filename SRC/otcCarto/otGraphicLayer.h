// otGraphicLayer.h : CotGraphicLayer ������

#pragma once
#include "resource.h"       // ������

#include "otcCarto.h"
#include "GraphicLayer.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotGraphicLayer

class ATL_NO_VTABLE CotGraphicLayer :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotGraphicLayer, &CLSID_otGraphicLayer>,
	public IotGraphicLayer,
	public IOriginData
{
public:
	CotGraphicLayer();
	~CotGraphicLayer();


	DECLARE_REGISTRY_RESOURCEID(IDR_OTGRAPHICLAYER)


	BEGIN_COM_MAP(CotGraphicLayer)
		COM_INTERFACE_ENTRY(IotGraphicLayer)
		COM_INTERFACE_ENTRY(IotLayer)
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


	// IotLayer Methods
public:
	STDMETHOD(get_Name)( BSTR * pVal);

	STDMETHOD(put_Name)( BSTR newVal);

	STDMETHOD(get_LayerDesciption)( BSTR * pVal);

	STDMETHOD(put_LayerDesciption)( BSTR newVal);

	STDMETHOD(get_Visible)( VARIANT_BOOL * pVal);

	STDMETHOD(put_Visible)( VARIANT_BOOL newVal);

	STDMETHOD(get_ScaleRangeValid)( VARIANT_BOOL * pVal);

	STDMETHOD(put_ScaleRangeValid)( VARIANT_BOOL newVal);

	STDMETHOD(get_ScaleRangeMin)( DOUBLE * pVal);

	STDMETHOD(put_ScaleRangeMin)( DOUBLE newVal);

	STDMETHOD(get_ScaleRangeMax)( DOUBLE * pVal);

	STDMETHOD(put_ScaleRangeMax)( DOUBLE newVal);

	STDMETHOD(get_LayerType)( otLayerType * pVal);

	STDMETHOD(get_DataObject)( IotDataObject * * pVal);

	STDMETHOD(put_DataObject)( IotDataObject * newVal);

	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);
private:
	bool CheckPointer();

private:
	Carto::CGraphicLayerPtr *m_ppLayer;

	bool m_bAutoDestroy;


public:
	STDMETHOD(get_Count)(LONG* pVal);
	STDMETHOD(AddElement)(IElement* element);
	STDMETHOD(GetElement)(LONG index, IElement** retElement);
	STDMETHOD(RemoveAllElements)(void);
	STDMETHOD(RemoveElement)(IElement* element);
	STDMETHOD(get_SelectedElementCount)(LONG* pVal);
	STDMETHOD(SelectElement)(IElement* element);
	STDMETHOD(IsElementSelected)(IElement* element, VARIANT_BOOL* bSelected);
	STDMETHOD(UnselectElement)(IElement* element);
	STDMETHOD(GetSelectedElement)(LONG index,IElement** retElement);
	STDMETHOD(SelectAllElements)(void);
	STDMETHOD(UnselectAllElements)(void);
};

OBJECT_ENTRY_AUTO(__uuidof(otGraphicLayer), CotGraphicLayer)
