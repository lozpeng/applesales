// otGraphicLayer.cpp : CotGraphicLayer 的实现

#include "stdafx.h"
#include "otGraphicLayer.h"
#include "InterfaceConvert.h"

// CotGraphicLayer

CotGraphicLayer::CotGraphicLayer()
{
	//创建一个新的FeatureLayer
	m_ppLayer =new Carto::CGraphicLayerPtr(new Carto::CGraphicLayer(GEOMETRY::geom::Envelope(0,0,1,1)));

	m_bAutoDestroy =true;
}

CotGraphicLayer::~CotGraphicLayer()
{
	if(m_ppLayer && m_bAutoDestroy)
	{
		delete m_ppLayer;
	}
}

/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotGraphicLayer::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppLayer;
	return S_OK;
}

STDMETHODIMP CotGraphicLayer::put_OriginData(long  pVal)
{

	if(m_ppLayer && m_bAutoDestroy)
	{
		delete m_ppLayer;
	}

	m_ppLayer =(Carto::CGraphicLayerPtr*)(pVal);

	return S_OK;
}

STDMETHODIMP CotGraphicLayer::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotGraphicLayer::put_AutoDestroy(long  pVal)
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

bool CotGraphicLayer::CheckPointer()
{
	if(!m_ppLayer)
	{
		return false;
	}
	if(!(*m_ppLayer))
	{

		return false;
	}
	return true;
}

/*****************************************************************************
* 实现IotLayer接口
******************************************************************************/

STDMETHODIMP CotGraphicLayer::get_Name(BSTR *pVal)
{
	
	return S_OK;
}

STDMETHODIMP CotGraphicLayer::put_Name(BSTR newVal)
{
	

	return S_OK;
}

STDMETHODIMP CotGraphicLayer::get_LayerDesciption(BSTR *pVal)
{
	
	return S_OK;
}

STDMETHODIMP CotGraphicLayer::put_LayerDesciption(BSTR newVal)
{
	
	return S_OK;
}

STDMETHODIMP CotGraphicLayer::get_LayerType(otLayerType *pVal)
{
	
	return S_OK;
}

STDMETHODIMP CotGraphicLayer::get_Visible(VARIANT_BOOL *pVal)
{
	


	return S_OK;
}

STDMETHODIMP CotGraphicLayer::put_Visible(VARIANT_BOOL newVal)
{
	

	return S_OK;
}

STDMETHODIMP CotGraphicLayer::get_ScaleRangeValid(VARIANT_BOOL *pVal)
{
	
	return S_OK;
}

STDMETHODIMP CotGraphicLayer::put_ScaleRangeValid(VARIANT_BOOL newVal)
{

	return S_OK;
}

STDMETHODIMP CotGraphicLayer::get_ScaleRangeMin(DOUBLE *pVal)
{
	
	return S_OK;
}

STDMETHODIMP CotGraphicLayer::put_ScaleRangeMin(DOUBLE newVal)
{
	
	return S_OK;
}

STDMETHODIMP CotGraphicLayer::get_ScaleRangeMax(DOUBLE *pVal)
{
	
	return S_OK;
}

STDMETHODIMP CotGraphicLayer::put_ScaleRangeMax(DOUBLE newVal)
{
	
	return S_OK;
}

STDMETHODIMP CotGraphicLayer::get_DataObject(IotDataObject **pVal)
{
	

    *pVal =NULL;

	return S_OK;
}

STDMETHODIMP CotGraphicLayer::put_DataObject(IotDataObject *newVal)
{
	


	return S_OK;
}

/*****************************************************************************
* 实现IotLayer接口
******************************************************************************/

STDMETHODIMP CotGraphicLayer::get_Count(LONG* pVal)
{
	
    if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =(*m_ppLayer)->GetElementCount();
	return S_OK;
}

STDMETHODIMP CotGraphicLayer::AddElement(IElement* element)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	Element::IElementPtr pEle =CInterfaceConvert::ConvertIElement(element);

	if(!pEle)
	{
		return E_FAIL;
	}
	(*m_ppLayer)->AddElement(pEle);

	return S_OK;
}

STDMETHODIMP CotGraphicLayer::GetElement(LONG index, IElement** retElement)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	Element::IElementPtr pEle =(*m_ppLayer)->GetElement(index);

	CInterfaceConvert::ConvertElement(pEle,retElement);

	return S_OK;
}

STDMETHODIMP CotGraphicLayer::RemoveAllElements(void)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	//清除所有选中要素
	(*m_ppLayer)->UnselectAllElements();

	//清除所有图元
    (*m_ppLayer)->RemoveAllElements();
	return S_OK;
}

STDMETHODIMP CotGraphicLayer::RemoveElement(IElement* element)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	Element::IElementPtr pe =CInterfaceConvert::ConvertIElement(element);
	if(!pe)
	{
		return E_FAIL;
	}
	(*m_ppLayer)->RemoveElement(pe);

	return S_OK;
}

STDMETHODIMP CotGraphicLayer::get_SelectedElementCount(LONG* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =(*m_ppLayer)->GetSelectedElementCount();
	return S_OK;
}

STDMETHODIMP CotGraphicLayer::SelectElement(IElement* element)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	Element::IElementPtr pe =CInterfaceConvert::ConvertIElement(element);
	if(!pe)
	{
		return E_FAIL;
	}
	(*m_ppLayer)->SelectElement(pe);

	return S_OK;
}

STDMETHODIMP CotGraphicLayer::IsElementSelected(IElement* element, VARIANT_BOOL* bSelected)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	Element::IElementPtr pe =CInterfaceConvert::ConvertIElement(element);
	if(!pe)
	{
		return E_FAIL;
	}
	*bSelected =((*m_ppLayer)->IsElementSelected(pe))?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CotGraphicLayer::UnselectElement(IElement* element)
{
	
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	Element::IElementPtr pe =CInterfaceConvert::ConvertIElement(element);
	if(!pe)
	{
		return E_FAIL;
	}
	(*m_ppLayer)->UnselectElement(pe);
	return S_OK;
}

STDMETHODIMP CotGraphicLayer::GetSelectedElement(LONG index,IElement** retElement)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	Element::IElementPtr pEle =(*m_ppLayer)->GetSelectedElement(index);

	CInterfaceConvert::ConvertElement(pEle,retElement);

	return S_OK;
}

STDMETHODIMP CotGraphicLayer::SelectAllElements(void)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	
	//(*m_ppLayer)->SelectAllElements();

	return S_OK;
}

STDMETHODIMP CotGraphicLayer::UnselectAllElements(void)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	(*m_ppLayer)->UnselectAllElements();

	return S_OK;
}
