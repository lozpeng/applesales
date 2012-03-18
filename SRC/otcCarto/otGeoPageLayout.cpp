// otGeoPageLayout.cpp : CotGeoPageLayout 的实现

#include "stdafx.h"
#include "otGeoPageLayout.h"


// CotGeoPageLayout
CotGeoPageLayout::CotGeoPageLayout()
{
	//创建一个新的GeoPageLayout
	m_ppLayout =new Carto::CPageLayoutPtr(new Carto::CPageLayout());

	m_bAutoDestroy =true;
}

CotGeoPageLayout::~CotGeoPageLayout()
{
	if(m_ppLayout && m_bAutoDestroy)
	{
		delete m_ppLayout;
	}
}

bool CotGeoPageLayout::CheckPointer()
{
	if(!m_ppLayout)
	{
		return false;
	}
	if(!(*m_ppLayout))
	{

		return false;
	}
	return true;
} 

STDMETHODIMP CotGeoPageLayout::get_GraphicLayer(IotGraphicLayer** pVal)
{
	
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	Carto::CGraphicLayerPtr pLayer =(*m_ppLayout)->GetGraphicLayer();
	if(!pLayer)
	{
		*pVal =NULL;
		return E_FAIL;
	}
	Carto::CGraphicLayerPtr *ppF =new Carto::CGraphicLayerPtr(pLayer);

	IOriginDataPtr pData;

	CoCreateInstance(CLSID_otGraphicLayer,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	pData->put_OriginData((long)ppF);
	pData->put_AutoDestroy(TRUE);

	pData->QueryInterface(__uuidof(IotGraphicLayer),(void**)pVal);
	return S_OK;
}


/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotGeoPageLayout::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppLayout;
	return S_OK;
}

STDMETHODIMP CotGeoPageLayout::put_OriginData(long  pVal)
{

	if(m_ppLayout && m_bAutoDestroy)
	{
		delete m_ppLayout;
	}

	m_ppLayout =(Carto::CPageLayoutPtr*)(pVal);

	return S_OK;
}

STDMETHODIMP CotGeoPageLayout::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotGeoPageLayout::put_AutoDestroy(long  pVal)
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


STDMETHODIMP CotGeoPageLayout::get_Page(IotPage** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	Element::CPagePtr pPage =(*m_ppLayout)->GetPage();
	if(!pPage)
	{
		*pVal =NULL;
		return S_OK;
	}
	Element::CPagePtr *ppF =new Element::CPagePtr(pPage);

	IOriginDataPtr pData;

	CoCreateInstance(CLSID_otPage,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	pData->put_OriginData((long)ppF);
	pData->put_AutoDestroy(TRUE);

	pData->QueryInterface(__uuidof(IotPage),(void**)pVal);
	return S_OK;

}
