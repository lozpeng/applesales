#ifndef _SYSTEM_EXCEPTION_H
#define _SYSTEM_EXCEPTION_H

#include <exception>
#include <string>

namespace SYSTEM {

class SYSTEM_DLL CException : public std::exception
{
public:
	CException() throw();
	CException(const char* reason) throw();
	CException(const std::string& reason) throw();
	CException(const char *reason,const char* file, const char* function, long line) throw();

	virtual ~CException() throw();
	virtual const char * what() const;
	virtual void SetExceptionText(const std::string& err);
	virtual void SetExceptionText(const char* err);

	long GetLine() const {return m_line;}
	const char* GetFile() const {return m_file.c_str();}
	const char* GetFunction() const {return m_function.c_str();}


private:
	std::string error_text;
	std::string m_function; //抛出异常的函数
	std::string m_file;     //异常所在文件
	long m_line;           //异常所在行

};

}

#ifndef THORW_EXCEPT
#define THORW_EXCEPT(desc)  throw new SYSTEM::CException(desc, __FILE__, __FUNCTION__, __LINE__);
#endif

#endif
