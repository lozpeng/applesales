#include "stdafx.h"
#include "SelectionSet.h"
#include "ITable.h"

namespace Geodatabase{


CSelctionSet::CSelctionSet(ITable *pTable) 
	:ISelctionSet(pTable)
{
	m_curPos =-1;
}

CSelctionSet::~CSelctionSet()
{
}

//选中的要素的数目
long CSelctionSet::Count() const
{
	return long(m_flags.count());
}

void CSelctionSet::Add(long id)
{
	if(id>0 && id<=m_flags.size())
	{
		m_flags[id-1] =true;
	}
	else if(id>m_flags.size())
	{
		//如果这个id超出了掩码位的长度，则重新设置掩码位长度
		m_flags.resize(id*2);
		m_flags[id-1] =true;
	}
}

long CSelctionSet::NextID()
{
	size_t index =0;
	if(m_curPos ==-1)
	{
		index =m_flags.find_first();
	}
	else
	{
		index =m_flags.find_next(m_curPos);
	}
	//如果没找到
	if(index ==boost::dynamic_bitset<>::npos)
	{
		return -1;
	}
	m_curPos =index;
	return (index+1);
}


bool CSelctionSet::IsEOF() const
{
	if(m_curPos>= (long)(m_flags.size()-1))
	{
		return true;
	}

	//如果之后没有选中的位，则也是到达了最后
	size_t index =0;
	if(m_curPos ==-1)
	{
		index =m_flags.find_first();
	}
	else
	{
		index =m_flags.find_next(m_curPos);
	}
	//如果没找到
	if(index ==boost::dynamic_bitset<>::npos)
	{
		return true;
	}

	return false;
}

void CSelctionSet::ResetIndex()
{
	m_curPos =-1;
}

void CSelctionSet::Combine(Geodatabase::ISelctionSet *pSelection, Geodatabase::SelSetOperation operatetype)
{
	if(!pSelection)
	{
		return;
	}
	long index;
	switch(operatetype)
	{
	case SetUnion:
		{
			pSelection->ResetIndex();
			while(!pSelection->IsEOF())
			{
				index =pSelection->NextID();
				if(index<=0)
				{
					continue;
				}
				else if(index<=m_flags.size())
				{
					m_flags[index-1] =true;
				}
				else
				{
					//如果这个id超出了掩码位的长度，则重新设置掩码位长度
					m_flags.resize(index);
					m_flags[index-1] =true;
				}
			}
			break;
		}
	case SetIntersect:
		{
			pSelection->ResetIndex();
			std::vector<long> tempids;
			while(!pSelection->IsEOF())
			{
				index =pSelection->NextID();
				if(index>0 && index<=m_flags.size())
				{
					if(m_flags[index-1])
					{
						tempids.push_back(index-1);
					}
				}

			}
			m_flags.reset();
			for(size_t i=0;i<tempids.size();i++)
			{
				m_flags[tempids[i]] =true;
			}
			break;
		}
	case SetSubtract:
		{
			pSelection->ResetIndex();

			while(!pSelection->IsEOF())
			{
				index =pSelection->NextID();
				if(index>0 && index<=m_flags.size())
				{
					if(m_flags[index-1])
					{
						m_flags[index-1] =false;
					}
				}

			}
			break;
		}
	case SetXOR:
		{
			pSelection->ResetIndex();
			while(!pSelection->IsEOF())
			{
				index =pSelection->NextID();
				if(index<=0)
				{
					continue;
				}
				else if(index<=m_flags.size())
				{
					if(m_flags[index-1])
					{
						m_flags[index-1] =false;
					}
					else
					{
						m_flags[index-1] =true;
					}
				}
				else
				{
					//如果这个id超出了掩码位的长度，则重新设置掩码位长度
					m_flags.resize(index);
					m_flags[index-1] =true;
				}
			}
			break;
		}
	}
}

} //namespace Geodatabase