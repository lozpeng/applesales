#include "stdafx.h"
#include "SysLog.h"

namespace SYSTEM {

const unsigned int MAX_LOG_FILE_COUNT = 3;

void CFileSysLog::init(std::string identity, EnumLogLevel level)
{
	CLogOutputFile::destination_file() = identity;
    CFileSysLog::reporting_level() = level;
	CLogOutputFile::open();
}

void CFileSysLog::uninit()
{
	CLogOutputFile::close();
}

FILE*& CLogOutputFile::stream()
{
    static FILE* pStream = stderr;
    return pStream;
}

std::string& CLogOutputFile::destination_file()
{
	static std::string log_destination_file;
	return log_destination_file;
}

unsigned int& CLogOutputFile::current_file_index()
{
	static unsigned int log_current_file_index = 0;
	return log_current_file_index;
}

void CLogOutputFile::output(const std::string& msg)
{   
	boost::mutex::scoped_lock lock(mutex());

    FILE* pStream = stream();
    if (!pStream)
        return;
    fprintf(pStream, "%s", msg.c_str());
    fflush(pStream);
	current_size() += msg.size();
	if(current_size() > limit_size())
	{
		current_file_index() ++;
		if(current_file_index() == MAX_LOG_FILE_COUNT)
			current_file_index() = 0;
		std::ostringstream os;
		os << destination_file() << "_" << current_file_index() << ".log";
		fclose( stream() );
		stream() = fopen(os.str().c_str(), "w");
		current_size() = 0;
	}
#if defined(WIN32) || defined(_WINDOWS)
	#if defined(_DEBUG)
	::OutputDebugString(msg.c_str());
	#endif
#endif
}

void CLogOutputFile::open()
{
	std::ostringstream os;
	os << destination_file() << "_" << current_file_index() << ".log";
	stream() = fopen(os.str().c_str(), "w");
}

void CLogOutputFile::close()
{
	FILE* pStream = stream();
    if (pStream != stderr)
	{
		fclose(pStream);
		stream() = stderr;
	}
}

size_t& CLogOutputFile::limit_size()
{
	static size_t log_limit_size = 2*1024*1024;
	return log_limit_size;
}

size_t& CLogOutputFile::current_size()
{
	static size_t log_current_size = 0;
	return log_current_size;
}

boost::mutex& CLogOutputFile::mutex()
{
	static boost::mutex log_mutex;
	return log_mutex;
}

///////////////////////////////////////////////////////////
CExecuteTimer::CExecuteTimer(std::string desc) : timer_desc(desc), elapsed_time(0)
{
#if defined(WIN32) || defined(_WINDOWS)
	elapsed_time = ::GetTickCount();
	InfoLog("Start Timer: "<<elapsed_time);
#endif
}

void CExecuteTimer::OutputElapsedTime()
{
#if defined(WIN32) || defined(_WINDOWS)
	elapsed_time = ::GetTickCount() - elapsed_time;
#endif
	InfoLog("Execute Timer: "<<timer_desc<<" cost "<<elapsed_time<<" ms.");
}

///////////////////////////////////////////////////////////
SYSTEM_DLL const char* get_file_name_from_path(const char* file_path)
{
	const char* file_name = strrchr(file_path, '\\');
	if( file_name == NULL)
	{
		file_name = strrchr(file_path, '/');
		if( file_name == NULL)
			file_name = file_path;
		else
			file_name++;
	}
	else
		file_name++;
	return file_name;
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)

#include <windows.h>

SYSTEM_DLL std::string now_time()
{
    char time_buffer[64];
    GetTimeFormat(LOCALE_USER_DEFAULT, 0, 0,("HH':'mm':'ss"), time_buffer, 64);
	return time_buffer;
}

#else

#include <sys/time.h>

std::string now_time()
{
    char buffer[11];
    time_t t;
    time(&t);
    tm r = {0};
    strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
    struct timeval tv;
    gettimeofday(&tv, 0);
    char result[100] = {0};
    std::sprintf(result, "%s.%03ld", buffer, (long)tv.tv_usec / 1000); 
    return result;
}

#endif //WIN32

}
