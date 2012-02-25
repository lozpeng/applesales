#include "StdAfx.h"
#include "Bandmath.h"
#include "IWorkspace.h"
#include "RasterWSFactory.h"

namespace ImageProcess
{

CBandmath::CBandmath(void)
{
}

CBandmath::~CBandmath(void)
{
}

bool CBandmath::dobandmath(const char *infile, const char *outfile, const char *expr)
{
	if(!infile || !outfile || !expr)
	{
		return false;
	}
	Geodatabase::IWorkspace *pSrcWp =CRasterWSFactory::GetInstance()->OpenFromFile(infile);
	if(!pSrcWp)
	{
		return false;
	}
	//打开原文件
	Geodatabase::IRasterDatasetPtr pSrcRS =pSrcWp->OpenRasterDataset(infile);
	if(!pSrcRS)
	{
		return false;
	}
	m_bandnum =pSrcRS->GetBandCount();
	m_expr =expr;
	if(!compile())
	{
		return false;
	}

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

static int isnum(char c)
{
	if( (c >= '0' && c <= '9'))
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
		return NULL;
	}
	//处理波段号
	else if(*expression=='b')
	{
        expression++;
		if(isnum(*expression))
		{
			token = (char *) malloc(strlen(expression)+2);
			token[0]='b';
			i_token = 1;
			while( isnum( *expression ) )
			{
				token[i_token++] = *(expression++);
			}
			token[i_token] = '\0';

		}
		else
		{
			return NULL;
		}

	}

	/* -------------------------------------------------------------------- */
	/*      Handle alpha-numerics.                                          */
	/* -------------------------------------------------------------------- */
	else if( isnum(*expression) )
	{
		token = (char *) malloc(strlen(expression)+1);
		i_token = 0;
		while( isnum( *expression ) || (*expression=='.') )
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
		char c =*expression;
		if(c=='+' || c=='-' || c=='*' ||c=='/' || c=='(' || c==')')
		{
			token = (char *) malloc(3);
			token[0] = *expression;
			token[1] = '\0';
            expression++;
		}
		else 
		{
			return NULL;
		}

	}

	*next = (char *) expression;

	return token;
}

bool CBandmath::compile()
{
#define TOKEN_BLOCK_SIZE 1024

	char        **token_list,*rest_of_expr;
	int         token_count = 0;
	int         tokens_consumed, i, token_list_size;

	//整理输入字符
	token_list = (char **)malloc(sizeof(char *) * TOKEN_BLOCK_SIZE);
	token_list_size = TOKEN_BLOCK_SIZE;
	rest_of_expr = new char[m_expr.size()+1];
	char *old =rest_of_expr;

	memset(rest_of_expr,0,sizeof(char)*(m_expr.size()+1));

	strcpy(rest_of_expr,m_expr.c_str());
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
	//bret = Subexpr_compile( token_list,&m_expr,&tokens_consumed );

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

}