// otField.cpp : CotField 的实现

#include "stdafx.h"
#include "otField.h"


// CotField


STDMETHODIMP CotField::get_Name(BSTR* pVal)
{
	// TODO: 在此添加实现代码

	*pVal =::SysAllocString(m_name.GetBSTR());
	return S_OK;
}

STDMETHODIMP CotField::put_Name(BSTR newVal)
{
	// TODO: 在此添加实现代码

    m_name =newVal;
	return S_OK;
}

STDMETHODIMP CotField::get_Length(LONG* pVal)
{
	// TODO: 在此添加实现代码

	*pVal =m_length;
	return S_OK;
}

STDMETHODIMP CotField::put_Length(LONG newVal)
{
	// TODO: 在此添加实现代码

	m_length =newVal;
	return S_OK;
}

STDMETHODIMP CotField::get_Type(otFieldType* pVal)
{
	// TODO: 在此添加实现代码

	*pVal =m_type;
	return S_OK;
}

STDMETHODIMP CotField::put_Type(otFieldType newVal)
{
	// TODO: 在此添加实现代码

	m_type =newVal;
	return S_OK;
}

STDMETHODIMP CotField::get_Precision(LONG* pVal)
{
	// TODO: 在此添加实现代码

	*pVal =m_precision;
	return S_OK;
}

STDMETHODIMP CotField::put_Precision(LONG newVal)
{
	// TODO: 在此添加实现代码

	m_precision =newVal;
	return S_OK;
}
