// otWorkspace.h : CotWorkspace ������

#pragma once
#include "resource.h"       // ������

#include "otcGeodataModel.h"
#include "IWorkspace.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotWorkspace

class ATL_NO_VTABLE CotWorkspace :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotWorkspace, &CLSID_otWorkspace>,
	public IotWorkspace,
	public IOriginData
{
public:
	CotWorkspace();


	DECLARE_REGISTRY_RESOURCEID(IDR_OTWORKSPACE)


	BEGIN_COM_MAP(CotWorkspace)
		COM_INTERFACE_ENTRY(IotWorkspace)
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
	Geodatabase::IWorkspace *m_pWorkspace;

public:
	//�õ������ռ�����
	STDMETHOD(get_Type)(otWorkspaceType* pVal);

	//�õ������ռ�·��
	STDMETHOD(get_Path)(BSTR* pVal);

	//��ʸ������Դ
	STDMETHOD(OpenFeatureClass)(BSTR filename, IotFeatureClass** FeatureClass);
	STDMETHOD(IsEditing)(VARIANT_BOOL* bret);
	STDMETHOD(StartEdit)(void);
	STDMETHOD(StopEdit)(VARIANT_BOOL save);
	STDMETHOD(StartEditOperation)(void);
	STDMETHOD(StopEditOperation)(void);
	STDMETHOD(UndoEdit)(void);
	STDMETHOD(RedoEdit)(void);
	STDMETHOD(CanUndo)(VARIANT_BOOL* bret);
	STDMETHOD(CanRedo)(VARIANT_BOOL* ret);

	//��դ������Դ
	STDMETHOD(OpenRasterDataset)(BSTR filename, VARIANT_BOOL ReadOnly, IotRasterDataset** ret);
	STDMETHOD(CreateFeatureClass)(BSTR filename, IotEnvelope* extent, BSTR projWkt, otGeometryType FeatureType, VARIANT_BOOL hasZ, VARIANT_BOOL hasM, LONG numField, SAFEARRAY** fields, IotFeatureClass** retFeatureClass);
};

OBJECT_ENTRY_AUTO(__uuidof(otWorkspace), CotWorkspace)
