// otRasterLayer.cpp : CotRasterLayer 的实现

#include "stdafx.h"
#include "otRasterLayer.h"
#include "IRasterDataset.h"
#include "RasterRGBRender.h"

// CotRasterLayer
CotRasterLayer::CotRasterLayer()
{
	//创建一个新的RasterLayer
	m_ppLayer =new Carto::CRasterLayerPtr(new Carto::CRasterLayer());

	m_bAutoDestroy =true;
}

CotRasterLayer::~CotRasterLayer()
{
	if(m_ppLayer && m_bAutoDestroy)
	{
		delete m_ppLayer;
	}
}

bool CotRasterLayer::CheckPointer()
{
	if(!m_ppLayer)
	{
		return false;
	}
	if(!(*m_ppLayer))
	{

		return false;
	}
	return true;
}

/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotRasterLayer::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppLayer;
	return S_OK;
}

STDMETHODIMP CotRasterLayer::put_OriginData(long  pVal)
{

	if(m_ppLayer && m_bAutoDestroy)
	{
		delete m_ppLayer;
	}

	m_ppLayer =(Carto::CRasterLayerPtr*)(pVal);

	return S_OK;
}

STDMETHODIMP CotRasterLayer::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotRasterLayer::put_AutoDestroy(long  pVal)
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



/*****************************************************************************
* 实现IotLayer接口
******************************************************************************/

STDMETHODIMP CotRasterLayer::get_Name(BSTR *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	std::string name =(*m_ppLayer)->GetName();
	_bstr_t str =name.c_str();
	*pVal =SysAllocString(str);
	return S_OK;
}

STDMETHODIMP CotRasterLayer::put_Name(BSTR newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	_bstr_t str =newVal;

	(*m_ppLayer)->SetName((const char*)str);

	return S_OK;
}

STDMETHODIMP CotRasterLayer::get_LayerDesciption(BSTR *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	std::string name =(*m_ppLayer)->GetLayerDesciption();
	_bstr_t str =name.c_str();
	*pVal =SysAllocString(str);
	return S_OK;
}

STDMETHODIMP CotRasterLayer::put_LayerDesciption(BSTR newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	_bstr_t str =newVal;

	(*m_ppLayer)->SetLayerDescription((const char*)str);
	return S_OK;
}

STDMETHODIMP CotRasterLayer::get_LayerType(otLayerType *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =(otLayerType)(*m_ppLayer)->GetLayerType();
	return S_OK;
}

STDMETHODIMP CotRasterLayer::get_Visible(VARIANT_BOOL *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =(*m_ppLayer)->GetVisible()?VARIANT_TRUE:VARIANT_FALSE;


	return S_OK;
}

STDMETHODIMP CotRasterLayer::put_Visible(VARIANT_BOOL newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	bool bv =(newVal==VARIANT_FALSE)?false:true;
	(*m_ppLayer)->SetVisible(bv);


	return S_OK;
}

STDMETHODIMP CotRasterLayer::get_ScaleRangeValid(VARIANT_BOOL *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =(*m_ppLayer)->GetEnableScaleRange()?VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CotRasterLayer::put_ScaleRangeValid(VARIANT_BOOL newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	bool bv =(newVal==VARIANT_FALSE)?false:true;
	(*m_ppLayer)->SetEnableScaleRange(bv);
	return S_OK;
}

STDMETHODIMP CotRasterLayer::get_ScaleRangeMin(DOUBLE *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =(*m_ppLayer)->GetScaleRangeMin();
	return S_OK;
}

STDMETHODIMP CotRasterLayer::put_ScaleRangeMin(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	(*m_ppLayer)->SetScaleRangeMin(newVal);
	return S_OK;
}

STDMETHODIMP CotRasterLayer::get_ScaleRangeMax(DOUBLE *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =(*m_ppLayer)->GetScaleRangeMax();
	return S_OK;
}

STDMETHODIMP CotRasterLayer::put_ScaleRangeMax(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	(*m_ppLayer)->SetScaleRangeMax(newVal);
	return S_OK;
}

STDMETHODIMP CotRasterLayer::get_DataObject(IotDataObject **pVal)
{
	if(!CheckPointer())
	{
		*pVal =NULL;
		return E_FAIL;
	}

	Geodatabase::IRasterDatasetPtr pRaster =(*m_ppLayer)->GetDataObject();
	if(!pRaster)
	{
		*pVal =NULL;
		return E_FAIL;
	}
	Geodatabase::IRasterDatasetPtr *ppF =new Geodatabase::IRasterDatasetPtr(pRaster);

	IOriginDataPtr pData;

	CoCreateInstance(CLSID_otRasterDataset,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	pData->put_OriginData((long)ppF);
	pData->put_AutoDestroy(TRUE);

	pData->QueryInterface(__uuidof(IotDataObject),(void**)pVal);



	return S_OK;
}

STDMETHODIMP CotRasterLayer::put_DataObject(IotDataObject *newVal)
{
	if(!CheckPointer())
	{

		return E_FAIL;
	}
	IotRasterDatasetPtr pf;
	HRESULT hr =newVal->QueryInterface(__uuidof(IotRasterDataset),(void**)&pf);
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	IOriginDataPtr pData;
	pf->QueryInterface(__uuidof(IOriginData),(void**)&pData);

	long lval;
	pData->get_OriginData(&lval);

	Geodatabase::IRasterDatasetPtr *ppf =(Geodatabase::IRasterDatasetPtr*)lval;
	if(!ppf)
	{
		return E_FAIL;
	}
	(*m_ppLayer)->SetData(*ppf);


	return S_OK;
}

STDMETHODIMP CotRasterLayer::get_TransparentValue(LONG* pVal)
{
	if(!CheckPointer())
	{

		return E_FAIL;
	}
	*pVal =(*m_ppLayer)->GetTransparentValue();

	return S_OK;
}

STDMETHODIMP CotRasterLayer::put_TransparentValue(LONG newVal)
{
	
	if(!CheckPointer())
	{

		return E_FAIL;
	}
	(*m_ppLayer)->SetTransparent(newVal);

	return S_OK;
}

STDMETHODIMP CotRasterLayer::Enhance(RasterEnhanceType type)
{
	if(!CheckPointer())
	{

		return E_FAIL;
	}

	Carto::CRasterRGBRenderPtr pRender =(*m_ppLayer)->GetRender();

	if(pRender)
	{
		pRender->ApplyEnhanceDraw(long(type));
	}

	return S_OK;
}

STDMETHODIMP CotRasterLayer::SetBrightAndContrast(LONG bright, LONG contrast)
{
	if(!CheckPointer())
	{

		return E_FAIL;
	}
	Carto::CRasterRGBRenderPtr pRender =(*m_ppLayer)->GetRender();

	if(pRender)
	{
		if(pRender->GetRGBMode())
		{
            BYTE rlut[256],glut[256],blut[256];
			for(int i=0;i<256;i++)
			{
				rlut[i] =glut[i] =blut[i] =i;
			}
			pRender->SetBrightAndContrast(rlut,glut,blut,bright,contrast);
		}
		else
		{
			BYTE rlut[256];
			for(int i=0;i<256;i++)
			{
				rlut[i] =i;
			}
			pRender->SetBrightAndContrast(rlut,bright,contrast);
		}
	}

	return S_OK;
}
