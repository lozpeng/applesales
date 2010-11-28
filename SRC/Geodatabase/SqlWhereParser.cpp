#include "stdafx.h"
#include "SqlWhereParser.h"
#include <set>
namespace Geodatabase
{

#define strcasecmp stricmp
#define SWQ_OP_IS_LOGICAL(op) ((op) == SWQ_OR || (op) == SWQ_AND || (op) == SWQ_NOT)
#define SWQ_OP_IS_POSTUNARY(op) ((op) == SWQ_ISNULL || (op) == SWQ_ISNOTNULL)

CSqlWhereParser::CSqlWhereParser()
{
     m_fnEvaluator=NULL;
	 m_expr =NULL;

}
CSqlWhereParser::~CSqlWhereParser()
{
   if(m_expr)
   {
      delete m_expr;
   }
}


bool CSqlWhereParser::Init(const char *where_clause,std::vector<CFieldPtr>& fields,swq_op_evaluator fnEvaluator)
{
	if((!where_clause) || (!fnEvaluator))
	{
		return false;
	}

	m_allFields.clear();

	for(size_t i=0;i<fields.size();i++)
	{
		m_allFields.push_back(fields[i]);
	}

	m_strWhere =where_clause;

	m_fnEvaluator =fnEvaluator;

	return Compile();

	
}

static int swq_isalphanum( char c )

{
	if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '.' || c == '+' || c == '-'
		|| c == '_' || c == '*' || ((unsigned char) c) > 127 )
		return TRUE;
	else
		return FALSE;
}

//解析输入字符串
static char *swq_token( const char *expression, char **next, int *is_literal )

{
	char        *token;
	int         i_token;

	if( is_literal != NULL )
		*is_literal = 0;

	while( *expression == ' ' || *expression == '\t'
		|| *expression == 10 || *expression == 13 )
		expression++;

	if( *expression == '\0' )
	{
		*next = (char *) expression;
		return NULL; 
	}

	/* -------------------------------------------------------------------- */
	/*      Handle string constants.                                        */
	/* -------------------------------------------------------------------- */
	if( *expression == '"' || *expression == '\'' )
	{
		expression++;

		token = (char *) malloc(strlen(expression)+1);
		i_token = 0;

		while( *expression != '\0' )
		{
			if( *expression == '\\' && expression[1] == '"' )
				expression++;
			else if( *expression == '\\' && expression[1] == '\'' )
				expression++;
			else if( *expression == '\'' && expression[1] == '\'' )
				expression++;
			else if( *expression == '"' )
			{
				expression++;
				break;
			}
			else if( *expression == '\'' )
			{
				expression++;
				break;
			}

			token[i_token++] = *(expression++);
		}
		token[i_token] = '\0';

		if( is_literal != NULL )
			*is_literal = 1;
	}

	/* -------------------------------------------------------------------- */
	/*      Handle alpha-numerics.                                          */
	/* -------------------------------------------------------------------- */
	else if( swq_isalphanum( *expression ) )
	{
		token = (char *) malloc(strlen(expression)+1);
		i_token = 0;

		while( swq_isalphanum( *expression ) )
		{
			token[i_token++] = *(expression++);
		}

		token[i_token] = '\0';
	}

	/* -------------------------------------------------------------------- */
	/*      Handle special tokens.                                          */
	/* -------------------------------------------------------------------- */
	else
	{
		token = (char *) malloc(3);
		token[0] = *expression;
		token[1] = '\0';
		expression++;

		/* special logic to group stuff like '>=' into one token. */

		if( (*token == '<' || *token == '>' || *token == '=' || *token == '!')
			&& (*expression == '<' || *expression == '>' || *expression == '='))
		{
			token[1] = *expression;
			token[2] = '\0';
			expression++;
		}
	}

	*next = (char *) expression;

	return token;
}

static void *swq_realloc( void *old_mem, int old_size, int new_size )

{
	void *new_mem;

	new_mem = malloc( new_size );

	if( old_mem != NULL )
	{
		memcpy( new_mem, old_mem, old_size < new_size ? old_size : new_size);
		free( old_mem );
	}
	if (old_size <= new_size )
		memset( ((char *) new_mem) + old_size, 0, new_size - old_size );

	return new_mem;
}

/************************************************************************/
/*                         swq_parse_in_list()                          */
/*                                                                      */
/*     解析如下形式的字符串                                              */
/*                                                                      */
/*        WHERE color IN ('Red', 'Green', 'Blue')                       */
/************************************************************************/

static char *swq_parse_in_list( char **tokens, int *tokens_consumed )

{
	int   i, text_off = 2;
	char *result;

	if( tokens[*tokens_consumed] == NULL
		|| strcasecmp(tokens[*tokens_consumed],"(") != 0 )
	{
		
		return NULL;
	}

	*tokens_consumed += 1;

	/* Establish length of all tokens plus separators. */

	for( i = *tokens_consumed; 
		tokens[i] != NULL && strcasecmp(tokens[i],")") != 0; 
		i++ )
	{
		text_off += strlen(tokens[i]) + 1;
	}

	result = new char [text_off];

	/* Actually capture all the arguments. */

	text_off = 0;
	while( tokens[*tokens_consumed] != NULL 
		&& strcasecmp(tokens[*tokens_consumed],")") != 0 )
	{
		strcpy( result + text_off, tokens[*tokens_consumed] );
		text_off += strlen(tokens[*tokens_consumed]) + 1;

		*tokens_consumed += 1;

		if( strcasecmp(tokens[*tokens_consumed],",") != 0
			&& strcasecmp(tokens[*tokens_consumed],")") != 0 )
		{
			
			delete []result;
			return NULL;
		}
		else if( strcasecmp(tokens[*tokens_consumed],",") == 0 )
			*tokens_consumed += 1;
	}

	/* add final extra terminating zero char */
	result[text_off] = '\0';

	if( tokens[*tokens_consumed] == NULL )
	{
		delete []result;
		return NULL;
	}

	*tokens_consumed += 1;

	return result;
}


static char *swq_strdup( const char *input )
{
	char *result;

	result = new char[strlen(input)+1];
	strcpy( result, input );

	return result;
}

bool CSqlWhereParser::Compile()
{
	#define TOKEN_BLOCK_SIZE 1024

	char        **token_list,*rest_of_expr;
	int         token_count = 0;
	int         tokens_consumed, i, token_list_size;

	//整理输入字符
	token_list = (char **)malloc(sizeof(char *) * TOKEN_BLOCK_SIZE);
	token_list_size = TOKEN_BLOCK_SIZE;
	rest_of_expr = new char[m_strWhere.size()+1];
	char *old =rest_of_expr;

	memset(rest_of_expr,0,sizeof(char)*(m_strWhere.size()+1));

	strcpy(rest_of_expr,m_strWhere.c_str());
	while( (token_list[token_count] = 
		swq_token(rest_of_expr,&rest_of_expr,NULL)) != NULL )
	{
		token_count++;

		//如果字符串超过TOKEN_BLOCK_SIZE，则重新分配内存
		if (token_count == token_list_size)
		{
			token_list = (char **)(token_list, 
				sizeof(char *) * token_list_size, 
				sizeof(char *) * (token_list_size + TOKEN_BLOCK_SIZE));
			token_list_size += TOKEN_BLOCK_SIZE;
		}
	}

	bool bret =false;
	bret = Subexpr_compile( token_list,&m_expr,&tokens_consumed );

	for( i = 0; i < token_count; i++ )
		free( token_list[i] );

	free(token_list);

	delete []old;

	//解析字符数小于输入字符数
	if( tokens_consumed < token_count )
	{
		
		return false;
	}

	return true;
}

int CSqlWhereParser::identify_field(const char *token,FIELD_TYPE *this_type, int *table_id)
{
	int i;
	char table_name[128];
	const char *field_token = token;
	int   tables_enabled;


	for( i = 0; i < m_allFields.size(); i++ )
	{
		int  t_id = 0;

		if( strcasecmp( m_allFields[i]->GetName().c_str(), field_token ) != 0 )
			continue;

		
		/* We have a match, return various information */
		if( this_type != NULL )
		{
			*this_type =(FIELD_TYPE) m_allFields[i]->GetType();
		}

		if( table_id != NULL )
			*table_id = t_id;

		return i;
	}

	/* -------------------------------------------------------------------- */
	/*     么有找到                                      */
	/* -------------------------------------------------------------------- */
	if( this_type != NULL )
		*this_type = FTYPE_UNKNOWN;

	if( table_id != NULL )
		*table_id = 0;

	return -1;
}

swq_op CSqlWhereParser::identify_op( char **tokens, int *tokens_consumed )

{
	const char *token = tokens[*tokens_consumed];

	if( strcasecmp(token,"OR") == 0 )
		return SWQ_OR;

	if( strcasecmp(token,"AND") == 0 )
		return SWQ_AND;

	if( strcasecmp(token,"NOT") == 0 )
	{
		if( tokens[*tokens_consumed+1] != NULL
			&& (strcasecmp(tokens[*tokens_consumed+1],"LIKE") == 0 
			|| strcasecmp(tokens[*tokens_consumed+1],"ILIKE") == 0) )
		{
			*tokens_consumed += 1;
			return SWQ_NOTLIKE;
		}
		else if( tokens[*tokens_consumed+1] != NULL
			&& strcasecmp(tokens[*tokens_consumed+1],"IN") == 0 )
		{
			*tokens_consumed += 1;
			return SWQ_NOTIN;
		}
		else
			return SWQ_NOT;
	}

	if( strcasecmp(token,"<=") == 0 )
		return SWQ_LE;

	if( strcasecmp(token,">=") == 0 )
		return SWQ_GE;

	if( strcasecmp(token,"=") == 0 )
		return SWQ_EQ;

	if( strcasecmp(token,"!=") == 0 )
		return SWQ_NE;

	if( strcasecmp(token,"<>") == 0 )
		return SWQ_NE;

	if( strcasecmp(token,"<") == 0 )
		return SWQ_LT;

	if( strcasecmp(token,">") == 0 )
		return SWQ_GT;

	if( strcasecmp(token,"LIKE") == 0 )
		return SWQ_LIKE;

	if( strcasecmp(token,"ILIKE") == 0 )
		return SWQ_LIKE;

	if( strcasecmp(token,"IN") == 0 )
		return SWQ_IN;

	if( strcasecmp(token,"IS") == 0 )
	{
		if( tokens[*tokens_consumed+1] == NULL )
			return SWQ_UNKNOWN;
		else if( strcasecmp(tokens[*tokens_consumed+1],"NULL") == 0 )
		{
			*tokens_consumed += 1;
			return SWQ_ISNULL;
		}
		else if( strcasecmp(tokens[*tokens_consumed+1],"NOT") == 0
			&& tokens[*tokens_consumed+2] != NULL
			&& strcasecmp(tokens[*tokens_consumed+2],"NULL") == 0 )
		{
			*tokens_consumed += 2;
			return SWQ_ISNOTNULL;
		}
		else 
			return SWQ_UNKNOWN;
	}

	return SWQ_UNKNOWN;
}
bool CSqlWhereParser::Subexpr_compile( char **tokens,swq_expr **expr_out, int *tokens_consumed )
{
	swq_expr    *op;
	int         op_code = 0;

	*tokens_consumed = 0;

	if( tokens[0] == NULL || tokens[1] == NULL )
	{
		return false;
	}
    op =new swq_expr();
	op->field_index = -1;

	if( strcmp(tokens[0],"(") == 0 )
	{
		int     sub_consumed = 0;

		//解析子语句
		bool bret =Subexpr_compile( tokens + 1,(swq_expr **) &(op->first_sub_expr), &sub_consumed );
		if( !bret)
		{
			delete op;
			return false;
		}

		if( strcmp(tokens[sub_consumed+1],")") != 0 )
		{
			delete op;
			return false;
		}

		*tokens_consumed += sub_consumed + 2;

		/* If we are at the end of the tokens, we should return our subnode */
		if( tokens[*tokens_consumed] == NULL
			|| strcmp(tokens[*tokens_consumed],")") == 0 )
		{
			*expr_out = (swq_expr *) op->first_sub_expr;
			op->first_sub_expr = NULL;
			delete op;
			return true;
		}
	}
	else if( strcasecmp(tokens[0],"NOT") == 0 )
	{
		/* do nothing, the NOT will be collected as the operation */
	}
	else
	{
		op->field_index = 
			identify_field( tokens[*tokens_consumed],
			&(op->field_type), 
			&(op->table_index) );

		if( op->field_index < 0 )
		{
			delete op;
			
			return false;
		}

		(*tokens_consumed)++;
	}

	/*
	** Identify the operation.
	*/
	if( tokens[*tokens_consumed] == NULL || tokens[*tokens_consumed+1] == NULL)
	{
		
		delete op;

		return false;
	}

	op->operation = identify_op( tokens, tokens_consumed );
	if( op->operation == SWQ_UNKNOWN )
	{
		delete op;

		return false;
	}

	if( SWQ_OP_IS_LOGICAL( op->operation ) 
		&& op->first_sub_expr == NULL 
		&& op->operation != SWQ_NOT )
	{
		delete op;

		return false;
	}

	if( op->field_index != -1 && op->field_type == FTYPE_STRING
		&& (op->operation != SWQ_EQ && op->operation != SWQ_NE
		&& op->operation != SWQ_GT && op->operation != SWQ_LT
		&& op->operation != SWQ_GE && op->operation != SWQ_LE
		&& op->operation != SWQ_LIKE && op->operation != SWQ_NOTLIKE
		&& op->operation != SWQ_IN && op->operation != SWQ_NOTIN
		&& op->operation != SWQ_ISNULL && op->operation != SWQ_ISNOTNULL ))
	{
		/* NOTE: the use of names[] here is wrong.  We should be looking
		up the field that matches op->field_index and op->table_index */

		delete op;

		return false;
	}

	(*tokens_consumed)++;

	/*
	** Collect the second operand as a subexpression.
	*/

	if( SWQ_OP_IS_POSTUNARY(op->operation) )
	{
		/* we don't need another argument. */
	}

	else if( tokens[*tokens_consumed] == NULL )
	{
		delete op;

		return false;
	}

	else if( SWQ_OP_IS_LOGICAL( op->operation ) )
	{
		int     sub_consumed = 0;

		bool bret = Subexpr_compile( tokens + *tokens_consumed,
			(swq_expr **) &(op->second_sub_expr), 
			&sub_consumed );
		if(!bret )
		{
			delete op;
			return false;
		}

		*tokens_consumed += sub_consumed;
	}

	/* 解析带有IN关键字的字符. */
	else if( op->operation == SWQ_IN || op->operation == SWQ_NOTIN )
	{
		op->string_value = swq_parse_in_list( tokens, tokens_consumed );
		if( op->string_value == NULL )
		{
			delete op;
			return false;
		}
	}

	/*
	** Otherwise collect it as a literal value.
	*/
	else
	{
		op->string_value = swq_strdup(tokens[*tokens_consumed]);
		op->int_value = atoi(op->string_value);
		op->float_value = atof(op->string_value);

		if( op->field_index != -1 
			&& (op->field_type == SWQ_INTEGER || op->field_type == SWQ_FLOAT) 
			&& op->string_value[0] != '-'
			&& op->string_value[0] != '+'
			&& op->string_value[0] != '.'
			&& (op->string_value[0] < '0' || op->string_value[0] > '9') )
		{
			/* NOTE: the use of names[] here is wrong.  We should be looking
			up the field that matches op->field_index and op->table_index */

			delete op;
			return false;
		}

		(*tokens_consumed)++;
	}

	*expr_out = op;

	/* Transform stuff like A NOT LIKE X into NOT (A LIKE X) */
	if( op->operation == SWQ_NOTLIKE
		|| op->operation == SWQ_ISNOTNULL 
		|| op->operation == SWQ_NOTIN )
	{
		if( op->operation == SWQ_NOTLIKE )
			op->operation = SWQ_LIKE;
		else if( op->operation == SWQ_NOTIN )
			op->operation = SWQ_IN;
		else if( op->operation == SWQ_ISNOTNULL )
			op->operation = SWQ_ISNULL;

		op = new swq_field_op;
		op->field_index = -1;
		op->second_sub_expr =  *expr_out;
		op->operation = SWQ_NOT;

		*expr_out = op;
	}

	op = NULL;

	/*
	** Are we part of an unparantized logical expression chain?  If so, 
	** grab the remainder of the expression at "this level" and add to the
	** local tree. 
	*/
	op_code = SWQ_UNKNOWN;
	if( tokens[*tokens_consumed] != NULL )
		op_code = identify_op( tokens, tokens_consumed );

	if( SWQ_OP_IS_LOGICAL(op_code) )
	{
		swq_expr *remainder = NULL;
		swq_expr *parent;
		int      sub_consumed;

		bool bret = Subexpr_compile( tokens + *tokens_consumed + 1,
			&remainder, &sub_consumed );
		if( !bret )
		{
			delete( *expr_out );
			*expr_out = NULL;
			return false;
		}

		parent = new swq_field_op;
		parent->field_index = -1;

		parent->first_sub_expr =  *expr_out;
		parent->second_sub_expr =  remainder;
		parent->operation =(swq_op) op_code;

		*expr_out = parent;

		*tokens_consumed += sub_consumed + 1;
	}

	return NULL;
}

bool CSqlWhereParser::Evaluator(void *record_handle)
{
	if((!m_expr) || (!m_fnEvaluator) || (!record_handle))
	{
		return false;
	}

	return subEvaluator(record_handle,m_expr);
}

bool CSqlWhereParser::subEvaluator(void *record_handle, Geodatabase::swq_expr *expr)
{
	if( expr->operation == SWQ_OR )
	{
		return subEvaluator(record_handle, (swq_expr *) expr->first_sub_expr) 
			|| subEvaluator(record_handle, (swq_expr *) expr->second_sub_expr);
	}
	else if( expr->operation == SWQ_AND )
	{
		return subEvaluator(record_handle, (swq_expr *) expr->first_sub_expr) 
			&& subEvaluator(record_handle, (swq_expr *) expr->second_sub_expr);
	}
	else if( expr->operation == SWQ_NOT )
	{
		return !subEvaluator(record_handle, (swq_expr *) expr->second_sub_expr);
	}
	else
	{
		return m_fnEvaluator( expr, record_handle );
	}
}

std::string CSqlWhereParser::GetNeedFields()
{
    if(!m_expr)
	{
		return "";
	}
	std::set<std::string> names;
	
	std::string fieldstr;

	std::string str;

	//查找主语句所需的字段
	if(m_expr->field_index!=-1)
	{
		fieldstr =m_allFields[m_expr->field_index]->GetName();
		names.insert(fieldstr);
		str+=fieldstr;
	}

	if(m_expr->first_sub_expr)
	{
		fieldstr =m_allFields[m_expr->first_sub_expr->field_index]->GetName();

		//如果这个字段没有出现，则加入
		if(names.find(fieldstr)==names.end())
		{
           names.insert(fieldstr);
		   if(!str.empty())
		   {
               str+=",";
		   }
		   
		   str+=fieldstr;
		}
		
	}

	if(m_expr->second_sub_expr)
	{
		fieldstr =m_allFields[m_expr->second_sub_expr->field_index]->GetName();

		//如果这个字段没有出现，则加入
		if(names.find(fieldstr)==names.end())
		{
			names.insert(fieldstr);
			if(!str.empty())
			{
				str+=",";
			}

			str+=fieldstr;
		}
	}

	


	return str;


}

} //namespace Geodatabase