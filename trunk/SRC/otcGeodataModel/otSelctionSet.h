// otSelectionSet.h : CotSelctionSet ������

#pragma once
#include "resource.h"       // ������

#include "otcGeodataModel.h"
#include "ISelectionSet.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotSelctionSet

class ATL_NO_VTABLE CotSelctionSet :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotSelctionSet, &CLSID_otSelectionSet>,
	public IotSelectionSet,
	public IOriginData
{
public:
	CotSelctionSet();
	~CotSelctionSet();


DECLARE_REGISTRY_RESOURCEID(IDR_OTSELCTIONSET)


BEGIN_COM_MAP(CotSelctionSet)
	COM_INTERFACE_ENTRY(IotSelectionSet)
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

	STDMETHOD(get_Count)(LONG* pVal);
	STDMETHOD(IsEOF)(VARIANT_BOOL* ret);
	STDMETHOD(ResetIndex)(void);
	STDMETHOD(NextID)(LONG* id);
	STDMETHOD(Add)(LONG id);
	STDMETHOD(get_Table)(IotTable** pVal);

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
	Geodatabase::ISelctionSetPtr* m_ppSel;
	bool m_bAutoDestroy;
};

OBJECT_ENTRY_AUTO(__uuidof(otSelectionSet), CotSelctionSet)
