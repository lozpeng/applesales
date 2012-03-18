// otProjTransform.cpp : CotProjTransform 的实现

#include "stdafx.h"
#include "otProjTransform.h"


// CotProjTransform
CotProjTransform::CotProjTransform()
{
	//创建一个新的ProjTransform
	m_ppTrans =new Geodatabase::CProjTransformPtr(new Geodatabase::CProjTransform());

	m_bAutoDestroy =true;
}

CotProjTransform::~CotProjTransform()
{
	if(m_ppTrans && m_bAutoDestroy)
	{
		delete m_ppTrans;
	}
}

bool CotProjTransform::CheckPointer()
{
	if(!m_ppTrans)
	{
		return false;
	}
	if(!(*m_ppTrans))
	{

		return false;
	}
	return true;
}

/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotProjTransform::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppTrans;
	return S_OK;
}

STDMETHODIMP CotProjTransform::put_OriginData(long  pVal)
{

	if(m_ppTrans && m_bAutoDestroy)
	{
		delete m_ppTrans;
	}

	m_ppTrans =(Geodatabase::CProjTransformPtr*)(pVal);

	return S_OK;
}

STDMETHODIMP CotProjTransform::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotProjTransform::put_AutoDestroy(long  pVal)
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

STDMETHODIMP CotProjTransform::get_FromSpatialReference(IotSpatialReference** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	Geodatabase::CSpatialReferencePtr ps =(*m_ppTrans)->GetSourceCS();
	if(!ps)
	{
		*pVal =NULL;
		return S_OK;
	}
	Geodatabase::CSpatialReferencePtr *pps =new Geodatabase::CSpatialReferencePtr(ps);

	IOriginDataPtr pData;
	CoCreateInstance(CLSID_otSpatialReference,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	pData->put_OriginData((long)pps);
	pData->put_AutoDestroy(TRUE);

	pData->QueryInterface(__uuidof(IotSpatialReference),(void**)pVal);

	return S_OK;
}

STDMETHODIMP CotProjTransform::get_ToSpatialReference(IotSpatialReference** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	Geodatabase::CSpatialReferencePtr ps =(*m_ppTrans)->GetTargetCS();
	if(!ps)
	{
		*pVal =NULL;
		return S_OK;
	}
	Geodatabase::CSpatialReferencePtr *pps =new Geodatabase::CSpatialReferencePtr(ps);

	IOriginDataPtr pData;
	CoCreateInstance(CLSID_otSpatialReference,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	pData->put_OriginData((long)pps);
	pData->put_AutoDestroy(TRUE);

	pData->QueryInterface(__uuidof(IotSpatialReference),(void**)pVal);

	return S_OK;
}

STDMETHODIMP CotProjTransform::SetSpatialReference(IotSpatialReference* from, IotSpatialReference* to)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	if(!from || !to)
	{
		(*m_ppTrans)->Init(NULL,NULL);
		return S_OK;
	}
	IOriginDataPtr pData;
	from->QueryInterface(__uuidof(IOriginData),(void**)&pData);
	long ldata;
	pData->get_OriginData(&ldata);

	Geodatabase::CSpatialReferencePtr pFrom =*(Geodatabase::CSpatialReferencePtr*)ldata;

	to->QueryInterface(__uuidof(IOriginData),(void**)&pData);
	pData->get_OriginData(&ldata);

	Geodatabase::CSpatialReferencePtr pTo =*(Geodatabase::CSpatialReferencePtr*)ldata;

    (*m_ppTrans)->Init(pFrom,pTo);

	return S_OK;
}

STDMETHODIMP CotProjTransform::Transform(LONG count, SAFEARRAY** inX, SAFEARRAY** inY, SAFEARRAY** outX, SAFEARRAY** outY)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

    double *dxs =new double[count];
	double *dys =new double[count];

	CComSafeArray<double> safeInx;
	CComSafeArray<double> safeIny;

	safeInx.Attach(*inX);
	safeIny.Attach(*inY);

	for(long i=0;i<count;i++)
	{
		dxs[i] =safeInx[i];
		dys[i] =safeIny[i];

	}
	safeInx.Detach();
	safeIny.Detach();

	//转换
    (*m_ppTrans)->Transform(count,dxs,dys);

	//将转换结果放到输出数组中
	safeInx.Attach(*outX);
	safeIny.Attach(*outY);

	for(long i=0;i<count;i++)
	{
		safeInx[i] = dxs[i] ;
		safeIny[i] = dys[i] ;

	}
	safeInx.Detach();
	safeIny.Detach();


	return S_OK;
}
