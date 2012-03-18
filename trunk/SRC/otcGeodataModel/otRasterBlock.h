// otRasterBlock.h : CotRasterBlock ������

#pragma once
#include "resource.h"       // ������

#include "otcGeodataModel.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotRasterBlock

class ATL_NO_VTABLE CotRasterBlock :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotRasterBlock, &CLSID_otRasterBlock>,
	public IotRasterBlock
{
public:
	CotRasterBlock();

	~CotRasterBlock();


DECLARE_REGISTRY_RESOURCEID(IDR_OTRASTERBLOCK)


BEGIN_COM_MAP(CotRasterBlock)
	COM_INTERFACE_ENTRY(IotRasterBlock)
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

	STDMETHOD(get_DataType)(otBandType* pVal);
	STDMETHOD(put_DataType)(otBandType newVal);
	STDMETHOD(get_Width)(LONG* pVal);
	STDMETHOD(put_Width)(LONG newVal);
	STDMETHOD(get_Height)(LONG* pVal);
	STDMETHOD(put_Height)(LONG newVal);
	STDMETHOD(GetValue)(LONG X, LONG Y, VARIANT* value);
	STDMETHOD(get_SafeArray)(VARIANT* pVal);
	STDMETHOD(put_SafeArray)(VARIANT newVal);

private:

	//��ȫ����
	CComSafeArray<VARIANT> m_sa;

	long m_lwidth;
	long m_lheight;

	otBandType m_type;

};

OBJECT_ENTRY_AUTO(__uuidof(otRasterBlock), CotRasterBlock)
