// otFeatureCursor.cpp : CotFeatureCursor 的实现

#include "stdafx.h"
#include "otFeatureCursor.h"
#include "IFeatureClass.h"

// CotFeatureCursor
CotFeatureCursor::CotFeatureCursor()
{
	m_ppCursor =NULL;
	m_bAutoDestroy =true;
}

CotFeatureCursor::~CotFeatureCursor()
{
	if(m_ppCursor && m_bAutoDestroy)
	{
		delete m_ppCursor;
	}
}

STDMETHODIMP CotFeatureCursor::NextFeature(IotFeature** retFeature)
{
	// TODO: 在此添加实现代码

	if(!CheckPointer())
	{
		*retFeature =NULL;
		return E_FAIL;
	}

	Geodatabase::CFeaturePtr pFeature =(*m_ppCursor)->NextFeature();
	if(!pFeature)
	{
		*retFeature =NULL;
		return S_OK;
	}
	Geodatabase::CFeaturePtr *ppF =new Geodatabase::CFeaturePtr(pFeature);

	IOriginDataPtr pData;
	CoCreateInstance(CLSID_otFeature,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	pData->put_OriginData((long)ppF);
	pData->put_AutoDestroy(TRUE);

	pData->QueryInterface(__uuidof(IotFeature),(void**)retFeature);

	return S_OK;
}

STDMETHODIMP CotFeatureCursor::get_Table( IotTable **pVal)
{
	if(!CheckPointer())
	{
		*pVal =NULL;
		return E_FAIL;
	}

	Geodatabase::IFeatureClass *pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>((*m_ppCursor)->GetTable());

	if(!pFeatureClass)
	{
		*pVal =NULL;
		return E_FAIL;
	}
	Geodatabase::IFeatureClassPtr *ppF =new Geodatabase::IFeatureClassPtr(pFeatureClass);

	IOriginDataPtr pData;
	CoCreateInstance(CLSID_otFeatureClass,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	pData->put_OriginData((long)ppF);
	pData->put_AutoDestroy(FALSE);

	pData->QueryInterface(__uuidof(IotTable),(void**)pVal);

	return S_OK;

}

STDMETHODIMP CotFeatureCursor::NextRow(IotRow **row)
{
	IotFeature *pFeature =NULL;
	NextFeature(&pFeature);
	if(!pFeature)
	{
		*row =NULL;
		return S_OK;
	}
    pFeature->QueryInterface(__uuidof(IotRow),(void**)&row);
	pFeature->Release();

	return S_OK;
}

STDMETHODIMP CotFeatureCursor::IsEOF(VARIANT_BOOL *ret)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*ret =(*m_ppCursor)->IsEOF()?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}
/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotFeatureCursor::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppCursor;
	return S_OK;
}

STDMETHODIMP CotFeatureCursor::put_OriginData(long  pVal)
{

	if(m_ppCursor && m_bAutoDestroy)
	{
		delete m_ppCursor;
	}

	m_ppCursor =(Geodatabase::IFeatureCursorPtr*)(pVal);

	return S_OK;
}

STDMETHODIMP CotFeatureCursor::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotFeatureCursor::put_AutoDestroy(long  pVal)
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

bool CotFeatureCursor::CheckPointer()
{
	if(!m_ppCursor)
	{
		return false;
	}
	if(!(*m_ppCursor))
	{

		return false;
	}
	return true;
}