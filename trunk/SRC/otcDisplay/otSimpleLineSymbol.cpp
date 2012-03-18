// otSimpleLineSymbol.cpp : CotSimpleLineSymbol ��ʵ��

#include "stdafx.h"
#include "otSimpleLineSymbol.h"


// CotSimpleLineSymbol
CotSimpleLineSymbol::CotSimpleLineSymbol()
{
	//����һ���µ��߷���
	m_pLineSymbol =new Display::CSimpleLineSymbol();

	m_ppSymbol =new Display::ISymbolPtr(m_pLineSymbol);

	m_bAutoDestroy =true;
}

CotSimpleLineSymbol::~CotSimpleLineSymbol()
{
	if(m_ppSymbol && m_bAutoDestroy)
	{
		delete m_ppSymbol;
	}
}

STDMETHODIMP CotSimpleLineSymbol::get_LineStyle(otSimpleLineStyle* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =(otSimpleLineStyle)m_pLineSymbol->GetLineStyle();

	return S_OK;
}

STDMETHODIMP CotSimpleLineSymbol::put_LineStyle(otSimpleLineStyle newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pLineSymbol->SetLineStyle(SIMLINE_STYLE(newVal));

	return S_OK;
}

bool CotSimpleLineSymbol::CheckPointer()
{
	if((!m_ppSymbol) || (!m_pLineSymbol))
	{
		return false;
	}
	if(!(*m_ppSymbol))
	{

		return false;
	}
	return true;
}


/*****************************************************************************
* ʵ��IOriginData�ӿ�
******************************************************************************/
STDMETHODIMP CotSimpleLineSymbol::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppSymbol;
	return S_OK;
}

STDMETHODIMP CotSimpleLineSymbol::put_OriginData(long  pVal)
{

	if(m_ppSymbol && m_bAutoDestroy)
	{
		delete m_ppSymbol;
		m_pLineSymbol =NULL;
	}

	Display::ISymbolPtr *ppSymbol =(Display::ISymbolPtr*)pVal;

	//��Symbolָ��ת������Ӧ���ŵ�ָ��
	m_pLineSymbol =dynamic_cast<Display::CSimpleLineSymbol*>(ppSymbol->get());

	if(!m_pLineSymbol)
	{
		m_ppSymbol =NULL;
	}
	else
	{
		m_ppSymbol =ppSymbol;
	}

	return S_OK;
}

STDMETHODIMP CotSimpleLineSymbol::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotSimpleLineSymbol::put_AutoDestroy(long  pVal)
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

STDMETHODIMP CotSimpleLineSymbol::get_Type(otSymbolType *pVal)
{
	*pVal = otSIMPLE_LINE_SYMBOL;

	return S_OK;
}

STDMETHODIMP CotSimpleLineSymbol::get_Unit(otSymbolUnit *pVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =CInterfaceConvert::ConvertSymbolUnit(m_pLineSymbol->GetUnit());

	return S_OK;
}

STDMETHODIMP CotSimpleLineSymbol::put_Unit(otSymbolUnit newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pLineSymbol->SetUnit(CInterfaceConvert::ConvertSymbolUnit(newVal));
	return S_OK;
}

/*****************************************************************************
* ʵ��IotLineSymbol�ӿ�
******************************************************************************/

STDMETHODIMP CotSimpleLineSymbol::get_LineWidth(DOUBLE *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pLineSymbol->GetLineWidth();
	return S_OK;
}

STDMETHODIMP CotSimpleLineSymbol::put_LineWidth(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pLineSymbol->SetLineWidth(newVal);
    return S_OK;
}

STDMETHODIMP CotSimpleLineSymbol::get_Color(IotColor **pVal)
{
	if(!CheckPointer())
	{

		return E_FAIL;
	}

	//��÷�����ɫ
	unsigned long color =m_pLineSymbol->GetLineColor();

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

STDMETHODIMP CotSimpleLineSymbol::put_Color(IotColor *newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	long red,green,blue;
	newVal->get_Red(&red);
	newVal->get_Blue(&blue);
	newVal->get_Green(&green);

	m_pLineSymbol->SetLineColor(RGB(red,green,blue));
}

