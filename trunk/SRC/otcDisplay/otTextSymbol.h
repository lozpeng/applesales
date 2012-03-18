// otTextSymbol.h : CotTextSymbol ������

#pragma once
#include "resource.h"       // ������

#include "otcDisplay.h"
#include  "TextSymbol.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CotTextSymbol

class ATL_NO_VTABLE CotTextSymbol :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CotTextSymbol, &CLSID_otTextSymbol>,
	public IotTextSymbol,
	public IOriginData
{
public:
	CotTextSymbol();
	~CotTextSymbol();


DECLARE_REGISTRY_RESOURCEID(IDR_OTTEXTSYMBOL)


BEGIN_COM_MAP(CotTextSymbol)
	COM_INTERFACE_ENTRY(IotTextSymbol)
	COM_INTERFACE_ENTRY(IOriginData)
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

	STDMETHOD(get_Size)(DOUBLE* pVal);
	STDMETHOD(put_Size)(DOUBLE newVal);
	STDMETHOD(get_Angle)(DOUBLE* pVal);
	STDMETHOD(put_Angle)(DOUBLE newVal);
	STDMETHOD(get_TextColor)(IotColor** pVal);
	STDMETHOD(put_TextColor)(IotColor* newVal);
	STDMETHOD(get_Font)(IFontDisp** pVal);
	STDMETHOD(put_Font)(IFontDisp* newVal);

	// IOriginData Methods
public:
	STDMETHOD(get_OriginData)(long * pVal);

	STDMETHOD(put_OriginData)(long pVal);

	STDMETHOD(get_AutoDestroy)(long * pVal);

	STDMETHOD(put_AutoDestroy)(long pVal);


	// IotSymbol Methods
public:
	STDMETHOD(get_Type)( otSymbolType * pVal);

	STDMETHOD(get_Unit)( otSymbolUnit * pVal);

	STDMETHOD(put_Unit)( otSymbolUnit newVal);
private:
	bool CheckPointer();
private:
	Display::ISymbolPtr *m_ppSymbol;
	Display::CTextSymbol *m_pTextSymbol;

	bool m_bAutoDestroy;
};

OBJECT_ENTRY_AUTO(__uuidof(otTextSymbol), CotTextSymbol)
