// otEnvelope.h : otEnvelope ������

#pragma once
#include "resource.h"       // ������

#include "otcGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// otEnvelope

class ATL_NO_VTABLE otEnvelope :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<otEnvelope, &CLSID_otEnvelope>,
	public IotEnvelope
{
public:
	otEnvelope();


DECLARE_REGISTRY_RESOURCEID(IDR_ENVELOPE)


BEGIN_COM_MAP(otEnvelope)
	COM_INTERFACE_ENTRY(IotEnvelope)
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

	STDMETHOD(get_MinX)(double* pVal);
	STDMETHOD(put_MinX)(double newVal);
	STDMETHOD(get_MinY)(double* pVal);
	STDMETHOD(put_MinY)(double newVal);
	STDMETHOD(get_MaxX)(double* pVal);
	STDMETHOD(put_MaxX)(double newVal);
	STDMETHOD(get_MaxY)(double* pVal);
	STDMETHOD(put_MaxY)(double newVal);
private:
	double  m_minx;
	double  m_miny;
	double  m_maxx;
	double  m_maxy;


};

OBJECT_ENTRY_AUTO(__uuidof(otEnvelope), otEnvelope)
