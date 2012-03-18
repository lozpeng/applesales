// otSpatialReference.cpp : CotSpatialReference 的实现

#include "stdafx.h"
#include "otSpatialReference.h"


// CotSpatialReference

CotSpatialReference::CotSpatialReference()
{
	//创建一个新的SpatialReference
	m_ppSR =new Geodatabase::CSpatialReferencePtr(new Geodatabase::CSpatialReference());

	m_bAutoDestroy =true;
}

CotSpatialReference::~CotSpatialReference()
{
	if(m_ppSR && m_bAutoDestroy)
	{
		delete m_ppSR;
	}

}

bool CotSpatialReference::CheckPointer()
{
	if(!m_ppSR)
	{
		return false;
	}
	if(!(*m_ppSR))
	{

		return false;
	}
	return true;
}

/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotSpatialReference::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppSR;
	return S_OK;
}

STDMETHODIMP CotSpatialReference::put_OriginData(long  pVal)
{

	if(m_ppSR && m_bAutoDestroy)
	{
		delete m_ppSR;
	}

	m_ppSR =(Geodatabase::CSpatialReferencePtr*)(pVal);

	return S_OK;
}

STDMETHODIMP CotSpatialReference::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotSpatialReference::put_AutoDestroy(long  pVal)
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


STDMETHODIMP CotSpatialReference::Clone(IotSpatialReference** spatialReference)
{
	
    if(!CheckPointer())
	{
		return E_FAIL;
	}
	Geodatabase::CSpatialReference *ps =(*m_ppSR)->Clone();
	if(!ps)
	{
		*spatialReference=NULL;
		return S_FALSE;
	}
	Geodatabase::CSpatialReferencePtr *pps =new Geodatabase::CSpatialReferencePtr(ps);

	IOriginDataPtr pData;
	CoCreateInstance(CLSID_otSpatialReference,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	pData->put_OriginData((long)pps);
	pData->put_AutoDestroy(TRUE);

    pData->QueryInterface(__uuidof(IotSpatialReference),(void**)spatialReference);

	return S_OK;
}

STDMETHODIMP CotSpatialReference::ImportFromWkt(BSTR wkt, VARIANT_BOOL* bSuccess)
{

	if(!CheckPointer())
	{
		return E_FAIL;
	}
    _bstr_t str =wkt;
	*bSuccess =(*m_ppSR)->ImportFromWkt(str)?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CotSpatialReference::ImportFromESRI(BSTR wkt, VARIANT_BOOL* bSuccess)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	_bstr_t str =wkt;
	*bSuccess =(*m_ppSR)->ImportFromESRI(str)?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CotSpatialReference::ExportToWkt(BSTR* wkt)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
    _bstr_t str =(*m_ppSR)->ExportToWkt().c_str();

	*wkt =SysAllocString(str);

	return S_OK;
}

STDMETHODIMP CotSpatialReference::IsGeographic(VARIANT_BOOL* bRet)
{
	
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	*bRet =(*m_ppSR)->IsGeographic()?VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CotSpatialReference::IsProjected(VARIANT_BOOL* bRet)
{
	
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	*bRet =(*m_ppSR)->IsProjected()?VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CotSpatialReference::IsSame(IotSpatialReference* other, VARIANT_BOOL* bSame)
{
	
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	if(!other)
	{
		*bSame =VARIANT_FALSE;
		return S_OK;
	}
	IOriginDataPtr pData;
	other->QueryInterface(__uuidof(IOriginData),(void**)&pData);
	long ldata;
	pData->get_OriginData(&ldata);

	Geodatabase::CSpatialReference *ps =(*(Geodatabase::CSpatialReferencePtr*)ldata).get();

	*bSame =(*m_ppSR)->IsSame(ps)?VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CotSpatialReference::GetGeogName(BSTR* name)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	_bstr_t str =(*m_ppSR)->GetGeogName().c_str();

	*name =SysAllocString(str);
	return S_OK;
}

STDMETHODIMP CotSpatialReference::GetProjName(BSTR* name)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	_bstr_t str =(*m_ppSR)->GetProjName().c_str();

	*name =SysAllocString(str);

	return S_OK;
}
