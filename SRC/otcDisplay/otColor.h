// otColor.h : CotColor ������

#pragma once
#include "resource.h"       // ������

#include "otcDisplay.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotColor

class ATL_NO_VTABLE CotColor :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotColor, &CLSID_otColor>,
	public IotColor
{
public:
	CotColor()
	{
		m_red =m_green =m_blue =0;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_OTCOLOR)


BEGIN_COM_MAP(CotColor)
	COM_INTERFACE_ENTRY(IotColor)
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

	STDMETHOD(get_Red)(LONG* pVal);
	STDMETHOD(put_Red)(LONG newVal);
	STDMETHOD(get_Green)(LONG* pVal);
	STDMETHOD(put_Green)(LONG newVal);
	STDMETHOD(get_Blue)(LONG* pVal);
	STDMETHOD(put_Blue)(LONG newVal);

private:
	long m_red;
	long m_green;
	long m_blue;
};

OBJECT_ENTRY_AUTO(__uuidof(otColor), CotColor)
