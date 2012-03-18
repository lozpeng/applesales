// otRasterDataset.h : CotRasterDataset ������

#pragma once
#include "resource.h"       // ������

#include "otcGeodataModel.h"
#include "IRasterDataset.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotRasterDataset

class ATL_NO_VTABLE CotRasterDataset :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotRasterDataset, &CLSID_otRasterDataset>,
	public IotRasterDataset,
	public IOriginData
{
public:
	CotRasterDataset();
	~CotRasterDataset();


DECLARE_REGISTRY_RESOURCEID(IDR_OTRASTERDATASET)


BEGIN_COM_MAP(CotRasterDataset)
	COM_INTERFACE_ENTRY(IotRasterDataset)
	COM_INTERFACE_ENTRY(IotDataObject)
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

	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);


	// IotDataObject Methods
public:
	STDMETHOD(GetType)(otDataType * type);

	STDMETHOD(GetName)( BSTR * name);

	STDMETHOD(GetExtent)( IotEnvelope * * envelope);

	STDMETHOD(get_Workspace)( IotWorkspace * * pVal);

private:
	//����ڲ�ָ���Ƿ���Ч
	bool CheckPointer();

public:
	STDMETHOD(get_Writable)(VARIANT_BOOL* pVal);
	STDMETHOD(get_ChannelCount)(LONG* pVal);
	STDMETHOD(get_Width)(LONG* pVal);
	STDMETHOD(get_Height)(LONG* pVal);
	STDMETHOD(get_Projection)(BSTR* pVal);
	STDMETHOD(put_Projection)(BSTR newVal);
	STDMETHOD(get_HasPyramid)(VARIANT_BOOL* pVal);
	STDMETHOD(CreateRasterBlock)(LONG BandIndex,LONG width, LONG height,IotRasterBlock **ret);
	STDMETHOD(ReadData)(LONG BandIndex, LONG row, LONG col, IotRasterBlock* RasterBlock);
	STDMETHOD(get_SpatialReference)(IotSpatialReference** pVal);

private:

	Geodatabase::IRasterDatasetPtr *m_ppRasterDataset;
	bool m_bAutoDestroy;

	//�ڲ��ռ�ο�ϵָ��
	IotSpatialReference *m_pSR;
};

OBJECT_ENTRY_AUTO(__uuidof(otRasterDataset), CotRasterDataset)
