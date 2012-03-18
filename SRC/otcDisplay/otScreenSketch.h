// otScreenSketch.h : CotScreenSketch ������

#pragma once
#include "resource.h"       // ������

#include "otcDisplay.h"
#include "ScreenSketch.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotScreenSketch

class ATL_NO_VTABLE CotScreenSketch :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotScreenSketch, &CLSID_otScreenSketch>,
	public IotScreenSketch
{
public:
	CotScreenSketch();
	~CotScreenSketch();


DECLARE_REGISTRY_RESOURCEID(IDR_OTSCREENSKETCH)


BEGIN_COM_MAP(CotScreenSketch)
	COM_INTERFACE_ENTRY(IotScreenSketch)
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

	STDMETHOD(Create)(otGeometryType type);
	STDMETHOD(put_ScreenCanvas)(IotCanvas* newVal);
	STDMETHOD(put_Symbol)(IotSymbol* newVal);
	STDMETHOD(Start)(void);
	STDMETHOD(Stop)(IotGeometry** retGeometry);
	STDMETHOD(AddPoint)(IotPoint* point);
	STDMETHOD(SetMousePoint)(IotPoint* point);

private:
	Display::CScreenSketch *m_pSketch;
public:
	STDMETHOD(SetCircleCenter)(IotPoint* point);
	STDMETHOD(SetEllipseTopLeft)(IotPoint* point);
	STDMETHOD(SetRectTopLeft)(IotPoint* point);
};

OBJECT_ENTRY_AUTO(__uuidof(otScreenSketch), CotScreenSketch)
