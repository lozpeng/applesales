// otSpatialReference.h : CotSpatialReference ������

#pragma once
#include "resource.h"       // ������

#include "otcGeodataModel.h"
#include "SpatialReference.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotSpatialReference

class ATL_NO_VTABLE CotSpatialReference :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotSpatialReference, &CLSID_otSpatialReference>,
	public IotSpatialReference,
	public IOriginData
{
public:
	CotSpatialReference();
	~CotSpatialReference();


DECLARE_REGISTRY_RESOURCEID(IDR_OTSPATIALREFERENCE)


BEGIN_COM_MAP(CotSpatialReference)
	COM_INTERFACE_ENTRY(IotSpatialReference)
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

	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);
public:


	STDMETHOD(Clone)(IotSpatialReference** spatialReference);
	STDMETHOD(ImportFromWkt)(BSTR wkt, VARIANT_BOOL* bSuccess);
	STDMETHOD(ImportFromESRI)(BSTR wkt, VARIANT_BOOL* bSuccess);
	STDMETHOD(ExportToWkt)(BSTR* wkt);
	STDMETHOD(IsGeographic)(VARIANT_BOOL* bRet);
	STDMETHOD(IsProjected)(VARIANT_BOOL* bRet);
	STDMETHOD(IsSame)(IotSpatialReference* other, VARIANT_BOOL* bSame);
	STDMETHOD(GetGeogName)(BSTR* name);
	STDMETHOD(GetProjName)(BSTR* name);

private:
	//����ڲ�ָ���Ƿ���Ч
	bool CheckPointer();

private:
	Geodatabase::CSpatialReferencePtr* m_ppSR;
	bool m_bAutoDestroy;
};

OBJECT_ENTRY_AUTO(__uuidof(otSpatialReference), CotSpatialReference)
