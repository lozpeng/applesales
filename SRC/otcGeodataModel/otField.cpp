// otField.cpp : CotField ��ʵ��

#include "stdafx.h"
#include "otField.h"


// CotField


STDMETHODIMP CotField::get_Name(BSTR* pVal)
{
	// TODO: �ڴ����ʵ�ִ���

	*pVal =::SysAllocString(m_name.GetBSTR());
	return S_OK;
}

STDMETHODIMP CotField::put_Name(BSTR newVal)
{
	// TODO: �ڴ����ʵ�ִ���

    m_name =newVal;
	return S_OK;
}

STDMETHODIMP CotField::get_Length(LONG* pVal)
{
	// TODO: �ڴ����ʵ�ִ���

	*pVal =m_length;
	return S_OK;
}

STDMETHODIMP CotField::put_Length(LONG newVal)
{
	// TODO: �ڴ����ʵ�ִ���

	m_length =newVal;
	return S_OK;
}

STDMETHODIMP CotField::get_Type(otFieldType* pVal)
{
	// TODO: �ڴ����ʵ�ִ���

	*pVal =m_type;
	return S_OK;
}

STDMETHODIMP CotField::put_Type(otFieldType newVal)
{
	// TODO: �ڴ����ʵ�ִ���

	m_type =newVal;
	return S_OK;
}

STDMETHODIMP CotField::get_Precision(LONG* pVal)
{
	// TODO: �ڴ����ʵ�ִ���

	*pVal =m_precision;
	return S_OK;
}

STDMETHODIMP CotField::put_Precision(LONG newVal)
{
	// TODO: �ڴ����ʵ�ִ���

	m_precision =newVal;
	return S_OK;
}
