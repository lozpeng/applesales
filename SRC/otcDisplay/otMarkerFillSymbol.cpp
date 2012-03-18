// otMarkerFillSymbol.cpp : CotMarkerFillSymbol 的实现

#include "stdafx.h"
#include "otMarkerFillSymbol.h"
#include "InterfaceConvert.h"

// CotMarkerFillSymbol
CotMarkerFillSymbol::CotMarkerFillSymbol()
{
	//构造一个新的面符号
	m_pFillSymbol =new Display::CMarkerFillSymbol();

	m_ppSymbol =new Display::ISymbolPtr(m_pFillSymbol);

	m_bAutoDestroy =true;
}

CotMarkerFillSymbol::~CotMarkerFillSymbol()
{
	if(m_ppSymbol && m_bAutoDestroy)
	{
		delete m_ppSymbol;
	}
}



bool CotMarkerFillSymbol::CheckPointer()
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


STDMETHODIMP CotMarkerFillSymbol::get_OffsetX(DOUBLE* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pFillSymbol->GetOffsetX();

	return S_OK;
}

STDMETHODIMP CotMarkerFillSymbol::put_OffsetX(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	float y =m_pFillSymbol->GetOffsetY();
	m_pFillSymbol->SetOffsetXY(newVal,y);

	return S_OK;
}

STDMETHODIMP CotMarkerFillSymbol::get_OffsetY(DOUBLE* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pFillSymbol->GetOffsetY();

	return S_OK;
}

STDMETHODIMP CotMarkerFillSymbol::put_OffsetY(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	float x =m_pFillSymbol->GetOffsetX();
	m_pFillSymbol->SetOffsetXY(x,newVal);

	return S_OK;
}

STDMETHODIMP CotMarkerFillSymbol::get_SeparationX(DOUBLE* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pFillSymbol->GetSeparationX();

	return S_OK;
}

STDMETHODIMP CotMarkerFillSymbol::put_SeparationX(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	float y =m_pFillSymbol->GetSeparationY();
	m_pFillSymbol->SetSeparationXY(newVal,y);

	return S_OK;
}

STDMETHODIMP CotMarkerFillSymbol::get_SeparationY(DOUBLE* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pFillSymbol->GetSeparationY();

	return S_OK;
}

STDMETHODIMP CotMarkerFillSymbol::put_SeparationY(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	float x =m_pFillSymbol->GetSeparationX();
	m_pFillSymbol->SetSeparationXY(x,newVal);

	return S_OK;
}

STDMETHODIMP CotMarkerFillSymbol::get_MarkSymbol(IotMarkerSymbol** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	Display::ISymbolPtr pSymbol =m_pFillSymbol->GetMarkSymbol();

	if(!pSymbol)
	{
		*pVal =NULL;
		return S_OK;
	}
	IotSymbol *ps =NULL;
	CInterfaceConvert::ConvertSymbol(pSymbol,&ps);
	if(!ps)
	{
		*pVal =NULL;
		return S_OK;
	}

	ps->QueryInterface(__uuidof(IotMarkerSymbol),(void**)pVal);

	ps->Release();


	return S_OK;
}

STDMETHODIMP CotMarkerFillSymbol::put_MarkSymbol(IotMarkerSymbol* newVal)
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

	Display::IMarkerSymbolPtr pMarkerSymbol =*((Display::ISymbolPtr*)(ldata));

	m_pFillSymbol->SetMarkSymbol(pMarkerSymbol);

	return S_OK;
}

/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotMarkerFillSymbol::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppSymbol;
	return S_OK;
}

STDMETHODIMP CotMarkerFillSymbol::put_OriginData(long  pVal)
{

	if(m_ppSymbol && m_bAutoDestroy)
	{
		delete m_ppSymbol;
		m_pFillSymbol =NULL;
	}

	Display::ISymbolPtr *ppSymbol =(Display::ISymbolPtr*)pVal;

	//将Symbol指针转换成相应符号的指针
	m_pFillSymbol =dynamic_cast<Display::CMarkerFillSymbol*>(ppSymbol->get());

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

STDMETHODIMP CotMarkerFillSymbol::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotMarkerFillSymbol::put_AutoDestroy(long  pVal)
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
* 实现IotSymbol接口
******************************************************************************/

STDMETHODIMP CotMarkerFillSymbol::get_Type(otSymbolType *pVal)
{
	*pVal = otMARKER_FILL_SYMBOL;

	return S_OK;
}

STDMETHODIMP CotMarkerFillSymbol::get_Unit(otSymbolUnit *pVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =CInterfaceConvert::ConvertSymbolUnit(m_pFillSymbol->GetUnit());

	return S_OK;
}

STDMETHODIMP CotMarkerFillSymbol::put_Unit(otSymbolUnit newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pFillSymbol->SetUnit(CInterfaceConvert::ConvertSymbolUnit(newVal));
	return S_OK;
}

/*****************************************************************************
* 实现IotFillSymbol接口
******************************************************************************/


STDMETHODIMP CotMarkerFillSymbol::get_DrawOutLine(VARIANT_BOOL *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	*pVal =m_pFillSymbol->GetDrawOutLine()?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CotMarkerFillSymbol::put_DrawOutLine(VARIANT_BOOL newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	m_pFillSymbol->SetDrawOutLine((newVal==VARIANT_FALSE)?false:true);
	return S_OK;
}

STDMETHODIMP CotMarkerFillSymbol::get_FillColor(IotColor **pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	//获得符号颜色
	unsigned long color =m_pFillSymbol->GetFillColor();

	long red,green,blue;
	red =GetRValue(color);
	green =GetGValue(color);
	blue =GetBValue(color);

	//构造一个颜色对象
	CoCreateInstance(CLSID_otColor,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotColor),(void**)pVal);
	(*pVal)->put_Red(red);
	(*pVal)->put_Green(green);
	(*pVal)->put_Blue(blue);
	return S_OK;
}

STDMETHODIMP CotMarkerFillSymbol::put_FillColor(IotColor *newVal)
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

STDMETHODIMP CotMarkerFillSymbol::get_OutLine(IotSymbol **pVal)
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

STDMETHODIMP CotMarkerFillSymbol::put_OutLine(IotSymbol *newVal)
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
