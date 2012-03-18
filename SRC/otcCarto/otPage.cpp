// otPage.cpp : CotPage 的实现

#include "stdafx.h"
#include "otPage.h"


// CotPage
CotPage::CotPage()
{
	m_ppPage =new Element::CPagePtr(new Element::CPage());

	m_bAutoDestroy =true;

}

CotPage::~CotPage()
{
	if(m_ppPage && m_bAutoDestroy)
	{
		delete m_ppPage;
	}
}

bool CotPage::CheckPointer()
{
	if(!m_ppPage)
	{
		return false;
	}
	if(!(*m_ppPage))
	{
		return false;
	}
	return true;
}

STDMETHODIMP CotPage::get_PageEnvelope(IotEnvelope** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	
	CoCreateInstance(CLSID_otEnvelope,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotEnvelope),(void**)pVal);

	
	//得到当前视图的范围
	GEOMETRY::geom::Envelope envelope =(*m_ppPage)->GetPageEnvelope();;


	(*pVal)->put_MinX(envelope.getMinX());
	(*pVal)->put_MinY(envelope.getMinY());
	(*pVal)->put_MaxX(envelope.getMaxX());
	(*pVal)->put_MaxY(envelope.getMaxY());

	return S_OK;
}

/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotPage::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppPage;
	return S_OK;
}

STDMETHODIMP CotPage::put_OriginData(long  pVal)
{

	if(m_ppPage && m_bAutoDestroy)
	{
		delete m_ppPage;
		m_ppPage =NULL;
	}

	m_ppPage =(Element::CPagePtr*)pVal;

	return S_OK;
}

STDMETHODIMP CotPage::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotPage::put_AutoDestroy(long  pVal)
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

