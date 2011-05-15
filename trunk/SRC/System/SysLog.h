#ifndef OT_SYS_LOG_H
#define OT_SYS_LOG_H

#include <sstream>
#include <string>
#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/format.hpp>
#include <stdio.h>

namespace SYSTEM {

SYSTEM_DLL std::string now_time();
SYSTEM_DLL const char* get_file_name_from_path(const char* file_path);

enum EnumLogLevel {LogNone, LogError, LogWarning, LogInfo, LogDebug, LogDebug1, LogDebug2, LogDebug3, LogDebug4};

template <typename T>
class CSysLog : public boost::noncopyable
{
public:
    CSysLog();
    virtual ~CSysLog();
    std::ostringstream& get(EnumLogLevel level = LogInfo);

public:
    static EnumLogLevel& reporting_level();
    static std::string to_string(EnumLogLevel level);

protected:
    std::ostringstream os;
};

template <typename T>
CSysLog<T>::CSysLog()
{
}

template <typename T>
CSysLog<T>::~CSysLog()
{
    os << std::endl;
    T::output(os.str());
}

template <typename T>
std::ostringstream& CSysLog<T>::get(EnumLogLevel level)
{
    os << "- " << now_time();
    os << " " << to_string(level) << ": ";
    os << std::string(level > LogDebug ? level - LogDebug : 0, '\t');
    return os;
}

template <typename T>
EnumLogLevel& CSysLog<T>::reporting_level()
{
	static EnumLogLevel log_reporting_level = LogDebug4;
    return log_reporting_level;
}

template <typename T>
std::string CSysLog<T>::to_string(EnumLogLevel level)
{
	static const char* const log_level_buffer[] = {"NONE", "ERROR", "WARNING", "INFO", "DEBUG", "DEBUG1", "DEBUG2", "DEBUG3", "DEBUG4"};
    return log_level_buffer[level];
}

class SYSTEM_DLL CLogOutputFile
{
public:
	static std::string& destination_file();
	static unsigned int& current_file_index();
	static void open();
	static void close();
	static size_t& limit_size();
	static size_t& current_size();
    static void output(const std::string& msg);
	static boost::mutex& mutex();

private:
	static FILE*& stream();
};

class SYSTEM_DLL CFileSysLog : public CSysLog<CLogOutputFile> 
{
public:
	static void init(std::string identity, EnumLogLevel level);
	static void uninit();
};

class SYSTEM_DLL CExecuteTimer
{
public:
	CExecuteTimer(std::string desc);
	void OutputElapsedTime();
private:
	std::string timer_desc;
	unsigned long elapsed_time;
};

}

#define Log(level) \
	if (level > SYSTEM::CFileSysLog::reporting_level()) ; \
    else SYSTEM::CFileSysLog().get(level)

#if defined(WIN32) || defined(_WINDOWS)

#define FullLogText(T) SYSTEM::get_file_name_from_path(__FILE__)<<"("<<__FUNCTION__<<":"<<__LINE__<<")"<<std::endl<<">>>"<<T<<std::endl

#else

#define FullLogText(T) SYSTEM::get_file_name_from_path(__FILE__)<<"("<<__LINE__<<")"<<std::endl<<">>>"<<T<<std::endl

#endif

#define ErrorLog(T) Log(SYSTEM::LogError)<<FullLogText(T)

#define InfoLog(T) Log(SYSTEM::LogInfo)<<FullLogText(T)

#define WarningLog(T) Log(SYSTEM::LogWarning)<<FullLogText(T)

#define DebugLog(T) Log(SYSTEM::LogDebug)<<FullLogText(T)

#define Debug1Log(T) Log(SYSTEM::LogDebug1)<<FullLogText(T)

#define Debug2Log(T) Log(SYSTEM::LogDebug2)<<FullLogText(T)

# if defined(_DEBUG) || defined(OT_ALWAYS_ENABLE_TIMER)

#define BEGIN_TIMER(timer, desc)	SYSTEM::CExecuteTimer _exe_timer_##timer(desc);
#define END_TIMER(timer)			_exe_timer_##timer.OutputElapsedTime();

#else

#define BEGIN_TIMER(timer, desc)
#define END_TIMER(timer)

#endif

#endif // OT_SYS_LOG_H
