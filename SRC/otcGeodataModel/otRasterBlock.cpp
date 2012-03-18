// otRasterBlock.cpp : CotRasterBlock µÄÊµÏÖ

#include "stdafx.h"
#include "otRasterBlock.h"


// CotRasterBlock
CotRasterBlock::CotRasterBlock()
{
   
	m_type =OTB_UNKNOWN;
	m_lwidth =m_lheight =0;
}

CotRasterBlock::~CotRasterBlock()
{

}

STDMETHODIMP CotRasterBlock::get_DataType(otBandType* pVal)
{
	
    *pVal =m_type;
	return S_OK;
}

STDMETHODIMP CotRasterBlock::put_DataType(otBandType newVal)
{

	m_type =newVal;

	return S_OK;
}

STDMETHODIMP CotRasterBlock::get_Width(LONG* pVal)
{
    *pVal =m_lwidth;

	return S_OK;
}

STDMETHODIMP CotRasterBlock::put_Width(LONG newVal)
{
	m_lwidth =newVal;

	return S_OK;
}

STDMETHODIMP CotRasterBlock::get_Height(LONG* pVal)
{
	*pVal= m_lheight;

	return S_OK;
}

STDMETHODIMP CotRasterBlock::put_Height(LONG newVal)
{
	m_lheight =newVal;

	return S_OK;
}

STDMETHODIMP CotRasterBlock::GetValue(LONG X, LONG Y, VARIANT* value)
{
	long index =Y*m_lwidth +X;

	*value =m_sa.GetAt(index);
	return S_OK;
}

STDMETHODIMP CotRasterBlock::get_SafeArray(VARIANT* pVal)
{
	pVal->vt =VT_ARRAY |VT_VARIANT;
	pVal->parray =*m_sa.GetSafeArrayPtr();

	return S_OK;
}

STDMETHODIMP CotRasterBlock::put_SafeArray(VARIANT newVal)
{
	
    m_sa =newVal.parray;

	return S_OK;
}
