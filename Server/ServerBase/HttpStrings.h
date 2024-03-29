#ifndef _HTTPSTRINGS_H_
#define _HTTPSTRINGS_H_


namespace ServerBase {

//Http�еĹؼ��ֵ��ַ���
class SERVERBASE_DLL HttpStrings
{
public:
	const static char* ServerName;
	const static char* ServerPort;
	const static char* ScriptName;
	const static char* Secure;
	const static char* Http;
	const static char* Https;
	const static char* QueryString;
	const static char* RequestMethod;
	const static char* HttpAuth;
	const static char* HttpRemoteUser;
	const static char* RemoteAddr;
	const static char* HttpClientIp;
	const static char* HttpXForwardedFor;
	const static char* Unknown;
	const static char* Username;
	const static char* Password;
	const static char* PhysicalPath;
	const static char* ContentType;
	const static char* UrlEncoded;
	const static char* MultiPartForm;
	const static char* ContentLength;
	const static char* BasicAuth;
	const static char* WWWAuth;
	const static char* UnauthorizedHeader;
	const static char* Unauthorized;
	const static char* ContentTypeHeader;
	const static char* Utf8Text;
	const static char* ContentLengthHeader;
	const static char* StatusHeader;
	const static char* StatusOkHeader;
	const static char* TextPlain;
	const static char* TextHtml;
	const static char* TextXml;
	const static char* PostBoundary;
	const static char* PostName;
	const static char* PostContent;
	const static char* PostFile;
	const static char* CrLf;
	const static char* ScriptFileName;
	const static char* StatusKey;
	const static char* StatusVal200OK;
	const static char* ContentLengthKey;
	const static char* ContentTypeKey;
	const static char* WWWAuthKey;
	const static char* WWWAuthVal;
	const static wchar_t* WebConfig;
	const static wchar_t* FailedAuth1;
	const static wchar_t* FailedAuth2;
	const static wchar_t* ProductName;
	const static wchar_t* TempfileKey;
};



}

#endif