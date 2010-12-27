//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.6
// ������  �����������ݿ���в�ѯ�Ĳ�ѯ����
//////////////////////////////////////////////////////////////////////

#ifndef  _GEODATABASE_SIMPLEQUERY_H_
#define  _GEODATABASE_SIMPLEQUERY_H_

#include "ITable.h"
#include "ISelectionSet.h"
#include <map>

namespace Geodatabase
{

class  GEODATABASE_DLL CSimpleQuery
{
public:
	CSimpleQuery( ) {m_strFields ="*";};
	virtual ~CSimpleQuery(){};

public:
	//�õ���ѯ���ֶ��ַ�������"Name,Population"
	std::string GetFields() const{return m_strFields;}

	//���ò�ѯ���ֶ��ַ���
	void SetFields(const char* strFields) {m_strFields =strFields;}

	//����һ�����ֶ�
	void AddField(const char *field)
	{
		if(m_strFields=="*")
		{
			m_strFields =field;
		}
		else
		{
			m_strFields+=",";
			m_strFields+=field;
		}
	}

	//�õ���ѯ��where���
	std::string GetWhereString() const{return m_strWhere;}

	//���ò�ѯ��where���
	void SetWhereString(const char* strWhere) {m_strWhere =strWhere;}


protected:
	std::string  m_strFields;

	std::string  m_strWhere;


};






}




#endif