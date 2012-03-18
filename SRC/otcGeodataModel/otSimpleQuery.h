// otSimpleQuery.h : CotSimpleQuery ������

#pragma once
#include "resource.h"       // ������

#include "otcGeodataModel.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotSimpleQuery

class ATL_NO_VTABLE CotSimpleQuery :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotSimpleQuery, &CLSID_otSimpleQuery>,
	public IotSimpleQuery
{
public:
	CotSimpleQuery();


DECLARE_REGISTRY_RESOURCEID(IDR_OTSIMPLEQUERY)


BEGIN_COM_MAP(CotSimpleQuery)
	COM_INTERFACE_ENTRY(IotSimpleQuery)
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

	STDMETHOD(get_Fields)(BSTR* pVal);
	STDMETHOD(put_Fields)(BSTR newVal);
	STDMETHOD(get_WhereString)(BSTR* pVal);
	STDMETHOD(put_WhereString)(BSTR newVal);
	STDMETHOD(AddField)(BSTR fieldname);

private:
	_bstr_t  m_strFields;

	_bstr_t  m_strWhere;
};

OBJECT_ENTRY_AUTO(__uuidof(otSimpleQuery), CotSimpleQuery)
