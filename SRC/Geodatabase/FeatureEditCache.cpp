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

//添加一个要素
void CFeatureEditCache::AppendFeature(Geodatabase::CFeaturePtr pFeature)
{
	//首先要把当前指针之后的操作清除
    RemoveRedundant();

	FEditStep *pnewStep =new FEditStep();

	pnewStep->Fid = m_lnextRecId;

	pnewStep->EditType =OP_ADD;

	pnewStep->pFeature =pFeature;

	//将编辑操作添加到堆栈中
	m_operationStack.push_back(pnewStep);

	m_lnextRecId++;

	m_lvalidNum++;

	m_lCursor++;
}

//删除一个要素
void CFeatureEditCache::DeleteFeature(long Fid)
{
	//判断这个要素的id是否有效
	if(Fid<=0 || Fid>(m_lnextRecId-1))
	{
		return;
	}

	//首先要把当前指针之后的操作清除
	RemoveRedundant();
    
	FEditStep *pnewStep =new FEditStep();

	pnewStep->Fid = Fid;

	pnewStep->EditType =OP_DELETE;

	pnewStep->pFeature  = this->m_pFeatureClass->GetFeature(Fid);
	//将编辑操作添加到堆栈中
	m_operationStack.push_back(pnewStep);

	m_lvalidNum--;

	m_lCursor++;

}

//更新一个要素
void CFeatureEditCache::UpdateFeature(Geodatabase::CFeaturePtr pFeature)
{
	long Fid =pFeature->GetId();
    
	//判断这个要素的id是否有效
	if(Fid<=0 || Fid>(m_lnextRecId-1))
	{
		return;
	}

	//首先要把当前指针之后的操作清除
	RemoveRedundant();

	FEditStep *pnewStep =new FEditStep();

	pnewStep->Fid = Fid;

	pnewStep->EditType =OP_UPDATE;

    pnewStep->pFeature =pFeature;
	//将编辑操作添加到堆栈中
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

			//如果被删除
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

//重新排列堆栈,用于将编辑结果写回，做法是将没用的操作删除，置成NULL
void CFeatureEditCache::Arrange()
{ 
	//将回滚点之后的记录删除
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
			//如果该记录是添加，则将之前有关它的记录删除
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
			//如果该记录是删除，则判断它是新加的记录还是原有的记录
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
			//如果该记录是更新，则判断它是新加的还是原有的
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

							//如果该记录是新增的，则将它的操作标志改为新加,并将它与现在更新的位置交换
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

//在缓存中使用矩形查询
void CFeatureEditCache::QueryByExtent(GEOMETRY::geom::Envelope *pEnvelop,boost::dynamic_bitset<> &flags)
{
	using std::set;
	using namespace GEOMETRY::geom;
	//已经处理过的要素id
	std::set<long> ProcessList;

	long fid;
	Envelope  extent;
	Geometry *pGeometry;
	for(long i=m_lCursor;i>=0;i--)
	{
		fid =m_operationStack[i]->Fid;
		//首先查看这个要素是否已经被处理了
		if(ProcessList.find(fid)!=ProcessList.end())
		{
			continue;
		}

		//如果要素被删除了
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
			//如果图形和矩形不想交
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
	//首先进行一个字段的sql语句查询
	std::string strWhere =query->GetWhereString();
	if(!strWhere.empty())
	{
		bsql =true;
	}

	long sprel =query->GetSpatialRel();
	Geometry *pQueryGeometry =query->GetGeometry();
	Geometry *pGeometry =NULL;

	//已经处理过的要素id
	std::set<long> ProcessList;
	long fid;
	bool bret;

	//两个图形执行空间操作的类型
	enum SPOperType
	{
		SOT_None,
		SOT_Intersect, //相交
		SOT_Intersected,//
		SOT_Cross, 
		SOT_Crossed,
		SOT_Contain,  //包含
		SOT_Contained

	};
	SPOperType optype;
	long queryShapetype,ShapeType;
	queryShapetype =pQueryGeometry->getGeometryTypeId();
	ShapeType =m_pFeatureClass->ShapeType();
	//空间相交的情况
	if(sprel ==SpatialRelIntersects)
	{


		for(long i=m_lCursor;i>=0;i--)
		{
			fid =m_operationStack[i]->Fid;
			//首先查看这个要素是否已经被处理了
			if(ProcessList.find(fid)!=ProcessList.end())
			{
				continue;
			}

			//如果要素被删除了
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
				//如果两个图形相交
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