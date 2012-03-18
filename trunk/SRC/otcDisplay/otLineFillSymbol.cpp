// otLineFillSymbol.cpp : CotLineFillSymbol 的实现

#include "stdafx.h"
#include "otLineFillSymbol.h"
#include "InterfaceConvert.h"

// CotLineFillSymbol
CotLineFillSymbol::CotLineFillSymbol()
{
	//构造一个新的面符号
	m_pFillSymbol =new Display::CLineFillSymbol();

	m_ppSymbol =new Display::ISymbolPtr(m_pFillSymbol);

	m_bAutoDestroy =true;
}

CotLineFillSymbol::~CotLineFillSymbol()
{
	if(m_ppSymbol && m_bAutoDestroy)
	{
		delete m_ppSymbol;
	}
}



bool CotLineFillSymbol::CheckPointer()
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


STDMETHODIMP CotLineFillSymbol::get_Angle(DOUBLE* pVal)
{
	
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pFillSymbol->GetAngle();
	return S_OK;
}

STDMETHODIMP CotLineFillSymbol::put_Angle(DOUBLE newVal)
{
	
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pFillSymbol->SetAngle(newVal);
	return S_OK;
}

STDMETHODIMP CotLineFillSymbol::get_separation(DOUBLE* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pFillSymbol->GetSeparation();

	return S_OK;
}

STDMETHODIMP CotLineFillSymbol::put_separation(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pFillSymbol->SetSeparation(newVal);

	return S_OK;
}

STDMETHODIMP CotLineFillSymbol::get_Offset(DOUBLE* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pFillSymbol->GetOffset();

	return S_OK;
}

STDMETHODIMP CotLineFillSymbol::put_Offset(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pFillSymbol->SetOffset(newVal);

	return S_OK;
}

STDMETHODIMP CotLineFillSymbol::get_LineSymbol(IotLineSymbol** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	Display::ISymbolPtr pSymbol =m_pFillSymbol->GetLineSymbol();

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

	ps->QueryInterface(__uuidof(IotLineSymbol),(void**)pVal);

	ps->Release();

	return S_OK;
}

STDMETHODIMP CotLineFillSymbol::put_LineSymbol(IotLineSymbol* newVal)
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

	m_pFillSymbol->SetLineSymbol(pLineSymbol);

	return S_OK;
}


/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotLineFillSymbol::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppSymbol;
	return S_OK;
}

STDMETHODIMP CotLineFillSymbol::put_OriginData(long  pVal)
{

	if(m_ppSymbol && m_bAutoDestroy)
	{
		delete m_ppSymbol;
		m_pFillSymbol =NULL;
	}

	Display::ISymbolPtr *ppSymbol =(Display::ISymbolPtr*)pVal;

	//将Symbol指针转换成相应符号的指针
	m_pFillSymbol =dynamic_cast<Display::CLineFillSymbol*>(ppSymbol->get());

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

STDMETHODIMP CotLineFillSymbol::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotLineFillSymbol::put_AutoDestroy(long  pVal)
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

STDMETHODIMP CotLineFillSymbol::get_Type(otSymbolType *pVal)
{
	*pVal = otLINE_FILL_SYMBOL;

	return S_OK;
}

STDMETHODIMP CotLineFillSymbol::get_Unit(otSymbolUnit *pVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =CInterfaceConvert::ConvertSymbolUnit(m_pFillSymbol->GetUnit());

	return S_OK;
}

STDMETHODIMP CotLineFillSymbol::put_Unit(otSymbolUnit newVal)
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


STDMETHODIMP CotLineFillSymbol::get_DrawOutLine(VARIANT_BOOL *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	*pVal =m_pFillSymbol->GetDrawOutLine()?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CotLineFillSymbol::put_DrawOutLine(VARIANT_BOOL newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	m_pFillSymbol->SetDrawOutLine((newVal==VARIANT_FALSE)?false:true);
	return S_OK;
}

STDMETHODIMP CotLineFillSymbol::get_FillColor(IotColor **pVal)
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

STDMETHODIMP CotLineFillSymbol::put_FillColor(IotColor *newVal)
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

STDMETHODIMP CotLineFillSymbol::get_OutLine(IotSymbol **pVal)
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

STDMETHODIMP CotLineFillSymbol::put_OutLine(IotSymbol *newVal)
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
