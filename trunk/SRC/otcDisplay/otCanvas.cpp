// otCanvas.cpp : CotCanvas 的实现

#include "stdafx.h"
#include "otCanvas.h"


// CotCanvas

CotCanvas::CotCanvas()
{
	m_ppDisplay=new Display::IDisplayPtr(new Display::IDisplay());
	m_bAutoDestroy =true;
}

CotCanvas::~CotCanvas()
{
    if(m_bAutoDestroy && m_ppDisplay)
	{
		delete m_ppDisplay;
	}
}

/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotCanvas::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppDisplay;
	return S_OK;
}

STDMETHODIMP CotCanvas::put_OriginData(long  pVal)
{

	if(m_ppDisplay && m_bAutoDestroy)
	{
		delete m_ppDisplay;
		m_ppDisplay=NULL;

	}

	m_ppDisplay =(Display::IDisplayPtr*)pVal;

	
	return S_OK;
}

STDMETHODIMP CotCanvas::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotCanvas::put_AutoDestroy(long  pVal)
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