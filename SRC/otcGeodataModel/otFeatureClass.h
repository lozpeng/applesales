// otFeatureClass.h : CotFeatureClass ������

#pragma once
#include "resource.h"       // ������

#include "otcGeodataModel.h"
#include "IFeatureClass.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotFeatureClass

class ATL_NO_VTABLE CotFeatureClass :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotFeatureClass, &CLSID_otFeatureClass>,
	public IotFeatureClass,
	public IOriginData
	
{
public:
	CotFeatureClass();
	virtual ~CotFeatureClass();

	DECLARE_REGISTRY_RESOURCEID(IDR_OTFEATURECLASS)


	BEGIN_COM_MAP(CotFeatureClass)
		COM_INTERFACE_ENTRY(IotFeatureClass)
        COM_INTERFACE_ENTRY(IotTable)
		COM_INTERFACE_ENTRY(IotDataObject)
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


	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);



	// IotDataObject Methods
public:
	STDMETHOD(GetType)(otDataType * type);

	STDMETHOD(GetName)( BSTR * name);

	STDMETHOD(GetExtent)( IotEnvelope * * envelope);

	STDMETHOD(get_Workspace)( IotWorkspace * * pVal);

private:
	//����ڲ�ָ���Ƿ���Ч
	bool CheckPointer();

	//IotFeatureClass
public:

	//�õ�Ҫ����Ŀ
	STDMETHOD(get_FeatureCount)(LONG* pVal);

	//ͼ�������ֶε�����
	STDMETHOD(get_ShapeFieldName)(BSTR* pVal);
	STDMETHOD(GetFeature)(LONG index, IotFeature** feature);
	STDMETHOD(get_HasM)(VARIANT_BOOL* pVal);
	STDMETHOD(get_HasZ)(VARIANT_BOOL* pVal);

	STDMETHOD(Query)(IotSimpleQuery* queryFilter, VARIANT_BOOL bReadOnly, IotCursor** retCursor);
	STDMETHOD(get_ShapeType)(otGeometryType* pVal);
	STDMETHOD(CreateFeature)(IotFeature** retFeature);
	STDMETHOD(DeleteFeature)(LONG index);
	STDMETHOD(Select)(IotSimpleQuery* queryFilter, IotSelectionSet** ret);
	STDMETHOD(get_FieldCount)(LONG* pVal);
	STDMETHOD(GetField)(LONG index, IotField** field);
	STDMETHOD(FindField)(BSTR name, LONG* index);
	STDMETHOD(AddFeature)(IotFeature* feature);
	STDMETHOD(get_SpatialReference)(IotSpatialReference** pVal);

private:

	Geodatabase::IFeatureClassPtr *m_ppFeatureClass;
	bool m_bAutoDestroy;

	//�ڲ��ռ�ο�ϵָ��
	IotSpatialReference *m_pSR;
};

OBJECT_ENTRY_AUTO(__uuidof(otFeatureClass), CotFeatureClass)
