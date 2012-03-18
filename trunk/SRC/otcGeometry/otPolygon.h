// otPolygon.h : CotPolygon 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotPolygon

class ATL_NO_VTABLE CotPolygon :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotPolygon, &CLSID_otPolygon>,
	public IotPolygon,
	public IOriginData,
	public IotGeometry,
	public IotTransform
{
public:
	CotPolygon();
	virtual ~CotPolygon();


	DECLARE_REGISTRY_RESOURCEID(IDR_OTPOLYGON)


	BEGIN_COM_MAP(CotPolygon)
		COM_INTERFACE_ENTRY(IotPolygon)
		COM_INTERFACE_ENTRY(IOriginData)
		COM_INTERFACE_ENTRY(IotGeometry)
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

	//内环的数目
	STDMETHOD(get_InteriorRingCount)(LONG* pVal);

	//面积
	STDMETHOD(get_Area)(DOUBLE* pVal);

	//外环
	STDMETHOD(get_ExteriorRing)(IotLineRing** pVal);
	STDMETHOD(put_ExteriorRing)(IotLineRing* newVal);

	//内环
	STDMETHOD(get_InteriorRing)(LONG index, IotLineRing** pVal);
	STDMETHOD(put_InteriorRing)(LONG index, IotLineRing* newVal);

	//添加内环
	STDMETHOD(AddInteriorRing)(IotLineRing* ring);

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

	// IotTransform Methods
public:
	STDMETHOD(Move)( DOUBLE dx,  DOUBLE dy);

	STDMETHOD(Scale)( IotPoint * Origin,  DOUBLE dx,  DOUBLE dy);

	STDMETHOD(Rotate)( IotPoint * Origin,  DOUBLE angle);

private:
	//保存Polygon的指针
	GEOMETRY::geom::Polygon *m_pGeometry;
	bool m_bAutoDestroy;  





	
};

OBJECT_ENTRY_AUTO(__uuidof(otPolygon), CotPolygon)
