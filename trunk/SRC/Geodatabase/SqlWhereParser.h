//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.6
// 描述：  SQL解析类
//////////////////////////////////////////////////////////////////////

#ifndef  _SQL_WHERE_PARSER_H_
#define  _SQL_WHERE_PARSER_H_

#include "Field.h"
#include <string>
#include <vector>

namespace Geodatabase
{

typedef enum {
	SWQ_OR,
	SWQ_AND,
	SWQ_NOT,
	SWQ_EQ,  //相等
	SWQ_NE,  //不等
	SWQ_GE,  //大于等于
	SWQ_LE,  //小于等于
	SWQ_LT,  //小于
	SWQ_GT,  //大于
	SWQ_LIKE,
	SWQ_NOTLIKE,
	SWQ_ISNULL,
	SWQ_ISNOTNULL,
	SWQ_IN,
	SWQ_NOTIN,
	SWQ_UNKNOWN
} swq_op;

typedef enum {
	SWQ_INTEGER,
	SWQ_FLOAT,
	SWQ_STRING, 
	SWQ_BOOLEAN,
	SWQ_DATE,
	SWQ_TIME,
	SWQ_TIMESTAMP,
	SWQ_OTHER
} swq_field_type;

//swq_field_op,是用来表述where语句的内部结构体
struct swq_field_op
{
public:
    swq_field_op()
	{
       first_sub_expr =second_sub_expr=NULL;
       string_value =NULL;
	   field_index=-1;
	}
	~swq_field_op()
	{
		if(first_sub_expr)
		{
			delete first_sub_expr;
		}
		if(second_sub_expr)
		{
			delete second_sub_expr;
		}
		if(string_value)
		{
			delete []string_value;
		}
	}
public:
	swq_op      operation;

	/* 当where条件是AND,OR等时，下面两个表示where的子条件 */
	swq_field_op  *first_sub_expr;
	swq_field_op  *second_sub_expr;

	//字段序号
	int         field_index;
	int         table_index;
	FIELD_TYPE  field_type;
	char        *string_value;
	int         int_value;
	double      float_value;
} ;

typedef swq_field_op swq_expr;

typedef bool (*swq_op_evaluator)(swq_field_op *op, void *record_handle);


class GEODATABASE_DLL CSqlWhereParser
{
public:
     CSqlWhereParser();
	 virtual ~CSqlWhereParser();
public:

	/**
	* 初始化解析器
	* @Param where_clause 要解析的where语句
	* @Param fields 要查询的表的字段描述数组
	* @Param fnEvaluator 比较字段值的函数指针
	* @return 成功返回true,否则返回false
	*/
	bool Init(const char *where_clause,std::vector<CFieldPtr>& fields,swq_op_evaluator fnEvaluator);

	/**
	* 判断一条记录是否可以满足where条件
	* @Param record_handle 记录的指针
	* @return 成功返回true,否则返回false
	*/
    bool Evaluator(void *record_handle);

	/**
	* 获得满足where查询的字段名称集
	* @return 返回形如 "name,id,class"这样的字符串
	*/
	std::string GetNeedFields();

private:
	//解析where语句
    bool Compile();

	bool Subexpr_compile( char **tokens, swq_expr **expr_out,int *tokens_consumed );

	/**
	* 通过输入的词条查找字段序号
	* @Param token 字段名
    * @Param this_type 返回字段类型
	* @Param table_id 表ID,保留
	* @return 序号
	*/
	int identify_field( const char *token,FIELD_TYPE *this_type, int *table_id );

	swq_op identify_op( char **tokens, int *tokens_consumed );

	bool  subEvaluator(void *record_handle,swq_expr *expr);

private:
	std::string  m_strWhere;

	//用来比较字段值的函数指针
    swq_op_evaluator m_fnEvaluator;

	std::vector<CFieldPtr> m_allFields;

	//解释后的结果
	swq_expr *m_expr;

	

};


}



#endif