// otGeoConvert.h : CotGeoConvert ������

#pragma once
#include "resource.h"       // ������

#include "otcGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotGeoConvert

class ATL_NO_VTABLE CotGeoConvert :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotGeoConvert, &CLSID_otGeoConvert>,
	public IotGeoConvert
{
public:
	CotGeoConvert()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_OTGEOCONVERT)


BEGIN_COM_MAP(CotGeoConvert)
	COM_INTERFACE_ENTRY(IotGeoConvert)
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
    //��C++Geometryָ��ת��ΪIotGeometry
	STDMETHOD(ConvertGeo)(LONG p, VARIANT_BOOL bown, IotGeometry** retGeo);
	//��IotGeometryת��ΪC++ Geometryָ��
	STDMETHOD(ConvertIGeo)(IotGeometry* geometry, LONG* ret);
};

OBJECT_ENTRY_AUTO(__uuidof(otGeoConvert), CotGeoConvert)
