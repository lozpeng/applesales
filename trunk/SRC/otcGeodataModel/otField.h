// otField.h : CotField ������

#pragma once
#include "resource.h"       // ������

#include "otcGeodataModel.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotField

class ATL_NO_VTABLE CotField :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotField, &CLSID_otField>,
	public IotField
{
public:
	CotField()
	{

		m_length =0;
		m_precision =0;
		m_type =FTYPE_UNKNOWN;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_OTFIELD)


BEGIN_COM_MAP(CotField)
	COM_INTERFACE_ENTRY(IotField)
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

	STDMETHOD(get_Name)(BSTR* pVal);
	STDMETHOD(put_Name)(BSTR newVal);
	STDMETHOD(get_Length)(LONG* pVal);
	STDMETHOD(put_Length)(LONG newVal);
	STDMETHOD(get_Type)(otFieldType* pVal);
	STDMETHOD(put_Type)(otFieldType newVal);
	STDMETHOD(get_Precision)(LONG* pVal);
	STDMETHOD(put_Precision)(LONG newVal);

private:

	_bstr_t m_name;

	long m_length;

	long m_precision;

	otFieldType m_type;
};

OBJECT_ENTRY_AUTO(__uuidof(otField), CotField)
