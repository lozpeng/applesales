// otFeatureLayer.cpp : CotFeatureLayer 的实现

#include "stdafx.h"
#include "otFeatureLayer.h"
#include "IFeatureClass.h"
#include "InterfaceConvert.h"
#include "SpatialQuery.h"
#include "FeatureLayer.h"
// CotFeatureLayer

CotFeatureLayer::CotFeatureLayer()
{
	//创建一个新的FeatureLayer
	m_ppLayer =new Carto::IFeatureLayerPtr(new Carto::CFeatureLayer());

	m_bAutoDestroy =true;
}

CotFeatureLayer::~CotFeatureLayer()
{
	if(m_ppLayer && m_bAutoDestroy)
	{
		delete m_ppLayer;
	}
}


/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotFeatureLayer::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppLayer;
	return S_OK;
}

STDMETHODIMP CotFeatureLayer::put_OriginData(long  pVal)
{

	if(m_ppLayer && m_bAutoDestroy)
	{
		delete m_ppLayer;
	}

	m_ppLayer =(Carto::IFeatureLayerPtr*)(pVal);

	return S_OK;
}

STDMETHODIMP CotFeatureLayer::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotFeatureLayer::put_AutoDestroy(long  pVal)
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

bool CotFeatureLayer::CheckPointer()
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
* 实现IotLayer接口
******************************************************************************/

STDMETHODIMP CotFeatureLayer::get_Name(BSTR *pVal)
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

STDMETHODIMP CotFeatureLayer::put_Name(BSTR newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
    _bstr_t str =newVal;

	(*m_ppLayer)->SetName((const char*)str);

	return S_OK;
}

STDMETHODIMP CotFeatureLayer::get_LayerDesciption(BSTR *pVal)
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

STDMETHODIMP CotFeatureLayer::put_LayerDesciption(BSTR newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	_bstr_t str =newVal;

	(*m_ppLayer)->SetLayerDescription((const char*)str);
	return S_OK;
}

STDMETHODIMP CotFeatureLayer::get_LayerType(otLayerType *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
    *pVal =(otLayerType)(*m_ppLayer)->GetLayerType();
    return S_OK;
}

STDMETHODIMP CotFeatureLayer::get_Visible(VARIANT_BOOL *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =(*m_ppLayer)->GetVisible()?VARIANT_TRUE:VARIANT_FALSE;


    return S_OK;
}

STDMETHODIMP CotFeatureLayer::put_Visible(VARIANT_BOOL newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	bool bv =(newVal==VARIANT_FALSE)?false:true;
	(*m_ppLayer)->SetVisible(bv);


    return S_OK;
}

STDMETHODIMP CotFeatureLayer::get_ScaleRangeValid(VARIANT_BOOL *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
    *pVal =(*m_ppLayer)->GetEnableScaleRange()?VARIANT_TRUE:VARIANT_FALSE;
    return S_OK;
}

STDMETHODIMP CotFeatureLayer::put_ScaleRangeValid(VARIANT_BOOL newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	bool bv =(newVal==VARIANT_FALSE)?false:true;
	(*m_ppLayer)->SetEnableScaleRange(bv);
    return S_OK;
}

STDMETHODIMP CotFeatureLayer::get_ScaleRangeMin(DOUBLE *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =(*m_ppLayer)->GetScaleRangeMin();
	return S_OK;
}

STDMETHODIMP CotFeatureLayer::put_ScaleRangeMin(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
    (*m_ppLayer)->SetScaleRangeMin(newVal);
	return S_OK;
}

STDMETHODIMP CotFeatureLayer::get_ScaleRangeMax(DOUBLE *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
    *pVal =(*m_ppLayer)->GetScaleRangeMax();
	return S_OK;
}

STDMETHODIMP CotFeatureLayer::put_ScaleRangeMax(DOUBLE newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	(*m_ppLayer)->SetScaleRangeMax(newVal);
	return S_OK;
}

STDMETHODIMP CotFeatureLayer::get_DataObject(IotDataObject **pVal)
{
	if(!CheckPointer())
	{
		*pVal =NULL;
		return E_FAIL;
	}
    
	Geodatabase::IFeatureClassPtr pFeatureClass =(*m_ppLayer)->GetDataObject();
	if(!pFeatureClass)
	{
		*pVal =NULL;
		return E_FAIL;
	}
	Geodatabase::IFeatureClassPtr *ppF =new Geodatabase::IFeatureClassPtr(pFeatureClass);

	IOriginDataPtr pData;

	CoCreateInstance(CLSID_otFeatureClass,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	pData->put_OriginData((long)ppF);
	pData->put_AutoDestroy(TRUE);

	pData->QueryInterface(__uuidof(IotDataObject),(void**)pVal);

    

	return S_OK;
}

STDMETHODIMP CotFeatureLayer::put_DataObject(IotDataObject *newVal)
{
	if(!CheckPointer())
	{
		
		return E_FAIL;
	}
	IotFeatureClassPtr pf;
	HRESULT hr =newVal->QueryInterface(__uuidof(IotFeatureClass),(void**)&pf);
	if(FAILED(hr))
	{
		return E_FAIL;
	}
    IOriginDataPtr pData;
	pf->QueryInterface(__uuidof(IOriginData),(void**)&pData);

    long lval;
	pData->get_OriginData(&lval);

	Geodatabase::IFeatureClassPtr *ppf =(Geodatabase::IFeatureClassPtr*)lval;
	if(!ppf)
	{
		return E_FAIL;
	}
	(*m_ppLayer)->SetData(*ppf);


	return S_OK;
}


STDMETHODIMP CotFeatureLayer::get_SelectionSet(IotSelectionSet** pVal)
{
	if(!CheckPointer())
	{

		return E_FAIL;
	}
	Geodatabase::ISelctionSetPtr pSel =(*m_ppLayer)->GetSelection();

	if(!pSel)
	{
		*pVal =NULL;
		return S_OK;
	}
	Geodatabase::ISelctionSetPtr *ppS =new Geodatabase::ISelctionSetPtr(pSel);

	IOriginDataPtr pData;

	CoCreateInstance(CLSID_otSelectionSet,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);
    
	pData->put_OriginData(long(ppS));
	pData->put_AutoDestroy(TRUE);

	pData->QueryInterface(__uuidof(IotSelectionSet),(void**)pVal);


	return S_OK;
}

STDMETHODIMP CotFeatureLayer::put_SelectionSet(IotSelectionSet* newVal)
{
	if(!CheckPointer())
	{

		return E_FAIL;
	}

	if(!newVal)
	{

        (*m_ppLayer)->SetSelection(NULL);
		return S_OK;
	}
	IOriginDataPtr pData;
	newVal->QueryInterface(__uuidof(IOriginData),(void**)&pData);

	long lval;
	pData->get_OriginData(&lval);

	Geodatabase::ISelctionSetPtr pSel =*((Geodatabase::ISelctionSetPtr*)lval);


    (*m_ppLayer)->SetSelection(pSel);
	return S_OK;
}

STDMETHODIMP CotFeatureLayer::ClearSelection(void)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	(*m_ppLayer)->ClearSelectionSet();

	return S_OK;
}

STDMETHODIMP CotFeatureLayer::Select(IotSimpleQuery* queryFilter, otSelectOption option)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	//判断查询是普通查询还是空间查询
	IotSpatialQuery *sq =NULL;
	queryFilter->QueryInterface(__uuidof(IotSpatialQuery),(void**)&sq);

	if(sq)
	{
		//空间查询
		Geodatabase::CSpatialQuery query;

		BSTR fields=NULL;
		queryFilter->get_Fields(&fields);
		_bstr_t str;
		str.Attach(fields);

		BSTR strWhere =NULL;
		queryFilter->get_WhereString(&strWhere);

		_bstr_t where ;

		if(strWhere)
		{
			where.Attach(strWhere);
		}
		query.SetFields(str);
		query.SetWhereString(where);

		//得到空间查询条件
		otSpatialRel rel;
		sq->get_SpatialRelation(&rel);
		query.SetSpatialRel(long(rel));

		//得到查询几何体
		IotGeometry *pg =NULL;
		sq->get_Geometry(&pg);

		if(!pg)
		{
			sq->Release();
			return E_FAIL;
		}

		IotGeoConvertPtr con;

		CoCreateInstance(CLSID_otGeoConvert,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotGeoConvert),(void**)&con);
        
		long ldata;
		con->ConvertIGeo(pg,&ldata);

		GEOMETRY::geom::Geometry *pgeo =(GEOMETRY::geom::Geometry*)ldata;

		query.SetGeometry(pgeo);

		(*m_ppLayer)->Select(&query,(Carto::SELECT_OPTION)option);



	}
	else
	{
		//普通查询
		Geodatabase::CSimpleQuery query;

		BSTR fields=NULL;
		queryFilter->get_Fields(&fields);
		_bstr_t str;
		str.Attach(fields);

		BSTR strWhere =NULL;
		queryFilter->get_WhereString(&strWhere);

		_bstr_t where ;
		if(strWhere)
		{
			where.Attach(strWhere);
		}
		query.SetFields(str);
		query.SetWhereString(where);

		(*m_ppLayer)->Select(&query,(Carto::SELECT_OPTION)option);


	}

	return S_OK;
}

//获取渲染器
STDMETHODIMP CotFeatureLayer::get_Render(IotFeatureRender** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	Carto::IRenderPtr pRender =(*m_ppLayer)->GetFeatureRender();

	CInterfaceConvert::ConvertFeatureRender(pRender,pVal);

	return S_OK;
}

//设置渲染器
STDMETHODIMP CotFeatureLayer::put_Render(IotFeatureRender* newVal)
{
	
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	Carto::IRenderPtr pRender =CInterfaceConvert::ConvertIFeatureRender(newVal);

	(*m_ppLayer)->SetFeatureRender(pRender);

	return S_OK;
}
