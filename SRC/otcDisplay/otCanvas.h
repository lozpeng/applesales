// otCanvas.h : CotCanvas ������

#pragma once
#include "resource.h"       // ������

#include "otcDisplay.h"
#include "IDisplay.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif


//CotCanvas��IDislay��һ���ģ�����ΪotCanvasΪ�˱���Display������ͻ
// CotCanvas

class ATL_NO_VTABLE CotCanvas :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotCanvas, &CLSID_otCanvas>,
	public IotCanvas,
	public IOriginData
{
public:
	CotCanvas();
	~CotCanvas();


	DECLARE_REGISTRY_RESOURCEID(IDR_OTCANVAS)


	BEGIN_COM_MAP(CotCanvas)
		COM_INTERFACE_ENTRY(IotCanvas)
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


	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);

private:
	bool CheckPointer();
private:
	Display::IDisplayPtr *m_ppDisplay;

	bool m_bAutoDestroy;

};

OBJECT_ENTRY_AUTO(__uuidof(otCanvas), CotCanvas)