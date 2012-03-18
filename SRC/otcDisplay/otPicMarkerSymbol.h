// otPicMarkerSymbol.h : CotPicMarkerSymbol ������

#pragma once
#include "resource.h"       // ������

#include "otcDisplay.h"
#include "PicMarkerSymbol.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotPicMarkerSymbol

class ATL_NO_VTABLE CotPicMarkerSymbol :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotPicMarkerSymbol, &CLSID_otPicMarkerSymbol>,
	public IotPicMarkerSymbol,
	public IOriginData
{
public:
	CotPicMarkerSymbol();
	~CotPicMarkerSymbol();


	DECLARE_REGISTRY_RESOURCEID(IDR_OTPICMARKERSYMBOL)


	BEGIN_COM_MAP(CotPicMarkerSymbol)
		COM_INTERFACE_ENTRY(IotPicMarkerSymbol)
		COM_INTERFACE_ENTRY(IOriginData)
		COM_INTERFACE_ENTRY(IotSymbol)
		COM_INTERFACE_ENTRY(IotMarkerSymbol)
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


	// IotMarkerSymbol Methods
public:
	STDMETHOD(get_Color)( IotColor * * pVal);

	STDMETHOD(put_Color)( IotColor * newVal);

	STDMETHOD(get_OffsetX)( DOUBLE * pVal);

	STDMETHOD(put_OffsetX)( DOUBLE newVal);

	STDMETHOD(get_OffsetY)( DOUBLE * pVal);

	STDMETHOD(put_OffsetY)( DOUBLE newVal);

	STDMETHOD(get_Angle)( DOUBLE * pVal);

	STDMETHOD(put_Angle)( DOUBLE newVal);

	STDMETHOD(get_Size)( DOUBLE * pVal);

	STDMETHOD(put_Size)( DOUBLE newVal);


	// IotSymbol Methods
public:
	STDMETHOD(get_Type)( otSymbolType * pVal);

	STDMETHOD(get_Unit)( otSymbolUnit * pVal);

	STDMETHOD(put_Unit)( otSymbolUnit newVal);

	//IotPicMarkerSymbol
public:
	STDMETHOD(get_PictureFile)(BSTR* pVal);
	STDMETHOD(put_PictureFile)(BSTR newVal);
	STDMETHOD(get_TransparentColor)(IotColor** pVal);
	STDMETHOD(put_TransparentColor)(IotColor* newVal);
	STDMETHOD(get_BackgroundColor)(IotColor** pVal);
	STDMETHOD(put_BackgroundColor)(IotColor* newVal);
    
private:
	bool CheckPointer();
private:
	Display::ISymbolPtr *m_ppSymbol;
	Display::CPicMarkerSymbol *m_pMarkerSymbol;

	bool m_bAutoDestroy;

	
};

OBJECT_ENTRY_AUTO(__uuidof(otPicMarkerSymbol), CotPicMarkerSymbol)
