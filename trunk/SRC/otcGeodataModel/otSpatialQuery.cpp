// otSpatialQuery.cpp : CotSpatialQuery ��ʵ��

#include "stdafx.h"
#include "otSpatialQuery.h"


// CotSpatialQuery


CotSpatialQuery::CotSpatialQuery()
{
	m_strFields =_T("*");
	m_strWhere =_T("");

	m_pGeometry=NULL;
	m_spatialRel =otSpatialRelUndefined;
}

CotSpatialQuery::~CotSpatialQuery()
{
	if(m_pGeometry)
	{
		m_pGeometry->Release();
	}
}
STDMETHODIMP CotSpatialQuery::get_Fields(BSTR* pVal)
{
	// TODO: �ڴ����ʵ�ִ���

	*pVal =SysAllocString(m_strFields);
	return S_OK;
}

STDMETHODIMP CotSpatialQuery::put_Fields(BSTR newVal)
{
	// TODO: �ڴ����ʵ�ִ���

	m_strFields =newVal;
	return S_OK;
}

STDMETHODIMP CotSpatialQuery::get_WhereString(BSTR* pVal)
{
	// TODO: �ڴ����ʵ�ִ���

	*pVal =SysAllocString(m_strWhere);
	return S_OK;
}

STDMETHODIMP CotSpatialQuery::put_WhereString(BSTR newVal)
{
	// TODO: �ڴ����ʵ�ִ���

	m_strWhere =newVal;
	return S_OK;
}

STDMETHODIMP CotSpatialQuery::AddField(BSTR fieldname)
{

	_bstr_t str =fieldname;

	if(m_strFields==str)
	{
		m_strFields =fieldname;
	}
	else
	{
		m_strFields+=_T(",");
		m_strFields+=fieldname;
	}
	return S_OK;
}
STDMETHODIMP CotSpatialQuery::get_SpatialRelation(otSpatialRel* pVal)
{
	// TODO: �ڴ����ʵ�ִ���
    
	*pVal =m_spatialRel;
	return S_OK;
}

STDMETHODIMP CotSpatialQuery::put_SpatialRelation(otSpatialRel newVal)
{
	// TODO: �ڴ����ʵ�ִ���

	m_spatialRel =newVal;
	return S_OK;
}

STDMETHODIMP CotSpatialQuery::get_Geometry(IotGeometry** pVal)
{
	*pVal =m_pGeometry;
    
	return S_OK;
}

STDMETHODIMP CotSpatialQuery::put_Geometry(IotGeometry* newVal)
{
	if(newVal)
	{
		m_pGeometry =newVal;
		//��������
		m_pGeometry->AddRef();
	}
    
	return S_OK;
}
