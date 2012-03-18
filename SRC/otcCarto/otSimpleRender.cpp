// otSimpleRender.cpp : CotSimpleRender 的实现

#include "stdafx.h"
#include "otSimpleRender.h"


// CotSimpleRender
CotSimpleRender::CotSimpleRender()
{
	m_ppRender =new Carto::CSimpleRenderPtr(new Carto::CSimpleRender());

	m_bAutoDestroy =true;
}

CotSimpleRender::~CotSimpleRender()
{
	if(m_ppRender && m_bAutoDestroy)
	{
		delete m_ppRender;
	}
}

bool CotSimpleRender::CheckPointer()
{
	if(!m_ppRender)
	{
		return false;
	}
	if(!(*m_ppRender))
	{

		return false;
	}
	return true;
}

STDMETHODIMP CotSimpleRender::get_Symbol(IotSymbol** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	Display::ISymbolPtr pSymbol =(*m_ppRender)->GetSymbol();

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

STDMETHODIMP CotSimpleRender::put_Symbol(IotSymbol* newVal)
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

	(*m_ppRender)->SetSymbol(*((Display::ISymbolPtr*)lval));

	return S_OK;
}

/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotSimpleRender::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppRender;
	return S_OK;
}

STDMETHODIMP CotSimpleRender::put_OriginData(long  pVal)
{

	if(m_ppRender && m_bAutoDestroy)
	{
		delete m_ppRender;
	}

	m_ppRender =(Carto::CSimpleRenderPtr*)(pVal);

	return S_OK;
}

STDMETHODIMP CotSimpleRender::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotSimpleRender::put_AutoDestroy(long  pVal)
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
* 实现IotFeatureRender接口
******************************************************************************/

STDMETHODIMP CotSimpleRender::get_RenderType(otFeatureRenderType * pVal)
{
	
	*pVal =OTSIMPLERENDER;
	return S_OK;
}

