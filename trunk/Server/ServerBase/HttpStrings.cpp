#include "stdafx.h"
#include "HttpStrings.h"

namespace ServerBase {



	const char* HttpStrings::ServerName = "SERVER_NAME";
	const char* HttpStrings::ServerPort = "SERVER_PORT";
	const char* HttpStrings::ScriptName = "SCRIPT_NAME";
	const char* HttpStrings::Secure = "HTTPS";
	const char* HttpStrings::Http = "http://";
	const char* HttpStrings::Https = "https://";
	const char* HttpStrings::QueryString = "QUERY_STRING";
	const char* HttpStrings::RequestMethod = "REQUEST_METHOD";
	const char* HttpStrings::HttpAuth = "HTTP_AUTHORIZATION";
	const char* HttpStrings::HttpRemoteUser = "REMOTE_USER";
	const char* HttpStrings::RemoteAddr = "REMOTE_ADDR";
	const char* HttpStrings::HttpClientIp = "HTTP_CLIENT_IP";
	const char* HttpStrings::HttpXForwardedFor = "HTTP_X_FORWARDED_FOR";
	const char* HttpStrings::Unknown = "unknown";
	const char* HttpStrings::Username = "USERNAME";
	const char* HttpStrings::Password = "PASSWORD";
	const char* HttpStrings::PhysicalPath = "APPL_PHYSICAL_PATH";
	const char* HttpStrings::ContentType = "CONTENT_TYPE";
	const char* HttpStrings::UrlEncoded = "application/x-www-form-urlencoded";
	const char* HttpStrings::MultiPartForm = "multipart/form-data";
	const char* HttpStrings::ContentLength = "CONTENT_LENGTH";
	const char* HttpStrings::BasicAuth = "Basic ";
	const char* HttpStrings::WWWAuth = "WWW-Authenticate: Basic realm=\"%s\"\r\n";
	const char* HttpStrings::UnauthorizedHeader = "Status: 401 Unauthorized\r\n";
	const char* HttpStrings::Unauthorized = "401 Unauthorized";
	const char* HttpStrings::ContentTypeHeader = "Content-type: %s%s\r\n";
	const char* HttpStrings::Utf8Text = "; charset=utf-8";
	const char* HttpStrings::ContentLengthHeader = "Content-Length: %d\r\n";
	const char* HttpStrings::StatusHeader = "Status: %d %s\r\n";
	const char* HttpStrings::StatusOkHeader = "Status: 200 OK\r\n";
	const char* HttpStrings::TextPlain = "text/plain";
	const char* HttpStrings::TextHtml = "text/html";
	const char* HttpStrings::TextXml = "text/xml";
	const char* HttpStrings::PostBoundary = "boundary=";
	const char* HttpStrings::PostName = "name=\"";
	const char* HttpStrings::PostContent = "Content-Type: ";
	const char* HttpStrings::PostFile = "filename=";
	const char* HttpStrings::CrLf = "\r\n";
	const char* HttpStrings::ScriptFileName = "SCRIPT_FILENAME";
	const char* HttpStrings::StatusKey = "Status";
	const char* HttpStrings::StatusVal200OK = "200 OK";
	const char* HttpStrings::ContentLengthKey = "Content-Length";
	const char* HttpStrings::ContentTypeKey = "Content-Type";
	const char* HttpStrings::WWWAuthKey = "WWW-Authenticate";
	const char* HttpStrings::WWWAuthVal = "Basic realm=\"%s\"";


	const wchar_t* HttpStrings::WebConfig = L"../webconfig.ini";
	const wchar_t* HttpStrings::FailedAuth1 = L"MgAuthenticationFailedException";
	const wchar_t* HttpStrings::FailedAuth2 = L"MgUnauthorizedAccessException";
	const wchar_t* HttpStrings::ProductName = L"MapGuide";

	// used to indicate the creation of temporary files as part of a request
	const wchar_t* HttpStrings::TempfileKey = L"tempfile";



}