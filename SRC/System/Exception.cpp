#include "stdafx.h"
#include "Exception.h"


namespace SYSTEM {

CException::CException():m_line(0)
{
}

CException::CException(const char* reason) throw() :m_line(0)
{
	SetExceptionText(reason);
}

CException::CException(const std::string& reason) throw() :m_line(0)
{
	SetExceptionText(reason);
}

CException::CException(const char *reason,const char* file, const char* function, long line) throw()
{
	error_text =reason;
	m_file =file;
	m_function =function;
	m_line =line;
}

CException::~CException() throw()
{
}

void CException::SetExceptionText(const std::string& err)
{
	error_text = err;
}

void CException::SetExceptionText(const char* err)
{
	error_text = err;
}

const char * CException::what() const
{
	return error_text.c_str();
}

}
