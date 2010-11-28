//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.6
// ������  SQL������
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
	SWQ_EQ,  //���
	SWQ_NE,  //����
	SWQ_GE,  //���ڵ���
	SWQ_LE,  //С�ڵ���
	SWQ_LT,  //С��
	SWQ_GT,  //����
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

//swq_field_op,����������where�����ڲ��ṹ��
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

	/* ��where������AND,OR��ʱ������������ʾwhere�������� */
	swq_field_op  *first_sub_expr;
	swq_field_op  *second_sub_expr;

	//�ֶ����
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
	* ��ʼ��������
	* @Param where_clause Ҫ������where���
	* @Param fields Ҫ��ѯ�ı���ֶ���������
	* @Param fnEvaluator �Ƚ��ֶ�ֵ�ĺ���ָ��
	* @return �ɹ�����true,���򷵻�false
	*/
	bool Init(const char *where_clause,std::vector<CFieldPtr>& fields,swq_op_evaluator fnEvaluator);

	/**
	* �ж�һ����¼�Ƿ��������where����
	* @Param record_handle ��¼��ָ��
	* @return �ɹ�����true,���򷵻�false
	*/
    bool Evaluator(void *record_handle);

	/**
	* �������where��ѯ���ֶ����Ƽ�
	* @return �������� "name,id,class"�������ַ���
	*/
	std::string GetNeedFields();

private:
	//����where���
    bool Compile();

	bool Subexpr_compile( char **tokens, swq_expr **expr_out,int *tokens_consumed );

	/**
	* ͨ������Ĵ��������ֶ����
	* @Param token �ֶ���
    * @Param this_type �����ֶ�����
	* @Param table_id ��ID,����
	* @return ���
	*/
	int identify_field( const char *token,FIELD_TYPE *this_type, int *table_id );

	swq_op identify_op( char **tokens, int *tokens_consumed );

	bool  subEvaluator(void *record_handle,swq_expr *expr);

private:
	std::string  m_strWhere;

	//�����Ƚ��ֶ�ֵ�ĺ���ָ��
    swq_op_evaluator m_fnEvaluator;

	std::vector<CFieldPtr> m_allFields;

	//���ͺ�Ľ��
	swq_expr *m_expr;

	

};


}



#endif