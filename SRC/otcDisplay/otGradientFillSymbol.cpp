// otGradientFillSymbol.cpp : CotGradientFillSymbol 的实现

#include "stdafx.h"
#include "otGradientFillSymbol.h"
#include "InterfaceConvert.h"

// CotGradientFillSymbol

CotGradientFillSymbol::CotGradientFillSymbol()
{
	//构造一个新的面符号
	m_pFillSymbol =new Display::CGradientFillSymbol();

	m_ppSymbol =new Display::ISymbolPtr(m_pFillSymbol);

	m_bAutoDestroy =true;
}

CotGradientFillSymbol::~CotGradientFillSymbol()
{
	if(m_ppSymbol && m_bAutoDestroy)
	{
		delete m_ppSymbol;
		m_pFillSymbol =NULL;
	}
}



bool CotGradientFillSymbol::CheckPointer()
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
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotGradientFillSymbol::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppSymbol;
	return S_OK;
}

STDMETHODIMP CotGradientFillSymbol::put_OriginData(long  pVal)
{

	if(m_ppSymbol && m_bAutoDestroy)
	{
		delete m_ppSymbol;
		m_pFillSymbol =NULL;
	}

	Display::ISymbolPtr *ppSymbol =(Display::ISymbolPtr*)pVal;

	//将Symbol指针转换成相应符号的指针
	m_pFillSymbol =dynamic_cast<Display::CGradientFillSymbol*>(ppSymbol->get());

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

STDMETHODIMP CotGradientFillSymbol::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotGradientFillSymbol::put_AutoDestroy(long  pVal)
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

STDMETHODIMP CotGradientFillSymbol::get_Type(otSymbolType *pVal)
{
	*pVal = otGRADIENT_FILL_SYMBOL;

	return S_OK;
}

STDMETHODIMP CotGradientFillSymbol::get_Unit(otSymbolUnit *pVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =CInterfaceConvert::ConvertSymbolUnit(m_pFillSymbol->GetUnit());

	return S_OK;
}

STDMETHODIMP CotGradientFillSymbol::put_Unit(otSymbolUnit newVal)
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


STDMETHODIMP CotGradientFillSymbol::get_DrawOutLine(VARIANT_BOOL *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	*pVal =m_pFillSymbol->GetDrawOutLine()?VARIANT_TRUE:VARIANT_FALSE;

    return S_OK;
}

STDMETHODIMP CotGradientFillSymbol::put_DrawOutLine(VARIANT_BOOL newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	m_pFillSymbol->SetDrawOutLine((newVal==VARIANT_FALSE)?false:true);
	return S_OK;
}

STDMETHODIMP CotGradientFillSymbol::get_OutLine(IotSymbol **pVal)
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

STDMETHODIMP CotGradientFillSymbol::put_OutLine(IotSymbol *newVal)
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

STDMETHODIMP CotGradientFillSymbol::get_FillColor( IotColor** pVal )
{

	return S_OK;
}

STDMETHODIMP CotGradientFillSymbol::put_FillColor( IotColor* pVal )
{
	return S_OK;
}
/*****************************************************************************
* 实现IotGradientFillSymbol接口
******************************************************************************/

STDMETHODIMP CotGradientFillSymbol::get_BeginColor( IotColor** pVal )
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	//获得符号颜色
	unsigned long color = m_pFillSymbol->GetBeginColor();

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

STDMETHODIMP CotGradientFillSymbol::put_BeginColor( IotColor* pVal )
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	long red,green,blue;
	pVal->get_Red(&red);
	pVal->get_Blue(&blue);
	pVal->get_Green(&green);

	m_pFillSymbol->SetBeginColor(RGB(red,green,blue));
}

STDMETHODIMP CotGradientFillSymbol::get_EndColor( IotColor** pVal )
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	//获得符号颜色
	unsigned long color = m_pFillSymbol->GetEndColor();

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

STDMETHODIMP CotGradientFillSymbol::put_EndColor( IotColor* pVal )
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	long red,green,blue;
	pVal->get_Red(&red);
	pVal->get_Blue(&blue);
	pVal->get_Green(&green);

	m_pFillSymbol->SetEndColor(RGB(red,green,blue));
}

STDMETHODIMP CotGradientFillSymbol::get_SegmentCounts( LONG * pVal )
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	*pVal = (LONG)( m_pFillSymbol->GetSegmentsCount() );
}

STDMETHODIMP CotGradientFillSymbol::put_SegmentCounts( LONG pVal )
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}	

	m_pFillSymbol->SetSegmentsCount( (long)pVal );
}

STDMETHODIMP CotGradientFillSymbol::get_Percent( LONG * pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	*pVal = (LONG)( m_pFillSymbol->GetPercent() );
}

STDMETHODIMP CotGradientFillSymbol::put_Percent( LONG pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}	

	m_pFillSymbol->SetPercent( (long)pVal );
}

STDMETHODIMP CotGradientFillSymbol::get_Angle( FLOAT * pVal )
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	*pVal = (FLOAT)( m_pFillSymbol->GetAngle() );
}

STDMETHODIMP CotGradientFillSymbol::put_Angle( FLOAT pVal )
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}	

	m_pFillSymbol->SetAngle( (float)pVal );
}

STDMETHODIMP CotGradientFillSymbol::get_GradientFillType( otGradientFillType * pVal )
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	*pVal = (otGradientFillType)( m_pFillSymbol->GetGradientFillType() );
}

STDMETHODIMP CotGradientFillSymbol::put_GradientFillType( otGradientFillType pVal )
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}	

	m_pFillSymbol->SetGradientFillType( (GRANDIENT_FILL_TYPE)pVal );
}