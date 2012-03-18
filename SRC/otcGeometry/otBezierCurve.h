// otBezierCurve.h : CotBezierCurve ������

#pragma once
#include "resource.h"       // ������

#include "otcGeometry.h"
#include <Geometry/geom/BezierCurve.h>

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotBezierCurve

class ATL_NO_VTABLE CotBezierCurve :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotBezierCurve, &CLSID_otBezierCurve>,
	public IotBezierCurve,
	public IOriginData,
	public IotGeometry
{
public:
	CotBezierCurve();
	~CotBezierCurve();
	

DECLARE_REGISTRY_RESOURCEID(IDR_OTBEZIERCURVE)


BEGIN_COM_MAP(CotBezierCurve)
	COM_INTERFACE_ENTRY(IotBezierCurve)
	COM_INTERFACE_ENTRY(IotSegment)
	COM_INTERFACE_ENTRY(IOriginData)
	COM_INTERFACE_ENTRY(IotGeometry)
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

	STDMETHOD(get_FirstCtrlPoint)(IotPoint** pVal);
	STDMETHOD(put_FirstCtrlPoint)(IotPoint* newVal);
	STDMETHOD(get_SecondCtrlPoint)(IotPoint** pVal);
	STDMETHOD(put_SecondCtrlPoint)(IotPoint* newVal);

	// IotSegment Methods
public:
	STDMETHOD(get_FromPoint)( IotPoint * * pVal);

	STDMETHOD(put_FromPoint)( IotPoint * newVal);

	STDMETHOD(get_ToPoint)( IotPoint * * pVal);

	STDMETHOD(put_ToPoint)( IotPoint * newVal);

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

private:
	//����BezierCurve��ָ��
	GEOMETRY::geom::BezierCurve *m_pGeometry;
	bool m_bAutoDestroy; 
};

OBJECT_ENTRY_AUTO(__uuidof(otBezierCurve), CotBezierCurve)
