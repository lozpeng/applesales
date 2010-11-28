//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.6
// ������  CSelctionSetʵ����ISelctionSet�Ľӿ�
//////////////////////////////////////////////////////////////////////

#ifndef  _CSELECTIONSET_H_
#define  _CSELECTIONSET_H_

#include "ISelectionSet.h"
#include <string>
#include <map>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
namespace Geodatabase
{

/********************************************************************************
* CSelctionSetʵ����ISelctionSet�Ľӿڣ����ķ�ʽ��ͨ���洢ѡ���Ҫ�ص�ID,ͨ��ID
* ö��Ҫ��
*********************************************************************************/
class GEODATABASE_DLL CSelctionSet :public ISelctionSet
{
public:
	CSelctionSet(ITable *pTable);
	virtual ~CSelctionSet();

public:

	//ѡ��Ҫ�ص���Ŀ
	virtual long Count() const;

	//���һ��Ҫ�ص�ѡ����
	virtual void Add(long id);

	//������һ��ѡ�񼯺ϲ�
	virtual void Combine(ISelctionSet* pSelection,SelSetOperation operatetype);

	//�õ���һ��Ԫ��,ͬʱָ��������
	virtual long NextID() ;


	//��������ָ�뵽ѡ�񼯿�ʼ��λ��
	virtual void ResetIndex();

	//ָ���Ƿ��Ѿ�������λ��
	bool IsEOF() const;


public:
	//��־λ
	boost::dynamic_bitset<>  m_flags;	

	long m_curPos;
};


typedef  SYSTEM::CSmartPtr<CSelctionSet> CSelctionSetPtr;



}


#endif