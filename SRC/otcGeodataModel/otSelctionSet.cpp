// otSelectionSet.cpp : CotSelctionSet 的实现

#include "stdafx.h"
#include "otSelctionSet.h"
#include "IFeatureClass.h"
#include  "SelectionSet.h"
// CotSelctionSet
CotSelctionSet::CotSelctionSet()
{
	m_ppSel =new Geodatabase::ISelctionSetPtr(new Geodatabase::CSelctionSet(NULL));

	m_bAutoDestroy =true;
}

CotSelctionSet::~CotSelctionSet()
{
	if(m_ppSel && m_bAutoDestroy)
	{
		delete m_ppSel;
	}
}

bool CotSelctionSet::CheckPointer()
{
	if(!m_ppSel)
	{
		return false;
	}
	if(!(*m_ppSel))
	{

		return false;
	}
	return true;
}

STDMETHODIMP CotSelctionSet::get_Count(LONG* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	*pVal =(*m_ppSel)->Count();

	return S_OK;
}

STDMETHODIMP CotSelctionSet::IsEOF(VARIANT_BOOL* ret)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*ret =((*m_ppSel)->IsEOF())?VARIANT_TRUE:VARIANT_FALSE;


	return S_OK;
}

STDMETHODIMP CotSelctionSet::ResetIndex(void)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	(*m_ppSel)->ResetIndex();

	return S_OK;
}

STDMETHODIMP CotSelctionSet::NextID(LONG* id)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	*id =(*m_ppSel)->NextID();

	return S_OK;
}

STDMETHODIMP CotSelctionSet::Add(LONG id)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
    (*m_ppSel)->Add(id);

	return S_OK;
}

STDMETHODIMP CotSelctionSet::get_Table(IotTable** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	Geodatabase::IFeatureClass *pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>((*m_ppSel)->GetTable());

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

/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotSelctionSet::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppSel;
	return S_OK;
}

STDMETHODIMP CotSelctionSet::put_OriginData(long  pVal)
{

	if(m_ppSel && m_bAutoDestroy)
	{
		delete m_ppSel;
	}

	m_ppSel =(Geodatabase::ISelctionSetPtr*)(pVal);

	return S_OK;
}

STDMETHODIMP CotSelctionSet::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotSelctionSet::put_AutoDestroy(long  pVal)
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

