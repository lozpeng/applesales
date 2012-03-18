#include "stdafx.h"
#include "otSimpleQuery.h"



CotSimpleQuery::CotSimpleQuery()
{
	m_strFields =_T("*");
	m_strWhere =_T("");

}
STDMETHODIMP CotSimpleQuery::get_Fields(BSTR* pVal)
{
	// TODO: �ڴ����ʵ�ִ���

	*pVal =SysAllocString(m_strFields);
	return S_OK;
}

STDMETHODIMP CotSimpleQuery::put_Fields(BSTR newVal)
{
	// TODO: �ڴ����ʵ�ִ���

	m_strFields =newVal;
	return S_OK;
}

STDMETHODIMP CotSimpleQuery::get_WhereString(BSTR* pVal)
{
	// TODO: �ڴ����ʵ�ִ���

    *pVal =SysAllocString(m_strWhere);
	return S_OK;
}

STDMETHODIMP CotSimpleQuery::put_WhereString(BSTR newVal)
{
	// TODO: �ڴ����ʵ�ִ���
    
	m_strWhere =newVal;
	return S_OK;
}

STDMETHODIMP CotSimpleQuery::AddField(BSTR fieldname)
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
