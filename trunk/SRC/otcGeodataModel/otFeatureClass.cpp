// otFeatureClass.cpp : CotFeatureClass 的实现

#include "stdafx.h"
#include "otFeatureClass.h"
#include "SpatialQuery.h"
#include "IFeatureCursor.h"
// CotFeatureClass


CotFeatureClass::CotFeatureClass()
{
	m_ppFeatureClass =NULL;
	m_bAutoDestroy =true;

	m_pSR =NULL;
}

CotFeatureClass::~CotFeatureClass()
{
	if(m_ppFeatureClass && m_bAutoDestroy)
	{
		delete m_ppFeatureClass;
	}

	if(m_pSR)
	{
		m_pSR->Release();
		m_pSR =NULL;
	}
}

/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotFeatureClass::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppFeatureClass;
	return S_OK;
}

STDMETHODIMP CotFeatureClass::put_OriginData(long  pVal)
{

	if(m_ppFeatureClass && m_bAutoDestroy)
	{
		delete m_ppFeatureClass;
	}
    
	m_ppFeatureClass =(Geodatabase::IFeatureClassPtr*)(pVal);

	//获得投影信息
	std::string wkt =(*m_ppFeatureClass)->GetWkt();

	if(wkt.empty())
	{
		m_pSR =NULL;
	}
	else
	{
        CoCreateInstance(CLSID_otSpatialReference,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotSpatialReference),(void**)&m_pSR);

		_bstr_t str =wkt.c_str();
		VARIANT_BOOL suc;
		m_pSR->ImportFromESRI(str,&suc);

		//判断是否解析投影成功
		if(suc ==VARIANT_FALSE)
		{
            m_pSR->Release();
			m_pSR =NULL;
		}
	}
	
	return S_OK;
}

STDMETHODIMP CotFeatureClass::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotFeatureClass::put_AutoDestroy(long  pVal)
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

STDMETHODIMP CotFeatureClass::GetType(otDataType *type)
{
	*type =OT_FEATURECLASS;
	return S_OK;
}

STDMETHODIMP CotFeatureClass::GetName(BSTR *name)
{
	if(!m_ppFeatureClass)
	{
		return E_FAIL;
	}
	if(!(*m_ppFeatureClass))
	{
		return E_FAIL;
	}
	_bstr_t str =(*m_ppFeatureClass)->Getname().c_str();

	*name =SysAllocString(str.GetBSTR());

	return S_OK;
}

STDMETHODIMP CotFeatureClass::GetExtent(IotEnvelope **envelope)
{
	if(!m_ppFeatureClass)
	{
		*envelope =NULL;
		return E_FAIL;
	}
	if(!(*m_ppFeatureClass))
	{
		*envelope =NULL;
		return E_FAIL;
	}

	GEOMETRY::geom::Envelope extent;
	(*m_ppFeatureClass)->GetExtent(&extent);
     
	CoCreateInstance(CLSID_otEnvelope,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotEnvelope),(void**)envelope);

	(*envelope)->put_MinX(extent.getMinX());
	(*envelope)->put_MinY(extent.getMinY());
	(*envelope)->put_MaxX(extent.getMaxX());
	(*envelope)->put_MaxY(extent.getMaxY());

	return S_OK;

}

STDMETHODIMP CotFeatureClass::get_Workspace(IotWorkspace **pVal)
{
	if(!m_ppFeatureClass)
	{
		*pVal =NULL;
		return E_FAIL;
	}
	if(!(*m_ppFeatureClass))
	{
		*pVal =NULL;
		return E_FAIL;
	}

	Geodatabase::IWorkspace *pWorkspace =(*m_ppFeatureClass)->GetWorkspace();
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


bool CotFeatureClass::CheckPointer()
{
	if(!m_ppFeatureClass)
	{
		return false;
	}
	if(!(*m_ppFeatureClass))
	{
		
		return false;
	}
	return true;
}
/*****************************************************************************
* 实现IotFeatureClass接口
******************************************************************************/
STDMETHODIMP CotFeatureClass::get_FeatureCount(LONG* pVal)
{
	// TODO: 在此添加实现代码
    
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =(*m_ppFeatureClass)->FeatureCount();
	return S_OK;
}




STDMETHODIMP CotFeatureClass::get_ShapeFieldName(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	_bstr_t str =(*m_ppFeatureClass)->ShapeFieldName().c_str();

	*pVal =SysAllocString(str);

	return S_OK;
}

STDMETHODIMP CotFeatureClass::GetFeature(LONG index, IotFeature** feature)
{
	
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	Geodatabase::CFeaturePtr pFeature =(*m_ppFeatureClass)->GetFeature(index);

	if(!pFeature)
	{
		*feature =NULL;
		return E_FAIL;
	}

	Geodatabase::CFeaturePtr *ppFeature =new Geodatabase::CFeaturePtr(pFeature);

	IOriginDataPtr pData;
	CoCreateInstance(CLSID_otFeature,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	pData->put_OriginData((long)ppFeature);
	pData->put_AutoDestroy(TRUE);

	pData->QueryInterface(__uuidof(IotFeature),(void**)feature);

	return S_OK;
}

STDMETHODIMP CotFeatureClass::get_HasM(VARIANT_BOOL* pVal)
{
	// TODO: 在此添加实现代码
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =((*m_ppFeatureClass)->HasM())? VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CotFeatureClass::get_HasZ(VARIANT_BOOL* pVal)
{
	// TODO: 在此添加实现代码
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	*pVal =((*m_ppFeatureClass)->HasZ())? VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CotFeatureClass::Query(IotSimpleQuery* queryFilter, VARIANT_BOOL bReadOnly, IotCursor** retCursor)
{
	// TODO: 在此添加实现代码
    
	if(!CheckPointer())
	{
		*retCursor =NULL;
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

		query.SetGeometry(pgeo->clone());

		bool bRead =(bReadOnly==VARIANT_FALSE) ?false:true;
		Geodatabase::ICursorPtr pCursor =(*m_ppFeatureClass)->Query(&query,bRead);

		if(!pCursor)
		{
			*retCursor =NULL;
			return E_FAIL;
		}
		Geodatabase::IFeatureCursorPtr *ppF =new Geodatabase::IFeatureCursorPtr(pCursor);

		IOriginDataPtr pData;
		CoCreateInstance(CLSID_otFeatureCursor,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

		pData->put_OriginData((long)ppF);
		pData->put_AutoDestroy(TRUE);


		HRESULT hr=  pData->QueryInterface(__uuidof(IotCursor),(void**)retCursor);


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

		bool bRead =(bReadOnly==VARIANT_FALSE) ?false:true;
		Geodatabase::ICursorPtr pCursor =(*m_ppFeatureClass)->Query(&query,bRead);

		if(!pCursor)
		{
			*retCursor =NULL;
			return E_FAIL;
		}
		Geodatabase::IFeatureCursorPtr *ppF =new Geodatabase::IFeatureCursorPtr(pCursor);

		IOriginDataPtr pData;
		CoCreateInstance(CLSID_otFeatureCursor,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

		pData->put_OriginData((long)ppF);
		pData->put_AutoDestroy(TRUE);

		
		HRESULT hr=  pData->QueryInterface(__uuidof(IotCursor),(void**)retCursor);


	}

	return S_OK;
}

STDMETHODIMP CotFeatureClass::get_ShapeType(otGeometryType* pVal)
{
	
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	long type =(*m_ppFeatureClass)->ShapeType();
	switch(type)
	{
	case GEOMETRY::geom::GEOS_POINT:
		{

            *pVal =OT_GEOM_POINT;
			break;
		}
	case GEOMETRY::geom::GEOS_LINESTRING:
		{

			*pVal =OT_GEOM_LINESTRING;
			break;
		}
	case GEOMETRY::geom::GEOS_LINEARRING:
		{
		    *pVal =OT_GEOM_LINERING;
			break;
		}
	case GEOMETRY::geom::GEOS_MULTIPOINT:
		{
			*pVal =OT_GEOM_MULTIPOINT;
			break;
		}
	case GEOMETRY::geom::GEOS_MULTILINESTRING:
		{
			*pVal =OT_GEOM_MULTILINESTRING;
			break;
		}
	case GEOMETRY::geom::GEOS_POLYGON:
		{
			*pVal =OT_GEOM_POLYGON;
			break;
		}
	case GEOMETRY::geom::GEOS_MULTIPOLYGON:
		{
			*pVal =OT_GEOM_POLYGON;
			break;
		}

	default:
		*pVal =OT_GEOM_NULL;
		break;
	}
	return S_OK;
}

STDMETHODIMP CotFeatureClass::CreateFeature(IotFeature** retFeature)
{
	
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	Geodatabase::CFeaturePtr pFeature =(*m_ppFeatureClass)->CreateFeature();

	if(!pFeature)
	{
		*retFeature =NULL;
		return E_FAIL;
	}

	Geodatabase::CFeaturePtr *ppFeature =new Geodatabase::CFeaturePtr(pFeature);

	IOriginDataPtr pData;
	CoCreateInstance(CLSID_otFeature,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	pData->put_OriginData((long)ppFeature);
	pData->put_AutoDestroy(TRUE);

	pData->QueryInterface(__uuidof(IotFeature),(void**)retFeature);
	return S_OK;
}

STDMETHODIMP CotFeatureClass::DeleteFeature(LONG index)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	(*m_ppFeatureClass)->DeleteFeature(index);

	return S_OK;
}

STDMETHODIMP CotFeatureClass::Select(IotSimpleQuery* queryFilter, IotSelectionSet** ret)
{
	if(!CheckPointer())
	{
		*ret =NULL;
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

		query.SetGeometry(pgeo->clone());

		Geodatabase::ISelctionSetPtr pSel =(*m_ppFeatureClass)->Select(&query);

		if(!pSel)
		{
			*ret =NULL;
			return E_FAIL;
		}
		Geodatabase::ISelctionSetPtr *ppF =new Geodatabase::ISelctionSetPtr(pSel);

		IOriginDataPtr pData;
		CoCreateInstance(CLSID_otSelectionSet,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

		pData->put_OriginData((long)ppF);
		pData->put_AutoDestroy(TRUE);


		pData->QueryInterface(__uuidof(IotSelectionSet),(void**)ret);



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

	
		Geodatabase::ISelctionSetPtr pSel =(*m_ppFeatureClass)->Select(&query);

		if(!pSel)
		{
			*ret =NULL;
			return E_FAIL;
		}
		Geodatabase::ISelctionSetPtr *ppF =new Geodatabase::ISelctionSetPtr(pSel);

		IOriginDataPtr pData;
		CoCreateInstance(CLSID_otSelectionSet,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

		pData->put_OriginData((long)ppF);
		pData->put_AutoDestroy(TRUE);


		pData->QueryInterface(__uuidof(IotSelectionSet),(void**)ret);


	}

	return S_OK;
}

STDMETHODIMP CotFeatureClass::get_FieldCount(LONG* pVal)
{
	if(!CheckPointer())
	{
		
		return E_FAIL;
	}

	*pVal =(*m_ppFeatureClass)->FieldCount();

	return S_OK;
}

STDMETHODIMP CotFeatureClass::GetField(LONG index, IotField** field)
{
	if(!CheckPointer())
	{

		return E_FAIL;
	}

	Geodatabase::CFieldPtr pField =(*m_ppFeatureClass)->GetField(index);
	if(!pField)
	{
		
		return E_FAIL;
	}

	//建立一个字段对象
	CoCreateInstance(CLSID_otField,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotField),(void**)field);

	(*field)->put_Length(pField->GetLength());
	(*field)->put_Precision(pField->Precision());
	(*field)->put_Type((otFieldType)pField->GetType());

	_bstr_t name =pField->GetName().c_str();
	(*field)->put_Name(name);

	return S_OK;
}

STDMETHODIMP CotFeatureClass::FindField(BSTR name, LONG* index)
{
	if(!CheckPointer())
	{

		return E_FAIL;
	}
	_bstr_t str =name;
	*index =(*m_ppFeatureClass)->FindField(str);


	return S_OK;
}

STDMETHODIMP CotFeatureClass::AddFeature(IotFeature* feature)
{
	if(!CheckPointer())
	{

		return E_FAIL;
	}
    if(!feature)
	{
		return E_FAIL;
	}
	IOriginDataPtr pData;
	feature->QueryInterface(__uuidof(IOriginData),(void**)&pData);
	long ldata;
	pData->get_OriginData(&ldata);

	(*m_ppFeatureClass)->AddFeature(((Geodatabase::CFeaturePtr*)ldata)->get());
	return S_OK;
}

STDMETHODIMP CotFeatureClass::get_SpatialReference(IotSpatialReference** pVal)
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
