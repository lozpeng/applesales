// otFeature.h : CotFeature 的声明

#pragma once
#include "resource.h"       // 主符号

#include "otcGeodataModel.h"
#include "feature.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
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
	//获取记录所在的表对象
	STDMETHOD(get_Table)( IotTable** pVal);

	//字段数目
	STDMETHOD(get_FieldCount)( LONG* pVal);

	//要素ID
	STDMETHOD(get_ID)( LONG * pVal);

	//获得某个字段的描述
	STDMETHOD(get_Field)( LONG index,  IotField * * pVal);

	//获得字段值
	STDMETHOD(get_Value)( LONG index,  VARIANT * pVal);

	//设置字段值
	STDMETHOD(put_Value)( LONG index,  VARIANT newVal);


	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);

private:
	//检查内部指针是否有效
	bool CheckPointer();

	//将VARIANT转换成fval
	static void ConvVar2Fval(VARIANT &var,Geodatabase::FieldValue &fval);

	//将FieldValue转换成var
	static void ConFval2Var(Geodatabase::FieldValue &fval,VARIANT &var);
private:

	//存放智能指针的指针
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
