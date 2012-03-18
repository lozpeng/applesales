// otWorkspace.cpp : CotWorkspace 的实现

#include "stdafx.h"
#include "otWorkspace.h"
#include "IFeatureClass.h"
#include "IRasterDataset.h"

// CotWorkspace

CotWorkspace::CotWorkspace()
{
	//数据源指针是由各个WorkspaceFactory来管理，CotWorkspace不负责销毁
    m_pWorkspace =NULL;

}

/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotWorkspace::get_OriginData(long * pVal)
{

	*pVal =(long)m_pWorkspace;
	return S_OK;
}

STDMETHODIMP CotWorkspace::put_OriginData(long  pVal)
{

	m_pWorkspace =(Geodatabase::IWorkspace*)(pVal);
	return S_OK;
}

STDMETHODIMP CotWorkspace::get_AutoDestroy(long * pVal)
{

	*pVal =FALSE;
	return S_OK;
}

STDMETHODIMP CotWorkspace::put_AutoDestroy(long  pVal)
{

	return S_OK;
}

/*****************************************************************************
* 实现IotWorkspace接口
******************************************************************************/

STDMETHODIMP CotWorkspace::get_Type(otWorkspaceType* pVal)
{
	// TODO: 在此添加实现代码

    if(!m_pWorkspace)
	{
		return E_FAIL;
	}
	*pVal =(otWorkspaceType)m_pWorkspace->GetType();

	return S_OK;
}

STDMETHODIMP CotWorkspace::get_Path(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	if(!m_pWorkspace)
	{
		return E_FAIL;
	}

	_bstr_t path =m_pWorkspace->GetPathname().c_str();

	*pVal =SysAllocString(path);
	return S_OK;
}

STDMETHODIMP CotWorkspace::OpenFeatureClass(BSTR filename, IotFeatureClass** FeatureClass)
{
	// TODO: 在此添加实现代码
	if(!m_pWorkspace)
	{
		return E_FAIL;
	}
    _bstr_t str =filename;

	Geodatabase::IFeatureClassPtr pFeatureClass =m_pWorkspace->OpenFeatureClass(str);
	if(!pFeatureClass)
	{
		*FeatureClass =NULL;
		return E_FAIL;
	}

	//拷贝一份引用
	Geodatabase::IFeatureClassPtr *ppF =new Geodatabase::IFeatureClassPtr(pFeatureClass); 
    
	IOriginDataPtr pData;
	CoCreateInstance(CLSID_otFeatureClass,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	pData->put_OriginData((long)ppF);
	pData->put_AutoDestroy(TRUE);

	pData->QueryInterface(__uuidof(IotFeatureClass),(void**)FeatureClass);


	return S_OK;
}

STDMETHODIMP CotWorkspace::IsEditing(VARIANT_BOOL* bret)
{
	if(!m_pWorkspace)
	{
		return E_FAIL;
	}
	*bret =(m_pWorkspace->IsEditing()) ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CotWorkspace::StartEdit(void)
{
	if(!m_pWorkspace)
	{
		return E_FAIL;
	}

	m_pWorkspace->StartEdit();

	return S_OK;
}

STDMETHODIMP CotWorkspace::StopEdit(VARIANT_BOOL save)
{
	if(!m_pWorkspace)
	{
		return E_FAIL;
	}

	m_pWorkspace->StopEdit((save==VARIANT_FALSE)?false:true);


	return S_OK;
}

STDMETHODIMP CotWorkspace::StartEditOperation(void)
{
	if(!m_pWorkspace)
	{
		return E_FAIL;
	}

	m_pWorkspace->StartEditOperation();

	return S_OK;
}

STDMETHODIMP CotWorkspace::StopEditOperation(void)
{
	if(!m_pWorkspace)
	{
		return E_FAIL;
	}

	m_pWorkspace->StopEditOperation();

	return S_OK;
}

STDMETHODIMP CotWorkspace::UndoEdit(void)
{
	if(!m_pWorkspace)
	{
		return E_FAIL;
	}

	m_pWorkspace->UndoEdit();

	return S_OK;
}

STDMETHODIMP CotWorkspace::RedoEdit(void)
{
	if(!m_pWorkspace)
	{
		return E_FAIL;
	}

	m_pWorkspace->RedoEdit();

	return S_OK;
}

STDMETHODIMP CotWorkspace::CanUndo(VARIANT_BOOL* bret)
{
	if(!m_pWorkspace)
	{
		return E_FAIL;
	}

	*bret =(m_pWorkspace->CanUndo())?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CotWorkspace::CanRedo(VARIANT_BOOL* ret)
{
	if(!m_pWorkspace)
	{
		return E_FAIL;
	}

	*ret =(m_pWorkspace->CanRedo())?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CotWorkspace::OpenRasterDataset(BSTR filename, VARIANT_BOOL ReadOnly, IotRasterDataset** ret)
{
	if(!m_pWorkspace)
	{
		return E_FAIL;
	}
	_bstr_t file =filename;

	Geodatabase::IRasterDatasetPtr pRaster =m_pWorkspace->OpenRasterDataset(file,(ReadOnly==VARIANT_FALSE)?false:true);

	if(!pRaster)
	{
		*ret =NULL;
		return E_FAIL;
	}

	Geodatabase::IRasterDatasetPtr *ppR =new Geodatabase::IRasterDatasetPtr(pRaster);

	IOriginDataPtr pData;
	CoCreateInstance(CLSID_otRasterDataset,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	pData->put_OriginData((long)ppR);
	pData->put_AutoDestroy(TRUE);

	pData->QueryInterface(__uuidof(IotRasterDataset),(void**)ret);


	return S_OK;
}

STDMETHODIMP CotWorkspace::CreateFeatureClass(BSTR filename, IotEnvelope* extent, BSTR projWkt, otGeometryType FeatureType, VARIANT_BOOL hasZ, VARIANT_BOOL hasM, LONG numField, SAFEARRAY** fields, IotFeatureClass** retFeatureClass)
{
	
	if(!m_pWorkspace)
	{
		return E_FAIL;
	}
	_bstr_t file =filename;

	Geodatabase::FeatureClassDef def;
	if(extent)
	{
		//设置数据范围
		extent->get_MinX(&def.minx);
		extent->get_MaxX(&def.maxx);
		extent->get_MinY(&def.miny);
		extent->get_MaxY(&def.maxy);

	}
	_bstr_t wkt =projWkt;
	def.wkt =(const char*)wkt;
	long type;
	switch(FeatureType)
	{
	case OT_GEOM_POINT:
		{

			type =GEOMETRY::geom::GEOS_POINT;
			break;
		}
	case OT_GEOM_LINESTRING:
		{

			type =GEOMETRY::geom::GEOS_LINESTRING;
			break;
		}
	case OT_GEOM_LINERING:
		{
			type =GEOMETRY::geom::GEOS_LINESTRING;
			break;
		}
	case OT_GEOM_MULTIPOINT:
		{
			type =GEOMETRY::geom::GEOS_MULTIPOINT;
			break;
		}
	case OT_GEOM_MULTILINESTRING:
		{
			type =GEOMETRY::geom::GEOS_MULTILINESTRING;
			break;
		}
	case OT_GEOM_POLYGON:
	case OT_GEOM_MULTIPOLYGON:
		{
			type =GEOMETRY::geom::GEOS_POLYGON;
			break;
		}
	
	default:
		type =GEOMETRY::geom::GEOM_NULL;
		break;
	}
    //要素类型
	def.lshptype =type;
	def.hasz =(hasZ==VARIANT_FALSE)?false:true;
	def.hasm =(hasM==VARIANT_FALSE)?false:true;

	//设置字段
	
	Geodatabase::CFieldPtr pField;
	_bstr_t tempstr;
	BSTR str =NULL;
	otFieldType ftype;
	long length;
	CComSafeArray<IUnknown*> safeFields;
	safeFields.Attach(*fields);

	IotField *pf =NULL;
	for(long i=0;i<numField;i++)
	{
		safeFields[i]->QueryInterface(__uuidof(IotField),(void**)&pf);

		pField =new Geodatabase::CField();
        
        pf->get_Name(&str);
		tempstr =str;

		//设置字段名
		pField->SetName(tempstr);
		if(str)
		{
			::SysFreeString(str);
			str =NULL;
		}
		
		pf->get_Type(&ftype);
		//设置字段类型
		pField->SetType((long)ftype);

		//设置字段长度
        pf->get_Length(&length);
		pField->SetLength(length);


		//设置精度
		pf->get_Precision(&length);
		pField->SetPrecision(length);

        def.FieldsDef.push_back(pField);
        
	}

	safeFields.Detach();


	Geodatabase::IFeatureClassPtr pFeatureClass =m_pWorkspace->CreateFeatureClass(file,def);

	if(!pFeatureClass)
	{
		*retFeatureClass =NULL;
		return E_FAIL;
	}

	//拷贝一份引用
	Geodatabase::IFeatureClassPtr *ppF =new Geodatabase::IFeatureClassPtr(pFeatureClass); 

	IOriginDataPtr pData;
	CoCreateInstance(CLSID_otFeatureClass,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	pData->put_OriginData((long)ppF);
	pData->put_AutoDestroy(TRUE);

	pData->QueryInterface(__uuidof(IotFeatureClass),(void**)retFeatureClass);


	return S_OK;
}
