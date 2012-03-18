// otShpWF.h : CotShpWF ������

#pragma once
#include "resource.h"       // ������

#include "otcGeodataModel.h"
#include "ShapefileWorkspaceFactory.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotShpWF

class ATL_NO_VTABLE CotShpWF :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotShpWF, &CLSID_otShpWF>,
	public IotShpWF
{
public:
	CotShpWF();


DECLARE_REGISTRY_RESOURCEID(IDR_OTSHPWF)


BEGIN_COM_MAP(CotShpWF)
	COM_INTERFACE_ENTRY(IotShpWF)
	COM_INTERFACE_ENTRY(IotWorkspaceFactory)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}


	// IotWorkspaceFactory Methods
public:
	STDMETHOD(OpenFromFile)( BSTR filename,  IotWorkspace **workspace);
	STDMETHOD(OpenFolder)(BSTR name, IotWorkspace** retWorkspace);

public:
	CShapefileWorkspaceFactory *m_pFactory;



	
};

OBJECT_ENTRY_AUTO(__uuidof(otShpWF), CotShpWF)
