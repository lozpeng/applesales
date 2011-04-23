#include "StdAfx.h"
#include "IRenderSetting.h"
#include "SymbolFactory.h"
IRenderSetting::IRenderSetting(void)
{
	m_pLayer = NULL;
}

IRenderSetting::~IRenderSetting(void)
{

}

void IRenderSetting::SetLayer(Carto::ILayer *pLayer)
{
	m_pLayer =pLayer;
}


void IRenderSetting::LoadFields(CWnd *pCmbBox, Geodatabase::IFeatureClass *pFeatureClass)
{
	using namespace Geodatabase;

	long lCount = pFeatureClass->FieldCount();
	CComboBox *pCombox = (CComboBox*)pCmbBox; 

	long lType = 0;
	BOOL bFlag = TRUE;
	std::string pszFieldName;
	CString csTemp;
	Geodatabase::CFieldPtr pField;
	for(int i=1 ; i<=lCount ;i++)
	{
		pField =pFeatureClass->GetField(i);

		lType =pField->GetType();
		pszFieldName =pField->GetName();
		switch(lType)
		{

		case FTYPE_STRING:	//字符型字段
			csTemp.Format("%s",pszFieldName.c_str()); 
			//csTemp += "(char)";

			break;
		case FTYPE_DATE:	//日期型字段
			csTemp.Format("%s",pszFieldName.c_str()); 
			//csTemp += "(date)";

			break;
		case FTYPE_FLOAT:	//浮点型字段
		case FTYPE_DOUBLE:
			csTemp.Format("%s",pszFieldName.c_str()); 
			//csTemp += "(float)";
			break;
		case FTYPE_BOOL:	//逻辑型字段
			csTemp.Format("%s",pszFieldName.c_str()); 
			//csTemp += "(logic)";

			break;
		case FTYPE_LONG:	//数字型字段
			csTemp.Format("%s",pszFieldName.c_str()); 
			//csTemp += "(long)";
			break;
		default:
			continue;

		}
		if(bFlag)
			pCombox->AddString(csTemp);		  
		bFlag = TRUE;
	}
}

void IRenderSetting::TrimField(CString &csValue)
{
	int pos = -1;
	pos = csValue.Find (_T('('));
	if (pos > 0)
		csValue = csValue.Left (pos);

}

Display::ISymbolPtr IRenderSetting::CreateDefaultSymbol(Geodatabase::IFeatureClass *pFeatureClass)
{
	long ltype =pFeatureClass->ShapeType();

	Display::ISymbolPtr pSymbol;

	if( ltype == GEOS_POINT || ltype == GEOS_MULTIPOINT )
	{
		pSymbol = Display::CSymbolFactory::CreateSymbol(SIMPLE_MARKER_SYMBOL);


	}
	else if( ltype == GEOS_LINESTRING || ltype == GEOS_MULTILINESTRING )
	{
		pSymbol = Display::CSymbolFactory::CreateSymbol(SIMPLE_LINE_SYMBOL);


	}
	else if( ltype == GEOS_POLYGON || ltype == GEOS_MULTIPOLYGON )
	{
		pSymbol = Display::CSymbolFactory::CreateSymbol(SIMPLE_FILL_SYMBOL);

	}

	return pSymbol;
}

void IRenderSetting::LoadNumericFields(CWnd *pCmbBox, Geodatabase::IFeatureClass *pFeatureClass)
{
	using namespace Geodatabase;

	long lCount = pFeatureClass->FieldCount();
	CComboBox *pCombox = (CComboBox*)pCmbBox; 

	long lType = 0;

	std::string pszFieldName;
	CString csTemp;
	Geodatabase::CFieldPtr pField;
	for(int i=1 ; i<=lCount ;i++)
	{
		pField =pFeatureClass->GetField(i);

		lType =pField->GetType();
		pszFieldName =pField->GetName();
		switch(lType)
		{

		case FTYPE_FLOAT:	//浮点型字段
		case FTYPE_DOUBLE:
			csTemp.Format("%s",pszFieldName.c_str()); 

			break;
		case FTYPE_LONG:	//数字型字段
			csTemp.Format("%s",pszFieldName.c_str()); 

			break;
		default:
			continue;

		}

		pCombox->AddString(csTemp);		  

	}
}

void IRenderSetting::GetMinMaxValue(Geodatabase::IFeatureClass *pFeatureClass, CString csFieldName, double *pMax, double *pMin)
{
	using namespace Geodatabase;
	if(!pFeatureClass)
	{
		return;
	}

	long index =pFeatureClass->FindField(csFieldName);
	if(index<=0)
	{
		return;
	}
	CFieldPtr pField =pFeatureClass->GetField(index);
	long ltype =pField->GetType();
	//判断是否是数字类型
	if(ltype!=FTYPE_LONG && ltype!=FTYPE_SHORT && ltype!=FTYPE_FLOAT && ltype!=FTYPE_DOUBLE)
	{
		return;
	}

	CSimpleQuery queryfilter;
	queryfilter.AddField(csFieldName);
	ICursorPtr pCursor =pFeatureClass->Query(&queryfilter);
	if(!pCursor)
	{
		return;
	}
	double dmin =1e38,dmax =1e-38;

	double dval;
	IRowPtr prow;
	while(!pCursor->IsEOF())
	{
		prow =pCursor->NextRow();
		if(!prow)
			continue;


		FieldValue &value =prow->GetValue(index);
		switch(value.vtype)
		{
		case FieldValue::VT_SHORT:
			dval =value.m_Var.sVal;
			break;
		case FieldValue::VT_INT:
			dval =value.m_Var.iVal;
			break;
		case FieldValue::VT_FLOAT:
			dval =value.m_Var.fVal;
			break;
		case FieldValue::VT_DOUBLE:
			dval =value.m_Var.dVal;
			break;
		default:
			break;
		}
		if(dval<dmin)
		{
			dmin =dval;
		}
		if(dval>dmax)
		{
			dmax =dval;
		}

	}
	*pMin =dmin;
	*pMax =dmax;
}