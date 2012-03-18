// otCalloutTextElement.cpp : CotCalloutTextElement 的实现

#include "stdafx.h"
#include "otCalloutTextElement.h"


// CotCalloutTextElement

CotCalloutTextElement::CotCalloutTextElement()
{
	//构造一个新的文本图元
	m_pCalloutElement =new Element::CCalloutTextElement();

	m_ppElement =new Element::IElementPtr(m_pCalloutElement);

	m_bAutoDestroy =true;
}

CotCalloutTextElement::~CotCalloutTextElement()
{
	if(m_ppElement && m_bAutoDestroy)
	{
		delete m_ppElement;
	}
}

bool CotCalloutTextElement::CheckPointer()
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

STDMETHODIMP CotCalloutTextElement::get_TextSymbol(IotSymbol** pVal)
{
	
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	Display::ISymbolPtr pSymbol =m_pCalloutElement->GetSymbol();

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

STDMETHODIMP CotCalloutTextElement::put_TextSymbol(IotSymbol* newVal)
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

	m_pCalloutElement->SetSymbol(*((Display::ISymbolPtr*)lval));

	return S_OK;
}

STDMETHODIMP CotCalloutTextElement::get_FillSymbol(IotSymbol** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	Display::ISymbolPtr pSymbol =m_pCalloutElement->GetFillSymbol();

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

STDMETHODIMP CotCalloutTextElement::put_FillSymbol(IotSymbol* newVal)
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

	m_pCalloutElement->SetFillSymbol(*((Display::ISymbolPtr*)lval));

	return S_OK;
}

STDMETHODIMP CotCalloutTextElement::get_Text(BSTR* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	_bstr_t str =m_pCalloutElement->GetText().c_str();
	*pVal =SysAllocString(str);

	return S_OK;
}

STDMETHODIMP CotCalloutTextElement::put_Text(BSTR newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	_bstr_t str =newVal;

	m_pCalloutElement->SetText(std::string(str));

	return S_OK;
}

STDMETHODIMP CotCalloutTextElement::get_AnchorPoint(IotPoint** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Coordinate coord =m_pCalloutElement->GetAnchorPoint();

	CoCreateInstance(CLSID_otPoint,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotPoint),(void**)pVal);

	(*pVal)->put_X(coord.x);
	(*pVal)->put_Y(coord.y);


	return S_OK;
}

STDMETHODIMP CotCalloutTextElement::put_AnchorPoint(IotPoint* newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	GEOMETRY::geom::Coordinate coord;
	newVal->get_X(&coord.x);
	newVal->get_Y(&coord.y);
	
	m_pCalloutElement->SetAnchorPoint(coord);


	return S_OK;
}

STDMETHODIMP CotCalloutTextElement::get_TextOriginPoint(IotPoint** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Coordinate coord =m_pCalloutElement->GetTextOrgPoint();

	CoCreateInstance(CLSID_otPoint,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotPoint),(void**)pVal);

	(*pVal)->put_X(coord.x);
	(*pVal)->put_Y(coord.y);

	return S_OK;
}

STDMETHODIMP CotCalloutTextElement::put_TextOriginPoint(IotPoint* newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	GEOMETRY::geom::Coordinate coord;
	newVal->get_X(&coord.x);
	newVal->get_Y(&coord.y);

	m_pCalloutElement->SetTextOrgPoint(coord);


	return S_OK;
}


/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotCalloutTextElement::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppElement;
	return S_OK;
}

STDMETHODIMP CotCalloutTextElement::put_OriginData(long  pVal)
{

	if(m_ppElement && m_bAutoDestroy)
	{
		delete m_ppElement;
		m_pCalloutElement =NULL;
	}

	Element::IElementPtr *ppEle =(Element::IElementPtr*)pVal;

	//将IElement指针转换成相应图元的指针
	m_pCalloutElement =dynamic_cast<Element::CCalloutTextElement*>(ppEle->get());

	if(!m_pCalloutElement)
	{
		m_ppElement =NULL;
	}
	else
	{
		m_ppElement =ppEle;
	}

	return S_OK;
}

STDMETHODIMP CotCalloutTextElement::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotCalloutTextElement::put_AutoDestroy(long  pVal)
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

STDMETHODIMP CotCalloutTextElement::get_Geometry(IotGeometry** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg=m_pCalloutElement->GetGeometry();
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

STDMETHODIMP CotCalloutTextElement::put_Geometry(IotGeometry*  newVal)
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

	m_pCalloutElement->SetGeometry(((GEOMETRY::geom::Geometry*)ldata));


	return S_OK;
}


STDMETHODIMP CotCalloutTextElement::get_Name(BSTR * pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	_bstr_t str =m_pCalloutElement->GetName().c_str();

	*pVal =SysAllocString(str);
	return S_OK;
}


STDMETHODIMP CotCalloutTextElement::put_Name(BSTR newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	_bstr_t str =newVal;

	m_pCalloutElement->SetName(std::string(str));

	return S_OK;
}

STDMETHODIMP CotCalloutTextElement::get_Type( ElementType * pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	*pVal =(ElementType)m_pCalloutElement->GetType();
	return S_OK;
}