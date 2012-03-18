// otPolylineElement.cpp : CotPolylineElement 的实现

#include "stdafx.h"
#include "otPolylineElement.h"


// CotPolylineElement
CotPolylineElement::CotPolylineElement()
{
	//构造一个新的线图元
	m_pPolylineElement =new Element::CPolylineElement();

	m_ppElement =new Element::IElementPtr(m_pPolylineElement);

	m_bAutoDestroy =true;
}

CotPolylineElement::~CotPolylineElement()
{
	if(m_ppElement && m_bAutoDestroy)
	{
		delete m_ppElement;
	}
}

bool CotPolylineElement::CheckPointer()
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

STDMETHODIMP CotPolylineElement::get_Symbol(IotSymbol** pVal)
{
	
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	Display::ISymbolPtr pSymbol =m_pPolylineElement->GetSymbol();

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

STDMETHODIMP CotPolylineElement::put_Symbol(IotSymbol* newVal)
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

	m_pPolylineElement->SetSymbol(*((Display::ISymbolPtr*)lval));

	return S_OK;
}

/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotPolylineElement::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppElement;
	return S_OK;
}

STDMETHODIMP CotPolylineElement::put_OriginData(long  pVal)
{

	if(m_ppElement && m_bAutoDestroy)
	{
		delete m_ppElement;
		m_pPolylineElement =NULL;
	}

	Element::IElementPtr *ppEle =(Element::IElementPtr*)pVal;

	//将IElement指针转换成相应图元的指针
	m_pPolylineElement =dynamic_cast<Element::CPolylineElement*>(ppEle->get());

	if(!m_pPolylineElement)
	{
		m_ppElement =NULL;
	}
	else
	{
		m_ppElement =ppEle;
	}

	return S_OK;
}

STDMETHODIMP CotPolylineElement::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotPolylineElement::put_AutoDestroy(long  pVal)
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

STDMETHODIMP CotPolylineElement::get_Geometry(IotGeometry** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg=m_pPolylineElement->GetGeometry();
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

STDMETHODIMP CotPolylineElement::put_Geometry(IotGeometry*  newVal)
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

	m_pPolylineElement->SetGeometry(*((GEOMETRY::geom::Geometry*)ldata));


	return S_OK;
}


STDMETHODIMP CotPolylineElement::get_Name(BSTR * pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	_bstr_t str =m_pPolylineElement->GetName().c_str();

	*pVal =SysAllocString(str);
	return S_OK;
}


STDMETHODIMP CotPolylineElement::put_Name(BSTR newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	_bstr_t str =newVal;

	m_pPolylineElement->SetName(std::string(str));

	return S_OK;
}

STDMETHODIMP CotPolylineElement::get_Type( ElementType * pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	*pVal =(ElementType)m_pPolylineElement->GetType();
	return S_OK;
}
