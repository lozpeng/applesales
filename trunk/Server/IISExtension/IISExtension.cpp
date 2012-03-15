// IISExtension.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "httpext.h"
#include <string>
#include <io.h>


BOOL WINAPI GetExtensionVersion(HSE_VERSION_INFO *pVer)
{
	pVer->dwExtensionVersion = HSE_VERSION;
	strncpy(pVer->lpszExtensionDesc, "Server IIS Extension", HSE_MAX_EXT_DLL_NAME_LEN);  // NOXLATE

	return TRUE;
}

void WriteContent(EXTENSION_CONTROL_BLOCK *pECB)
{
	//std::string header ="<html>\r\n<body>\r\n";

	//DWORD dwsize =header.size();
	//pECB->WriteClient(pECB->ConnID,(LPVOID)header.c_str(),&dwsize,0);
	//   
	////写入内容
	//std::string str ="<p>aaa</p>";
	//dwsize =str.size();
	//pECB->WriteClient(pECB->ConnID,(LPVOID)str.c_str(),&dwsize,0);

	//std::string end ="</body>\r\n</html>";
	//dwsize =end.size();
	//pECB->WriteClient(pECB->ConnID,(LPVOID)end.c_str(),&dwsize,0);

	std::string sResponseHeader="Status: 200 OK\r\n";
	sResponseHeader+="Content-type: image/jpeg\r\n"; 
	sResponseHeader+="Content-Length: ";
	char strlen[100];
	FILE *file =fopen("f:\\1.jpg","rb");
	if(!file)
	{
		return;
	}
	/*int length =filelength(fileno(file));*/
	char buffer[4096];
	int length =0;
	int nBytes = fread(buffer,1,4096,file);
	while (nBytes > 0)
	{
		length+=nBytes;

		nBytes = fread(buffer,1,4096,file);

	}

	sprintf(strlen,"%d\r\n",length);
	sResponseHeader+=strlen;
	sResponseHeader+="\r\n";
	DWORD dwUnused =sResponseHeader.size();
	//写入响应头
	pECB->ServerSupportFunction(pECB->ConnID, HSE_REQ_SEND_RESPONSE_HEADER, NULL, &dwUnused, (LPDWORD)sResponseHeader.c_str());

	fseek(file,0,SEEK_SET);
	nBytes = fread(buffer,1,4096,file);
	DWORD dwSize;
	while (nBytes > 0)
	{
		dwSize = nBytes;
		pECB->WriteClient(pECB->ConnID, buffer, &dwSize, 0);
		memset(buffer,0,4096);
		nBytes = fread(buffer,1,4096,file);

	}
	fclose(file);

}

void PostRequest(EXTENSION_CONTROL_BLOCK *pECB)
{ 
	
	//std::string sResponseHeader="Status: 200 OK\r\n";
	//sResponseHeader+="Content-type: image/jpeg\r\n"; 
	//sResponseHeader+="Content-Length: ";
	//char strlen[100];

	//
	//unsigned char buffer[4096];
	//int length =pReader->GetLength();
	//sprintf(strlen,"%d\r\n",length);
	//sResponseHeader+=strlen;
	//sResponseHeader+="\r\n";
	//DWORD dwUnused =sResponseHeader.size();
	////写入响应头
	//pECB->ServerSupportFunction(pECB->ConnID, HSE_REQ_SEND_RESPONSE_HEADER, NULL, &dwUnused, (LPDWORD)sResponseHeader.c_str());

	//DWORD dwSize;
	//int nBytes = pReader->Read(buffer,4096);
	//while (nBytes > 0)
	//{s


	//	dwSize = nBytes;
	//	pECB->WriteClient(pECB->ConnID, buffer, &dwSize, 0);
	//	memset(buffer,0,4096);
	//	nBytes = pReader->Read(buffer,4096);

	//}



}

DWORD WINAPI HttpExtensionProc(EXTENSION_CONTROL_BLOCK *pECB)
{
	
	//DWORD size = 1024;
	//char serverName[1024];
	//BOOL bServerName = pECB->GetServerVariable(pECB->ConnID, (LPSTR)HttpStrings::ServerName, serverName, &size);

	//size = 1024;
	//char serverPort[1024];
	//BOOL bServerPort = pECB->GetServerVariable(pECB->ConnID, (LPSTR)HttpStrings::ServerPort, serverPort, &size);

	//size = 1024;
	//char scriptName[1024];
	//BOOL bScriptName = pECB->GetServerVariable(pECB->ConnID, (LPSTR)HttpStrings::ScriptName, scriptName, &size);

	//size = 1024;
	//char remoteAddr[1024];
	//BOOL bRemoteAddr = pECB->GetServerVariable(pECB->ConnID, (LPSTR)HttpStrings::RemoteAddr, remoteAddr, &size);

	//size = 1024;
	//char httpClientIp[1024];
	//BOOL bHttpClientIp = pECB->GetServerVariable(pECB->ConnID, (LPSTR)HttpStrings::HttpClientIp, httpClientIp, &size);

	//size = 1024;
	//char httpXFF[1024];
	//BOOL bHttpXFF = pECB->GetServerVariable(pECB->ConnID, (LPSTR)HttpStrings::HttpXForwardedFor, httpXFF, &size);

	//size = 1024;
	//char secure[1024];
	//BOOL bSecure = pECB->GetServerVariable(pECB->ConnID, (LPSTR)HttpStrings::Secure, secure, &size);

	//bool isSecure = (bSecure && secure != NULL && !stricmp(secure, "on"));  // NOXLATE

	//std::string url = isSecure? HttpStrings::Https : HttpStrings::Http;
	//if (bServerName && bServerPort && bScriptName
	//	&& NULL != serverName && NULL != serverPort && NULL != scriptName)
	//{
	//	url.append(serverName);
	//	url += ':';
	//	url.append(serverPort);
	//	url.append(scriptName);
	//}
	////形成一个完整的地址,如:http://192.168.10.10:80/webmap/webmap.fcgi
	//std::wstring wUrl = Util::MultiByteToWideChar(url);

	//////解析http请求以及参数
	//HttpHandler::CHttpRequestPtr request = new CHttpRequest(wUrl);
	//CHttpRequestParamPtr params = request->GetRequestParam();

	//// Parse inputs GET/POST
	//char* query = pECB->lpszQueryString;
	//char* requestMethod = pECB->lpszMethod;

	//if (NULL != requestMethod && NULL != strstr(requestMethod, "POST"))  // NOXLATE
	//{

	//	/*	IsapiPostParser postParser(pECB);
	//	postParser.Parse(params);*/
	//}
	//else if (NULL != query && strlen(query) > 0)
	//{
	//	//目前只考虑Get方法,请求字符类似于:service=WMS&version=1.1.0&request=GetMap&layers=tiger:poly_landmarks&styles=&bbox=-74.047185,40.679648,-
	//	//73.90782,40.882078&width=352&height=512&srs=EPSG:4326&format=application/openlayers

	//	MapAgentGetParser::Parse(query, params.get());

	//}

	////如果请求的参数里没有clientip,则把客户端地址加入到参数列表中
	//if (!params->ContainsParameter(L"CLIENTIP")) 
	//{
	//	//if (bHttpClientIp && NULL != httpClientIp && strlen(httpClientIp) > 0
	//	//	&& _stricmp(httpClientIp, MapAgentStrings::Unknown) != 0)
	//	//{
	//	//	STRING wHttpClientIp = MgUtil::MultiByteToWideChar(httpClientIp);
	//	//	params->AddParameter(L"CLIENTIP", wHttpClientIp); // NOXLATE
	//	//}
	//	//else if (bHttpXFF && NULL != httpXFF && strlen(httpXFF) > 0
	//	//	&& _stricmp(httpXFF, MapAgentStrings::Unknown) != 0)
	//	//{
	//	//	STRING wHttpXFF = MgUtil::MultiByteToWideChar(httpXFF);
	//	//	params->AddParameter(L"CLIENTIP", wHttpXFF); // NOXLATE
	//	//}
	//	//else if (bRemoteAddr && NULL != remoteAddr && strlen(remoteAddr) > 0)
	//	//{
	//	//	STRING wRemoteAddr = MgUtil::MultiByteToWideChar(remoteAddr);
	//	//	params->AddParameter(L"CLIENTIP", wRemoteAddr); // NOXLATE
	//	//}
	//}

	//// Check for HTTP Basic Auth header
	//size = 1024;
	//char auth[1024];
	//BOOL bAuth = pECB->GetServerVariable(pECB->ConnID, (LPSTR)HttpStrings::HttpAuth, auth, &size);
	//bool gotAuth = bAuth && MapAgentCommon::ParseAuth(auth, params.get());

	//if (!gotAuth)
	//{
	//	// And check for a REMOTE_USER remapped header
	//	size = 1024;
	//	pECB->GetServerVariable(pECB->ConnID, (LPSTR)HttpStrings::HttpRemoteUser, auth, &size);
	//	gotAuth = MapAgentCommon::ParseAuth(auth, params.get());
	//}


	////IsapiResponseHandler responseHandler(pECB);

	//// Check to be sure that we have some kind of credentials before continuing.  Either
	//// username/password or sessionid.
	//bool bValid = params->ContainsParameter(HttpResourceStrings::reqSession);
	//// Strike two: no session? how about a username?
	//if (!bValid)
	//	bValid = params->ContainsParameter(HttpResourceStrings::reqUsername);
	//// Strike three: no username either? How about if it's an XML POST
	//if (!bValid)
	//	//bValid = params->GetXmlPostData().length() != 0;

	//	if (!bValid)
	//	{
	//		// Invalid authentication information is not fatal, we should continue.
	//		//responseHandler.RequestAuth();

	//		// clean up any temporary files we created
	//		MapAgentCommon::DeleteTempFiles(params.get());

	//		return HSE_STATUS_SUCCESS;
	//	}

	//	//Ptr<MgHttpResponse> response = request->Execute();

	//	// NOTE: temporary files are deleted when we execute the request

	//	//responseHandler.SendResponse(response);





		return HSE_STATUS_SUCCESS;
}


BOOL WINAPI TerminateExtension(DWORD dwFlags)
{
	
	return TRUE;
}