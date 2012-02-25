#pragma once
#include <string>
namespace ImageProcess
{

class CBandmath
{
public:
	CBandmath(void);
	~CBandmath(void);
public:
	bool dobandmath(const char *infile,const char *outfile,const char* expr);

	//�������ʽ
	bool compile();

private:
	int m_bandnum;
	std::string m_expr;

};


}