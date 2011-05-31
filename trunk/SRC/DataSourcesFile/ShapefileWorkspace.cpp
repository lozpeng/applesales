#include "stdafx.h"
#include "ShapefileWorkspaceFactory.h"
#include "ShapefileWorkspace.h"
#include "ShapefileFeatureClass.h"
#include "Exception.h"
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/LineString.h>
#include <Geometry/geom/MultiLineString.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/LinearRing.h>
#include <geometry/geom/MultiPolygon.h>
#include "stringOperate.h"

using namespace Geodatabase;
using namespace GEOMETRY::geom;
using namespace std;


CShapefileWorkspace::CShapefileWorkspace(CShapefileWorkspaceFactory *pFactory):IWorkspace(pFactory)
{
	m_type =WT_FileSystem;

	m_lcursor=-1;

	m_bStartOp =false;
}

CShapefileWorkspace::~CShapefileWorkspace()
{
	//清理编辑缓存
	ClearEditCache();
}

////CShapefileWorkspace没有矢量数据集
//long CShapefileWorkspace::DatasetCount(Geodatabase::GEODATATYPE type) const
//{
//	return 0;
//}

//不实现打开数据集
IFeatureDatasetPtr CShapefileWorkspace::OpenFeatureDataset(const char *name)
{
	return NULL;
}


IFeatureClassPtr CShapefileWorkspace::OpenFeatureClass(const char *name)
{
	//首先判断该文件是否是这个工作空间的
	string path =name;
	m_FullName = name;
	path =path.substr(0,path.rfind('\\'));

	if(path!=m_pathname)
	{
		return IFeatureClassPtr();
	}
    SHPHandle hshp =SHPOpen(name,"r");
	if(!hshp)
	{
		return IFeatureClassPtr();
	}
    
	string dbfname =name;
	dbfname =dbfname.substr(0,dbfname.rfind("."));
	dbfname+=".dbf";
	DBFHandle hdbf =DBFOpen(dbfname.c_str(),"r");
	if(!hdbf)
	{
		SHPClose(hshp);
        return IFeatureClassPtr();
	}
	
	CShapefileFeatureClass *pFeatureClass =new CShapefileFeatureClass(this,hshp,hdbf,name,true);

	m_FeatureClass = IFeatureClassPtr(pFeatureClass);
	return IFeatureClassPtr(pFeatureClass);

}
/*****************************************************************************************************
*  以下为创建数据相关的操作
*
*******************************************************************************************************/

IFeatureClassPtr CShapefileWorkspace::CreateFeatureClass(const char *name, const Geodatabase::FeatureClassDef &FDef)
{
	std::string filename =name;
	//基础文件名称
	std::string basename =filename.substr(0,filename.rfind("."));

	/* -------------------------------------------------------------------- */
	/*     创建图形shp文件                                                  */
	/* -------------------------------------------------------------------- */
	int  nShapeType;

	switch(FDef.lshptype)
	{
	case GEOMETRY::geom::GEOS_POINT:
		{
			//判断是否包含M和Z信息
			if(FDef.hasz)
			{
				nShapeType =SHPT_POINTZ;
			}
			else
			{
				if(FDef.hasm)
				{
					nShapeType =SHPT_POINTM;
				}
				else
				{
					nShapeType =SHPT_POINT;
				}
			}
			break;
		}
	case GEOMETRY::geom::GEOS_MULTIPOINT:
		{
			//判断是否包含M和Z信息
			if(FDef.hasz)
			{
				nShapeType =SHPT_MULTIPOINTZ;
			}
			else
			{
				if(FDef.hasm)
				{
					nShapeType =SHPT_MULTIPOINTM;
				}
				else
				{
					nShapeType =SHPT_MULTIPOINT;
				}
			}
			break;
		}
	case GEOMETRY::geom::GEOS_LINESTRING:
	case GEOMETRY::geom::GEOS_LINEARRING:
	case GEOMETRY::geom::GEOS_MULTILINESTRING:
		{
			//判断是否包含M和Z信息
			if(FDef.hasz)
			{
				nShapeType =SHPT_ARCZ;
			}
			else
			{
				if(FDef.hasm)
				{
					nShapeType =SHPT_ARCM;
				}
				else
				{
					nShapeType =SHPT_ARC;
				}
			}
			break;
		}
	case GEOMETRY::geom::GEOS_POLYGON:
	case GEOMETRY::geom::GEOS_MULTIPOLYGON:
		{
			//判断是否包含M和Z信息
			if(FDef.hasz)
			{
				nShapeType =SHPT_POLYGONZ;
			}
			else
			{
				if(FDef.hasm)
				{
					nShapeType =SHPT_POLYGONM;
				}
				else
				{
					nShapeType =SHPT_POLYGON;
				}
			}
			break;
		}
	default:
		return NULL;
	}

	SHPHandle hSHP = SHPCreate( name, nShapeType );

	if(hSHP ==NULL)
	{
		return NULL;
	}

	/* -------------------------------------------------------------------- */
	/*     创建DBF文件                                                      */
	/* -------------------------------------------------------------------- */
    
	std::string dbfname =basename +".dbf";
    
	DBFHandle hDBF = DBFCreate( dbfname.c_str());

	if(hDBF ==NULL)
	{
		return NULL;
	}

	Geodatabase::CFieldPtr pField;
	//创建DBF的字段结构
    for(long i=0;i<FDef.FieldsDef.size();i++)
	{
        pField =FDef.FieldsDef[i];

		if(!pField)
		{
			continue;
		}
		switch(pField->GetType())
		{
		case FTYPE_LONG:
		case FTYPE_SHORT:
			{
				if( pField->GetLength() == 0 )
				{
					DBFAddField( hDBF, pField->GetName().c_str(), FTInteger, 11, 0 );
				}			
				else
				{
					DBFAddField( hDBF, pField->GetName().c_str(), FTInteger,
					pField->GetLength(), 0 );
				}

				break;
			}
		case FTYPE_FLOAT:
		case FTYPE_DOUBLE:
			{
				if( pField->GetLength() == 0 )
				{
					DBFAddField( hDBF, pField->GetName().c_str(), FTDouble, 24, pField->Precision());
				}			
				else
				{
					DBFAddField( hDBF, pField->GetName().c_str(), FTDouble,
						pField->GetLength(), pField->Precision() );
				}
				break;
			}
		case FTYPE_STRING:
			{
				if( pField->GetLength() < 1)
				{
					DBFAddField( hDBF, pField->GetName().c_str(), FTString, 80, 0 );
				}			
				else
				{
					DBFAddField( hDBF, pField->GetName().c_str(), FTString,
						pField->GetLength(), 0 );
				}
				break;
			}
		case FTYPE_TIME:
		case FTYPE_DATE:
			{
                DBFAddNativeFieldType( hDBF, pField->GetName().c_str(), 'D', 8, 0 );
			}
		default:
			continue;
			break;

		}
	}

	/* -------------------------------------------------------------------- */
	/*     创建投影PRJ文件                                                  */
	/* -------------------------------------------------------------------- */
    
     if(!FDef.wkt.empty())
	 {
		 std::string prjfile =basename+".prj";

		 FILE *fp = fopen(prjfile.c_str(),"wt");

		 if(fp)
		 {
			 
			 fwrite(FDef.wkt.c_str(),sizeof(char),FDef.wkt.length(),fp);

			 fclose(fp);
		 }
		 

		 
	 }


	 CShapefileFeatureClass *pFeatureClass =new CShapefileFeatureClass(this,hSHP,hDBF,name,false);

	 return IFeatureClassPtr(pFeatureClass);



}


/*****************************************************************************************************
*  以下为编辑相关的操作
*
*******************************************************************************************************/

void CShapefileWorkspace::StartEdit()
{
	if(!m_bEditing)
	{

		m_bEditing =true;
		ClearEditCache();

		//导入增量信息
		std::string path = SYSTEM::CSystemPath::GetSystemPath();
		path.append("\Incremental.xml");	
		this->IncrementalImport(path.c_str());
	}
}

void CShapefileWorkspace::Commit()
{

    SaveEdit();
    
	ClearEditCache();
}

void CShapefileWorkspace::Abort()
{
   ClearEditCache();
}



void CShapefileWorkspace::StopEdit(bool bsave)
{
	if(!m_bEditing)
	{
		return;
	}
	if(bsave)
	{
		//导出增量信息
		std::string path = SYSTEM::CSystemPath::GetSystemPath();
		path.append("\Incremental.xml");	
		this->IncrementalExport(path.c_str());

		SaveEdit();

	}

	m_bEditing =false;

	ClearEditCache();


}

void CShapefileWorkspace::StartEditOperation()
{

	if(!m_bEditing)
	{
		return;
	}
	if(!m_curOperation.empty())
	{
		m_curOperation.clear();
	}

	m_bStartOp =true;
	//将回滚点之后的堆栈清空
	RemoveRedundant();

}

void CShapefileWorkspace::StopEditOperation()
{
	//将这次的操作压入堆栈
	if(!m_curOperation.empty())
	{
		m_EditStack.push_back(m_curOperation);

		m_lcursor++;
	}

	m_bStartOp =false;
}

//放弃这次编辑操作
void CShapefileWorkspace::AbortOperation()
{

}

void CShapefileWorkspace::UndoEdit()
{
	if(!CanUndo())
	{
		return;
	}

	EditCacheMap::iterator iter;
	//依次调用每个数据类缓存的回退方法
	for(size_t i=0;i<m_EditStack[m_lcursor].size();i++)
	{
		iter = m_EditCacheMap.find(m_EditStack[m_lcursor][i]);

		if(iter!=m_EditCacheMap.end())
		{
			iter->second->Undo();
		}
	}

	m_lcursor--;

}

void CShapefileWorkspace::RedoEdit()
{
	if(!CanRedo())
	{
		return;
	}
	EditCacheMap::iterator iter;
	//依次调用每个数据类缓存的回退方法
	for(size_t i=0;i<m_EditStack[m_lcursor+1].size();i++)
	{
		iter = m_EditCacheMap.find(m_EditStack[m_lcursor+1][i]);

		if(iter!=m_EditCacheMap.end())
		{
			iter->second->Redo();
		}
	}

	m_lcursor++;

}

bool CShapefileWorkspace::CanUndo() const
{
	return (m_lcursor>=0);
}

bool CShapefileWorkspace::CanRedo() const
{
	long num =m_EditStack.size();

	return (num>0 && m_lcursor<(num-1));
}

/*****************************************************************************************************
*  以下为供内部类使用的操作编辑缓存的接口
*
*******************************************************************************************************/
//清理编辑缓存
void CShapefileWorkspace::ClearEditCache()
{
	EditCacheMap::iterator iter;

	for(iter=m_EditCacheMap.begin();iter!=m_EditCacheMap.end();iter++)
	{
		delete iter->second;

		iter->second =NULL;
	}
	m_EditCacheMap.clear();

	//回滚堆栈清空
	m_EditStack.clear();

	m_curOperation.clear();

	m_lcursor=-1;
}

bool CShapefileWorkspace::ExistEditCache(std::string filename)
{
	EditCacheMap::iterator iter =m_EditCacheMap.find(filename);

	return (iter!=m_EditCacheMap.end());

}

void CShapefileWorkspace::RemoveEditCache(std::string filename)
{
	EditCacheMap::iterator iter =m_EditCacheMap.find(filename);

	if(iter!=m_EditCacheMap.end())
	{
		delete iter->second;
		m_EditCacheMap.erase(iter);
	}
}

void CShapefileWorkspace::BuildEditCache(IFeatureClass *pFeatureClass)
{
	string filename =pFeatureClass->Getname();

	if(ExistEditCache(filename))
	{
		return;
	}

	//建立一个新的编辑缓存
	CFeatureEditCache *pEditCache =new CFeatureEditCache(pFeatureClass);

	//设置有效要素的数目
	pEditCache->m_lnextRecId =pFeatureClass->FeatureCount()+1;

	pEditCache->m_lvalidNum =pFeatureClass->FeatureCount();

	m_EditCacheMap[filename] =pEditCache;

}

//查找一个数据类的缓存
CFeatureEditCache* CShapefileWorkspace::FindEditCache(std::string filename)
{
	EditCacheMap::iterator iter =m_EditCacheMap.find(filename);

	if(iter==m_EditCacheMap.end())
	{
		return NULL;
	}

	return iter->second;
}

void CShapefileWorkspace::AddFeature(Geodatabase::IFeatureClass *pFeatureClass, Geodatabase::CFeaturePtr pFeature)
{
	//如果不是处于编辑状态，则返回
	if(!m_bEditing)
	{
		return;
	}
	if(!pFeature)
	{
		return;
	}

	string name =pFeatureClass->Getname();

	CFeatureEditCache *pCache =FindEditCache(name);
	if(!pCache)
	{
		BuildEditCache(pFeatureClass);

		pCache =FindEditCache(name);
	}

	//将新的id赋给Feature
	pFeature->SetId(pCache->GetTotalNum()+1);

	pCache->AppendFeature(pFeature);
	if(m_bStartOp)
	{
		m_curOperation.push_back(name);
	}


}
void CShapefileWorkspace::UpdateFeature(Geodatabase::IFeatureClass *pFeatureClass,CFeaturePtr pFeature)
{
	//如果不是处于编辑状态，则返回
	if(!m_bEditing)
	{
		return;
	}
	if(!pFeature)
	{
		return;
	}

	string name =pFeatureClass->Getname();

	CFeatureEditCache *pCache =FindEditCache(name);
	if(!pCache)
	{
		BuildEditCache(pFeatureClass);

		pCache =FindEditCache(name);
	}

	pCache->UpdateFeature(pFeature);

	if(m_bStartOp)
	{
		m_curOperation.push_back(name);
	}
}

void CShapefileWorkspace::DeleteFeature(Geodatabase::IFeatureClass *pFeatureClass, long index)
{
	//如果不是处于编辑状态，则返回
	if(!m_bEditing)
	{
		return;
	}

	string name =pFeatureClass->Getname();

	CFeatureEditCache *pCache =FindEditCache(name);
	if(!pCache)
	{
		BuildEditCache(pFeatureClass);

		pCache =FindEditCache(name);
	}

	pCache->DeleteFeature(index);

	if(m_bStartOp)
	{
		m_curOperation.push_back(name);
	}
}
//清除掉堆栈中多余的记录
void CShapefileWorkspace::RemoveRedundant()
{
	if(m_lcursor!=(m_EditStack.size()-1))
	{
		long lstart =(m_lcursor>=-1) ?(m_lcursor+1) :0;

		m_EditStack.erase(m_EditStack.begin()+lstart,m_EditStack.end());
	}

}


void CShapefileWorkspace::SaveEdit()
{
	FEditStep *pStep;

	bool bhasTable =true;

	CFeature *pFeature =NULL;

	long curRec,editId;

	size_t i =0;

	bool OnlyUpdate =true;

	std::string filename;

	//保存缓存中编辑的要素
	EditCacheMap::iterator iter;
	for(iter =m_EditCacheMap.begin();iter!=m_EditCacheMap.end();iter++)
	{
		
		CFeatureEditCache *pCache =iter->second;

		CShapefileFeatureClass *pFeatureClass =(CShapefileFeatureClass*)pCache->m_pFeatureClass;

		//如果原来的文件是只读方式，则重新按照读写方式打开
		if(pFeatureClass->m_Readonly)
		{
			DBFClose( pFeatureClass->m_dbfHandle );

			SHPClose( pFeatureClass->m_shpHandle );
			pFeatureClass->m_dbfHandle =NULL;
			pFeatureClass->m_shpHandle =NULL;

			filename =pFeatureClass->Getname();
            SHPHandle hshp =SHPOpen(filename.c_str(),"r+");
			if(!hshp)
			{
				std::string des =filename;
				des+="文件无法以读写方式打开，请确保文件没有被其它程序占用";
				//EXCEPT(des.c_str());
			    continue;
			}

			string dbfname =filename;
			dbfname =dbfname.substr(0,dbfname.rfind("."));
			dbfname+=".dbf";
			DBFHandle hdbf =DBFOpen(dbfname.c_str(),"r+");
			if(!hdbf)
			{
				SHPClose(hshp);
				std::string des =filename;
				des+="文件无法以读写方式打开，请确保文件没有被其它程序占用";
				
				continue;
			}
            
			pFeatureClass->m_dbfHandle =hdbf;
			pFeatureClass->m_shpHandle =hshp;

			pFeatureClass->m_Readonly =false;

		}

		//排列缓存里的要素记录
		pCache->Arrange();

		//判断缓存里的记录是不是只是修改要素
        OnlyUpdate =true;
		for(i=0;i<pCache->m_operationStack.size();i++)
		{
            pStep =pCache->m_operationStack[i];

			if(!pStep)
			{
				continue;
			}
			if(pStep->EditType!=OP_UPDATE)
			{
               OnlyUpdate =false;
			   break;
			}
		}

		//如果只是修改要素，则不需要重新生成数据文件，只需在原来的文件上修改
		if(OnlyUpdate)
		{
			for(i=0;i<pCache->m_operationStack.size();i++)
			{
				pStep =pCache->m_operationStack[i];

				if(!pStep)
				{
					continue;
				}

                WriteFeature(pStep->pFeature.get(),pFeatureClass->m_shpHandle,pFeatureClass->m_dbfHandle);

			}

		}
		else
		{
			//如果是添加，删除了要素，则要重新建立一个文件，将原来的要素和新要素都写入，最后将原来文件删除
			DBFHandle hNewDBF = NULL;

			std::string filename  =pFeatureClass->Getname();
			std::string basename =filename.substr(0,filename.find_last_of('.'));
			basename=basename.substr(basename.find_last_of('\\')+1,basename.size()-basename.find_last_of('\\')-1);


			std::string dbfname =m_pathname+"\\";
			dbfname+=basename;
			dbfname+="_packed.dbf";

			//创建一个空的临时dbf文件
			hNewDBF = DBFCloneEmpty( pFeatureClass->m_dbfHandle, dbfname.c_str());
			if( hNewDBF == NULL )
			{
				//EXCEPT("无法创建临时文件");
				continue;
			}

			/* -------------------------------------------------------------------- */
			/*     创建一个shpfile临时文件                                          */
			/* -------------------------------------------------------------------- */
			SHPHandle hNewSHP = NULL;

			std::string shpname =m_pathname+"\\";
			shpname+=basename;
			shpname+="_packed.shp";

			hNewSHP = SHPCreate( shpname.c_str(),pFeatureClass->m_shpHandle->nShapeType );
			if( hNewSHP == NULL )
			{
				//EXCEPT("无法创建临时文件");
				continue;
			}


			/* -------------------------------------------------------------------- */
			/*    首先将原有的记录拷贝到临时文件里                                  */
			/* -------------------------------------------------------------------- */
            
			int iShape;
			int i=0;
            bool bFound =false;
			SHPObject *hObject;
			void *pTuple =NULL;
            int iDestShape =0;
			for( iShape = 0; iShape < pFeatureClass->m_shpHandle->nRecords;iShape++ )
			{
				bFound =false;

				//判断该要素是否被删除或者修改
				for(i=0;i<pCache->m_operationStack.size();i++)
				{
					pStep =pCache->m_operationStack[i];
					if(pStep==NULL)
					{
						continue;
					}
					if(pStep->Fid==iShape+1)
					{
						
						if(pStep->EditType==OP_UPDATE)
						{
                            WriteFeature(pStep->pFeature.get(),hNewSHP,hNewDBF,true);
							iDestShape++;
						}
						bFound =true;
						break;
					}
					
				}
				if(!bFound)
				{
					
                    //写入图形
					hObject = SHPReadObject( pFeatureClass->m_shpHandle, iShape );
					if(!hObject)
					{
						continue;
					}
					SHPWriteObject( hNewSHP, -1, hObject );

					SHPDestroyObject( hObject );

					//写入属性
					pTuple = (void *) DBFReadTuple( pFeatureClass->m_dbfHandle, iShape );
					if( pTuple == NULL )
					{
						continue;
					}
					DBFWriteTuple( hNewDBF, iDestShape++, pTuple );
					

				}
				
			}

		    //写入编辑缓存中新添加的记录
			for(i=0;i<pCache->m_operationStack.size();i++)
			{
				pStep =pCache->m_operationStack[i];
				if(pStep==NULL)
				{
					continue;
				}
				if(pStep->EditType==OP_ADD)
				{

				    WriteFeature(pStep->pFeature.get(),hNewSHP,hNewDBF,true);
					
				}

			}

			/* -------------------------------------------------------------------- */
			/*     删除原来的文件，将临时文件重命名                                 */
			/* -------------------------------------------------------------------- */
			DBFClose( pFeatureClass->m_dbfHandle );
			SHPClose( pFeatureClass->m_shpHandle );
			DBFClose( hNewDBF );
			SHPClose( hNewSHP );

			pFeatureClass->m_dbfHandle  = hNewDBF = NULL;
			pFeatureClass->m_shpHandle =hNewSHP =NULL;

			std::string olddbf =m_pathname+"\\";
			olddbf+=basename;
			olddbf +=".dbf";

			std::string oldshp =m_pathname+"\\";
			oldshp+=basename;
			oldshp +=".shp";

			std::string oldshx =m_pathname+"\\";
			oldshx+=basename;
			oldshx +=".shx";

			std::string shxname =m_pathname+"\\";
			shxname+=basename;
			shxname+="_packed.shx";
            
			if(_unlink(olddbf.c_str())!=0)
			{
                //EXCEPT("无法删除原有文件，请确保文件不是只读，并且没有被其它程序打开");
			}
			if(_unlink(oldshp.c_str())!=0)
			{
				//EXCEPT("无法删除原有文件，请确保文件不是只读，并且没有被其它程序打开");
			}
			if(_unlink(oldshx.c_str())!=0)
			{
				//EXCEPT("无法删除原有文件，请确保文件不是只读，并且没有被其它程序打开");
			}

			rename(dbfname.c_str(),olddbf.c_str());

			rename(shpname.c_str(),oldshp.c_str());

			rename(shxname.c_str(),oldshx.c_str());
            
			

			/* -------------------------------------------------------------------- */
			/*      打开新的shp文件                                                 */
			/*                                                                      */
			/* -------------------------------------------------------------------- */
		

			pFeatureClass->m_shpHandle = SHPOpen (oldshp.c_str(), "r" );
			pFeatureClass->m_dbfHandle = DBFOpen (olddbf.c_str(),"r" );

			
			
		}

		
	}
}

bool CShapefileWorkspace::WriteFeature(Geodatabase::CFeature *pFeature, SHPHandle &hshp, DBFHandle &hdbf,bool bAppend)
{
    if(!pFeature)
	{
		return false;
	}
	int Fid;
	if(bAppend)
	{
        Fid =-1;
	}
	else
	{
       Fid = pFeature->GetId()-1;
	}
	GEOMETRY::geom::Geometry *pg =pFeature->GetShape();
	if(pg)
	{
		//将图形转化为Shp内部格式
        SHPObject *shpobj =Geometry2Shp(pg,hshp->nShapeType);
		if(!shpobj)
		{
			return false;
		}

		//写入图形数据
		SHPWriteObject( hshp, Fid, shpobj );
		SHPDestroyObject( shpobj );
	}
	if(hdbf)
	{
        if(bAppend)
		{
			Fid =hdbf->nRecords;
		}
		Geodatabase::FieldValue::VTYPE type;
		//写入属性数据
		for(long iField=0;iField<pFeature->FieldCount();iField++)
		{
			type =pFeature->GetValue(iField+1).vtype;

			bool bFlagNull = false;
			//判断属性值是否空值
			if(type ==Geodatabase::FieldValue::VT_EMPTY || type==Geodatabase::FieldValue::VT_NULL)
			{
				bFlagNull = true;
				//continue; //hhzhao 注释掉，不然dbf表记录与shp记录不一致
			}

			if ( hdbf->pachFieldType[iField] == 'L' )
			{
				//逻辑型

			}
			else if( hdbf->pachFieldType[iField] == 'N' 
				|| hdbf->pachFieldType[iField] == 'F' )
			{
				if( hdbf->panFieldDecimals[iField] > 0 
					|| hdbf->panFieldSize[iField] > 10 )
				{
					//double型
					DBFWriteDoubleAttribute(hdbf,Fid,iField,pFeature->GetValue(iField+1).m_Var.dVal);
				}
				else
				{
					//整型
					DBFWriteIntegerAttribute(hdbf,Fid,iField,pFeature->GetValue(iField+1).m_Var.iVal);
				}
			}
			else
			{
				//字符型
				if(!bFlagNull)
					DBFWriteStringAttribute(hdbf,Fid,iField,pFeature->GetValue(iField+1).m_Var.pstrVal->c_str());
			}
		}
	}
	

}

SHPObject *CShapefileWorkspace::Geometry2Shp(GEOMETRY::geom::Geometry *pGeometry,int nSHPType)
{
	using namespace GEOMETRY::geom;
	typedef vector<Coordinate> CoordVect;

	if(!pGeometry)
	{
		return NULL;
	}
	bool hasz =pGeometry->HasZ();
	bool hasm =pGeometry->HasM();

	SHPObject *pshape =NULL;
	GEOMETRY::geom::Coordinate coord;

	switch(pGeometry->getGeometryTypeId())
	{
	case GEOMETRY::geom::GEOS_POINT:
		{
			coord =pGeometry->GetPoint(0);
			pshape = SHPCreateObject( nSHPType, -1, 0, NULL, NULL,
				1, &coord.x, &coord.y, &coord.z, &coord.m );
			break;
		}
	case GEOMETRY::geom::GEOS_MULTIPOINT:
	case GEOMETRY::geom::GEOS_LINESTRING:
	case GEOMETRY::geom::GEOS_LINEARRING:
		{
			long lcount =pGeometry->PointCount();
			double *pdx =new double[lcount];
			double *pdy =new double[lcount];
			double *pdz =new double[lcount];
			double *pdm =new double[lcount];

			for(long i=0;i<lcount;i++)
			{
				coord =pGeometry->GetPoint(i);
				pdx[i] =coord.x;
				pdy[i] =coord.y;
				pdz[i] =coord.z;
				pdm[i] =coord.m;

			}
			pshape = SHPCreateObject( nSHPType, -1, 0, NULL, NULL,
				lcount, pdx, pdy, pdz, pdm );

			delete []pdx;
			delete []pdy;
			delete []pdz;
			delete []pdm;

			break;
		}
	case GEOMETRY::geom::GEOS_MULTILINESTRING:
		{
			long lcount =pGeometry->PointCount();
			if(lcount<=0)
			{
				break;
			}
			double *pdx =new double[lcount];
			double *pdy =new double[lcount];
			double *pdz =new double[lcount];
			double *pdm =new double[lcount];

			
			GEOMETRY::geom::Geometry *pg =NULL;
			long lpart =((GEOMETRY::geom::MultiLineString*)pGeometry)->getNumGeometries();

			
			CoordVect *pcoords=NULL;
			int *plParts =new int[lpart];
			
			long lptnum,index=0;
			long i,j;
			for( i=0;i<lpart;i++)
			{
				plParts[i] =index;
				pg =const_cast<Geometry*>(((MultiLineString*)pGeometry)->getGeometryN(i));

				pcoords =const_cast<CoordVect*>((dynamic_cast<LineString*>(pg))->getCoordinatesRO()->toVector());
				lptnum =pg->PointCount();
				for(j=0;j<lptnum;j++)
				{
					coord =(*pcoords)[j];
					pdx[index] =coord.x;
					pdy[index] =coord.y;
					pdz[index] =coord.z;
					pdm[index] =coord.m;
					index++;
				}


			}

			pshape = SHPCreateObject( nSHPType, -1, 
				lpart, 
				plParts, NULL,
				lcount, pdx,  pdy, pdz, pdm);

			delete []pdx;
			delete []pdy;
			delete []pdz;
			delete []pdm;
			break;
		}
	case GEOMETRY::geom::GEOS_POLYGON:
		{
			long lcount =pGeometry->PointCount();
			if(lcount<=0)
			{
				break;
			}
			double *pdx =new double[lcount];
			double *pdy =new double[lcount];
			double *pdz =new double[lcount];
			double *pdm =new double[lcount];
			Geometry *pg =NULL;
			long lpart =((GEOMETRY::geom::Polygon*)pGeometry)->GeometryCount();

			CoordVect *pcoords =NULL;
			
			int *plParts =new int[lpart];
			

			long lptnum,index=0;
			long i,j;
			for( i=0;i<lpart;i++)
			{
				plParts[i] =index;
				pg =((GEOMETRY::geom::Polygon*)pGeometry)->GetGeometry(i);
				pcoords=const_cast<CoordVect*>((dynamic_cast<GEOMETRY::geom::LinearRing*>(pg))->getCoordinatesRO()->toVector());
				lptnum =pg->PointCount();
				for(j=0;j<lptnum;j++)
				{
					coord =(*pcoords)[j];
					pdx[index] =coord.x;
					pdy[index] =coord.y;
					pdz[index] =coord.z;
					pdm[index] =coord.m;
					index++;
				}


			}
			pshape = SHPCreateObject( nSHPType, -1, 
				lpart, 
				plParts, NULL,
				lcount, pdx,  pdy, pdz, pdm);

			delete []pdx;
			delete []pdy;
			delete []pdz;
			delete []pdm;
			break;
		}
	case GEOMETRY::geom::GEOS_MULTIPOLYGON:
		{
			long lcount =pGeometry->getNumPoints();
			if(lcount<=0)
			{
				break;
			}
			double *pdx =new double[lcount];
			double *pdy =new double[lcount];
			double *pdz =new double[lcount];
			double *pdm =new double[lcount];
			Geometry *pg =NULL;

			//多边形的数目
			long lPolygons =((GEOMETRY::geom::MultiPolygon*)pGeometry)->GeometryCount();

			//线环的总数目
			long lTotalPart=0,lpart =0;
			long i,j;
			std::vector<GEOMETRY::geom::LinearRing*> rings;
			

			for(i=0;i<lPolygons;i++)
			{
               pg =((GEOMETRY::geom::MultiPolygon*)pGeometry)->GetGeometry(i);

			   lpart=((GEOMETRY::geom::Polygon*)pg)->GeometryCount();

			   lTotalPart+=lpart;

			   for(j =0;j<lpart;j++)
			   {
                   rings.push_back(dynamic_cast<GEOMETRY::geom::LinearRing*>(((GEOMETRY::geom::Polygon*)pg)->GetGeometry(j)));

			   }

			}
				
			CoordVect *pcoords =NULL;

			int *plParts =new int[lTotalPart];

			long lptnum,index=0;
			
			for( i=0;i<lTotalPart;i++)
			{
				plParts[i] =index;
				
				pcoords=const_cast<CoordVect*>((rings[i])->getCoordinatesRO()->toVector());
				lptnum =rings[i]->PointCount();
				for(j=0;j<lptnum;j++)
				{
					coord =(*pcoords)[j];
					pdx[index] =coord.x;
					pdy[index] =coord.y;
					pdz[index] =coord.z;
					pdm[index] =coord.m;
					index++;
				}


			}
			pshape = SHPCreateObject( nSHPType, -1, 
				lTotalPart, 
				plParts, NULL,
				lcount, pdx,  pdy, pdz, pdm);

			delete []pdx;
			delete []pdy;
			delete []pdz;
			delete []pdm;
			break;
		}
	default:
		return NULL;
		break;
	}
    

	return pshape;

}

//增量导出、导入
const std::string node_Incremental ="incremental";
const std::string node_CaptureTime ="CaptureTime";
const std::string node_PolygonFeature ="PolygonFeature";
const std::string node_LineFeature ="LineFeature";
const std::string node_PointFeature ="PointFeature";
const std::string node_FlagAdd ="Add";
const std::string node_FlagDelete ="Delete";
const std::string node_FlagAttribute ="Attribute";
const std::string node_FlagModify ="Modify";
const std::string node_coordinate = "coordinate";
const std::string node_FeatID = "FeatID";

SYSTEM::XMLConfigurationPtr ipIncremenalFile = NULL;
#include <boost/filesystem.hpp>
void CShapefileWorkspace::IncrementalExport(std::string incrementalFile)
{

	SYSTEM::CXMLConfiguration::Initialize();
	try
	{
		if(ipIncremenalFile == NULL)
		   ipIncremenalFile = new SYSTEM::CXMLConfiguration;
		ipIncremenalFile->Create(incrementalFile,"UTF-8",node_Incremental);
		
		//增加时间节点
		SYSTEM::IConfigItemPtr ipCurTimeNode = ipIncremenalFile->AddChildNode(node_CaptureTime.c_str());
		time_t t = time(0);    
		char szCurTime[64];    
		strftime( szCurTime, sizeof(szCurTime), "%Y-%m-%d %X",localtime(&t));    
		ipCurTimeNode->SetValue(szCurTime);

		FEditStep *pStep;
		CFeature *pFeature =NULL;
		char destBuf[1024];

		//保存缓存中编辑的要素
		EditCacheMap::iterator iter;
		for(iter =m_EditCacheMap.begin();iter!=m_EditCacheMap.end();iter++)
		{

			CFeatureEditCache *pCache =iter->second;

			CShapefileFeatureClass *pFeatureClass =(CShapefileFeatureClass*)pCache->m_pFeatureClass;
			//要素类型
			long shapeType = pFeatureClass->ShapeType();
			std::string strFeatureType;
			if( shapeType == GEOS_POINT || shapeType == GEOS_MULTIPOINT )
			{
				strFeatureType = node_PointFeature;
			}
			else if( shapeType == GEOS_LINESTRING || shapeType == GEOS_MULTILINESTRING )
			{
				strFeatureType = node_LineFeature;
			}
			else if( shapeType == GEOS_POLYGON || shapeType == GEOS_MULTIPOLYGON )
			{
				strFeatureType = node_PolygonFeature;
			}
			SYSTEM::IConfigItemPtr ipFeatureTypeNode = ipIncremenalFile->GetChildByName(strFeatureType.c_str());
			if (ipFeatureTypeNode == NULL)
			{
				ipFeatureTypeNode = ipIncremenalFile->AddChildNode(strFeatureType.c_str());
			}

			//要素名称  m_pathname

			std::string strFeatureClsName = pFeatureClass->Getname();
			std::string basename =strFeatureClsName.substr(0,strFeatureClsName.find_last_of('.'));
			basename=basename.substr(basename.find_last_of('\\')+1,basename.size()-basename.find_last_of('\\')-1);
			SYSTEM::IConfigItemPtr ipFeatureNameNode = ipFeatureTypeNode->GetChildByName(basename.c_str());
			if (ipFeatureNameNode == NULL)
			{
				strcpy(destBuf,basename.c_str());
				ipFeatureNameNode = ipFeatureTypeNode->AddChildNode(destBuf);
			}

			//ChangeType Add、Delete、Modify、Attribute
			//排列缓存里的要素记录
			pCache->Arrange();

			//判断缓存里的记录是不是只是修改要素
			
			for(int i=0;i<pCache->m_operationStack.size();i++)
			{
				pStep =pCache->m_operationStack[i];

				if(!pStep)
				{
					continue;
				}
				if(pStep->EditType == OP_ADD)
				{
					SYSTEM::IConfigItemPtr ipFlagAddNode  = ipFeatureNameNode->AddChildNode(node_FlagAdd.c_str());
					
					//各个字段值
					for(int j = 0;j<pFeatureClass->FieldCount();j++)
					{	
						//得到字段名
						std::string fieldName = pFeatureClass->GetField(j+1)->GetName();
						SYSTEM::IConfigItemPtr   ipFeildNode= ipFlagAddNode->AddChildNode(fieldName.c_str());
						//得到字段值
						std::string csValue =pStep->pFeature->GetValue(j+1).GetasString().c_str();
						ipFeildNode->SetValue(csValue.c_str());
					}
					
					//坐标值
					SYSTEM::IConfigItemPtr   ipCoorNode= ipFlagAddNode->AddChildNode(node_coordinate.c_str());
					GEOMETRY::geom::Geometry* pgeometry = pStep->pFeature->GetShape();
					CoordinateSequence* pCoordinateSequence = pgeometry->getCoordinates();
					std::string strCoordinate;
					
					for (int k = 0;k<pCoordinateSequence->getSize();k++)
					{
						double dx = pCoordinateSequence->getX(k);
						double dy = pCoordinateSequence->getY(k);
						gcvt(dx,10,destBuf);
						strCoordinate.append(destBuf);
						strCoordinate.append(",");
						gcvt(dy,10,destBuf);
						strCoordinate.append(destBuf);
						if(k<pCoordinateSequence->getSize()-1)
							strCoordinate.append(" ");
					}
					ipCoorNode->SetValue(strCoordinate.c_str());
				}
				else if (pStep->EditType == OP_UPDATE) //暂时认为update了，图行和所有属性都修改
				{
					bool bGeoChanged = pFeatureClass->GetFeatureShape(pStep->Fid)->compareTo(pStep->pFeature->GetShape());
					

					SYSTEM::IConfigItemPtr ipFlagModifyNode  = ipFeatureNameNode->AddChildNode(node_FlagModify.c_str());
					
					//FeatID 字段
					SYSTEM::IConfigItemPtr ipChangeIndexNode  = ipFlagModifyNode->AddChildNode(node_FeatID.c_str());
					int featID = pFeatureClass->FindField(node_FeatID.c_str());
					if(featID >0)
					{
						pFeature =pCache->m_operationStack[i]->pFeature.get();
						std::string csValue =pFeature->GetValue(featID).GetasString();
						ipChangeIndexNode->SetValue(csValue.c_str());
					}

					//坐标值
					SYSTEM::IConfigItemPtr   ipCoorNode= ipFlagModifyNode->AddChildNode(node_coordinate.c_str());
					GEOMETRY::geom::Geometry* pgeometry = pStep->pFeature->GetShape();
					CoordinateSequence* pCoordinateSequence = pgeometry->getCoordinates();
					std::string strCoordinate;

					for (int k = 0;k<pCoordinateSequence->getSize();k++)
					{
						double dx = pCoordinateSequence->getX(k);
						double dy = pCoordinateSequence->getY(k);
						gcvt(dx,10,destBuf);
						strCoordinate.append(destBuf);
						strCoordinate.append(",");
						gcvt(dy,10,destBuf);
						strCoordinate.append(destBuf);
						if(k<pCoordinateSequence->getSize()-1)
							strCoordinate.append(" ");
					}
					ipCoorNode->SetValue(strCoordinate.c_str());

					SYSTEM::IConfigItemPtr ipFlagAttriNode  = ipFeatureNameNode->AddChildNode(node_FlagAttribute.c_str());

					ipChangeIndexNode  = ipFlagAttriNode->AddChildNode(node_FeatID.c_str());
					
					if(featID >0)
					{
						std::string csValue =pStep->pFeature->GetValue(featID).GetasString();
						ipChangeIndexNode->SetValue(csValue.c_str());
					}

					//各个字段值
					for(int j = 0;j<pFeatureClass->FieldCount();j++)
					{	
						//得到字段名
						std::string fieldName = pFeatureClass->GetField(j+1)->GetName();
						if(fieldName == node_FeatID)
							continue;
						SYSTEM::IConfigItemPtr   ipFeildNode= ipFlagAttriNode->AddChildNode(fieldName.c_str());
						//得到字段值
						std::string csValue =pStep->pFeature->GetValue(j+1).GetasString().c_str();
						ipFeildNode->SetValue(csValue.c_str());
						
					}



				}
				else if (pStep->EditType == OP_DELETE)
				{
					SYSTEM::IConfigItemPtr ipFlagDeleteNode = ipFeatureTypeNode->GetChildByName(node_FlagDelete.c_str());
					if (ipFlagDeleteNode == NULL)
					{
						 ipFlagDeleteNode  = ipFeatureTypeNode->AddChildNode(node_FlagDelete.c_str());
					}

					//FeatID 字段
					SYSTEM::IConfigItemPtr ipDeleteIndexNode  = ipFlagDeleteNode->AddChildNode(node_FeatID.c_str());
                    int featID = pFeatureClass->FindField(node_FeatID.c_str());
					if(featID >0)
					{
						pFeature =pCache->m_operationStack[i]->pFeature.get();
						std::string csValue =pFeature->GetValue(featID).GetasString();
						ipDeleteIndexNode->SetValue(csValue.c_str());
					}

				}
			}

		}

		ipIncremenalFile->Save();
	}
	catch(std::exception&)
	{
		return ;
	}
	
}
void CShapefileWorkspace::IncrementalImport(std::string incrementalFile)
{
	SYSTEM::CXMLConfiguration::Initialize();
	try
	{
		if(ipIncremenalFile == NULL)
			ipIncremenalFile = new SYSTEM::CXMLConfiguration;
		ipIncremenalFile->Open(incrementalFile);

		if(ipIncremenalFile->GetName() != node_Incremental)
			return;
	
		IFeatureClassPtr ipFeatureCls = m_FeatureClass;//this->OpenFeatureClass(m_FullName.c_str());
		
		//要素类型
		long shapeType = ipFeatureCls->ShapeType();
		std::string strFeatureType;
		if( shapeType == GEOS_POINT || shapeType == GEOS_MULTIPOINT )
		{
			strFeatureType = node_PointFeature;
		}
		else if( shapeType == GEOS_LINESTRING || shapeType == GEOS_MULTILINESTRING )
		{
			strFeatureType = node_LineFeature;
		
		}
		else if( shapeType == GEOS_POLYGON || shapeType == GEOS_MULTIPOLYGON )
		{
			strFeatureType = node_PolygonFeature;
		}


		for (int i = 0;i< ipIncremenalFile->GetChildCount();i++)
		{
			SYSTEM::IConfigItemPtr ipFeatureTypeNode = ipIncremenalFile->GetChilds(i);
			if(ipFeatureTypeNode->GetName()!=strFeatureType)
				continue;

			std::string basename =m_FullName.substr(0,m_FullName.find_last_of('.'));
			basename=basename.substr(basename.find_last_of('\\')+1,basename.size()-basename.find_last_of('\\')-1);

			SYSTEM::IConfigItemPtr pNameItem = ipFeatureTypeNode->GetChildByName(basename.c_str());
			if( pNameItem == NULL )
				continue;

			//具体要素处理节点
			for (int j = 0;j< pNameItem->GetChildCount();j++)
			{
				SYSTEM::IConfigItemPtr pItem = pNameItem->GetChilds(j);
				std::string strNodename = pItem->GetName();
				if(strNodename == node_FlagAdd)
				{
					CFeaturePtr pFeature = ipFeatureCls->CreateFeature();
				
					//解析坐标
					std::vector<std::string> vecCoord;
					const std::string spCoord = " ";
					std::vector<std::string> vecXY;
					const std::string spXY = ",";
					SYSTEM::IConfigItemPtr   ipCoordNode= pNameItem->GetChildByName(node_coordinate.c_str());
					
					const char* itemVal = ipCoordNode->GetValue();
					if(itemVal == NULL)
						continue;
					std::string strCoordinate = itemVal;

					vecCoord= SYSTEM::split(strCoordinate,spCoord);


					GEOMETRY::geom::Geometry* m_pGeometry = NULL;
					switch(shapeType)
					{
						//点
					case GEOMETRY::geom::GEOS_POINT:
						m_pGeometry=(Geometry*)GeometryFactory::getDefaultInstance()->createPoint();
						for (int k = 0;k< vecCoord.size();k++)
						{
							vecXY= SYSTEM::split(vecCoord[k],spXY);

							GEOMETRY::geom::Coordinate coord;
							coord.x = atof(vecXY[0].c_str());
							coord.y = atof(vecXY[1].c_str());
							m_pGeometry->AddPoint(coord);

						}
						break;
						//线
					case GEOMETRY::geom::GEOS_LINESTRING:

						m_pGeometry =(Geometry*) GeometryFactory::getDefaultInstance()->createLineString();
						for (int k = 0;k< vecCoord.size();k++)
						{
							vecXY= SYSTEM::split(vecCoord[k],spXY);

							GEOMETRY::geom::Coordinate coord;
							coord.x = atof(vecXY[0].c_str());
							coord.y = atof(vecXY[1].c_str());
							m_pGeometry->AddPoint(coord);
							
						}

						break;
						//线圈
					case GEOMETRY::geom::GEOS_LINEARRING:

						m_pGeometry =(Geometry*) GeometryFactory::getDefaultInstance()->createLinearRing();
						break;

						//多线
					case GEOMETRY::geom::GEOS_MULTILINESTRING:
						{
							m_pGeometry = (Geometry*)GeometryFactory::getDefaultInstance()->createMultiLineString();

							Geometry *pg =(Geometry*) GeometryFactory::getDefaultInstance()->createLineString();
							for (int k = 0;k< vecCoord.size();k++)
							{
								vecXY= SYSTEM::split(vecCoord[k],spXY);

								GEOMETRY::geom::Coordinate coord;
								coord.x = atof(vecXY[0].c_str());
								coord.y = atof(vecXY[1].c_str());
								//m_pGeometry->AddPoint(coord);
								pg->AddPoint(coord);
							}

							((MultiLineString*)m_pGeometry)->AddGeometry(pg);
							break;
						}


						//多边形
					case GEOMETRY::geom::GEOS_POLYGON:
						{
							m_pGeometry =(Geometry*) GeometryFactory::getDefaultInstance()->createPolygon();
							//多边形比较特殊,要加入两个点
							GEOMETRY::geom::Geometry *pg =((GEOMETRY::geom::Polygon*)m_pGeometry)->GetGeometry(0);

							for (int k = 0;k< vecCoord.size();k++)
							{
								vecXY= SYSTEM::split(vecCoord[k],spXY);

								GEOMETRY::geom::Coordinate coord;
								coord.x = atof(vecXY[0].c_str());
								coord.y = atof(vecXY[1].c_str());
								//((GEOMETRY::geom::Polygon*)m_pGeometry)->AddPoint(coord);
								if(pg->PointCount()==0)
									pg->AddPoint(coord);
								else if(pg->PointCount()==1)
									pg->AddPoint(coord);
								else
									pg->InsertPoint(pg->PointCount()-1,coord);

							}

							break;
						}


						//多点
					case GEOMETRY::geom::GEOS_MULTIPOINT:

						m_pGeometry = (Geometry*)GeometryFactory::getDefaultInstance()->createMultiPoint();
						for (int k = 0;k< vecCoord.size();k++)
						{
							vecXY= SYSTEM::split(vecCoord[k],spXY);

							GEOMETRY::geom::Coordinate coord;
							coord.x = atof(vecXY[0].c_str());
							coord.y = atof(vecXY[1].c_str());
							m_pGeometry->AddPoint(coord);

						}
						break;

						//多多边形
					case GEOMETRY::geom::GEOS_MULTIPOLYGON:

						m_pGeometry =(Geometry*) GeometryFactory::getDefaultInstance()->createMultiPolygon();
						break;

					default:
						m_pGeometry =NULL;
						break;

					}

					pFeature->SetShape(m_pGeometry->clone());

					//各个字段值
					for(int j = 0;j<ipFeatureCls->FieldCount();j++)
					{	
						//得到字段名
						std::string fieldName = ipFeatureCls->GetField(j+1)->GetName();
						
						SYSTEM::IConfigItemPtr   ipFeildNode= pNameItem->GetChildByName(fieldName.c_str());
						if(ipFeildNode == NULL)
							continue;
						//得到字段值
						const char* itemVal = ipFeildNode->GetValue();
						if(itemVal == NULL)
							continue;
						std::string csValue = itemVal;

						long lFieldtype =ipFeatureCls->GetField(j+1)->GetType();

						switch(lFieldtype)
						{

						case Geodatabase::FTYPE_STRING:    //字符型
							{
								pFeature->GetValue(j+1).SetString((const char*)(csValue.c_str()));

							}
							break;
						case Geodatabase::FTYPE_DATE:    //日期型
							{

							}
							break;
						case Geodatabase::FTYPE_DOUBLE:
						case Geodatabase::FTYPE_FLOAT:    //浮点型
							{
								pFeature->GetValue(j+1).m_Var.dVal =atof(csValue.c_str());

							}
							break;
						case Geodatabase::FTYPE_BOOL:    //逻辑型
							{

							}
							break;
						case Geodatabase::FTYPE_LONG:    //整型
							{
								pFeature->GetValue(j+1).m_Var.iVal =atoi(csValue.c_str());

							}
							break;

						default:
							continue;
							break;
						}

					}

					//提交feature
					ipFeatureCls->AddFeature(pFeature.get());
				}
				else if (strNodename == node_FlagDelete)
				{

				}
				else if (strNodename == node_FlagModify)
				{

				}
				else if (strNodename == node_FlagAttribute)
				{

				}	
				
				
			}
		}


		

		
	}
	catch(std::exception&)
	{
		return;
	}

}

