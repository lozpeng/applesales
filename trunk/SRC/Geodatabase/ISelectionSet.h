//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.6
// ������  ѡ�񼯵Ļ���
//////////////////////////////////////////////////////////////////////

#ifndef  _ISELECTIONSET_H_
#define  _ISELECTIONSET_H_

#include "IRow.h"
#include <string>
#include <map>

namespace Geodatabase
{


class ITable;

class GEODATABASE_DLL ISelctionSet
{
public:
	ISelctionSet(ITable *pTable) {m_pTable =pTable;};
	virtual ~ISelctionSet(){};

public:
	//���ѡ����������Table����
	ITable *GetTable() const{return m_pTable;}

	//ѡ��Ҫ�ص���Ŀ
	virtual long Count() const =0;

	//���һ��Ҫ�ص�ѡ����
	virtual void Add(long id) =0;

	//������һ��ѡ�񼯺ϲ�
	virtual void Combine(ISelctionSet* pSelection,SelSetOperation operatetype) =0;

	//�õ���һ��Ԫ�ص�ID,ͬʱָ��������
	virtual long NextID() =0;


	//��������ָ�뵽ѡ�񼯿�ʼ��λ��
	virtual void ResetIndex() =0;

	//ָ���Ƿ��Ѿ�������λ��
	virtual bool IsEOF() const =0;


public:
	ITable  *m_pTable;


};

typedef  SYSTEM::CSmartPtr<ISelctionSet> ISelctionSetPtr;




}




#endif