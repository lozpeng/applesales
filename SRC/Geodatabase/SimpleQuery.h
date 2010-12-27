//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.6
// 描述：  定义了在数据库表中查询的查询条件
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
	//得到查询的字段字符串，如"Name,Population"
	std::string GetFields() const{return m_strFields;}

	//设置查询的字段字符串
	void SetFields(const char* strFields) {m_strFields =strFields;}

	//增加一个子字段
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

	//得到查询的where语句
	std::string GetWhereString() const{return m_strWhere;}

	//设置查询的where语句
	void SetWhereString(const char* strWhere) {m_strWhere =strWhere;}


protected:
	std::string  m_strFields;

	std::string  m_strWhere;


};






}




#endif