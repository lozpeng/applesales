// otArrowMarkerSymbol.cpp : CotArrowMarkerSymbol ��ʵ��

#include "stdafx.h"
#include "otArrowMarkerSymbol.h"
#include "InterfaceConvert.h"

// CotArrowMarkerSymbol

CotArrowMarkerSymbol::CotArrowMarkerSymbol()
{
	//����һ���µĵ����
	m_pMarkerSymbol =new Display::CArrowMarkerSymbol();

	m_ppSymbol =new Display::ISymbolPtr(m_pMarkerSymbol);

	m_bAutoDestroy =true;
}

CotArrowMarkerSymbol::~CotArrowMarkerSymbol()
{
	if(m_ppSymbol && m_bAutoDestroy)
	{
		delete m_ppSymbol;
	}
}

bool CotArrowMarkerSymbol::CheckPointer()
{
	if((!m_ppSymbol) || (!m_pMarkerSymbol))
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
STDMETHODIMP CotArrowMarkerSymbol::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppSymbol;
	return S_OK;
}

STDMETHODIMP CotArrowMarkerSymbol::put_OriginData(long  pVal)
{

	if(m_ppSymbol && m_bAutoDestroy)
	{
		delete m_ppSymbol;
		m_pMarkerSymbol =NULL;
	}

	Display::ISymbolPtr *ppSymbol =(Display::ISymbolPtr*)pVal;

	//��Symbolָ��ת������Ӧ���ŵ�ָ��
	m_pMarkerSymbol =dynamic_cast<Display::CArrowMarkerSymbol*>(ppSymbol->get());

	if(!m_pMarkerSymbol)
	{
		m_ppSymbol =NULL;
	}
	else
	{
		m_ppSymbol =ppSymbol;
	}

	return S_OK;
}

STDMETHODIMP CotArrowMarkerSymbol::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotArrowMarkerSymbol::put_AutoDestroy(long  pVal)
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

STDMETHODIMP CotArrowMarkerSymbol::get_Type(otSymbolType *pVal)
{
	*pVal = otARROW_MARKER_SYMBOL;

	return S_OK;
}

STDMETHODIMP CotArrowMarkerSymbol::get_Unit(otSymbolUnit *pVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =CInterfaceConvert::ConvertSymbolUnit(m_pMarkerSymbol->GetUnit());

	return S_OK;
}

STDMETHODIMP CotArrowMarkerSymbol::put_Unit(otSymbolUnit newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pMarkerSymbol->SetUnit(CInterfaceConvert::ConvertSymbolUnit(newVal));
	return S_OK;
}

/*****************************************************************************
* ʵ��IotMarkerSymbol�ӿ�
******************************************************************************/
STDMETHODIMP CotArrowMarkerSymbol::get_Color(IotColor **pVal)
{
	if(!CheckPointer())
	{

		return E_FAIL;
	}

	//��÷�����ɫ
	unsigned long color =m_pMarkerSymbol->GetMarkColor();

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

STDMETHODIMP CotArrowMarkerSymbol::put_Color(IotColor *newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	long red,green,blue;
	newVal->get_Red(&red);
	newVal->get_Blue(&blue);
	newVal->get_Green(&green);

	m_pMarkerSymbol->SetMarkerColor(RGB(red,green,blue));

	return S_OK;
}

STDMETHODIMP CotArrowMarkerSymbol::get_Angle(DOUBLE *pVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pMarkerSymbol->GetAngle();


	return S_OK;
}

STDMETHODIMP CotArrowMarkerSymbol::put_Angle(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pMarkerSymbol->SetAngle(newVal);
	return S_OK;
}

STDMETHODIMP CotArrowMarkerSymbol::get_OffsetX(DOUBLE *pVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pMarkerSymbol->GetOffsetX();
	return S_OK;
}

STDMETHODIMP CotArrowMarkerSymbol::put_OffsetX(DOUBLE newVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	float y =m_pMarkerSymbol->GetOffsetY();
	m_pMarkerSymbol->SetOffSet(newVal,y);
	return S_OK;
}


STDMETHODIMP CotArrowMarkerSymbol::get_OffsetY(DOUBLE *pVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pMarkerSymbol->GetOffsetY();
	return S_OK;
}

STDMETHODIMP CotArrowMarkerSymbol::put_OffsetY(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	float x =m_pMarkerSymbol->GetOffsetX();
	m_pMarkerSymbol->SetOffSet(x,newVal);
	return S_OK;

}

STDMETHODIMP CotArrowMarkerSymbol::get_Size(DOUBLE *pVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pMarkerSymbol->GetMarkerSize();
	return S_OK;
}

STDMETHODIMP CotArrowMarkerSymbol::put_Size(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pMarkerSymbol->SetMarkerSize(newVal);
	return S_OK;

}
