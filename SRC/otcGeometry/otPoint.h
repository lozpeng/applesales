// otPoint.h : CotPoint 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CotPoint

class ATL_NO_VTABLE CotPoint :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotPoint, &CLSID_otPoint>,
	public IotPoint,
	public IDispatchImpl<IotGeometry, &__uuidof(IotGeometry), &LIBID_otcGeometry, /* wMajor = */ 1, /* wMinor = */ 0>
{
public:
	CotPoint();


	DECLARE_REGISTRY_RESOURCEID(IDR_OTPOINT)


	BEGIN_COM_MAP(CotPoint)
		COM_INTERFACE_ENTRY(IotPoint)
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

	STDMETHOD(get_X)(DOUBLE* pVal);
	STDMETHOD(put_X)(DOUBLE newVal);
	STDMETHOD(get_Y)(DOUBLE* pVal);
	STDMETHOD(put_Y)(DOUBLE newVal);
	STDMETHOD(get_Z)(DOUBLE* pVal);
	STDMETHOD(put_Z)(DOUBLE newVal);
	STDMETHOD(get_M)(DOUBLE* pVal);
	STDMETHOD(put_M)(DOUBLE newVal);



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
	double m_x;
	double m_y;
	double m_z;
	double m_m;
	bool   m_bz;
	bool   m_bm;
};

//声明智能指针
_COM_SMARTPTR_TYPEDEF(IotPoint, __uuidof(IotPoint));

OBJECT_ENTRY_AUTO(__uuidof(otPoint), CotPoint)
