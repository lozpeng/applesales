#include "stdafx.h"
#include "FeatureEditCache.h"
#include "Feature.h"
#include <Geometry/geom/Envelope.h>
#include <Geometry/geom/Geometry.h>
#include <set>

namespace Geodatabase{

CFeatureEditCache::CFeatureEditCache(Geodatabase::IFeatureClass *pFeatureClass)
{
	m_pFeatureClass =pFeatureClass;

	m_lCursor =-1;

	m_lnextRecId =0;

	m_lvalidNum =0;

	//m_lnextRecId =pFeatureClass->FeatureCount();
}

CFeatureEditCache::~CFeatureEditCache()
{
    for(size_t i=0;i<m_operationStack.size();i++)
	{
		delete m_operationStack[i];
		m_operationStack[i] =NULL;
	}

	m_lCursor =-1;
}

long CFeatureEditCache::GetTotalNum() const
{
	return m_lnextRecId-1;
}

long CFeatureEditCache::GetValidNum() const
{
	return m_lvalidNum;
}

bool CFeatureEditCache::CanUndo() const
{
	return (m_lCursor>=0);
}

bool CFeatureEditCache::CanRedo() const
{
	long num =m_operationStack.size();

	return (num>0 && m_lCursor<(num-1));
}

void CFeatureEditCache::Undo()
{
	if(CanUndo())
	{
		m_lCursor--;
		switch(m_operationStack[m_lCursor+1]->EditType)
		{
		case OP_ADD:
            m_lvalidNum--;
			break;
		case OP_DELETE:
			m_lvalidNum++;
			break;
		default:
			break;
		}
	}
    

}

void CFeatureEditCache::Redo()
{
	if(CanRedo())
	{
		m_lCursor++;

		switch(m_operationStack[m_lCursor]->EditType)
		{
		case OP_ADD:
			m_lvalidNum++;
			break;
		case OP_DELETE:
			m_lvalidNum--;
			break;
		default:
			break;
		}


	}
}

//���һ��Ҫ��
void CFeatureEditCache::AppendFeature(Geodatabase::CFeaturePtr pFeature)
{
	//����Ҫ�ѵ�ǰָ��֮��Ĳ������
    RemoveRedundant();

	FEditStep *pnewStep =new FEditStep();

	pnewStep->Fid = m_lnextRecId;

	pnewStep->EditType =OP_ADD;

	pnewStep->pFeature =pFeature;

	//���༭������ӵ���ջ��
	m_operationStack.push_back(pnewStep);

	m_lnextRecId++;

	m_lvalidNum++;

	m_lCursor++;
}

//ɾ��һ��Ҫ��
void CFeatureEditCache::DeleteFeature(long Fid)
{
	//�ж����Ҫ�ص�id�Ƿ���Ч
	if(Fid<=0 || Fid>(m_lnextRecId-1))
	{
		return;
	}

	//����Ҫ�ѵ�ǰָ��֮��Ĳ������
	RemoveRedundant();
    
	FEditStep *pnewStep =new FEditStep();

	pnewStep->Fid = Fid;

	pnewStep->EditType =OP_DELETE;

	pnewStep->pFeature  = this->m_pFeatureClass->GetFeature(Fid);
	//���༭������ӵ���ջ��
	m_operationStack.push_back(pnewStep);

	m_lvalidNum--;

	m_lCursor++;

}

//����һ��Ҫ��
void CFeatureEditCache::UpdateFeature(Geodatabase::CFeaturePtr pFeature)
{
	long Fid =pFeature->GetId();
    
	//�ж����Ҫ�ص�id�Ƿ���Ч
	if(Fid<=0 || Fid>(m_lnextRecId-1))
	{
		return;
	}

	//����Ҫ�ѵ�ǰָ��֮��Ĳ������
	RemoveRedundant();

	FEditStep *pnewStep =new FEditStep();

	pnewStep->Fid = Fid;

	pnewStep->EditType =OP_UPDATE;

    pnewStep->pFeature =pFeature;
	//���༭������ӵ���ջ��
	m_operationStack.push_back(pnewStep);

	m_lCursor++;

}

void  CFeatureEditCache::RemoveRedundant()
{
	if(m_lCursor!=(m_operationStack.size()-1))
	{
		long lstart =(m_lCursor>=-1) ?(m_lCursor+1) :0;

		m_operationStack.erase(m_operationStack.begin()+lstart,m_operationStack.end());
	}
}

bool CFeatureEditCache::IsFeatureDelete(long Fid) const
{
    bool bdeleted =false;
	for(long i=m_lCursor;i>=0;i--)
	{
		if(m_operationStack[i]==NULL)
		{
			continue;
		}
        if(m_operationStack[i]->Fid ==Fid)
		{
			if(m_operationStack[i]->EditType==OP_DELETE)
			{
				bdeleted =true;
				break;
				
			}
		}

	}

	return bdeleted;
}

bool CFeatureEditCache::IsFeatureExist(long Fid) const
{
	bool bexist =false;

	EditOperationType otype;
	for(long i=m_lCursor;i>=0;i--)
	{
		if(m_operationStack[i]==NULL)
		{
			continue;
		}
		if(m_operationStack[i]->Fid ==Fid)
		{
			otype =m_operationStack[i]->EditType;

			if(otype==OP_DELETE)
			{
				bexist =false;
				break;

			}
			else
			{
				bexist =true;
				break;
			}

		}

	}

	return bexist;
}

CFeaturePtr CFeatureEditCache::GetFeature(long Fid)
{
	EditOperationType otype;
	for(long i=m_lCursor;i>=0;i--)
	{

		if(m_operationStack[i]==NULL)
		{
			continue;
		}
		if(m_operationStack[i]->Fid ==Fid)
		{
			otype =m_operationStack[i]->EditType;

			//�����ɾ��
			if(otype==OP_DELETE)
			{
				
                return CFeaturePtr();
			}
			else
			{
				
				CFeature *pFeature =new CFeature(*m_operationStack[i]->pFeature);

				//pFeature->SetShape(m_operationStack[i]->pFeature->GetShapeClone());

				return CFeaturePtr(pFeature);
			}

		}

	}

	return CFeaturePtr();
}

//�������ж�ջ,���ڽ��༭���д�أ������ǽ�û�õĲ���ɾ�����ó�NULL
void CFeatureEditCache::Arrange()
{ 
	//���ع���֮��ļ�¼ɾ��
	RemoveRedundant();

	if(m_lCursor<0)
	{
		return;
	}

	long lcursor =m_operationStack.size()-1;

	long i=0;

	FEditStep *pStep =NULL;

	EditOperationType otype,otype1;

	long fid;

	while(lcursor>=0)
	{

		pStep =m_operationStack[lcursor];
		if(pStep==NULL)
		{
			lcursor--;
			continue;
		}

		otype =pStep->EditType;

		fid =pStep->Fid;

		switch(otype)
		{
			//����ü�¼����ӣ���֮ǰ�й����ļ�¼ɾ��
		case OP_ADD:
			{
				for(i=lcursor-1;i>=0;i--)
				{
					if(m_operationStack[i]==NULL)
					{
						continue;
					}
					if(m_operationStack[i]->Fid ==fid)
					{
						delete m_operationStack[i];
						m_operationStack[i] =NULL;
					}

				}
			}

			break;
		case OP_DELETE: 
			//����ü�¼��ɾ�������ж������¼ӵļ�¼����ԭ�еļ�¼
			{
				for(i=lcursor-1;i>=0;i--)
				{
					if(m_operationStack[i]==NULL)
					{
						continue;
					}
					if(m_operationStack[i]->Fid ==fid)
					{
						otype1 =m_operationStack[i]->EditType;

						if(otype1==OP_ADD)
						{
							delete m_operationStack[i];
							m_operationStack[i] =NULL;

							delete m_operationStack[lcursor];
							m_operationStack[lcursor] =NULL;

							goto NEXT;

						}
						else
						{
							delete m_operationStack[i];
							m_operationStack[i] =NULL;
						}
					}

				}
			}
			break;
		case OP_UPDATE:
			//����ü�¼�Ǹ��£����ж������¼ӵĻ���ԭ�е�
			{
				for(i=lcursor-1;i>=0;i--)
				{
					if(m_operationStack[i]==NULL)
					{
						continue;
					}
					if(m_operationStack[i]->Fid ==fid)
					{
						otype1 =m_operationStack[i]->EditType;

						if(otype1==OP_ADD)
						{
							delete m_operationStack[i];
							m_operationStack[i] =NULL;

							//����ü�¼�������ģ������Ĳ�����־��Ϊ�¼�,�����������ڸ��µ�λ�ý���
							pStep->EditType =OP_ADD;
							m_operationStack[i] =pStep;

							m_operationStack[lcursor] =NULL;

							goto NEXT;

						}
						else
						{
							delete m_operationStack[i];
							m_operationStack[i] =NULL;
						}
					}

				}
			}
			break;
		}

NEXT:
		lcursor--;
	}


}

//�ڻ�����ʹ�þ��β�ѯ
void CFeatureEditCache::QueryByExtent(GEOMETRY::geom::Envelope *pEnvelop,boost::dynamic_bitset<> &flags)
{
	using std::set;
	using namespace GEOMETRY::geom;
	//�Ѿ��������Ҫ��id
	std::set<long> ProcessList;

	long fid;
	Envelope  extent;
	Geometry *pGeometry;
	for(long i=m_lCursor;i>=0;i--)
	{
		fid =m_operationStack[i]->Fid;
		//���Ȳ鿴���Ҫ���Ƿ��Ѿ���������
		if(ProcessList.find(fid)!=ProcessList.end())
		{
			continue;
		}

		//���Ҫ�ر�ɾ����
		if(m_operationStack[i]->EditType==OP_DELETE)
		{
			flags[fid-1] =false;


		}
		else
		{
			pGeometry =m_operationStack[i]->pFeature->GetShape();
			if(!pGeometry)
			{
				continue;
			}
			extent =*(pGeometry->getEnvelopeInternal());
			//���ͼ�κ;��β��뽻
			if(!extent.intersects(pEnvelop))
			{
				flags[fid-1] =false;
			}
			else
			{
				flags[fid-1] =true;
			}

		}
		ProcessList.insert(fid);


	}

}

void CFeatureEditCache::Query(Geodatabase::CSimpleQuery *query, boost::dynamic_bitset<> &flags)
{
	CSpatialQuery *pspatialQuery =dynamic_cast<CSpatialQuery*>(query);
	if(pspatialQuery)
	{
		return SpatialQuery(pspatialQuery,flags);
	}
	else
	{
		return SimpleQuery(query,flags);
	}
}

void CFeatureEditCache::SimpleQuery(CSimpleQuery *query,boost::dynamic_bitset<> &flags)
{

}

void CFeatureEditCache::SpatialQuery(CSpatialQuery *query,boost::dynamic_bitset<> &flags)
{
	using namespace GEOMETRY::geom;

	if(query->GetGeometry()==NULL)
	{
		SimpleQuery(query,flags);
		return;
	}


	bool bsql =false;
	//���Ƚ���һ���ֶε�sql����ѯ
	std::string strWhere =query->GetWhereString();
	if(!strWhere.empty())
	{
		bsql =true;
	}

	long sprel =query->GetSpatialRel();
	Geometry *pQueryGeometry =query->GetGeometry();
	Geometry *pGeometry =NULL;

	//�Ѿ��������Ҫ��id
	std::set<long> ProcessList;
	long fid;
	bool bret;

	//����ͼ��ִ�пռ����������
	enum SPOperType
	{
		SOT_None,
		SOT_Intersect, //�ཻ
		SOT_Intersected,//
		SOT_Cross, 
		SOT_Crossed,
		SOT_Contain,  //����
		SOT_Contained

	};
	SPOperType optype;
	long queryShapetype,ShapeType;
	queryShapetype =pQueryGeometry->getGeometryTypeId();
	ShapeType =m_pFeatureClass->ShapeType();
	//�ռ��ཻ�����
	if(sprel ==SpatialRelIntersects)
	{


		for(long i=m_lCursor;i>=0;i--)
		{
			fid =m_operationStack[i]->Fid;
			//���Ȳ鿴���Ҫ���Ƿ��Ѿ���������
			if(ProcessList.find(fid)!=ProcessList.end())
			{
				continue;
			}

			//���Ҫ�ر�ɾ����
			if(m_operationStack[i]->EditType==OP_DELETE)
			{
				flags[fid-1] =false;


			}
			else
			{
				/*try
				{*/
				pGeometry =m_operationStack[i]->pFeature->GetShape();
				if(!pGeometry)
				{
					continue;
				}

				bret =pGeometry->intersects(pQueryGeometry);
				//�������ͼ���ཻ
				if(bret)
				{
					flags[fid-1] =true;
				}
				else
				{
					flags[fid-1] =false;
				}
				/*}*/
				/*catch (...)
				{
				continue;
				}*/


			}
			ProcessList.insert(fid);


		}

	}


}

} //namespace Geodatabase