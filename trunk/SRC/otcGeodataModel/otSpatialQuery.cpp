// otSpatialQuery.cpp : CotSpatialQuery 的实现

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
	// TODO: 在此添加实现代码

	*pVal =SysAllocString(m_strFields);
	return S_OK;
}

STDMETHODIMP CotSpatialQuery::put_Fields(BSTR newVal)
{
	// TODO: 在此添加实现代码

	m_strFields =newVal;
	return S_OK;
}

STDMETHODIMP CotSpatialQuery::get_WhereString(BSTR* pVal)
{
	// TODO: 在此添加实现代码

	*pVal =SysAllocString(m_strWhere);
	return S_OK;
}

STDMETHODIMP CotSpatialQuery::put_WhereString(BSTR newVal)
{
	// TODO: 在此添加实现代码

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
	// TODO: 在此添加实现代码
    
	*pVal =m_spatialRel;
	return S_OK;
}

STDMETHODIMP CotSpatialQuery::put_SpatialRelation(otSpatialRel newVal)
{
	// TODO: 在此添加实现代码

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
		//增加引用
		m_pGeometry->AddRef();
	}
    
	return S_OK;
}
