// otMultiPolygon.h : CotMultiPolygon ������

#pragma once
#include "resource.h"       // ������

#include "otcGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotMultiPolygon

class ATL_NO_VTABLE CotMultiPolygon :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotMultiPolygon, &CLSID_otMultiPolygon>,
	public IotMultiPolygon,
	public IOriginData,
	public IotGeometry,
	public IotGeometryCollection,
	public IotTransform
{
public:
	CotMultiPolygon();
	~CotMultiPolygon();


	DECLARE_REGISTRY_RESOURCEID(IDR_OTMULTIPOLYGON)


	BEGIN_COM_MAP(CotMultiPolygon)
		COM_INTERFACE_ENTRY(IotMultiPolygon)
		COM_INTERFACE_ENTRY(IOriginData)
		COM_INTERFACE_ENTRY(IotGeometry)
		COM_INTERFACE_ENTRY(IotGeometryCollection)
		COM_INTERFACE_ENTRY(IotTransform)
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

	// IotGeometry Methods
public:
	STDMETHOD(get_GeometryType)( otGeometryType * pVal);

	STDMETHOD(get_PointCount)( LONG * pVal);

	STDMETHOD(GetEnvelope)( IotEnvelope * * envelope);

	STDMETHOD(get_HasZ)( VARIANT_BOOL * pVal);

	STDMETHOD(put_HasZ)( VARIANT_BOOL newVal);

	STDMETHOD(get_HasM)( VARIANT_BOOL * pVal);

	STDMETHOD(put_HasM)( VARIANT_BOOL newVal);

	STDMETHOD(get_IsEmpty)( VARIANT_BOOL * pVal);

	STDMETHOD(SetEmpty)();

	STDMETHOD(Clone)( IotGeometry * * geometry);

	STDMETHOD(get_IsValid)( VARIANT_BOOL * pVal);

	STDMETHOD(Disjoint)( IotGeometry * other,  VARIANT_BOOL * bRet);

	STDMETHOD(Touches)( IotGeometry * other,  VARIANT_BOOL * bRet);

	STDMETHOD(Intersects)( IotGeometry * other,  VARIANT_BOOL * bRet);

	STDMETHOD(Crosses)( IotGeometry * other,  VARIANT_BOOL * bRet);

	STDMETHOD(Within)( IotGeometry * other,  VARIANT_BOOL * bRet);

	STDMETHOD(Overlaps)( IotGeometry * other,  VARIANT_BOOL * bRet);

	STDMETHOD(Equals)( IotGeometry * other,  VARIANT_BOOL * bRet);

	STDMETHOD(Covers)( IotGeometry * other,  VARIANT_BOOL * bRet);

	STDMETHOD(ConvexHull)( IotGeometry * * retGeometry);

	STDMETHOD(Buffer)( DOUBLE distance,  IotGeometry * * retGeometry);

	STDMETHOD(Intersection)( IotGeometry * other,  IotGeometry * * retGeometry);

	STDMETHOD(Union)( IotGeometry * other,  IotGeometry * * retGeometry);

	STDMETHOD(Difference)( IotGeometry * other,  IotGeometry * * retGeometry);

	STDMETHOD(SymDifference)( IotGeometry * other,  IotGeometry * * retGeometry);

	// IotGeometryCollection Methods
public:
	STDMETHOD(get_GeometryCount)( LONG * pVal);

	STDMETHOD(GetGeometry)( LONG index,  IotGeometry * * retGeometry);

	STDMETHOD(AddGeometry)( IotGeometry * geometry);

	//IotPolygon
public:
	STDMETHOD(get_Area)(DOUBLE* pVal);

	// IotTransform Methods
public:
	STDMETHOD(Move)( DOUBLE dx,  DOUBLE dy);

	STDMETHOD(Scale)( IotPoint * Origin,  DOUBLE dx,  DOUBLE dy);

	STDMETHOD(Rotate)( IotPoint * Origin,  DOUBLE angle);

private:
	//����MutiPolygon��ָ��
	GEOMETRY::geom::MultiPolygon *m_pGeometry;
	bool m_bAutoDestroy;
};

OBJECT_ENTRY_AUTO(__uuidof(otMultiPolygon), CotMultiPolygon)
