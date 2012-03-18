// otSimpleMarkerSymbol.cpp : CotSimpleMarkerSymbol 的实现

#include "stdafx.h"
#include "otSimpleMarkerSymbol.h"
#include "InterfaceConvert.h"

// CotSimpleMarkerSymbol

CotSimpleMarkerSymbol::CotSimpleMarkerSymbol()
{
    //构造一个新的点符号
	m_pMarkerSymbol =new Display::CSimpleMarkerSymbol();

	m_ppSymbol =new Display::ISymbolPtr(m_pMarkerSymbol);

	m_bAutoDestroy =true;
}

CotSimpleMarkerSymbol::~CotSimpleMarkerSymbol()
{
	if(m_ppSymbol && m_bAutoDestroy)
	{
		delete m_ppSymbol;
	}
}

/*****************************************************************************
* 实现IotSimpleMarkerSymbol接口
******************************************************************************/
STDMETHODIMP CotSimpleMarkerSymbol::get_DrawOutLine(VARIANT_BOOL* pVal)
{
	
    if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pMarkerSymbol->GetOutLineFlag()?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CotSimpleMarkerSymbol::put_DrawOutLine(VARIANT_BOOL newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pMarkerSymbol->SetOutLineFlag((newVal==VARIANT_FALSE)?false:true);


	return S_OK;
}



STDMETHODIMP CotSimpleMarkerSymbol::get_OutLineWidth(DOUBLE* pVal)
{
	
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pMarkerSymbol->GetOutLineWidth();
	return S_OK;
}

STDMETHODIMP CotSimpleMarkerSymbol::put_OutLineWidth(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pMarkerSymbol->SetOutLineWidth(newVal);

	return S_OK;
}

STDMETHODIMP CotSimpleMarkerSymbol::get_MarkerStyle(otSimpleMarkerStyle* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =(otSimpleMarkerStyle)m_pMarkerSymbol->GetMarkerType();
	return S_OK;
}

STDMETHODIMP CotSimpleMarkerSymbol::put_MarkerStyle(otSimpleMarkerStyle newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pMarkerSymbol->SetMarkerType((SIMPLE_MARKER_STYLE)newVal);

	return S_OK;
}

bool CotSimpleMarkerSymbol::CheckPointer()
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
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotSimpleMarkerSymbol::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppSymbol;
	return S_OK;
}

STDMETHODIMP CotSimpleMarkerSymbol::put_OriginData(long  pVal)
{

	if(m_ppSymbol && m_bAutoDestroy)
	{
		delete m_ppSymbol;
		m_pMarkerSymbol =NULL;
	}
    
	Display::ISymbolPtr *ppSymbol =(Display::ISymbolPtr*)pVal;

	//将Symbol指针转换成相应符号的指针
	m_pMarkerSymbol =dynamic_cast<Display::CSimpleMarkerSymbol*>(ppSymbol->get());

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

STDMETHODIMP CotSimpleMarkerSymbol::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotSimpleMarkerSymbol::put_AutoDestroy(long  pVal)
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

STDMETHODIMP CotSimpleMarkerSymbol::get_Type(otSymbolType *pVal)
{
	*pVal = otSIMPLE_MARKER_SYMBOL;

	return S_OK;
}

STDMETHODIMP CotSimpleMarkerSymbol::get_Unit(otSymbolUnit *pVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =CInterfaceConvert::ConvertSymbolUnit(m_pMarkerSymbol->GetUnit());

    return S_OK;
}

STDMETHODIMP CotSimpleMarkerSymbol::put_Unit(otSymbolUnit newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pMarkerSymbol->SetUnit(CInterfaceConvert::ConvertSymbolUnit(newVal));
	return S_OK;
}

/*****************************************************************************
* 实现IotMarkerSymbol接口
******************************************************************************/
STDMETHODIMP CotSimpleMarkerSymbol::get_Color(IotColor **pVal)
{
	if(!CheckPointer())
	{
		
		return E_FAIL;
	}

	//获得符号颜色
    unsigned long color =m_pMarkerSymbol->GetMarkColor();

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

STDMETHODIMP CotSimpleMarkerSymbol::put_Color(IotColor *newVal)
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

STDMETHODIMP CotSimpleMarkerSymbol::get_Angle(DOUBLE *pVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pMarkerSymbol->GetAngle();


	return S_OK;
}

STDMETHODIMP CotSimpleMarkerSymbol::put_Angle(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pMarkerSymbol->SetAngle(newVal);
	return S_OK;
}

STDMETHODIMP CotSimpleMarkerSymbol::get_OffsetX(DOUBLE *pVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pMarkerSymbol->GetOffsetX();
	return S_OK;
}

STDMETHODIMP CotSimpleMarkerSymbol::put_OffsetX(DOUBLE newVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	float y =m_pMarkerSymbol->GetOffsetY();
	m_pMarkerSymbol->SetOffSet(newVal,y);
	return S_OK;
}


STDMETHODIMP CotSimpleMarkerSymbol::get_OffsetY(DOUBLE *pVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pMarkerSymbol->GetOffsetY();
	return S_OK;
}

STDMETHODIMP CotSimpleMarkerSymbol::put_OffsetY(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	float x =m_pMarkerSymbol->GetOffsetX();
	m_pMarkerSymbol->SetOffSet(x,newVal);
	return S_OK;

}

STDMETHODIMP CotSimpleMarkerSymbol::get_Size(DOUBLE *pVal)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =m_pMarkerSymbol->GetMarkerSize();
	return S_OK;
}

STDMETHODIMP CotSimpleMarkerSymbol::put_Size(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	m_pMarkerSymbol->SetMarkerSize(newVal);
	return S_OK;

}

STDMETHODIMP CotSimpleMarkerSymbol::get_OutLineColor(IotColor** pVal)
{
	if(!CheckPointer())
	{

		return E_FAIL;
	}

	//获得符号颜色
	unsigned long color =m_pMarkerSymbol->GetOutLineColor();

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

STDMETHODIMP CotSimpleMarkerSymbol::put_OutLineColor(IotColor* newVal)
{
	
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	long red,green,blue;
	newVal->get_Red(&red);
	newVal->get_Blue(&blue);
	newVal->get_Green(&green);

	m_pMarkerSymbol->SetOutLineColor(RGB(red,green,blue));
	return S_OK;
}
