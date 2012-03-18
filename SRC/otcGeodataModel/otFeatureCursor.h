// otFeatureCursor.h : CotFeatureCursor ������

#pragma once
#include "resource.h"       // ������

#include "otcGeodataModel.h"
#include "IFeatureCursor.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotFeatureCursor

class ATL_NO_VTABLE CotFeatureCursor :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotFeatureCursor, &CLSID_otFeatureCursor>,
	public IotFeatureCursor,
	public IOriginData
{
public:
	CotFeatureCursor();

    virtual ~CotFeatureCursor();

	DECLARE_REGISTRY_RESOURCEID(IDR_OTFEATURECURSOR)


	BEGIN_COM_MAP(CotFeatureCursor)
		COM_INTERFACE_ENTRY(IotFeatureCursor)
		COM_INTERFACE_ENTRY(IOriginData)
		COM_INTERFACE_ENTRY(IotCursor)
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

	STDMETHOD(NextFeature)(IotFeature** retFeature);

	// IotCursor Methods
public:
	STDMETHOD(get_Table)( IotTable * * pVal);

	STDMETHOD(NextRow)( IotRow * * row);

	STDMETHOD(IsEOF)( VARIANT_BOOL * ret);


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
	Geodatabase::IFeatureCursorPtr* m_ppCursor;
	bool m_bAutoDestroy;

};

OBJECT_ENTRY_AUTO(__uuidof(otFeatureCursor), CotFeatureCursor)
