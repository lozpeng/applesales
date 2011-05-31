#ifndef _STRING_OPERATE
#define _STRING_OPERATE

#include "stdafx.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

namespace SYSTEM
{
	std::string SYSTEM_DLL trimLeft(const std::string& str);
	std::string SYSTEM_DLL trimRight(const std::string& str);
	std::string SYSTEM_DLL trim(const std::string& str);

	std::string SYSTEM_DLL toLower(const std::string& str);
	std::string SYSTEM_DLL toUpper(const std::string& str);

	bool SYSTEM_DLL startsWith(const std::string& str, const std::string& substr);
	bool SYSTEM_DLL endsWith(const std::string& str, const std::string& substr);
	bool SYSTEM_DLL equalsIgnoreCase(const std::string& str1, const std::string& str2);

	template<class T> T SYSTEM_DLL parseString(const std::string& str);
	template<class T> T SYSTEM_DLL parseHexString(const std::string& str);
	template<bool> bool SYSTEM_DLL parseString(const std::string& str);

	template<class T> std::string SYSTEM_DLL toString(const T& value);
	template<class T> std::string SYSTEM_DLL toHexString(const T& value, int width = 0);
	std::string SYSTEM_DLL toString(const bool& value);

	std::vector<std::string> SYSTEM_DLL split(const std::string& str, const std::string& delimiters);

	class Tokenizer
    {
    public:
        static const std::string DEFAULT_DELIMITERS;
        Tokenizer(const std::string& str);
        Tokenizer(const std::string& str, const std::string& delimiters);

        bool nextToken();
        bool nextToken(const std::string& delimiters);
        const std::string getToken() const;

        /**
        * to reset the tokenizer. After reset it, the tokenizer can get
        * the tokens from the first token.
        */
        void reset();

    protected:
        size_t m_Offset;
        const std::string m_String;
        std::string m_Token;
        std::string m_Delimiters;
    };

}

// implementation of template functions
namespace SYSTEM {

    template<class T> T parseString(const std::string& str) {
        T value;
        std::istringstream iss(str);
        iss >> value;
        return value;
    }

    template<class T> T parseHexString(const std::string& str) {
        T value;
        std::istringstream iss(str);
        iss >> hex >> value;
        return value;
    }

    template<class T> std::string toString(const T& value) {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }

    template<class T> std::string toHexString(const T& value, int width) {
        std::ostringstream oss;
        oss << hex;
        if (width > 0) {
            oss << setw(width) << setfill('0');
        }
        oss << value;
        return oss.str();
    }

}

#endif