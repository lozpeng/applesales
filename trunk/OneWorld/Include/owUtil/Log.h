#pragma once

#include <owUtil/export.h>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <osg/Referenced>

namespace owUtil 
{
	class OWUTIL_EXPORT LogFile
	{
	public:
		///Change the name of the log file (defaults to "ot3d_log.html")
		static void SetFileName(const std::string& name);

		///Get the current filename of the log file.
		static const std::string GetFileName();

		/// change the title string used in HTML 
		/// defaults to "otitan 3D Engine Log File" or "otitan 3D Engine Log File (Debug Libs)"
		static void SetTitle(const std::string& title);

		///Get the current HTML title string.
		static const std::string& GetTitle();
	};

	/**
	* Helps making logging a little easier.  However, printf style
	*   logging is desired, you cannot use this macro.
	*/
#define LOG_DEBUG(msg)\
	owUtil::Log::GetInstance().LogMessage(__FUNCTION__, __LINE__, msg,owUtil::Log::LOG_DEBUG);

#define LOG_INFO(msg)\
	owUtil::Log::GetInstance().LogMessage(__FUNCTION__, __LINE__, msg,owUtil::Log::LOG_INFO);

#define LOG_WARNING(msg)\
	owUtil::Log::GetInstance().LogMessage(__FUNCTION__, __LINE__, msg,owUtil::Log::LOG_WARNING);

#define LOG_ERROR(msg)\
	owUtil::Log::GetInstance().LogMessage(__FUNCTION__, __LINE__, msg,owUtil::Log::LOG_ERROR);

#define LOG_ALWAYS(msg)\
	owUtil::Log::GetInstance().LogMessage(__FUNCTION__, __LINE__, msg,owUtil::Log::LOG_ALWAYS);

#define LOGN_DEBUG(name, msg)\
	owUtil::Log::GetInstance(name).LogMessage(__FUNCTION__, __LINE__, msg,owUtil::Log::LOG_DEBUG);

#define LOGN_INFO(name, msg)\
	owUtil::Log::GetInstance(name).LogMessage(__FUNCTION__, __LINE__, msg,owUtil::Log::LOG_INFO);

#define LOGN_WARNING(name, msg)\
	owUtil::Log::GetInstance(name).LogMessage(__FUNCTION__, __LINE__, msg,owUtil::Log::LOG_WARNING);

#define LOGN_ERROR(name, msg)\
	owUtil::Log::GetInstance(name).LogMessage(__FUNCTION__, __LINE__, msg,owUtil::Log::LOG_ERROR);

#define LOGN_ALWAYS(name, msg)\
	owUtil::Log::GetInstance(name).LogMessage(__FUNCTION__, __LINE__, msg,owUtil::Log::LOG_ALWAYS);

	/**
	* Log class which the engine uses for all of its logging
	* needs.  The log file is formatted using html tags,
	* therefore, any browser should display the log without
	*  any problems.
	*/
	class OWUTIL_EXPORT Log : public osg::Referenced 
	{
	public:

		/**
		* 日志消息的不同类型.
		*/
		enum LogMessageType
		{
			LOG_DEBUG,
			LOG_INFO,
			LOG_WARNING,
			LOG_ERROR,
			LOG_ALWAYS
		};


		/**
		* Logs a time-stamped message.
		* @param source - 消息源字符串标识.
		*  (__FUNCTION__ 用在这里.
		* @param line - 行数.
		*  @param msg - 消息显示.
		*  @param msgType - 显示的消息类型. (error,warning,info)
		*/
		void LogMessage(const std::string &source, int line, const std::string &msg,
			LogMessageType msgType = LOG_INFO) const;

		/**
		* Little more sophisticated method for logging messages.  Allows for
		*  an unlimited number of parameters in a C-style printf syntax.
		*  @param msgType - 显示的消息类型. (error,warning,info)
		*  @param source - 消息源字符串标识.
		*  @param line - 行数.
		*  @param msg - （Printf - style） 格式字符串.
		*  @note
		*      输出字符串的最大长度为2048个字符.
		*/
		void LogMessage(LogMessageType msgType, const std::string &source, int line,
			const char *msg, ...) const;

		/**
		* Little more sophisticated method for logging messages.  Allows for
		*  an unlimited number of parameters in a C-style printf syntax.
		*  @param msgType - 显示的消息类型. (error,warning,info)
		*  @param source - 消息源字符串标识.
		*  @param line - the line number.
		*  @param msg - std::string that has been formatted.
		*  @note
		*      输出字符串的最大长度为2048个字符.
		*/
		void LogMessage(LogMessageType msgType, const std::string &source, int line,
			const std::string &msg) const;

		/**
		* Little more sophisticated method for logging messages.  Allows for
		*  an unlimited number of parameters in a C-style printf syntax.
		*  @param msgType - Type of message being displayed. (error,warning,info)
		*  @param source - String identifier of the source of the message.
		*  @param msg - Printf - style format string.
		*  @note
		*      Max length of the string to be printed is 2048 characters.
		*/
		void LogMessage(LogMessageType msgType, const std::string &source,
			const char *msg, ...) const;
		/**
		* 在日志文件中插入一条水平线.
		*/
		void LogHorizRule();

		/**
		* @return true if log messages of the given level will be sent to the log
		* output
		* @param msgType -  所要查询的消息类型.
		*/
		bool IsLevelEnabled(LogMessageType msgType) const { return msgType >= mLevel; }

		/**
		* Sets the lowest level of logging that will be logged.
		* If the level in set to Debug, all messages will be sent. If the level is set error, only
		* errors will be sent.
		* @param msgType the new logging level
		*/
		void SetLogLevel(LogMessageType msgType)  { mLevel = msgType; }

		/**
		* @return the lowest level of logging that will be logged.
		*/
		LogMessageType GetLogLevel() const { return mLevel; }

		///@return a string version of a log level.
		const std::string GetLogLevelString( LogMessageType msgType) const;

		///@return the log level matching a string or WARNING if there is no match.
		LogMessageType GetLogLevelForString( const std::string& levelString) const;

		/*
		* 得到唯一的log类实例.
		*/
		static Log& GetInstance();

		/*
		* 得到唯一的制定文件名的log类实例.
		* @param name - 日志文件名
		*/
		static Log& GetInstance(const std::string& name);

		enum OutputStreamOptions
		{
			NO_OUTPUT =   0x00000000, ///<日志消息不输出到任何机制
			TO_FILE =     0x00000001,   ///<日志消息被输出到文件中
			TO_CONSOLE =  0x00000002,///<日志消息输出到控制台
			STANDARD = TO_FILE | TO_CONSOLE ///<默认设置
		};

		///Configure where the Log messages get directed
		void SetOutputStreamBit(unsigned int option);

		///得到当前默认输出流选项.
		unsigned int GetOutputStreamBit() const;

		///返回日志文件的名称.
		const std::string& GetName() const { return mName; }

		//Constructor and destructor are both protected since this is a singleton.
	protected:
		/**
		* 打开日志文件并写入html标题信息.
		*/
		Log(const std::string& name);

		/**
		* 关闭日志文件.
		*/
		~Log();

	private:
		static const std::string mDefaultName;

		LogMessageType mLevel;
		unsigned int mOutputStreamBit; ///<当前输出流选项
		std::string mName;
	};

}

