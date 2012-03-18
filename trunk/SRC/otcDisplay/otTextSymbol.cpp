// otTextSymbol.cpp : CotTextSymbol ��ʵ��

#include "stdafx.h"
#include "otTextSymbol.h"


// CotTextSymbol
CotTextSymbol::CotTextSymbol()
{
	//����һ���µ����ַ���
	m_pTextSymbol =new Display::CTextSymbol();

	m_ppSymbol =new Display::ISymbolPtr(m_pTextSymbol);

	m_bAutoDestroy =true;
}

CotTextSymbol::~CotTextSymbol()
{
	if(m_ppSymbol && m_bAutoDestroy)
	{
		delete m_ppSymbol;
	}
}



bool CotTextSymbol::CheckPointer()
{
	if((!m_ppSymbol) || (!m_pTextSymbol))
	{
		return false;
	}
	if(!(*m_ppSymbol))
	{

		return false;
	}
	return true;
}

STDMETHODIMP CotTextSymbol::get_Size(DOUBLE* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pTextSymbol->GetTextSize();

	return S_OK;
}

STDMETHODIMP CotTextSymbol::put_Size(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pTextSymbol->SetTextSize(newVal);

	return S_OK;
}

STDMETHODIMP CotTextSymbol::get_Angle(DOUBLE* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pTextSymbol->GetAngle();

	return S_OK;
}

STDMETHODIMP CotTextSymbol::put_Angle(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pTextSymbol->SetAngle(newVal);

	return S_OK;
}

STDMETHODIMP CotTextSymbol::get_TextColor(IotColor** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	//��÷�����ɫ
	unsigned long color =m_pTextSymbol->GetTextColor();

	long red,green,blue;
	red =GetRValue(color);
	green =GetGValue(color);
	blue =GetBValue(color);

	//����һ����ɫ����
	CoCreateInstance(CLSID_otColor,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotColor),(void**)pVal);
	(*pVal)->put_Red(red);
	(*pVal)->put_Green(green);
	(*pVal)->put_Blue(blue);	

	return S_OK;
}

STDMETHODIMP CotTextSymbol::put_TextColor(IotColor* newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	long red,green,blue;
	newVal->get_Red(&red);
	newVal->get_Blue(&blue);
	newVal->get_Green(&green);

	m_pTextSymbol->SetTextColor(RGB(red,green,blue));
	return S_OK;
}

STDMETHODIMP CotTextSymbol::get_Font(IFontDisp** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
    

	return S_OK;
}

STDMETHODIMP CotTextSymbol::put_Font(IFontDisp* newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
    if(!newVal)
	{
		return E_FAIL;
	}
	CComPtr<IFont> pFont;
	newVal->QueryInterface(IID_IFont, (void**)&pFont);

	//�ȵõ����ŵ�����
	DisFont font =m_pTextSymbol->GetTextFont();

	HFONT hfont =NULL;
	pFont->get_hFont(&hfont);

	//������������
	LOGFONT logfont;
	::GetObject(hfont,sizeof(LOGFONT),&logfont);

	font.lfWidth =logfont.lfWidth;
	font.lfHeight =logfont.lfHeight;
	font.lfWeight =logfont.lfWeight;
	font.lfCharSet =logfont.lfCharSet;
	font.lfItalic =logfont.lfItalic;
	font.lfUnderline =logfont.lfUnderline;
	font.lfStrikeOut =logfont.lfStrikeOut;
	font.lfClipPrecision =logfont.lfClipPrecision;
	font.lfEscapement =logfont.lfEscapement;
	font.lfOrientation =logfont.lfOrientation;
	font.lfOutPrecision =logfont.lfOutPrecision;
	font.lfPitchAndFamily =logfont.lfPitchAndFamily;
	font.lfQuality =logfont.lfQuality;

	_bstr_t str =logfont.lfFaceName;

	strcpy(font.lfFaceName,(const char*)str);

	//���÷�������
	m_pTextSymbol->SetTextFont(font);





	return S_OK;
}




/*****************************************************************************
* ʵ��IOriginData�ӿ�
******************************************************************************/
STDMETHODIMP CotTextSymbol::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppSymbol;
	return S_OK;
}

STDMETHODIMP CotTextSymbol::put_OriginData(long  pVal)
{

	if(m_ppSymbol && m_bAutoDestroy)
	{
		delete m_ppSymbol;
		m_pTextSymbol =NULL;
	}

	Display::ISymbolPtr *ppSymbol =(Display::ISymbolPtr*)pVal;

	//��Symbolָ��ת������Ӧ���ŵ�ָ��
	m_pTextSymbol =dynamic_cast<Display::CTextSymbol*>(ppSymbol->get());

	if(!m_pTextSymbol)
	{
		m_ppSymbol =NULL;
	}
	else
	{
		m_ppSymbol =ppSymbol;
	}

	return S_OK;
}

STDMETHODIMP CotTextSymbol::get_AutoDestroy(long * pVal)
{

	if(m_bAutoDestroy)
	{
		*pVal =TRUE;
	}
	else
	{
		*pVal =FALSE;
	}
	return S_OK;
}

STDMETHODIMP CotTextSymbol::put_AutoDestroy(long  pVal)
{

	if(pVal)
	{
		m_bAutoDestroy =true;
	}
	else
	{
		m_bAutoDestroy =false;
	}
	return S_OK;
}

/*****************************************************************************
* ʵ��IotSymbol�ӿ�
******************************************************************************/

STDMETHODIMP CotTextSymbol::get_Type(otSymbolType *pVal)
{
	*pVal = otTEXT_SYMBOL;

	return S_OK;
}

STDMETHODIMP CotTextSymbol::get_Unit(otSymbolUnit *pVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =CInterfaceConvert::ConvertSymbolUnit(m_pTextSymbol->GetUnit());

	return S_OK;
}

STDMETHODIMP CotTextSymbol::put_Unit(otSymbolUnit newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pTextSymbol->SetUnit(CInterfaceConvert::ConvertSymbolUnit(newVal));
	return S_OK;
}