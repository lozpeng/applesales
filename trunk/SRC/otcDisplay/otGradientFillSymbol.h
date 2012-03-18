// otGradientFillSymbol.h : CotGradientFillSymbol ������

#pragma once
#include "resource.h"       // ������

#include "otcDisplay.h"
#include "GradientFillSymbol.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotGradientFillSymbol

class ATL_NO_VTABLE CotGradientFillSymbol :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotGradientFillSymbol, &CLSID_otGradientFillSymbol>,
	public IotGradientFillSymbol,
	public IOriginData
{
public:
	CotGradientFillSymbol();
	~CotGradientFillSymbol();
	

	DECLARE_REGISTRY_RESOURCEID(IDR_OTGRADIENTFILLSYMBOL)


	BEGIN_COM_MAP(CotGradientFillSymbol)
		COM_INTERFACE_ENTRY(IotGradientFillSymbol)
		COM_INTERFACE_ENTRY(IOriginData)
		COM_INTERFACE_ENTRY(IotFillSymbol)
		COM_INTERFACE_ENTRY(IotSymbol)
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

	// IotFillSymbol Methods
public:
	STDMETHOD(get_DrawOutLine)( VARIANT_BOOL * pVal);

	STDMETHOD(put_DrawOutLine)( VARIANT_BOOL newVal);
	
	STDMETHOD(get_OutLine)( IotSymbol * * pVal);
	
	STDMETHOD(put_OutLine)( IotSymbol * newVal);
	

	// IotSymbol Methods
public:
	STDMETHOD(get_Type)( otSymbolType * pVal);

	STDMETHOD(get_Unit)( otSymbolUnit * pVal);

	STDMETHOD(put_Unit)( otSymbolUnit newVal);

	STDMETHOD(get_FillColor)( IotColor * * pVal);

	STDMETHOD(put_FillColor)( IotColor * newVal);

	//IotGradientFillSymbol Methods
public:
	STDMETHOD(get_BeginColor)( IotColor** pVal );

	STDMETHOD(put_BeginColor)( IotColor* pVal );
	
	STDMETHOD(get_EndColor)(  IotColor** pVal );
	
	STDMETHOD(put_EndColor)(  IotColor* pVal );
	
	STDMETHOD(get_SegmentCounts)( LONG * pVal );
	
	STDMETHOD(put_SegmentCounts)( LONG pVal );
	
	STDMETHOD(get_Percent)( LONG * pVal);
	
	STDMETHOD(put_Percent)( LONG pVal);
	
	STDMETHOD(get_Angle)( FLOAT * pVal );
	
	STDMETHOD(put_Angle)( FLOAT pVal );
	
	STDMETHOD(get_GradientFillType)( otGradientFillType * pVal );
	
	STDMETHOD(put_GradientFillType)( otGradientFillType pVal );
	
private:
	bool CheckPointer();
private:
	Display::ISymbolPtr *m_ppSymbol;
	Display::CGradientFillSymbol *m_pFillSymbol;

	bool m_bAutoDestroy;

};

OBJECT_ENTRY_AUTO(__uuidof(otGradientFillSymbol), CotGradientFillSymbol)
