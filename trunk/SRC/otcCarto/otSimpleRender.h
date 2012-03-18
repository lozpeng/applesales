// otSimpleRender.h : CotSimpleRender ������

#pragma once
#include "resource.h"       // ������

#include "otcCarto.h"
#include "IRender.h"
#include "SimpleRender.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotSimpleRender

class ATL_NO_VTABLE CotSimpleRender :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotSimpleRender, &CLSID_otSimpleRender>,
	public IotSimpleRender,
	public IOriginData
{
public:
	CotSimpleRender();
	~CotSimpleRender();


	DECLARE_REGISTRY_RESOURCEID(IDR_OTSIMPLERENDER)


	BEGIN_COM_MAP(CotSimpleRender)
		COM_INTERFACE_ENTRY(IotSimpleRender)
		COM_INTERFACE_ENTRY(IOriginData)
		COM_INTERFACE_ENTRY(IotFeatureRender)
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

	STDMETHOD(get_Symbol)(IotSymbol** pVal);
	STDMETHOD(put_Symbol)(IotSymbol* newVal);

	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);



	// IotFeatureRender Methods
public:
	STDMETHOD(get_RenderType)( otFeatureRenderType * pVal);

private:
	bool CheckPointer();
private:
	Carto::CSimpleRenderPtr *m_ppRender;
	bool m_bAutoDestroy;


};

OBJECT_ENTRY_AUTO(__uuidof(otSimpleRender), CotSimpleRender)
