// otEnvelope.cpp : Envelope 的实现

#include "stdafx.h"
#include "otEnvelope.h"


// Envelope

otEnvelope::otEnvelope() 
{
	m_minx =m_miny =m_maxx=m_maxy =0.0;
}


STDMETHODIMP otEnvelope::get_MinX(double *pVal)
{
	// TODO: 在此添加实现代码
    *pVal =m_minx;
	return S_OK;
}

STDMETHODIMP otEnvelope::put_MinX(double newVal)
{
	m_minx =newVal;
    
	return S_OK;

}

STDMETHODIMP otEnvelope::get_MinY(double *pVal)
{
	// TODO: 在此添加实现代码
	*pVal =m_miny;
	return S_OK;
}

STDMETHODIMP otEnvelope::put_MinY(double newVal)
{
	m_miny =newVal;

	return S_OK;

}

STDMETHODIMP otEnvelope::get_MaxX(double *pVal)
{
	// TODO: 在此添加实现代码
	*pVal =m_maxx;
	return S_OK;
}

STDMETHODIMP otEnvelope::put_MaxX(double newVal)
{
	m_maxx =newVal;

	return S_OK;

}

STDMETHODIMP otEnvelope::get_MaxY(double *pVal)
{
	// TODO: 在此添加实现代码
	*pVal =m_maxy;
	return S_OK;
}

STDMETHODIMP otEnvelope::put_MaxY(double newVal)
{
	m_maxy =newVal;

	return S_OK;

}