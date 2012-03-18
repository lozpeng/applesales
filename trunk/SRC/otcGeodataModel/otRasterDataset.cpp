// otRasterDataset.cpp : CotRasterDataset 的实现

#include "stdafx.h"
#include "otRasterDataset.h"


// CotRasterDataset

CotRasterDataset::CotRasterDataset()
{
	m_ppRasterDataset =NULL;
	m_bAutoDestroy =true;

	m_pSR =NULL;
}

CotRasterDataset::~CotRasterDataset()
{
	if(m_ppRasterDataset && m_bAutoDestroy)
	{
		delete m_ppRasterDataset;
	}

	if(m_pSR)
	{
		m_pSR->Release();
		m_pSR =NULL;
	}
}

bool CotRasterDataset::CheckPointer()
{
	if(!m_ppRasterDataset)
	{
		return false;
	}
	if(!(*m_ppRasterDataset))
	{

		return false;
	}
	return true;
}

/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotRasterDataset::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppRasterDataset;
	return S_OK;
}

STDMETHODIMP CotRasterDataset::put_OriginData(long  pVal)
{

	if(m_ppRasterDataset && m_bAutoDestroy)
	{
		delete m_ppRasterDataset;
	}

	m_ppRasterDataset =(Geodatabase::IRasterDatasetPtr*)(pVal);

	//获得投影信息
	std::string wkt =(*m_ppRasterDataset)->GetProjection();

	if(wkt.empty())
	{
		m_pSR =NULL;
	}
	else
	{
		CoCreateInstance(CLSID_otSpatialReference,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotSpatialReference),(void**)&m_pSR);

		_bstr_t str =wkt.c_str();
		VARIANT_BOOL suc;
		m_pSR->ImportFromWkt(str,&suc);

		//判断是否解析投影成功
		if(suc ==VARIANT_FALSE)
		{
			m_pSR->Release();
			m_pSR =NULL;
		}
	}

	return S_OK;
}

STDMETHODIMP CotRasterDataset::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotRasterDataset::put_AutoDestroy(long  pVal)
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
* 实现IotDataObject接口
******************************************************************************/

STDMETHODIMP CotRasterDataset::GetType(otDataType *type)
{
	*type =OT_RASTERDATASET;
	return S_OK;
}

STDMETHODIMP CotRasterDataset::GetName(BSTR *name)
{
	if(!m_ppRasterDataset)
	{
		return E_FAIL;
	}
	if(!(*m_ppRasterDataset))
	{
		return E_FAIL;
	}
	_bstr_t str =(*m_ppRasterDataset)->Getname().c_str();

	*name =SysAllocString(str.GetBSTR());

	return S_OK;
}

STDMETHODIMP CotRasterDataset::GetExtent(IotEnvelope **envelope)
{
	if(!m_ppRasterDataset)
	{
		*envelope =NULL;
		return E_FAIL;
	}
	if(!(*m_ppRasterDataset))
	{
		*envelope =NULL;
		return E_FAIL;
	}

	GEOMETRY::geom::Envelope extent;
	(*m_ppRasterDataset)->GetExtent(&extent);

	CoCreateInstance(CLSID_otEnvelope,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotEnvelope),(void**)envelope);

	(*envelope)->put_MinX(extent.getMinX());
	(*envelope)->put_MinY(extent.getMinY());
	(*envelope)->put_MaxX(extent.getMaxX());
	(*envelope)->put_MaxY(extent.getMaxY());

}

STDMETHODIMP CotRasterDataset::get_Workspace(IotWorkspace **pVal)
{
	if(!m_ppRasterDataset)
	{
		*pVal =NULL;
		return E_FAIL;
	}
	if(!(*m_ppRasterDataset))
	{
		*pVal =NULL;
		return E_FAIL;
	}

	Geodatabase::IWorkspace *pWorkspace =(*m_ppRasterDataset)->GetWorkspace();
	if(!pWorkspace)
	{
		*pVal =NULL;
	}
	else
	{
		IOriginDataPtr pData =NULL;
		CoCreateInstance(CLSID_otWorkspace,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

		pData->put_OriginData((long)pWorkspace);
		pData->put_AutoDestroy(FALSE);

		pData->QueryInterface(__uuidof(IotWorkspace),(void**)pVal);

	}

	return S_OK;
}

/*****************************************************************************
* 实现IotRasterDataset接口
******************************************************************************/
STDMETHODIMP CotRasterDataset::get_Writable(VARIANT_BOOL* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =(*m_ppRasterDataset)->IsWritable()?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CotRasterDataset::get_ChannelCount(LONG* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	
	*pVal =(*m_ppRasterDataset)->GetBandCount();

	return S_OK;
}

STDMETHODIMP CotRasterDataset::get_Width(LONG* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	long height;
	(*m_ppRasterDataset)->GetSize(pVal,&height);


	return S_OK;
}

STDMETHODIMP CotRasterDataset::get_Height(LONG* pVal)
{
	
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	long width;
	(*m_ppRasterDataset)->GetSize(&width,pVal);
	return S_OK;
}

STDMETHODIMP CotRasterDataset::get_Projection(BSTR* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	_bstr_t str =(*m_ppRasterDataset)->GetProjection().c_str();

	*pVal =SysAllocString(str);

	return S_OK;
}

STDMETHODIMP CotRasterDataset::put_Projection(BSTR newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	_bstr_t str =newVal;
    
	(*m_ppRasterDataset)->SetProjection(str);

	return S_OK;
}

STDMETHODIMP CotRasterDataset::get_HasPyramid(VARIANT_BOOL* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =(*m_ppRasterDataset)->HasPyramid()?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CotRasterDataset::CreateRasterBlock(LONG BandIndex,LONG width, LONG height,IotRasterBlock **ret)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	long lbandCount =(*m_ppRasterDataset)->GetBandCount();
	if(BandIndex<=0 || BandIndex>lbandCount)
	{
		return E_FAIL;
	}
	
	IotRasterBlock* pBlock =NULL;
	CoCreateInstance(CLSID_otRasterBlock,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotRasterBlock),(void**)&pBlock);

	pBlock->put_Width(width);
	pBlock->put_Height(height);
	pBlock->put_DataType(otBandType((*m_ppRasterDataset)->GetBandDataType(BandIndex)));

	//构造一个安全数组
	CComSafeArray<VARIANT> sa;
	SAFEARRAYBOUND bound;
	bound.cElements =width*height;

	bound.lLbound =0;

	sa.Create(&bound);
    
    VARIANT var;
	var.vt =VT_ARRAY |VT_VARIANT;

	var.parray =*(sa.GetSafeArrayPtr());

	pBlock->put_SafeArray(var);

    *ret =pBlock;



	return S_OK;
}

STDMETHODIMP CotRasterDataset::ReadData(LONG BandIndex, LONG row, LONG col, IotRasterBlock* RasterBlock)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	if(!RasterBlock)
	{
		return E_FAIL;
	}
	long lbandCount =(*m_ppRasterDataset)->GetBandCount();
	if(BandIndex<=0 || BandIndex>lbandCount)
	{
		return E_FAIL;
	}


	long lwidth,lheight;
	RasterBlock->get_Width(&lwidth);
	RasterBlock->get_Height(&lheight);
    
    CComSafeArray<VARIANT> sa;
	VARIANT var;
	//获取安全数组的指针
	RasterBlock->get_SafeArray(&var);
	sa.Attach(var.parray);

	Geodatabase::BANDDATATYPE type =(*m_ppRasterDataset)->GetBandDataType(BandIndex);

	
	long ltotal =lwidth*lheight;
	VARIANT value;
	switch(type)
	{
	case otBandType::OTB_BYTE:
		{
			unsigned char *pbuffer =new unsigned char[ltotal];
			if(!(*m_ppRasterDataset)->DataReadBand(BandIndex,row,col,lwidth,lheight,lwidth,lheight,pbuffer))
			{
				sa.Detach();
				delete []pbuffer;
				return E_FAIL;
			}
			value.vt =VT_UI1;
			for(long i=0;i<ltotal;i++)
			{
				value.bVal =((BYTE*)pbuffer)[i];
				sa.SetAt(i,value);
			}
			delete []pbuffer;
			break;
		}
	case otBandType::OTB_SHORT:
		{
			short *pbuffer =new short[ltotal];
			if(!(*m_ppRasterDataset)->DataReadBand(BandIndex,row,col,lwidth,lheight,lwidth,lheight,pbuffer))
			{
			    sa.Detach();
				delete []pbuffer;
				return E_FAIL;
				
			}
			value.vt =VT_I2;
			for(long i=0;i<ltotal;i++)
			{
				value.iVal =((short*)pbuffer)[i];
				sa.SetAt(i,value);
			}
			delete []pbuffer;
			break;
		}
	case otBandType::OTB_USHORT:
		{
			unsigned short* pbuffer =new unsigned short[ltotal];
			if(!(*m_ppRasterDataset)->DataReadBand(BandIndex,row,col,lwidth,lheight,lwidth,lheight,pbuffer))
			{
				sa.Detach();
				delete []pbuffer;
				return E_FAIL;
			}
			value.vt =VT_UI2;
			for(long i=0;i<ltotal;i++)
			{
				value.uiVal =((unsigned short*)pbuffer)[i];
				sa.SetAt(i,value);
			}
			delete []pbuffer;
			break;
		}
	case otBandType::OTB_LONG:
		{
			long *pbuffer =new long[ltotal];
			if(!(*m_ppRasterDataset)->DataReadBand(BandIndex,row,col,lwidth,lheight,lwidth,lheight,pbuffer))
			{
				sa.Detach();
				delete []pbuffer;
				return E_FAIL;
			}
			value.vt =VT_I4;
			for(long i=0;i<ltotal;i++)
			{
				value.lVal =((long*)pbuffer)[i];
				sa.SetAt(i,value);
			}
			delete []pbuffer;
			break;
		}
	case otBandType::OTB_FLOAT:
		{
			float *pbuffer =new float[ltotal];
			if(!(*m_ppRasterDataset)->DataReadBand(BandIndex,row,col,lwidth,lheight,lwidth,lheight,pbuffer))
			{
				sa.Detach();
				delete []pbuffer;
				return E_FAIL;
			}
			value.vt =VT_R4;
			for(long i=0;i<ltotal;i++)
			{
				value.fltVal =((float*)pbuffer)[i];
				sa.SetAt(i,value);
			}
			delete []pbuffer;
			break;
		}
	case otBandType::OTB_DOUBLE:
		{
			double *pbuffer =new double[ltotal];
			if(!(*m_ppRasterDataset)->DataReadBand(BandIndex,row,col,lwidth,lheight,lwidth,lheight,pbuffer))
			{
				sa.Detach();
				delete []pbuffer;
				return E_FAIL;
			}
			value.vt =VT_R8;
			for(long i=0;i<ltotal;i++)
			{
				value.dblVal =((double*)pbuffer)[i];
				sa.SetAt(i,value);
			}
			delete []pbuffer;
			break;
		}
	default:
		sa.Detach();
		return E_FAIL;
	}
	sa.Detach();


	return S_OK;
}

STDMETHODIMP CotRasterDataset::get_SpatialReference(IotSpatialReference** pVal)
{
	if(!CheckPointer())
	{

		return E_FAIL;
	}
	if(m_pSR)
	{
		*pVal =m_pSR;
		m_pSR->AddRef();
	}
	else
	{
		*pVal =NULL;
	}

	return S_OK;
}
