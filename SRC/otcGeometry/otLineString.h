// otLineString.h : CotLineString ������

#pragma once
#include "resource.h"       // ������

#include "otcGeometry.h"
#include <Geometry/geom/LineString.h>

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotLineString

class ATL_NO_VTABLE CotLineString :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotLineString, &CLSID_otLineString>,
	public IotLineString,
	public IOriginData,
	public IotGeometry,
	public IotPointCollection,
	public IotTransform,
	public IotSegmentCollection
{
public:
	CotLineString();
	virtual ~CotLineString();


	DECLARE_REGISTRY_RESOURCEID(IDR_OTLINESTRING)


	BEGIN_COM_MAP(CotLineString)
		COM_INTERFACE_ENTRY(IotLineString)
		COM_INTERFACE_ENTRY(IOriginData)
		COM_INTERFACE_ENTRY(IotGeometry)
		COM_INTERFACE_ENTRY(IotPointCollection)
		COM_INTERFACE_ENTRY(IotTransform)
		COM_INTERFACE_ENTRY(IotSegmentCollection)
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

	STDMETHOD(IsClosed)(VARIANT_BOOL* bRet);
	STDMETHOD(get_Length)(DOUBLE* pVal);
	STDMETHOD(get_StartPoint)(IotPoint** pVal);
	STDMETHOD(put_StartPoint)(IotPoint* newVal);
	STDMETHOD(get_EndPoint)(IotPoint** pVal);
	STDMETHOD(put_EndPoint)(IotPoint* newVal);

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


	// IotPointCollection Methods
public:
	STDMETHOD(get_Point)( LONG index,  IotPoint * * pVal);

	STDMETHOD(AddPoint)( IotPoint * point);

	STDMETHOD(InsertPoint)( LONG index,  IotPoint * point);

	STDMETHOD(ReplacePoint)( LONG index,  IotPoint * point);

	STDMETHOD(RemovePoint)( LONG index);

	STDMETHOD(get_PointNum)(LONG* pVal);

	// IotSegmentCollection Methods
public:
	STDMETHOD(get_SegmentCount)( LONG * pVal);

	STDMETHOD(AddSegment)( IotSegment * segment);

	STDMETHOD(GetSegment)( LONG index,  IotSegment * * ret);

	// IotTransform Methods
public:
	STDMETHOD(Move)( DOUBLE dx,  DOUBLE dy);

	STDMETHOD(Scale)( IotPoint * Origin,  DOUBLE dx,  DOUBLE dy);

	STDMETHOD(Rotate)( IotPoint * Origin,  DOUBLE angle);


private:
	//����LineString��ָ��
	GEOMETRY::geom::LineString *m_pGeometry;
	bool m_bAutoDestroy;  

	
	
};

OBJECT_ENTRY_AUTO(__uuidof(otLineString), CotLineString)
