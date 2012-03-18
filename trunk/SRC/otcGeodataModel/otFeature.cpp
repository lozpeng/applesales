// otFeature.cpp : CotFeature 的实现

#include "stdafx.h"
#include "otFeature.h"
#include "IFeatureClass.h"

// CotFeature
CotFeature::CotFeature()
{
	m_ppFeature =NULL;
	m_bAutoDestroy =true;
}

CotFeature::~CotFeature()
{
	if(m_ppFeature && m_bAutoDestroy)
	{
		delete m_ppFeature;
	}
}

/*****************************************************************************
* 实现IotRow接口
******************************************************************************/
STDMETHODIMP CotFeature::get_Table(IotTable **pVal)
{
    if(!CheckPointer())
	{
		*pVal =NULL;
		return E_FAIL;
	}
	Geodatabase::IFeatureClass *pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>
		((*m_ppFeature)->GetTable());

	if(!pFeatureClass)
	{
		*pVal =NULL;
		return S_OK;
	}

	Geodatabase::IFeatureClassPtr *ppFc =new Geodatabase::IFeatureClassPtr(pFeatureClass);
	IOriginDataPtr pData;
	CoCreateInstance(CLSID_otFeatureClass,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	pData->put_OriginData((long)ppFc);
	pData->put_AutoDestroy(FALSE);

	pData->QueryInterface(__uuidof(IotTable),(void**)pVal);
    


	return S_OK;
}

STDMETHODIMP CotFeature::get_ID(LONG *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =(*m_ppFeature)->GetId();
	return S_OK;
}

STDMETHODIMP CotFeature::get_FieldCount(LONG *pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	*pVal =(*m_ppFeature)->FieldCount();
	return S_OK;
}

STDMETHODIMP CotFeature::get_Field( LONG index,  IotField * * pVal)
{
	if(!CheckPointer())
	{
		*pVal =NULL;
		return E_FAIL;
	}
	Geodatabase::CFieldPtr pField =(*m_ppFeature)->GetField(index);
	if(!pField)
	{
		*pVal =NULL;
		return E_FAIL;
	}

	//建立一个字段对象
    CoCreateInstance(CLSID_otField,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotField),(void**)pVal);
    
	(*pVal)->put_Length(pField->GetLength());
	(*pVal)->put_Precision(pField->Precision());
	(*pVal)->put_Type((otFieldType)pField->GetType());

	_bstr_t name =pField->GetName().c_str();
	(*pVal)->put_Name(name);
	


	return S_OK;
}

STDMETHODIMP CotFeature::get_Value( LONG index,  VARIANT * pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	long lcount =(*m_ppFeature)->FieldCount();

	//判断序号是否越界
	if(index<0 || index>=lcount)
	{
		return E_FAIL;
	}
    
	Geodatabase::FieldValue &fval =(*m_ppFeature)->GetValue(index+1);
	ConFval2Var(fval,*pVal);

	return S_OK;
}

STDMETHODIMP CotFeature::put_Value(LONG index, VARIANT newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	long lcount =(*m_ppFeature)->FieldCount();

	//判断序号是否越界
	if(index<0 || index>=lcount)
	{
		return E_FAIL;
	}

	Geodatabase::FieldValue fval;
	ConvVar2Fval(newVal,fval);
	(*m_ppFeature)->m_values[index] =fval;

	return S_OK;
}

STDMETHODIMP CotFeature::get_Shape(IotGeometry** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =(*m_ppFeature)->GetShape();

	if(!pg)
	{
		*pVal =NULL;
		return E_FAIL;
	}
    IotGeoConvertPtr con;

     CoCreateInstance(CLSID_otGeoConvert,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotGeoConvert),(void**)&con);

	 con->ConvertGeo((long)pg,VARIANT_FALSE,pVal);


    
	return S_OK;
}

STDMETHODIMP CotFeature::put_Shape(IotGeometry* newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	IotGeoConvertPtr con;

	CoCreateInstance(CLSID_otGeoConvert,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotGeoConvert),(void**)&con);
    
	long ldata;
	con->ConvertIGeo(newVal,&ldata);

	GEOMETRY::geom::Geometry *pg =(GEOMETRY::geom::Geometry*)ldata;

	(*m_ppFeature)->SetShape(pg->clone());

	////将组件对象中的指针设为不自动销毁
	//IOriginDataPtr pData;
	//newVal->QueryInterface(__uuidof(IOriginData),(void**)&pData);

	//pData->put_AutoDestroy(FALSE);

	return S_OK;
}

STDMETHODIMP CotFeature::get_ShapeClone(IotGeometry** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =(*m_ppFeature)->GetShapeClone();

	if(!pg)
	{
		*pVal =NULL;
		return E_FAIL;
	}
	IotGeoConvertPtr con;

	CoCreateInstance(CLSID_otGeoConvert,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotGeoConvert),(void**)&con);

	con->ConvertGeo((long)pg,VARIANT_TRUE,pVal);

	return S_OK;
}


/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotFeature::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppFeature;
	return S_OK;
}

STDMETHODIMP CotFeature::put_OriginData(long  pVal)
{

	if(m_ppFeature && m_bAutoDestroy)
	{
		delete m_ppFeature;
	}

	m_ppFeature =(Geodatabase::CFeaturePtr*)(pVal);

	return S_OK;
}

STDMETHODIMP CotFeature::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotFeature::put_AutoDestroy(long  pVal)
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

bool CotFeature::CheckPointer()
{
	if(!m_ppFeature)
	{
		return false;
	}
	if(!(*m_ppFeature))
	{
		
		return false;
	}
	return true;
}

void CotFeature::ConFval2Var(Geodatabase::FieldValue &fval, VARIANT &var)
{
    switch(fval.vtype)
	{
	case Geodatabase::FieldValue::VT_BOOL:
		{
			var.vt =VT_BOOL;
			var.boolVal=(fval.m_Var.bVal)? VARIANT_TRUE : VARIANT_FALSE;

			break;
		}
	case Geodatabase::FieldValue::VT_FLOAT:
		{
			var.vt =VT_R4;
			var.fltVal =fval.m_Var.fVal;
			break;
		}
	case Geodatabase::FieldValue::VT_DOUBLE:
		{
			var.vt =VT_R8;
			var.dblVal =fval.m_Var.dVal;
			break;
		}
	case Geodatabase::FieldValue::VT_INT:
		{
			var.vt = VT_I4;
			var.lVal =fval.m_Var.iVal;
			break;
		}
	case Geodatabase::FieldValue::VT_SHORT:
		{
			var.vt = VT_I2;
			var.iVal =fval.m_Var.sVal;
			break;
		}
	case Geodatabase::FieldValue::VT_STR:
		{
			var.vt =VT_BSTR;
			_bstr_t str =fval.m_Var.pstrVal->c_str();
			var.bstrVal =SysAllocString(str);
			break;
		}
	default:
		var.vt =VT_EMPTY;
		break;

		
	}
}

void CotFeature::ConvVar2Fval(VARIANT &var, Geodatabase::FieldValue &fval)
{
    switch(var.vt)
	{
	case VT_BOOL:
		{
			fval.vtype =Geodatabase::FieldValue::VT_BOOL;
			if(var.boolVal ==VARIANT_FALSE)
			{
				fval.m_Var.bVal =false;
			}
			else
			{
				fval.m_Var.bVal =true;
			}
			break;
		}
	case VT_BSTR:
		{
           
			_bstr_t str =var.bstrVal;
			fval.SetString(str);
			break;
		}
	case VT_I4:
		{
            fval.vtype =Geodatabase::FieldValue::VT_INT;
			fval.m_Var.iVal =var.lVal;
			break;
		}
	case VT_R4:
		{
			fval.vtype =Geodatabase::FieldValue::VT_FLOAT;
			fval.m_Var.fVal =var.fltVal;

            break;
		}
	case VT_R8:
		{
			fval.vtype =Geodatabase::FieldValue::VT_DOUBLE;
			fval.m_Var.dVal =var.dblVal;
			break;
		}
	case VT_I2:
		{
			fval.vtype =Geodatabase::FieldValue::VT_SHORT;
			fval.m_Var.sVal =var.iVal;
			break;
		}
	default:
		fval.vtype =Geodatabase::FieldValue::VT_EMPTY;
		break;	
	}
}


STDMETHODIMP CotFeature::Update(void)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	(*m_ppFeature)->Update();

	return S_OK;
}

STDMETHODIMP CotFeature::Delete(void)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	(*m_ppFeature)->Delete();

	return S_OK;
}
