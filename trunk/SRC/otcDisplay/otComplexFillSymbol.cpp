// otComplexFillSymbol.cpp : CotComplexFillSymbol ��ʵ��

#include "stdafx.h"
#include "otComplexFillSymbol.h"
#include "InterfaceConvert.h"

// CotComplexFillSymbol

CotComplexFillSymbol::CotComplexFillSymbol()
{
	//����һ���µ������
	m_pFillSymbol =new Display::CComplexFillSymbol();

	m_ppSymbol =new Display::ISymbolPtr(m_pFillSymbol);

	m_bAutoDestroy =true;
}

CotComplexFillSymbol::~CotComplexFillSymbol()
{
	if(m_ppSymbol && m_bAutoDestroy)
	{
		delete m_ppSymbol;
	}
}



bool CotComplexFillSymbol::CheckPointer()
{
	if((!m_ppSymbol) || (!m_pFillSymbol))
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
STDMETHODIMP CotComplexFillSymbol::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppSymbol;
	return S_OK;
}

STDMETHODIMP CotComplexFillSymbol::put_OriginData(long  pVal)
{

	if(m_ppSymbol && m_bAutoDestroy)
	{
		delete m_ppSymbol;
		m_pFillSymbol =NULL;
	}

	Display::ISymbolPtr *ppSymbol =(Display::ISymbolPtr*)pVal;

	//��Symbolָ��ת������Ӧ���ŵ�ָ��
	m_pFillSymbol =dynamic_cast<Display::CComplexFillSymbol*>(ppSymbol->get());

	if(!m_pFillSymbol)
	{
		m_ppSymbol =NULL;
	}
	else
	{
		m_ppSymbol =ppSymbol;
	}

	return S_OK;
}

STDMETHODIMP CotComplexFillSymbol::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotComplexFillSymbol::put_AutoDestroy(long  pVal)
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

STDMETHODIMP CotComplexFillSymbol::get_Type(otSymbolType *pVal)
{
	*pVal = otCOMPLEX_FILL_SYMBOL;

	return S_OK;
}

STDMETHODIMP CotComplexFillSymbol::get_Unit(otSymbolUnit *pVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =CInterfaceConvert::ConvertSymbolUnit(m_pFillSymbol->GetUnit());

	return S_OK;
}

STDMETHODIMP CotComplexFillSymbol::put_Unit(otSymbolUnit newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pFillSymbol->SetUnit(CInterfaceConvert::ConvertSymbolUnit(newVal));
	return S_OK;
}

/*****************************************************************************
* ʵ��IotFillSymbol�ӿ�
******************************************************************************/


STDMETHODIMP CotComplexFillSymbol::get_DrawOutLine(VARIANT_BOOL *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	*pVal =m_pFillSymbol->GetDrawOutLine()?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CotComplexFillSymbol::put_DrawOutLine(VARIANT_BOOL newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	m_pFillSymbol->SetDrawOutLine((newVal==VARIANT_FALSE)?false:true);
	return S_OK;
}

STDMETHODIMP CotComplexFillSymbol::get_FillColor(IotColor **pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	//��÷�����ɫ
	unsigned long color =m_pFillSymbol->GetFillColor();

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

STDMETHODIMP CotComplexFillSymbol::put_FillColor(IotColor *newVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	long red,green,blue;
	newVal->get_Red(&red);
	newVal->get_Blue(&blue);
	newVal->get_Green(&green);

	m_pFillSymbol->SetFillColor(RGB(red,green,blue));
	return S_OK;
}

STDMETHODIMP CotComplexFillSymbol::get_OutLine(IotSymbol **pVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	Display::ISymbolPtr pSymbol =m_pFillSymbol->GetOutLineSymbol();

	if(!pSymbol)
	{
		*pVal =NULL;
		return S_OK;
	}

	CInterfaceConvert::ConvertSymbol(pSymbol,pVal);

	return S_OK;
}

STDMETHODIMP CotComplexFillSymbol::put_OutLine(IotSymbol *newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	if(!newVal)
	{
		return E_FAIL;
	}
	IOriginDataPtr pData;

	newVal->QueryInterface(__uuidof(IOriginData),(void**)&pData);

	long ldata;
	pData->get_OriginData(&ldata);

	Display::ILineSymbolPtr pLineSymbol =*((Display::ISymbolPtr*)(ldata));

	m_pFillSymbol->SetOutLineSymbol(pLineSymbol);

	return S_OK;
}


