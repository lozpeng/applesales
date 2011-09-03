#include "stdafx.h"
#include "ShapefileFeatureClass.h"
#include "ShapefileWorkspaceFactory.h"
#include "Feature.h"
#include "ShapefileFeatureCursor.h"
#include "SelectionSet.h"
#include "IFeatureSelection.h"
#include "SpatialQuery.h"
#include "SqlWhereParser.h"
#include  <Geometry/geom/Geometry.h>
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/CoordinateArraySequenceFactory.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/MultiLineString.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/LinearRing.h>
#include "RelativePath.h"

using namespace Geodatabase;
using namespace std;
using namespace GEOMETRY::geom;

#define  SPATIALINDEX_MIN_SHAPE 10000


CShapefileFeatureClass::CShapefileFeatureClass(CShapefileWorkspace *pWorkspace,SHPHandle hShp,DBFHandle hDbf,const char *name,bool ReadOnly)
:IFeatureClass(pWorkspace,NULL)
{
    m_shpHandle =hShp;
	m_dbfHandle =hDbf;
	m_Readonly =ReadOnly;
	m_name =name;
	m_IndexTree =NULL;
	Init();
	
}

CShapefileFeatureClass::~CShapefileFeatureClass()
{

	if( m_dbfHandle != NULL )
		DBFClose( m_dbfHandle );

	if( m_shpHandle != NULL )
		SHPClose( m_shpHandle );

	if(m_IndexTree!=NULL)
        fclose(m_IndexTree);

}

void CShapefileFeatureClass::Init()
{

	//获得矢量的图形类型
	switch( m_shpHandle->nShapeType )
	{
	case SHPT_POINT:
	case SHPT_POINTM:
	case SHPT_POINTZ:
		m_lshptype =GEOMETRY::geom::GEOS_POINT;
		break;

	case SHPT_ARC:
	case SHPT_ARCM:
	case SHPT_ARCZ:
		m_lshptype =GEOMETRY::geom::GEOS_MULTILINESTRING;
		break;

	case SHPT_MULTIPOINT:
	case SHPT_MULTIPOINTM:
	case SHPT_MULTIPOINTZ:
		m_lshptype =GEOMETRY::geom::GEOS_MULTIPOINT;
		break;

	case SHPT_POLYGON:
	case SHPT_POLYGONM:
	case SHPT_POLYGONZ:
		m_lshptype =GEOMETRY::geom::GEOS_POLYGON;
		break;
	default:
		m_lshptype =GEOMETRY::geom::GEOM_NULL;
		break;

	}
	int iField;
	int lFieldnum =DBFGetFieldCount(m_dbfHandle);
	char            szFieldName[20];
	int             nWidth, nPrecision;
	char            chNativeType;
	DBFFieldType    eDBFType;
    //获得属性字段的信息
	for( iField = 0; 
		m_dbfHandle != NULL && iField < lFieldnum; 
		iField++ )
	{
		CField *pField =new CField();



		chNativeType = DBFGetNativeFieldType( m_dbfHandle, iField );
		eDBFType = DBFGetFieldInfo( m_dbfHandle, iField, szFieldName,
			&nWidth, &nPrecision );

		pField->SetName(szFieldName);

		pField->SetLength(nWidth);

        pField->SetPrecision(nPrecision);

		if( chNativeType == 'D' )
		{
			/* XXX - mloskot:
			* Shapefile date has following 8-chars long format: 20060101.
			* OGR splits it as YYYY/MM/DD, so 2 additional characters are required.
			* Is this correct assumtion? What about time part of date?
			* Shouldn't this format look as datetime: YYYY/MM/DD HH:MM:SS
			* with 4 additional characters?
			*/
			pField->SetLength( nWidth + 2 );
			pField->SetType( FTYPE_DATE );
		}
		else if( eDBFType == FTDouble )
			pField->SetType( FTYPE_DOUBLE);
		else if( eDBFType == FTInteger )
			pField->SetType(FTYPE_LONG);
		else
			pField->SetType( FTYPE_STRING);

		m_allFields.push_back(CFieldPtr(pField));
	}

	//获得投影信息
    ReadPrj();

    //如果记录大于10000条，则建立空间索引
	if(m_shpHandle->nRecords>=SPATIALINDEX_MIN_SHAPE)
	{
		BuildSpatialIndex();
	}


}

//要素的数目
long CShapefileFeatureClass::RowCount() const
{
	return FeatureCount();
}

long CShapefileFeatureClass::FeatureCount() const
{
	
	CShapefileWorkspace *pWorkspace =dynamic_cast<CShapefileWorkspace*>(m_pWorkspace);
	//是否在进行编辑
	if(pWorkspace->IsEditing())
	{
		if(pWorkspace->ExistEditCache(m_name))
		{
			//如果正在编辑，则从编辑缓存中读取有效数目
			CFeatureEditCache *pCache =pWorkspace->FindEditCache(m_name);

			if(pCache)
			{
				return pCache->GetValidNum();
			}
		}

	}
	
	return m_shpHandle->nRecords;
}

long CShapefileFeatureClass::GetTotalNum() 
{


	CShapefileWorkspace *pWorkspace =dynamic_cast<CShapefileWorkspace*>(m_pWorkspace);
	//是否在进行编辑
	if(pWorkspace->IsEditing())
	{
		if(pWorkspace->ExistEditCache(m_name))
		{
			//如果正在编辑，则从编辑缓存中读取有效数目
			CFeatureEditCache *pCache =pWorkspace->FindEditCache(m_name);

			if(pCache)
			{
				return pCache->GetTotalNum();
			}
		}

	}
	
	return m_shpHandle->nRecords;
}

/************************************************************************************************
* 以下为要素的操作方法
*
*************************************************************************************************/


//获得图形的类型
long CShapefileFeatureClass::ShapeType() 
{
	
	return m_lshptype;
}

//产生一个空的要素,并将要素加入到数据集中
CFeaturePtr CShapefileFeatureClass::CreateFeature()
{
	//这个函数只能在处于编辑状态下才能够调用
	CShapefileWorkspace *pWorkspace =dynamic_cast<CShapefileWorkspace*>(m_pWorkspace);
	//是否在进行编辑
	if(!pWorkspace->IsEditing())
	{ 
		return CFeaturePtr(); 
	}
	if(!pWorkspace->ExistEditCache(m_name))
	{
		pWorkspace->BuildEditCache(this);
	}

	CFeatureEditCache *pCache =pWorkspace->FindEditCache(m_name);

	long id =pCache->GetTotalNum();
	//产生一个新的要素
	CFeature *pFeature =new CFeature(this,id+1);

	return CFeaturePtr(pFeature);



}

CFeaturePtr CShapefileFeatureClass::GetFeature(long index)
{
	long ltotal =GetTotalNum();

	//id是否有效
	if(index<1 || index>ltotal)
	{
		return CFeaturePtr();
	}
	CShapefileWorkspace *pWorkspace =dynamic_cast<CShapefileWorkspace*>(m_pWorkspace);
	//是否在进行编辑
	if(pWorkspace->IsEditing())
	{ 
		//现在编辑缓存中查找该要素
		CFeatureEditCache *pCache =pWorkspace->FindEditCache(m_name);

		if(pCache)
		{
			//如果要素被删除
			if(pCache->IsFeatureDelete(index))
			{
				return CFeaturePtr();
			}
			CFeaturePtr pFeature=pCache->GetFeature(index);

			if(pFeature)
			{
				return pFeature;
			}
		}
	}

	//读取shape

	return CFeaturePtr(ShpReadFeature(index-1));

}

Geometry* CShapefileFeatureClass::GetFeatureShape(long index)
{
	long ltotal =GetTotalNum();

	//id是否有效
	if(index<1 || index>ltotal)
	{
		return NULL;
	}
	CShapefileWorkspace *pWorkspace =dynamic_cast<CShapefileWorkspace*>(m_pWorkspace);
	//是否在进行编辑
	if(pWorkspace->IsEditing())
	{ 
		//现在编辑缓存中查找该要素
		CFeatureEditCache *pCache =pWorkspace->FindEditCache(m_name);

		if(pCache)
		{
			//如果要素被删除
			if(pCache->IsFeatureDelete(index))
			{
				return NULL;
			}
			CFeaturePtr pFeature=pCache->GetFeature(index);

			if(pFeature)
			{
				return pFeature->GetShapeClone();
			}
		}
	}
 
	return ReadShape(index-1);
}

//添加一个新的要素
void CShapefileFeatureClass::AddFeature(Geodatabase::CFeature *pFeature)
{
	if(!pFeature)
	{
		return;
	}
	CShapefileWorkspace *pWorkspace =dynamic_cast<CShapefileWorkspace*>(m_pWorkspace);
	//是否在进行编辑
	if(pWorkspace->IsEditing())
	{ 
		if(!pWorkspace->ExistEditCache(m_name))
		{
			pWorkspace->BuildEditCache(this);
		}

		CFeatureEditCache *pCache =pWorkspace->FindEditCache(m_name);


		//产生一个要素的拷贝
		CFeature *pcopyFeature =new CFeature(*pFeature);

		pWorkspace->AddFeature(this,CFeaturePtr(pcopyFeature));
	}
}
//更新一个要素
void CShapefileFeatureClass::UpdateFeature(Geodatabase::CFeature *pFeature)
{
	CShapefileWorkspace *pWorkspace =dynamic_cast<CShapefileWorkspace*>(m_pWorkspace);
	//是否在进行编辑
	if(pWorkspace->IsEditing())
	{ 
		if(!pWorkspace->ExistEditCache(m_name))
		{
			pWorkspace->BuildEditCache(this);
		}

		CFeatureEditCache *pCache =pWorkspace->FindEditCache(m_name);


		//产生一个要素的拷贝
		CFeature *pcopyFeature =new CFeature(*pFeature);
		//pcopyFeature->SetShape(pFeature->GetShapeClone());

		pWorkspace->UpdateFeature(this,CFeaturePtr(pcopyFeature));
	}


}
//删除要素
void CShapefileFeatureClass::DeleteFeature(long index)
{
	CShapefileWorkspace *pWorkspace =dynamic_cast<CShapefileWorkspace*>(m_pWorkspace);
	//是否在进行编辑
	if(pWorkspace->IsEditing())
	{ 
		if(!pWorkspace->ExistEditCache(m_name))
		{
			pWorkspace->BuildEditCache(this);
		}

		CFeatureEditCache *pCache =pWorkspace->FindEditCache(m_name);

		pWorkspace->DeleteFeature(this,index);
	}
}

/************************************************************************************************
* 以下为字段的操作方法
*************************************************************************************************/

//增加一个字段
void CShapefileFeatureClass::AddField(Geodatabase::CField *pField)
{

}

//删除一个字段
void CShapefileFeatureClass::DeleteField(long index)
{

}

long CShapefileFeatureClass::FieldCount() const
{
	
	return (long)(m_allFields.size());
}
//通过字段名查找字段的序号
long CShapefileFeatureClass::FindField(const char *name)
{
	long index =-1;
	for(size_t i=0;i<m_allFields.size();i++)
	{
		if(!stricmp(name,m_allFields[i]->GetName().c_str()))
		{
			index =i+1;
			break;
		}
	}
	return index;
}

CFieldPtr CShapefileFeatureClass::GetField(long index)
{
	if(index<=0 || index>m_allFields.size())
	{
		return CFieldPtr();
	}

	return m_allFields[index-1];
}

string CShapefileFeatureClass::ShapeFieldName()
{
	//该几何字段是一个虚拟字段，并没有存在于数据表中
	return "ESRISHP_GEOM";
}


/************************************************************************************************
* 以下为查询选择操作方法
*************************************************************************************************/

ISelctionSetPtr CShapefileFeatureClass::Select(Geodatabase::CSimpleQuery *query)
{

	CSpatialQuery *pspatialQuery =dynamic_cast<CSpatialQuery*>(query);
	if(pspatialQuery)
	{
		return SpatialSelect(pspatialQuery);
	}
	else
	{
		return SimpleSelect(query);
	}
}

ISelctionSetPtr CShapefileFeatureClass::SelectByRect(const double &xmin,const double &ymin, const double &xmax,const double &ymax)
{
	//CttBset		cShapeset;
	//cShapeset.Create();

	//long ltotal=GetTotalNum();
	//cShapeset.SetNumBits(ltotal);

	//CttExtent extent(xmin,ymin,xmax,ymax);

	////矩形查询
	//m_pOtTheme->mg_cTsfFile.SearchShapes(&extent,FALSE,cShapeset);

	//CSelctionSet *pSelectionSet =new CSelctionSet(this);

	//pSelectionSet->m_flags.resize(ltotal);

	//BOOL bSelect;

	////填充选择集
	//for(long i=0;i<ltotal;i++)
	//{
	//	bSelect =FALSE;

	//	cShapeset.GetBit(i,&bSelect);

	//	if(bSelect)
	//	{
	//		pSelectionSet->m_flags[i] =true;
	//	}

	//}

	////如果正在编辑，则查找缓存
	//CTmsWorkspace *pWorkspace =dynamic_cast<CTmsWorkspace*>(m_pWorkspace);
	////是否在进行编辑
	//if(pWorkspace->IsEditing())
	//{
	//	if(pWorkspace->ExistEditCache(m_name))
	//	{
	//		//如果正在编辑，则从编辑缓存中读取有效数目
	//		CFeatureEditCache *pCache =pWorkspace->FindEditCache(m_name);

	//		if(pCache)
	//		{
	//			GEOMETRY::geom::Envelope envelop(xmin,xmax,ymin,ymax);
	//			pCache->QueryByExtent(&envelop,pSelectionSet->m_flags);
	//		}
	//	}

	//}

	long ltotal=GetTotalNum();


	IFeatureSelection *pSelectionSet =new IFeatureSelection(this);

	pSelectionSet->m_flags.resize(ltotal);
	
	double dfBound[4];
	GEOMETRY::geom::Envelope shpEnvelop;
	GEOMETRY::geom::Envelope QueryEnvelop(xmin,xmax,ymin,ymax);

	//查询索引文件
	if(m_IndexTree)
	{
		int nSpatialFIDCount, *panSpatialFIDs,index;
		double adfBoundsMin[4], adfBoundsMax[4];
		adfBoundsMin[0] = xmin;
		adfBoundsMin[1] = ymin;
		adfBoundsMin[2] = 0.0;
		adfBoundsMin[3] = 0.0;
		adfBoundsMax[0] = xmax;
		adfBoundsMax[1] = ymax;
		adfBoundsMax[2] = 0.0;
		adfBoundsMax[3] = 0.0;

		panSpatialFIDs = SHPSearchDiskTree( m_IndexTree, 
			adfBoundsMin, adfBoundsMax, 
			&nSpatialFIDCount );

		for(int i=0;i<nSpatialFIDCount;i++)
		{
			index =panSpatialFIDs[i];
			if(index<ltotal)
			{
				pSelectionSet->m_flags[panSpatialFIDs[i]] =true;
			}
			;
		}
		if ( panSpatialFIDs )
			free( panSpatialFIDs );

	}
	else
	{
		//填充选择集
		for(long i=0;i<FeatureCount();i++)
		{

			SHPReadObjectExtent(m_shpHandle,i,dfBound);
			shpEnvelop.init(dfBound[0],dfBound[2],dfBound[1],dfBound[3]);

			if(QueryEnvelop.intersects(shpEnvelop))
			{
				pSelectionSet->m_flags[i] =true;
			}

		}
	}
	

	//如果正在编辑，则查找缓存
	CShapefileWorkspace *pWorkspace =dynamic_cast<CShapefileWorkspace*>(m_pWorkspace);
	//是否在进行编辑
	if(pWorkspace->IsEditing())
	{
		if(pWorkspace->ExistEditCache(m_name))
		{
			//如果正在编辑，则从编辑缓存中读取有效数目
			CFeatureEditCache *pCache =pWorkspace->FindEditCache(m_name);

			if(pCache)
			{
				for(int k=0;k<ltotal;k++)
					pSelectionSet->m_flags[k] = true;
				pCache->QueryByExtent(&QueryEnvelop,pSelectionSet->m_flags);
			}
		}

	}

	return ISelctionSetPtr(pSelectionSet);
}

ICursorPtr CShapefileFeatureClass::Query(CSimpleQuery *query, bool bReadOnly)
{
	CSpatialQuery *pspatialQuery =dynamic_cast<CSpatialQuery*>(query);
	if(pspatialQuery)
	{
		return SpatialQuery(pspatialQuery,bReadOnly);
	}
	else
	{
		return SimpleQuery(query,bReadOnly);
	}

}

//判断条件是否满足
static bool shp_evaluator(swq_field_op *op, Geodatabase::CFeature *record_handle)
{
	
	
	switch( op->field_type )
	{
	case FTYPE_LONG:
		switch( op->operation )
		{
		case SWQ_EQ:
			return record_handle->m_values[op->field_index].m_Var.iVal == op->int_value;
		case SWQ_NE:
			return record_handle->m_values[op->field_index].m_Var.iVal != op->int_value;
		case SWQ_LT:
			return record_handle->m_values[op->field_index].m_Var.iVal < op->int_value;
		case SWQ_GT:
			return record_handle->m_values[op->field_index].m_Var.iVal > op->int_value;
		case SWQ_LE:
			return record_handle->m_values[op->field_index].m_Var.iVal <= op->int_value;
		case SWQ_GE:
			return record_handle->m_values[op->field_index].m_Var.iVal >= op->int_value;

		/*case SWQ_IN:
			{
				const char *pszSrc;

				pszSrc = op->string_value;
				while( *pszSrc != '\0' )
				{
					if( atoi(pszSrc) == psField->Integer )
						return TRUE;
					pszSrc += strlen(pszSrc) + 1;
				}

				return FALSE;
			}*/

		default:
			
			return false;
		}

	case FTYPE_FLOAT:
	case FTYPE_DOUBLE:
		switch( op->operation )
		{
		case SWQ_EQ:
			return record_handle->m_values[op->field_index].m_Var.dVal == op->float_value;
		case SWQ_NE:
			return record_handle->m_values[op->field_index].m_Var.dVal != op->float_value;
		case SWQ_LT:
			return record_handle->m_values[op->field_index].m_Var.dVal < op->float_value;
		case SWQ_GT:
			return record_handle->m_values[op->field_index].m_Var.dVal > op->float_value;
		case SWQ_LE:
			return record_handle->m_values[op->field_index].m_Var.dVal <= op->float_value;
		case SWQ_GE:
			return record_handle->m_values[op->field_index].m_Var.dVal >= op->float_value;
		/*case SWQ_ISNULL:
			return !poFeature->IsFieldSet( op->field_index );
		case SWQ_IN:
			{
				const char *pszSrc;

				pszSrc = op->string_value;
				while( *pszSrc != '\0' )
				{
					if( atof(pszSrc) == psField->Real )
						return TRUE;
					pszSrc += strlen(pszSrc) + 1;
				}

				return FALSE;
			}*/

		default:
			
			return false;
		}

	case FTYPE_STRING:
		{
	        std::string str;
			switch( op->operation )
			{
			case SWQ_EQ:
				
				str =record_handle->m_values[op->field_index].GetasString();
				return str==op->string_value;
				
			case SWQ_NE:
				str =record_handle->m_values[op->field_index].GetasString();
				return str!=op->string_value;

			case SWQ_LT:
				str =record_handle->m_values[op->field_index].GetasString();
				return str<op->string_value;
			case SWQ_GT:
				str =record_handle->m_values[op->field_index].GetasString();
				return str>op->string_value;
			case SWQ_LE:
				str =record_handle->m_values[op->field_index].GetasString();
				return str<=op->string_value;
			case SWQ_GE:
				str =record_handle->m_values[op->field_index].GetasString();
				return str>=op->string_value;

			case SWQ_ISNULL:
				{
					str =record_handle->m_values[op->field_index].GetasString();
				   return str.empty();
				}
				

			/*case SWQ_LIKE:
				if (psField->Set.nMarker1 != OGRUnsetMarker
					|| psField->Set.nMarker2 != OGRUnsetMarker )
					return swq_test_like(psField->String, op->string_value);
				else
					return FALSE;

			case SWQ_IN:
				{
					const char *pszSrc;

					if( !poFeature->IsFieldSet(op->field_index) )
						return FALSE;

					pszSrc = op->string_value;
					while( *pszSrc != '\0' )
					{
						if( EQUAL(pszSrc,psField->String) )
							return TRUE;
						pszSrc += strlen(pszSrc) + 1;
					}

					return FALSE;
				}*/

			default:
				
				return false;
			}
			return false;
		}
		


	default:
		
		return false;
	}
}

//简单的条件查询
ICursorPtr CShapefileFeatureClass::SimpleQuery(Geodatabase::CSimpleQuery* query,bool bReadOnly)
{
	
	bool ball =false;
	if(query->GetWhereString().empty())
	{
		ball =true;
	}
    
    long ltotal=GetTotalNum();
	CShapefileFeatureCursor *pCursor =new CShapefileFeatureCursor(this,query->GetFields().c_str());
	if(!ball)
	{
		
		Geodatabase::CSqlWhereParser parser;
		if(!parser.Init(query->GetWhereString().c_str(),m_allFields,(swq_op_evaluator)shp_evaluator))
		{
            //解析where条件失败
			delete pCursor;
			return NULL;
		}
        
		//构造一个查询记录
		CShapefileFeatureCursor *tempCursor =new CShapefileFeatureCursor(this,parser.GetNeedFields().c_str());
        
        tempCursor->m_flags.resize(ltotal,true);

		pCursor->m_flags.resize(ltotal);

		CFeaturePtr pFeature;
		while(!tempCursor->IsEOF())
		{
            pFeature =tempCursor->NextFeature();

			if(!pFeature)
			{
				continue;
			}

            if(parser.Evaluator(pFeature.get()))
			{
                 //通过了where测试
				pCursor->m_flags[pFeature->GetId()-1] =true;
			}
		}

		delete tempCursor;

		

	}
	else
	{
		//选择全部记录
		
		pCursor->m_flags.resize(ltotal,true);
	}


	return ICursorPtr(pCursor);
}



ICursorPtr CShapefileFeatureClass::SpatialQuery(Geodatabase::CSpatialQuery* query,bool bReadOnly)
{
	return ICursorPtr();
}
ICursorPtr CShapefileFeatureClass::QueryByExtent(GEOMETRY::geom::Envelope *pEnvelop,CSimpleQuery *pQuery, bool bReadOnly)
{
    
	

	long ltotal=GetTotalNum();


	CShapefileFeatureCursor *pCursor =new CShapefileFeatureCursor(this,pQuery->GetFields().c_str());

	pCursor->m_flags.resize(ltotal);

    double dfBound[4];
	GEOMETRY::geom::Envelope shpEnvelop;

	//查询索引文件
	if(m_IndexTree)
	{
		int nSpatialFIDCount, *panSpatialFIDs,index;
		double adfBoundsMin[4], adfBoundsMax[4];
		adfBoundsMin[0] = pEnvelop->getMinX();
		adfBoundsMin[1] = pEnvelop->getMinY();
		adfBoundsMin[2] = 0.0;
		adfBoundsMin[3] = 0.0;
		adfBoundsMax[0] = pEnvelop->getMaxX();
		adfBoundsMax[1] = pEnvelop->getMaxY();
		adfBoundsMax[2] = 0.0;
		adfBoundsMax[3] = 0.0;

		panSpatialFIDs = SHPSearchDiskTree( m_IndexTree, 
			adfBoundsMin, adfBoundsMax, 
			&nSpatialFIDCount );

        for(int i=0;i<nSpatialFIDCount;i++)
		{
			index =panSpatialFIDs[i];
			if(index<ltotal)
			{
               pCursor->m_flags[panSpatialFIDs[i]] =true;
			}
           ;
		}
		if ( panSpatialFIDs )
			free( panSpatialFIDs );

	}
	else
	{
	    //填充选择集
		for(long i=0;i<FeatureCount();i++)
		{

			SHPReadObjectExtent(m_shpHandle,i,dfBound);
			shpEnvelop.init(dfBound[0],dfBound[2],dfBound[1],dfBound[3]);
			
			if(pEnvelop->intersects(shpEnvelop))
			{
				pCursor->m_flags[i] =true;
			}

		}
	}
	

	//如果正在编辑，则查找缓存
	CShapefileWorkspace *pWorkspace =dynamic_cast<CShapefileWorkspace*>(m_pWorkspace);
	//是否在进行编辑
	if(pWorkspace->IsEditing())
	{
		if(pWorkspace->ExistEditCache(m_name))
		{
			//如果正在编辑，则从编辑缓存中读取有效数目
			CFeatureEditCache *pCache =pWorkspace->FindEditCache(m_name);

			if(pCache)
			{
				for(int k=0;k<ltotal;k++)
					pCursor->m_flags[k] = true;

				pCache->QueryByExtent(pEnvelop,pCursor->m_flags);
			}
		}

	}
	return ICursorPtr(pCursor);

}

//简单的条件选择
ISelctionSetPtr CShapefileFeatureClass::SimpleSelect(Geodatabase::CSimpleQuery* query)
{
	IFeatureSelection *pSelectionSet =new IFeatureSelection(this);
	if (query == NULL)
		return ISelctionSetPtr(pSelectionSet);

	bool ball =false;
	if(query->GetWhereString().empty())
	{
		ball =true;
	}

	long ltotal=GetTotalNum();
	
	if(!ball)
	{

		Geodatabase::CSqlWhereParser parser;
		if(!parser.Init(query->GetWhereString().c_str(),m_allFields,(swq_op_evaluator)shp_evaluator))
		{
			//解析where条件失败
			delete pSelectionSet;
			return NULL;
		}

		//构造一个查询记录
		CShapefileFeatureCursor *tempCursor =new CShapefileFeatureCursor(this,parser.GetNeedFields().c_str());

		tempCursor->m_flags.resize(ltotal,true);

		pSelectionSet->m_flags.resize(ltotal);

		CFeaturePtr pFeature;
		while(!tempCursor->IsEOF())
		{
			pFeature =tempCursor->NextFeature();

			if(!pFeature)
			{
				continue;
			}

			if(parser.Evaluator(pFeature.get()))
			{
				//通过了where测试
				pSelectionSet->m_flags[pFeature->GetId()-1] =true;
			}
		}

		delete tempCursor;



	}
	else
	{
		//选择全部记录

		pSelectionSet->m_flags.resize(ltotal,true);
	}


	
	return ISelctionSetPtr(pSelectionSet);
}

//空间查询选择
ISelctionSetPtr CShapefileFeatureClass::SpatialSelect(Geodatabase::CSpatialQuery *query)
{

	if(query->GetGeometry()==NULL)
	{
		return SimpleSelect(query);
	}
	long ltotal =GetTotalNum();

	
	IFeatureSelection *pSelectionSet =new IFeatureSelection(this);

	pSelectionSet->m_flags.resize(ltotal);

	bool bsql =false;
	//首先进行一个字段的sql语句查询
	std::string strWhere =query->GetWhereString();
	if(!strWhere.empty())
	{
		bsql =true;
		
		ISelctionSetPtr pSel =SimpleSelect(query);
		if(pSel)
		{
			while(!pSel->IsEOF())
			{
				pSelectionSet->m_flags[pSel->NextID()-1] =true;
			}
            
		}
		
	}
	
	GEOMETRY::geom::Geometry *pg =query->GetGeometry();

	GEOMETRY::geom::Geometry *pGeometry =NULL;

	long sprel =query->GetSpatialRel();
	//空间相交的情况
	if(sprel ==SpatialRelIntersects)
	{
		const GEOMETRY::geom::Envelope *pEnvelope =pg->getEnvelopeInternal();
		//首先进行一个矩形查询
		Geodatabase::CSelctionSetPtr pSel =SelectByRect(pEnvelope->getMinX(),pEnvelope->getMinY(),
			                    pEnvelope->getMaxX(),pEnvelope->getMaxY());
		
		for(long  lId = 0;lId <ltotal;lId++ )
		{

			if(bsql)
			{
				if(! pSelectionSet->m_flags[lId])
				{
					continue;
				}
				pSelectionSet->m_flags[lId] =false;
			}
			
			//矩形查询时是否查到
			if(!pSel->m_flags[lId])
			{
				continue;
			}
			pGeometry =GetFeatureShape(lId+1);
			if (!pGeometry)
				continue;
			if (pGeometry->intersects(pg))
			{
               pSelectionSet->m_flags[lId] =true;
			}
				
			pGeometry->getFactory()->destroyGeometry(pGeometry);		
			
		}
	}

	//如果正在编辑，则查找缓存
	CShapefileWorkspace *pWorkspace =dynamic_cast<CShapefileWorkspace*>(m_pWorkspace);
	//是否在进行编辑
	if(pWorkspace->IsEditing())
	{
		if(pWorkspace->ExistEditCache(m_name))
		{
			//如果正在编辑，则从编辑缓存中读取有效数目
			CFeatureEditCache *pCache =pWorkspace->FindEditCache(m_name);

			if(pCache)
			{
				pCache->Query(query,pSelectionSet->m_flags);
			}
		}

	}
	return ISelctionSetPtr(pSelectionSet);
}



/************************************************************************************************
* 以下为投影和M,Z值操作方法
*************************************************************************************************/

//获得投影字符串
std::string CShapefileFeatureClass::GetWkt() const
{

	return m_wkt;
}

//设置投影字符串
void CShapefileFeatureClass::SetWkt(const char *strwkt)
{
	m_wkt =strwkt;

}

bool CShapefileFeatureClass::HasZ() const
{
	bool bhas =false;

	switch( m_shpHandle->nShapeType )
	{

	case SHPT_POINTZ:
	
	case SHPT_ARCZ:
		
	case SHPT_MULTIPOINTZ:

	case SHPT_POLYGONZ:
		bhas =true;
		break;
	default:
		
		break;

	}
	return bhas;
}

bool CShapefileFeatureClass::HasM() const
{

	bool bhas =false;
	switch( m_shpHandle->nShapeType )
	{
	
	case SHPT_POINTM:
	case SHPT_POINTZ:
	
	case SHPT_ARCM:
	case SHPT_ARCZ:
		
	case SHPT_MULTIPOINTM:
	case SHPT_MULTIPOINTZ:
		
	case SHPT_POLYGONM:
	case SHPT_POLYGONZ:
		bhas =true;
		break;
	default:
		
		break;

	}

	return bhas;
}

bool CShapefileFeatureClass::GetExtent(GEOMETRY::geom::Envelope *pEnvelop) const
{

    double adMin[4], adMax[4];
	SHPGetInfo(m_shpHandle, NULL, NULL, adMin, adMax);

	pEnvelop->init(adMin[0],adMax[0],adMin[1],adMax[1]);
	
	return true;
}

bool CShapefileFeatureClass::ReadPrj()
{
	//得到投影文件的名称
	std::string prjfile =m_name.substr(0,m_name.rfind("."));
	prjfile+=".prj";
    FILE *fp = fopen(prjfile.c_str(),"r");

	if(!fp)
	{
		return false;
	}
	char *csWkt =new char[2048];
	memset(csWkt,0,2048);

	fread(csWkt,sizeof(char),2048,fp);

	fclose(fp);

	m_wkt =csWkt;

	delete []csWkt;
	return true;
}

/************************************************************************************************
* 以下为通过ShpLib读取的函数
*************************************************************************************************/

Geodatabase::CFeature* CShapefileFeatureClass::ShpReadFeature(long index)
{

	Geometry* pGeometry = NULL;
	pGeometry = ReadShape(index);


	CFeature *pFeature =new CFeature(this,index+1);
	pFeature->SetShape(pGeometry);

	for( int iField = 0; iField < m_allFields.size();iField++ )
	{
		// Skip null fields.
		if( DBFIsAttributeNULL( m_dbfHandle, index, iField ) )
			continue;

		switch( m_allFields[iField]->GetType())
		{
		case Geodatabase::FTYPE_DATE:
			{
				
				const char* pszDateValue = 
					DBFReadStringAttribute(m_dbfHandle,index,iField); 

				pFeature->m_values[iField].vtype =Geodatabase::FieldValue::VT_DATE;

				if( pszDateValue[2] == '/' && pszDateValue[5] == '/' 
					&& strlen(pszDateValue) >= 10 )
				{
					pFeature->m_values[iField].m_Var.date.Month =atoi(pszDateValue+0);
						
					pFeature->m_values[iField].m_Var.date.Day   = atoi(pszDateValue+3);
					pFeature->m_values[iField].m_Var.date.Year  = atoi(pszDateValue+6);
				}
				else
				{
					int nFullDate = atoi(pszDateValue);
					pFeature->m_values[iField].m_Var.date.Year = (int)(nFullDate / 10000);
					pFeature->m_values[iField].m_Var.date.Month = (unsigned char)((nFullDate / 100) % 100);
					pFeature->m_values[iField].m_Var.date.Day = (unsigned char)(nFullDate % 100);
				}
				break;
			}
		case Geodatabase::FTYPE_STRING:

			pFeature->m_values[iField].SetString(DBFReadStringAttribute(m_dbfHandle, index,iField ));

			break;

		case Geodatabase::FTYPE_LONG:
			pFeature->m_values[iField].vtype =FieldValue::VT_INT;
			pFeature->m_values[iField].m_Var.iVal =DBFReadIntegerAttribute(m_dbfHandle, index,iField );

			break;

		case Geodatabase::FTYPE_FLOAT:
		case Geodatabase::FTYPE_DOUBLE:
			pFeature->m_values[iField].vtype =FieldValue::VT_DOUBLE;
			pFeature->m_values[iField].m_Var.dVal =DBFReadDoubleAttribute(m_dbfHandle, index,iField );

			break;

		default:
			break;
		}
	}


	return  pFeature;
}


//读取Shape图形
GEOMETRY::geom::Geometry* CShapefileFeatureClass::ReadShape(long index)
{

	typedef vector<GEOMETRY::geom::Coordinate> CoordVect;

	SHPObject   *psShape;
	Geometry *pGeometry = NULL;

	psShape = SHPReadObject( m_shpHandle, index );

	if( psShape == NULL )
	{
		return NULL;
	}

	Coordinate coord;

	/* -------------------------------------------------------------------- */
	/*      Point.                                                          */
	/* -------------------------------------------------------------------- */
	if( psShape->nSHPType == SHPT_POINT
		|| psShape->nSHPType == SHPT_POINTM
		|| psShape->nSHPType == SHPT_POINTZ )
	{

		coord.x =psShape->padfX[0];
		coord.y = psShape->padfY[0];
		coord.z = psShape->padfZ[0];
		coord.m =psShape->padfM[0];
		pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createPoint(coord);

		
	}

	/* -------------------------------------------------------------------- */
	/*      Multipoint.                                                     */
	/* -------------------------------------------------------------------- */
	else if( psShape->nSHPType == SHPT_MULTIPOINT
		|| psShape->nSHPType == SHPT_MULTIPOINTM
		|| psShape->nSHPType == SHPT_MULTIPOINTZ )
	{
		if (psShape->nVertices == 0)
		{
			pGeometry = NULL;
		}
		else
		{
			CoordVect *pcoords =new CoordVect(psShape->nVertices);


			for(long i=0;i<psShape->nVertices;i++)
			{
				coord.x =psShape->padfX[i];
				coord.y = psShape->padfY[i];
				coord.z = psShape->padfZ[i];
				coord.m =psShape->padfM[i];
				
				(*pcoords)[i] =coord;
			}
			CoordinateSequence *coords = GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(pcoords);

			pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createMultiPoint(*coords);

			delete coords;

		}
	}

	/* -------------------------------------------------------------------- */
	/*      Arc (LineString)                                                */
	/*                                                                      */
	/*                                                                      */
	/* -------------------------------------------------------------------- */
	else if( psShape->nSHPType == SHPT_ARC
		|| psShape->nSHPType == SHPT_ARCM
		|| psShape->nSHPType == SHPT_ARCZ )
	{
		if( psShape->nParts == 0 )
		{
			pGeometry = NULL;
		}
		/*else if( psShape->nParts == 1 )
		{

			CoordVect *pcoords =new CoordVect(psShape->nVertices);


			for(long i=0;i<psShape->nVertices;i++)
			{
				coord.x =psShape->padfX[i];
				coord.y = psShape->padfY[i];
				coord.z = psShape->padfZ[i];
				coord.m =psShape->padfM[i];
				(*pcoords)[i] =coord;
			}

			CoordinateSequence *coords = GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(pcoords);
			pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createLineString(coords);

		}*/
		else
		{
			int iRing;
			int     nRingPoints;
			int     nRingStart;
			CoordVect *pcoords;
			int i;
			//建立一个空的多线要素
			pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createMultiLineString();
			for( iRing = 0; iRing < psShape->nParts; iRing++ )
			{
				if( psShape->panPartStart == NULL )
				{
					nRingPoints = psShape->nVertices;
					nRingStart = 0;
				}
				else
				{

					if( iRing == psShape->nParts - 1 )
						nRingPoints =psShape->nVertices - psShape->panPartStart[iRing];
					else
						nRingPoints = psShape->panPartStart[iRing+1]- psShape->panPartStart[iRing];
					nRingStart = psShape->panPartStart[iRing];
				}

				pcoords =new CoordVect(nRingPoints);

				for(i=0;i<nRingPoints;i++)
				{
					coord.x = *(psShape->padfX+nRingStart+i);
					coord.y = *(psShape->padfY+nRingStart+i);
					coord.z = *(psShape->padfZ+nRingStart+i);
					coord.m = *(psShape->padfM+nRingStart+i);
					(*pcoords)[i] =coord;
				}

				CoordinateSequence *coords = GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(pcoords);
				LineString *pline = GeometryFactory::getDefaultInstance()->createLineString(coords);

				((MultiLineString*)pGeometry)->AddGeometry((Geometry*)pline);
               

			}
		}

	
	}

	/* -------------------------------------------------------------------- */
	/*      Polygon                                                         */
	/*                                                                      */
	/*   现在没有判断是否是内环外环，需要改进                               */
	/* -------------------------------------------------------------------- */
	else if( psShape->nSHPType == SHPT_POLYGON
		|| psShape->nSHPType == SHPT_POLYGONM
		|| psShape->nSHPType == SHPT_POLYGONZ )
	{
		


		if ( psShape->nParts == 0 )
		{
			pGeometry = NULL;
		}
		
		//建立一个空的多边形要素
		pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createPolygon();

		if ( psShape->nParts == 1 )
		{
	        CoordVect *pcoords =new CoordVect(psShape->nVertices);
            for(int i=0;i<psShape->nVertices;i++)
			{
				coord.x =psShape->padfX[i];
				coord.y = psShape->padfY[i];
				coord.z = psShape->padfZ[i];
				coord.m =psShape->padfM[i];
				(*pcoords)[i] =coord;
			}
            
			CoordinateSequence *coords = GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(pcoords);
			LinearRing *pring = GeometryFactory::getDefaultInstance()->createLinearRing(coords);

			((GEOMETRY::geom::Polygon*)pGeometry)->AddGeometry((Geometry*)pring);
		}

		else
		{
			
			int iRing;
			int     nRingPoints;
			int     nRingStart;
			int i;
			CoordVect *pcoords =NULL;

			for( iRing = 0; iRing < psShape->nParts; iRing++ )
			{
				if( psShape->panPartStart == NULL )
				{
					nRingPoints = psShape->nVertices;
					nRingStart = 0;
				}
				else
				{

					if( iRing == psShape->nParts - 1 )
						nRingPoints =psShape->nVertices - psShape->panPartStart[iRing];
					else
						nRingPoints = psShape->panPartStart[iRing+1]- psShape->panPartStart[iRing];
					nRingStart = psShape->panPartStart[iRing];
				}

				pcoords =new CoordVect(nRingPoints);

				for(i=0;i<nRingPoints;i++)
				{
					coord.x = *(psShape->padfX+nRingStart+i);
					coord.y = *(psShape->padfY+nRingStart+i);
					coord.z = *(psShape->padfZ+nRingStart+i);
					coord.m = *(psShape->padfM+nRingStart+i);
					(*pcoords)[i] =coord;
				}

				CoordinateSequence *coords = GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(pcoords);
				LinearRing *pring = GeometryFactory::getDefaultInstance()->createLinearRing(coords);

				((GEOMETRY::geom::Polygon*)pGeometry)->AddGeometry((Geometry*)pring);
			}
			
		}

	}

	/* -------------------------------------------------------------------- */
	/*      Otherwise for now we just ignore the object.  Eventually we     */
	/*      should implement multipatch.                                    */
	/* -------------------------------------------------------------------- */
	else
	{
		if( psShape->nSHPType != SHPT_NULL )
		{
			
		}

		/* nothing returned */
	}

	/* -------------------------------------------------------------------- */
	/*      Cleanup shape, and set feature id.                              */
	/* -------------------------------------------------------------------- */
	SHPDestroyObject( psShape );

	if(pGeometry)
	{
		pGeometry->SetbZ(HasZ());
		pGeometry->SetbM(HasM());
	}

	return pGeometry;
}

void CShapefileFeatureClass::GetFeatureValue(long &index, Geodatabase::CFeaturePtr &pFeature, bool &bhasShape, std::vector<long> &fieldsIndex)
{
	//id是否有效
	if(index<1)
	{
		return;
	}
     CShapefileWorkspace *pWorkspace =dynamic_cast<CShapefileWorkspace*>(m_pWorkspace);
	//是否在进行编辑
	if(pWorkspace->IsEditing())
	{ 
		//现在编辑缓存中查找该要素
		CFeatureEditCache *pCache =pWorkspace->FindEditCache(m_name);

		if(pCache)
		{
			//如果要素被删除
			if(pCache->IsFeatureDelete(index))
			{
				pFeature=CFeaturePtr();
				return;
			}
			CFeaturePtr peditFeature=pCache->GetFeature(index);

			if(peditFeature)
			{
				pFeature =peditFeature;
				return;
			}

		}
	}

	if(bhasShape)
	{

		//读取shape
	
		Geometry *pGeometry =ReadShape(index-1);

	
		//设置图形
		pFeature->SetShape(pGeometry);

	

	}

	if(fieldsIndex.empty())
	{
		return;
	}
	
	long lpos;
	for(size_t i=0;i<fieldsIndex.size();i++)
	{
		lpos =fieldsIndex[i]-1;
		if( DBFIsAttributeNULL( m_dbfHandle, index-1, lpos) )
			continue;

		switch( m_allFields[lpos]->GetType())
		{
		case Geodatabase::FTYPE_DATE:
			{
				const char* pszDateValue = 
					DBFReadStringAttribute(m_dbfHandle,index-1,lpos); 

				pFeature->m_values[lpos].vtype =Geodatabase::FieldValue::VT_DATE;

				if( pszDateValue[2] == '/' && pszDateValue[5] == '/' 
					&& strlen(pszDateValue) >= 10 )
				{
					pFeature->m_values[lpos].m_Var.date.Month =atoi(pszDateValue+0);

					pFeature->m_values[lpos].m_Var.date.Day   = atoi(pszDateValue+3);
					pFeature->m_values[lpos].m_Var.date.Year  = atoi(pszDateValue+6);
				}
				else
				{
					int nFullDate = atoi(pszDateValue);
					pFeature->m_values[lpos].m_Var.date.Year = (int)(nFullDate / 10000);
					pFeature->m_values[lpos].m_Var.date.Month = (unsigned char)((nFullDate / 100) % 100);
					pFeature->m_values[lpos].m_Var.date.Day = (unsigned char)(nFullDate % 100);
				}
				break;
			}
		case Geodatabase::FTYPE_STRING:

			pFeature->m_values[lpos].SetString(DBFReadStringAttribute(m_dbfHandle, index-1,lpos ));

			break;

		case Geodatabase::FTYPE_LONG:
			pFeature->m_values[lpos].vtype =FieldValue::VT_INT;
			pFeature->m_values[lpos].m_Var.iVal =DBFReadIntegerAttribute(m_dbfHandle, index-1,lpos );

			break;

		case Geodatabase::FTYPE_FLOAT:
		case Geodatabase::FTYPE_DOUBLE:
			pFeature->m_values[lpos].vtype =FieldValue::VT_DOUBLE;
			pFeature->m_values[lpos].m_Var.dVal =DBFReadDoubleAttribute(m_dbfHandle, index-1,lpos );

			break;

		default:
			break;
		}

	}
}

void CShapefileFeatureClass::serialization(SYSTEM::IArchive &ar)
{
	if(ar.IsSave())
	{
		std::string type ="ShpDriver";
		ar&type;
		//序列化工作空间
		if(m_pWorkspace)
		{
			m_pWorkspace->serialization(ar);
		}
		

		//存储相对路径
		//计算相对路径
		std::string relPath =SYSTEM::CRelativePath::RelativePath(m_name.c_str());
		ar&relPath;
	}
}

void CShapefileFeatureClass::BuildSpatialIndex()
{
    //检查索引文件是否存在
	std::string path =m_name;
	path =path.substr(0,path.rfind("."));
	path+=".qix";

	m_IndexTree =fopen(path.c_str(),"rb");

	//原来没有索引，则建立索引文件
	if(m_IndexTree==NULL)
	{
		SHPTree	*psTree;

		
		psTree = SHPCreateTree( m_shpHandle, 2, 0, NULL, NULL );

		if( NULL == psTree )
		{
			
			return ;
		}

		
		SHPTreeTrimExtraNodes( psTree );

		/* -------------------------------------------------------------------- */
		/*      将索引树保存成文件                                              */
		/* -------------------------------------------------------------------- */
		
		SHPWriteTree( psTree, path.c_str());
	
		SHPDestroyTree( psTree );

		//打开索引文件
        m_IndexTree =fopen(path.c_str(),"rb");
	}
}

