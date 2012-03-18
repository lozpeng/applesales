// otFeature.h : CotFeature ������

#pragma once
#include "resource.h"       // ������

#include "otcGeodataModel.h"
#include "feature.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotFeature

class ATL_NO_VTABLE CotFeature :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotFeature, &CLSID_otFeature>,
	public IotFeature,
	public IOriginData

{
public:
	CotFeature();
	virtual ~CotFeature();

	DECLARE_REGISTRY_RESOURCEID(IDR_OTFEATURE)


	BEGIN_COM_MAP(CotFeature)
		COM_INTERFACE_ENTRY(IotFeature)
        COM_INTERFACE_ENTRY(IotRow)
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


	// IotRow Methods
public:
	//��ȡ��¼���ڵı����
	STDMETHOD(get_Table)( IotTable** pVal);

	//�ֶ���Ŀ
	STDMETHOD(get_FieldCount)( LONG* pVal);

	//Ҫ��ID
	STDMETHOD(get_ID)( LONG * pVal);

	//���ĳ���ֶε�����
	STDMETHOD(get_Field)( LONG index,  IotField * * pVal);

	//����ֶ�ֵ
	STDMETHOD(get_Value)( LONG index,  VARIANT * pVal);

	//�����ֶ�ֵ
	STDMETHOD(put_Value)( LONG index,  VARIANT newVal);


	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);

private:
	//����ڲ�ָ���Ƿ���Ч
	bool CheckPointer();

	//��VARIANTת����fval
	static void ConvVar2Fval(VARIANT &var,Geodatabase::FieldValue &fval);

	//��FieldValueת����var
	static void ConFval2Var(Geodatabase::FieldValue &fval,VARIANT &var);
private:

	//�������ָ���ָ��
	Geodatabase::CFeaturePtr *m_ppFeature;
	bool m_bAutoDestroy;



public:
	STDMETHOD(get_Shape)(IotGeometry** pVal);
	STDMETHOD(put_Shape)(IotGeometry* newVal);
	STDMETHOD(get_ShapeClone)(IotGeometry** pVal);
	STDMETHOD(Update)(void);
	STDMETHOD(Delete)(void);
};

OBJECT_ENTRY_AUTO(__uuidof(otFeature), CotFeature)
