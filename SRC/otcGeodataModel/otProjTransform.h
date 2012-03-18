// otProjTransform.h : CotProjTransform ������

#pragma once
#include "resource.h"       // ������

#include "otcGeodataModel.h"
#include "ProjTransform.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotProjTransform

class ATL_NO_VTABLE CotProjTransform :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotProjTransform, &CLSID_otProjTransform>,
	public IotProjTransform,
	public IOriginData
{
public:
	CotProjTransform();
	~CotProjTransform();


DECLARE_REGISTRY_RESOURCEID(IDR_OTPROJTRANSFORM)


BEGIN_COM_MAP(CotProjTransform)
	COM_INTERFACE_ENTRY(IotProjTransform)
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

	STDMETHOD(get_FromSpatialReference)(IotSpatialReference** pVal);
	STDMETHOD(get_ToSpatialReference)(IotSpatialReference** pVal);
	STDMETHOD(SetSpatialReference)(IotSpatialReference* from, IotSpatialReference* to);
	STDMETHOD(Transform)(LONG count, SAFEARRAY** inX, SAFEARRAY** inY, SAFEARRAY** outX, SAFEARRAY** outY);

	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);

private:
	//����ڲ�ָ���Ƿ���Ч
	bool CheckPointer();

private:
	Geodatabase::CProjTransformPtr* m_ppTrans;
	bool m_bAutoDestroy;
};

OBJECT_ENTRY_AUTO(__uuidof(otProjTransform), CotProjTransform)
