// otCircleElement.cpp : CotCircleElement 的实现

#include "stdafx.h"
#include "otCircleElement.h"


// CotCircleElement
CotCircleElement::CotCircleElement()
{

	//构造一个新的圆形图元
	m_pCircleElement =new Element::CCircleElement();

	m_ppElement =new Element::IElementPtr(m_pCircleElement);

	m_bAutoDestroy =true;
}

CotCircleElement::~CotCircleElement()
{

	if(m_ppElement && m_bAutoDestroy)
	{
		delete m_ppElement;
	}
}

bool CotCircleElement::CheckPointer()
{
	if(!m_ppElement)
	{
		return false;
	}
	if(!(*m_ppElement))
	{
		return false;
	}
	return true;
}

STDMETHODIMP CotCircleElement::get_Symbol(IotSymbol** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	Display::ISymbolPtr pSymbol =m_pCircleElement->GetSymbol();

	if(!pSymbol)
	{
		*pVal =NULL;
		return E_FAIL;
	}

	Display::ISymbolPtr *ppSymbol =new Display::ISymbolPtr(pSymbol);

	IotSymbolConvertPtr pCon;

	CoCreateInstance(CLSID_otSymbolConvert,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotSymbolConvert),(void**)&pCon);

	pCon->ConvertSymbol(long(ppSymbol),VARIANT_TRUE,pVal);

	return S_OK;
}

STDMETHODIMP CotCircleElement::put_Symbol(IotSymbol* newVal)
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

	long lval;
	pData->get_OriginData(&lval);

	m_pCircleElement->SetSymbol(*((Display::ISymbolPtr*)lval));

	return S_OK;
}


/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotCircleElement::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppElement;
	return S_OK;
}

STDMETHODIMP CotCircleElement::put_OriginData(long  pVal)
{

	if(m_ppElement && m_bAutoDestroy)
	{
		delete m_ppElement;
		m_pCircleElement =NULL;
	}

	Element::IElementPtr *ppEle =(Element::IElementPtr*)pVal;

	//将IElement指针转换成相应图元的指针
	m_pCircleElement =dynamic_cast<Element::CCircleElement*>(ppEle->get());

	if(!m_pCircleElement)
	{
		m_ppElement =NULL;
	}
	else
	{
		m_ppElement =ppEle;
	}

	return S_OK;
}

STDMETHODIMP CotCircleElement::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotCircleElement::put_AutoDestroy(long  pVal)
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
* 实现IElement接口
******************************************************************************/

STDMETHODIMP CotCircleElement::get_Geometry(IotGeometry** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg=m_pCircleElement->GetGeometry();
	if(!pg)
	{
		*pVal =NULL;
		return S_OK;
	}
	pg =pg->clone();

	IotGeoConvertPtr pCon;

	CoCreateInstance(CLSID_otGeoConvert,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotGeoConvert),(void**)&pCon);

	pCon->ConvertGeo(long(pg),VARIANT_TRUE,pVal);

	return S_OK;
}

STDMETHODIMP CotCircleElement::put_Geometry(IotGeometry*  newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	if(!newVal)
	{
		return E_FAIL;
	}
	IotGeoConvertPtr pCon;

	CoCreateInstance(CLSID_otGeoConvert,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotGeoConvert),(void**)&pCon);

	long ldata;
	pCon->ConvertIGeo(newVal,&ldata);

	m_pCircleElement->SetGeometry(*((GEOMETRY::geom::Geometry*)ldata));


	return S_OK;
}


STDMETHODIMP CotCircleElement::get_Name(BSTR * pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	_bstr_t str =m_pCircleElement->GetName().c_str();

	*pVal =SysAllocString(str);
	return S_OK;
}


STDMETHODIMP CotCircleElement::put_Name(BSTR newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	_bstr_t str =newVal;

	m_pCircleElement->SetName(std::string(str));

	return S_OK;
}

STDMETHODIMP CotCircleElement::get_Type( ElementType * pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	*pVal =(ElementType)m_pCircleElement->GetType();
	return S_OK;
}



