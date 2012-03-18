// otColor.cpp : CotColor µÄÊµÏÖ

#include "stdafx.h"
#include "otColor.h"


// CotColor


STDMETHODIMP CotColor::get_Red(LONG* pVal)
{
	

    *pVal =m_red;
	return S_OK;
}

STDMETHODIMP CotColor::put_Red(LONG newVal)
{
	if(newVal<0 || newVal>255)
	{
		return E_FAIL;
	}
	m_red =newVal;


	return S_OK;
}

STDMETHODIMP CotColor::get_Green(LONG* pVal)
{
	*pVal =m_green;

	return S_OK;
}

STDMETHODIMP CotColor::put_Green(LONG newVal)
{
	if(newVal<0 || newVal>255)
	{
		return E_FAIL;
	}
	m_green =newVal;

	return S_OK;
}

STDMETHODIMP CotColor::get_Blue(LONG* pVal)
{
	*pVal =m_blue;

	return S_OK;
}

STDMETHODIMP CotColor::put_Blue(LONG newVal)
{
	if(newVal<0 || newVal>255)
	{
		return E_FAIL;
	}
	m_blue =newVal;

	return S_OK;
}
