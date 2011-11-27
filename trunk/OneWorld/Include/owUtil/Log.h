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
		* ��־��Ϣ�Ĳ�ͬ����.
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
		* @param source - ��ϢԴ�ַ�����ʶ.
		*  (__FUNCTION__ ��������.
		* @param line - ����.
		*  @param msg - ��Ϣ��ʾ.
		*  @param msgType - ��ʾ����Ϣ����. (error,warning,info)
		*/
		void LogMessage(const std::string &source, int line, const std::string &msg,
			LogMessageType msgType = LOG_INFO) const;

		/**
		* Little more sophisticated method for logging messages.  Allows for
		*  an unlimited number of parameters in a C-style printf syntax.
		*  @param msgType - ��ʾ����Ϣ����. (error,warning,info)
		*  @param source - ��ϢԴ�ַ�����ʶ.
		*  @param line - ����.
		*  @param msg - ��Printf - style�� ��ʽ�ַ���.
		*  @note
		*      ����ַ�������󳤶�Ϊ2048���ַ�.
		*/
		void LogMessage(LogMessageType msgType, const std::string &source, int line,
			const char *msg, ...) const;

		/**
		* Little more sophisticated method for logging messages.  Allows for
		*  an unlimited number of parameters in a C-style printf syntax.
		*  @param msgType - ��ʾ����Ϣ����. (error,warning,info)
		*  @param source - ��ϢԴ�ַ�����ʶ.
		*  @param line - the line number.
		*  @param msg - std::string that has been formatted.
		*  @note
		*      ����ַ�������󳤶�Ϊ2048���ַ�.
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
		* ����־�ļ��в���һ��ˮƽ��.
		*/
		void LogHorizRule();

		/**
		* @return true if log messages of the given level will be sent to the log
		* output
		* @param msgType -  ��Ҫ��ѯ����Ϣ����.
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
		* �õ�Ψһ��log��ʵ��.
		*/
		static Log& GetInstance();

		/*
		* �õ�Ψһ���ƶ��ļ�����log��ʵ��.
		* @param name - ��־�ļ���
		*/
		static Log& GetInstance(const std::string& name);

		enum OutputStreamOptions
		{
			NO_OUTPUT =   0x00000000, ///<��־��Ϣ��������κλ���
			TO_FILE =     0x00000001,   ///<��־��Ϣ��������ļ���
			TO_CONSOLE =  0x00000002,///<��־��Ϣ���������̨
			STANDARD = TO_FILE | TO_CONSOLE ///<Ĭ������
		};

		///Configure where the Log messages get directed
		void SetOutputStreamBit(unsigned int option);

		///�õ���ǰĬ�������ѡ��.
		unsigned int GetOutputStreamBit() const;

		///������־�ļ�������.
		const std::string& GetName() const { return mName; }

		//Constructor and destructor are both protected since this is a singleton.
	protected:
		/**
		* ����־�ļ���д��html������Ϣ.
		*/
		Log(const std::string& name);

		/**
		* �ر���־�ļ�.
		*/
		~Log();

	private:
		static const std::string mDefaultName;

		LogMessageType mLevel;
		unsigned int mOutputStreamBit; ///<��ǰ�����ѡ��
		std::string mName;
	};

}

