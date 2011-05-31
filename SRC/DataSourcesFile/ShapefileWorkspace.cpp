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
	//����༭����
	ClearEditCache();
}

////CShapefileWorkspaceû��ʸ�����ݼ�
//long CShapefileWorkspace::DatasetCount(Geodatabase::GEODATATYPE type) const
//{
//	return 0;
//}

//��ʵ�ִ����ݼ�
IFeatureDatasetPtr CShapefileWorkspace::OpenFeatureDataset(const char *name)
{
	return NULL;
}


IFeatureClassPtr CShapefileWorkspace::OpenFeatureClass(const char *name)
{
	//�����жϸ��ļ��Ƿ�����������ռ��
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
*  ����Ϊ����������صĲ���
*
*******************************************************************************************************/

IFeatureClassPtr CShapefileWorkspace::CreateFeatureClass(const char *name, const Geodatabase::FeatureClassDef &FDef)
{
	std::string filename =name;
	//�����ļ�����
	std::string basename =filename.substr(0,filename.rfind("."));

	/* -------------------------------------------------------------------- */
	/*     ����ͼ��shp�ļ�                                                  */
	/* -------------------------------------------------------------------- */
	int  nShapeType;

	switch(FDef.lshptype)
	{
	case GEOMETRY::geom::GEOS_POINT:
		{
			//�ж��Ƿ����M��Z��Ϣ
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
			//�ж��Ƿ����M��Z��Ϣ
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
			//�ж��Ƿ����M��Z��Ϣ
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
			//�ж��Ƿ����M��Z��Ϣ
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
	/*     ����DBF�ļ�                                                      */
	/* -------------------------------------------------------------------- */
    
	std::string dbfname =basename +".dbf";
    
	DBFHandle hDBF = DBFCreate( dbfname.c_str());

	if(hDBF ==NULL)
	{
		return NULL;
	}

	Geodatabase::CFieldPtr pField;
	//����DBF���ֶνṹ
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
	/*     ����ͶӰPRJ�ļ�                                                  */
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
*  ����Ϊ�༭��صĲ���
*
*******************************************************************************************************/

void CShapefileWorkspace::StartEdit()
{
	if(!m_bEditing)
	{

		m_bEditing =true;
		ClearEditCache();

		//����������Ϣ
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
		//����������Ϣ
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
	//���ع���֮��Ķ�ջ���
	RemoveRedundant();

}

void CShapefileWorkspace::StopEditOperation()
{
	//����εĲ���ѹ���ջ
	if(!m_curOperation.empty())
	{
		m_EditStack.push_back(m_curOperation);

		m_lcursor++;
	}

	m_bStartOp =false;
}

//������α༭����
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
	//���ε���ÿ�������໺��Ļ��˷���
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
	//���ε���ÿ�������໺��Ļ��˷���
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
*  ����Ϊ���ڲ���ʹ�õĲ����༭����Ľӿ�
*
*******************************************************************************************************/
//����༭����
void CShapefileWorkspace::ClearEditCache()
{
	EditCacheMap::iterator iter;

	for(iter=m_EditCacheMap.begin();iter!=m_EditCacheMap.end();iter++)
	{
		delete iter->second;

		iter->second =NULL;
	}
	m_EditCacheMap.clear();

	//�ع���ջ���
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

	//����һ���µı༭����
	CFeatureEditCache *pEditCache =new CFeatureEditCache(pFeatureClass);

	//������ЧҪ�ص���Ŀ
	pEditCache->m_lnextRecId =pFeatureClass->FeatureCount()+1;

	pEditCache->m_lvalidNum =pFeatureClass->FeatureCount();

	m_EditCacheMap[filename] =pEditCache;

}

//����һ��������Ļ���
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
	//������Ǵ��ڱ༭״̬���򷵻�
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

	//���µ�id����Feature
	pFeature->SetId(pCache->GetTotalNum()+1);

	pCache->AppendFeature(pFeature);
	if(m_bStartOp)
	{
		m_curOperation.push_back(name);
	}


}
void CShapefileWorkspace::UpdateFeature(Geodatabase::IFeatureClass *pFeatureClass,CFeaturePtr pFeature)
{
	//������Ǵ��ڱ༭״̬���򷵻�
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
	//������Ǵ��ڱ༭״̬���򷵻�
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
//�������ջ�ж���ļ�¼
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

	//���滺���б༭��Ҫ��
	EditCacheMap::iterator iter;
	for(iter =m_EditCacheMap.begin();iter!=m_EditCacheMap.end();iter++)
	{
		
		CFeatureEditCache *pCache =iter->second;

		CShapefileFeatureClass *pFeatureClass =(CShapefileFeatureClass*)pCache->m_pFeatureClass;

		//���ԭ�����ļ���ֻ����ʽ�������°��ն�д��ʽ��
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
				des+="�ļ��޷��Զ�д��ʽ�򿪣���ȷ���ļ�û�б���������ռ��";
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
				des+="�ļ��޷��Զ�д��ʽ�򿪣���ȷ���ļ�û�б���������ռ��";
				
				continue;
			}
            
			pFeatureClass->m_dbfHandle =hdbf;
			pFeatureClass->m_shpHandle =hshp;

			pFeatureClass->m_Readonly =false;

		}

		//���л������Ҫ�ؼ�¼
		pCache->Arrange();

		//�жϻ�����ļ�¼�ǲ���ֻ���޸�Ҫ��
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

		//���ֻ���޸�Ҫ�أ�����Ҫ�������������ļ���ֻ����ԭ�����ļ����޸�
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
			//�������ӣ�ɾ����Ҫ�أ���Ҫ���½���һ���ļ�����ԭ����Ҫ�غ���Ҫ�ض�д�룬���ԭ���ļ�ɾ��
			DBFHandle hNewDBF = NULL;

			std::string filename  =pFeatureClass->Getname();
			std::string basename =filename.substr(0,filename.find_last_of('.'));
			basename=basename.substr(basename.find_last_of('\\')+1,basename.size()-basename.find_last_of('\\')-1);


			std::string dbfname =m_pathname+"\\";
			dbfname+=basename;
			dbfname+="_packed.dbf";

			//����һ���յ���ʱdbf�ļ�
			hNewDBF = DBFCloneEmpty( pFeatureClass->m_dbfHandle, dbfname.c_str());
			if( hNewDBF == NULL )
			{
				//EXCEPT("�޷�������ʱ�ļ�");
				continue;
			}

			/* -------------------------------------------------------------------- */
			/*     ����һ��shpfile��ʱ�ļ�                                          */
			/* -------------------------------------------------------------------- */
			SHPHandle hNewSHP = NULL;

			std::string shpname =m_pathname+"\\";
			shpname+=basename;
			shpname+="_packed.shp";

			hNewSHP = SHPCreate( shpname.c_str(),pFeatureClass->m_shpHandle->nShapeType );
			if( hNewSHP == NULL )
			{
				//EXCEPT("�޷�������ʱ�ļ�");
				continue;
			}


			/* -------------------------------------------------------------------- */
			/*    ���Ƚ�ԭ�еļ�¼��������ʱ�ļ���                                  */
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

				//�жϸ�Ҫ���Ƿ�ɾ�������޸�
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
					
                    //д��ͼ��
					hObject = SHPReadObject( pFeatureClass->m_shpHandle, iShape );
					if(!hObject)
					{
						continue;
					}
					SHPWriteObject( hNewSHP, -1, hObject );

					SHPDestroyObject( hObject );

					//д������
					pTuple = (void *) DBFReadTuple( pFeatureClass->m_dbfHandle, iShape );
					if( pTuple == NULL )
					{
						continue;
					}
					DBFWriteTuple( hNewDBF, iDestShape++, pTuple );
					

				}
				
			}

		    //д��༭����������ӵļ�¼
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
			/*     ɾ��ԭ�����ļ�������ʱ�ļ�������                                 */
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
                //EXCEPT("�޷�ɾ��ԭ���ļ�����ȷ���ļ�����ֻ��������û�б����������");
			}
			if(_unlink(oldshp.c_str())!=0)
			{
				//EXCEPT("�޷�ɾ��ԭ���ļ�����ȷ���ļ�����ֻ��������û�б����������");
			}
			if(_unlink(oldshx.c_str())!=0)
			{
				//EXCEPT("�޷�ɾ��ԭ���ļ�����ȷ���ļ�����ֻ��������û�б����������");
			}

			rename(dbfname.c_str(),olddbf.c_str());

			rename(shpname.c_str(),oldshp.c_str());

			rename(shxname.c_str(),oldshx.c_str());
            
			

			/* -------------------------------------------------------------------- */
			/*      ���µ�shp�ļ�                                                 */
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
		//��ͼ��ת��ΪShp�ڲ���ʽ
        SHPObject *shpobj =Geometry2Shp(pg,hshp->nShapeType);
		if(!shpobj)
		{
			return false;
		}

		//д��ͼ������
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
		//д����������
		for(long iField=0;iField<pFeature->FieldCount();iField++)
		{
			type =pFeature->GetValue(iField+1).vtype;

			bool bFlagNull = false;
			//�ж�����ֵ�Ƿ��ֵ
			if(type ==Geodatabase::FieldValue::VT_EMPTY || type==Geodatabase::FieldValue::VT_NULL)
			{
				bFlagNull = true;
				//continue; //hhzhao ע�͵�����Ȼdbf���¼��shp��¼��һ��
			}

			if ( hdbf->pachFieldType[iField] == 'L' )
			{
				//�߼���

			}
			else if( hdbf->pachFieldType[iField] == 'N' 
				|| hdbf->pachFieldType[iField] == 'F' )
			{
				if( hdbf->panFieldDecimals[iField] > 0 
					|| hdbf->panFieldSize[iField] > 10 )
				{
					//double��
					DBFWriteDoubleAttribute(hdbf,Fid,iField,pFeature->GetValue(iField+1).m_Var.dVal);
				}
				else
				{
					//����
					DBFWriteIntegerAttribute(hdbf,Fid,iField,pFeature->GetValue(iField+1).m_Var.iVal);
				}
			}
			else
			{
				//�ַ���
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

			//����ε���Ŀ
			long lPolygons =((GEOMETRY::geom::MultiPolygon*)pGeometry)->GeometryCount();

			//�߻�������Ŀ
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

//��������������
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
		
		//����ʱ��ڵ�
		SYSTEM::IConfigItemPtr ipCurTimeNode = ipIncremenalFile->AddChildNode(node_CaptureTime.c_str());
		time_t t = time(0);    
		char szCurTime[64];    
		strftime( szCurTime, sizeof(szCurTime), "%Y-%m-%d %X",localtime(&t));    
		ipCurTimeNode->SetValue(szCurTime);

		FEditStep *pStep;
		CFeature *pFeature =NULL;
		char destBuf[1024];

		//���滺���б༭��Ҫ��
		EditCacheMap::iterator iter;
		for(iter =m_EditCacheMap.begin();iter!=m_EditCacheMap.end();iter++)
		{

			CFeatureEditCache *pCache =iter->second;

			CShapefileFeatureClass *pFeatureClass =(CShapefileFeatureClass*)pCache->m_pFeatureClass;
			//Ҫ������
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

			//Ҫ������  m_pathname

			std::string strFeatureClsName = pFeatureClass->Getname();
			std::string basename =strFeatureClsName.substr(0,strFeatureClsName.find_last_of('.'));
			basename=basename.substr(basename.find_last_of('\\')+1,basename.size()-basename.find_last_of('\\')-1);
			SYSTEM::IConfigItemPtr ipFeatureNameNode = ipFeatureTypeNode->GetChildByName(basename.c_str());
			if (ipFeatureNameNode == NULL)
			{
				strcpy(destBuf,basename.c_str());
				ipFeatureNameNode = ipFeatureTypeNode->AddChildNode(destBuf);
			}

			//ChangeType Add��Delete��Modify��Attribute
			//���л������Ҫ�ؼ�¼
			pCache->Arrange();

			//�жϻ�����ļ�¼�ǲ���ֻ���޸�Ҫ��
			
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
					
					//�����ֶ�ֵ
					for(int j = 0;j<pFeatureClass->FieldCount();j++)
					{	
						//�õ��ֶ���
						std::string fieldName = pFeatureClass->GetField(j+1)->GetName();
						SYSTEM::IConfigItemPtr   ipFeildNode= ipFlagAddNode->AddChildNode(fieldName.c_str());
						//�õ��ֶ�ֵ
						std::string csValue =pStep->pFeature->GetValue(j+1).GetasString().c_str();
						ipFeildNode->SetValue(csValue.c_str());
					}
					
					//����ֵ
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
				else if (pStep->EditType == OP_UPDATE) //��ʱ��Ϊupdate�ˣ�ͼ�к��������Զ��޸�
				{
					bool bGeoChanged = pFeatureClass->GetFeatureShape(pStep->Fid)->compareTo(pStep->pFeature->GetShape());
					

					SYSTEM::IConfigItemPtr ipFlagModifyNode  = ipFeatureNameNode->AddChildNode(node_FlagModify.c_str());
					
					//FeatID �ֶ�
					SYSTEM::IConfigItemPtr ipChangeIndexNode  = ipFlagModifyNode->AddChildNode(node_FeatID.c_str());
					int featID = pFeatureClass->FindField(node_FeatID.c_str());
					if(featID >0)
					{
						pFeature =pCache->m_operationStack[i]->pFeature.get();
						std::string csValue =pFeature->GetValue(featID).GetasString();
						ipChangeIndexNode->SetValue(csValue.c_str());
					}

					//����ֵ
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

					//�����ֶ�ֵ
					for(int j = 0;j<pFeatureClass->FieldCount();j++)
					{	
						//�õ��ֶ���
						std::string fieldName = pFeatureClass->GetField(j+1)->GetName();
						if(fieldName == node_FeatID)
							continue;
						SYSTEM::IConfigItemPtr   ipFeildNode= ipFlagAttriNode->AddChildNode(fieldName.c_str());
						//�õ��ֶ�ֵ
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

					//FeatID �ֶ�
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
		
		//Ҫ������
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

			//����Ҫ�ش���ڵ�
			for (int j = 0;j< pNameItem->GetChildCount();j++)
			{
				SYSTEM::IConfigItemPtr pItem = pNameItem->GetChilds(j);
				std::string strNodename = pItem->GetName();
				if(strNodename == node_FlagAdd)
				{
					CFeaturePtr pFeature = ipFeatureCls->CreateFeature();
				
					//��������
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
						//��
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
						//��
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
						//��Ȧ
					case GEOMETRY::geom::GEOS_LINEARRING:

						m_pGeometry =(Geometry*) GeometryFactory::getDefaultInstance()->createLinearRing();
						break;

						//����
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


						//�����
					case GEOMETRY::geom::GEOS_POLYGON:
						{
							m_pGeometry =(Geometry*) GeometryFactory::getDefaultInstance()->createPolygon();
							//����αȽ�����,Ҫ����������
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


						//���
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

						//������
					case GEOMETRY::geom::GEOS_MULTIPOLYGON:

						m_pGeometry =(Geometry*) GeometryFactory::getDefaultInstance()->createMultiPolygon();
						break;

					default:
						m_pGeometry =NULL;
						break;

					}

					pFeature->SetShape(m_pGeometry->clone());

					//�����ֶ�ֵ
					for(int j = 0;j<ipFeatureCls->FieldCount();j++)
					{	
						//�õ��ֶ���
						std::string fieldName = ipFeatureCls->GetField(j+1)->GetName();
						
						SYSTEM::IConfigItemPtr   ipFeildNode= pNameItem->GetChildByName(fieldName.c_str());
						if(ipFeildNode == NULL)
							continue;
						//�õ��ֶ�ֵ
						const char* itemVal = ipFeildNode->GetValue();
						if(itemVal == NULL)
							continue;
						std::string csValue = itemVal;

						long lFieldtype =ipFeatureCls->GetField(j+1)->GetType();

						switch(lFieldtype)
						{

						case Geodatabase::FTYPE_STRING:    //�ַ���
							{
								pFeature->GetValue(j+1).SetString((const char*)(csValue.c_str()));

							}
							break;
						case Geodatabase::FTYPE_DATE:    //������
							{

							}
							break;
						case Geodatabase::FTYPE_DOUBLE:
						case Geodatabase::FTYPE_FLOAT:    //������
							{
								pFeature->GetValue(j+1).m_Var.dVal =atof(csValue.c_str());

							}
							break;
						case Geodatabase::FTYPE_BOOL:    //�߼���
							{

							}
							break;
						case Geodatabase::FTYPE_LONG:    //����
							{
								pFeature->GetValue(j+1).m_Var.iVal =atoi(csValue.c_str());

							}
							break;

						default:
							continue;
							break;
						}

					}

					//�ύfeature
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

