#include <stdio.h>
#include <initguid.h>
#include <winsock2.h>
#include <ws2bth.h>
#include <strsafe.h>
#include <iostream>

using namespace std;
DEFINE_GUID(g_guidServiceClass, 0xb62c4e8d, 0x62cc, 0x404b, 0xbb, 0xbf, 0xbf, 0x3e, 0x3b, 0xbb, 0x13, 0x74);

#define CXN_SUCCESS                       0    //success
#define CXN_ERROR                         1    //error
#define CXN_INSTANCE_STRING "Bluetooth Server"
int Run(const char* path);

int  main(int argc, char *argv[])
{

	ULONG 		ulRetCode = 0;
	WSADATA		WSAData = {0};

	ulRetCode = WSAStartup(MAKEWORD(2, 2), &WSAData);

	if(ulRetCode!=0)
	{
		cout<<"WSAStartup调用失败"<<endl;
		return 0;
	}
    FILE *confile =fopen("server.cfg","rt");
	if(confile==NULL)
	{
		cout<<"无法打开配置文件"<<endl;
		return 0;
	}
	char path[256];
	memset(path,0,256);
	int numread =fread(path,1,255,confile);
	cout<<"接收文件路径:"<<path<<endl;
	fclose(confile);
    
    Run(path);


    return 0;
}

int ReciveFile(SOCKET ClientSocket,const char *path)
{
	int nLength;
	int iLengthReceived;
	char filename[256];

    memset(filename,0,256);

	//用来接收长度
	
	iLengthReceived = recv(ClientSocket,(char*)&nLength,sizeof(int),0);

	cout<<"文件名长度:"<<nLength<<endl;

    iLengthReceived =recv(ClientSocket,filename,nLength,0);

	cout<<"文件名:"<<filename<<endl;

	iLengthReceived = recv(ClientSocket,(char*)&nLength,sizeof(int),0);

	if(iLengthReceived==sizeof(int))
	{
        cout<<"文件长度为:"<<nLength<<endl;
	}
	else 
	{

        return 0;
	}
	std::string sname =path;
	sname+="\\";
	sname+=filename;

    FILE *file =fopen(sname.c_str(),"wb");
	if(!file)
	{
		cout<<"创建文件失败"<<endl;
		return 0;
	}
    
	char *buffer =new char[nLength];

	bool bContinue =true;
	int uiTotalLengthReceived =0;
	//循环接收数据
	while ( bContinue && uiTotalLengthReceived < nLength) 
	{
		
		iLengthReceived = recv(ClientSocket,
			buffer,
			(nLength - uiTotalLengthReceived),
			0);

		switch ( iLengthReceived ) {
			case 0: // socket connection has been closed gracefully
				bContinue = false;
				break;

			case SOCKET_ERROR:
				
				bContinue = false;
				break;

			default: // most cases when data is being read
				
				uiTotalLengthReceived += iLengthReceived;
				fwrite(buffer,1,iLengthReceived,file);
				break;
		}
	}



	delete []buffer;
	fclose(file);
    return 0;
}

int Run(const char* path)
{

	ULONG			ulRetCode = 0;
	int				iAddrLen = sizeof(SOCKADDR_BTH);
	int				iCxnCount = 0;
	int				iLengthReceived = 0;
	UINT			uiTotalLengthReceived;
	size_t			cbInstanceNameSize;
	char *			pszDataBuffer = NULL;
	char *			pszDataBufferIndex = NULL;
	char *			pszInstanceName = NULL;
	char			szThisComputerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD			dwLenComputerName = MAX_COMPUTERNAME_LENGTH + 1;
	SOCKET			LocalSocket = INVALID_SOCKET;
	SOCKET			ClientSocket = INVALID_SOCKET;
	WSAQUERYSET		wsaQuerySet = {0};
	SOCKADDR_BTH	SockAddrBthLocal = {0};
	LPCSADDR_INFO	lpCSAddrInfo = NULL;
	HRESULT			res;

	//
	// This fixed-size allocation can be on the stack assuming the
	// total doesn't cause a stack overflow (depends on your compiler settings)
	// However, they are shown here as dynamic to allow for easier expansion
	//
	lpCSAddrInfo = (LPCSADDR_INFO) HeapAlloc( GetProcessHeap(),
		HEAP_ZERO_MEMORY,
		sizeof(CSADDR_INFO) );
	if ( NULL == lpCSAddrInfo ) {
		printf("!ERROR! | Unable to allocate memory for CSADDR_INFO\n");
		ulRetCode = -1;
		goto CleanupAndExit;
	}

	if ( !GetComputerName((LPTSTR)szThisComputerName, &dwLenComputerName) ) {
		printf("=CRITICAL= | GetComputerName() call failed. WSAGetLastError=[%d]\n", WSAGetLastError());
		ulRetCode = CXN_ERROR;
		goto CleanupAndExit;
	}

	//
	// 建立本地监听socket
	//
	LocalSocket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
	if ( INVALID_SOCKET == LocalSocket ) {
		printf("=CRITICAL= | socket() call failed. WSAGetLastError = [%d]\n", WSAGetLastError());
		ulRetCode = CXN_ERROR;
		goto CleanupAndExit;
	}

	
	printf("*INFO* | socket() call succeeded. Socket = [0x%X]\n", LocalSocket);
	

	//
	// Setting address family to AF_BTH indicates winsock2 to use Bluetooth port
	//
	SockAddrBthLocal.addressFamily = AF_BTH;
	SockAddrBthLocal.port = BT_PORT_ANY;

	//
	// bind() associates a local address and port combination
	// with the socket just created. This is most useful when
	// the application is a server that has a well-known port
	// that clients know about in advance.
	//
	if ( SOCKET_ERROR == bind(LocalSocket,
		(struct sockaddr *) &SockAddrBthLocal,
		sizeof(SOCKADDR_BTH) ) ) {
			printf("=CRITICAL= | bind() call failed w/socket = [0x%X]. WSAGetLastError=[%d]\n", LocalSocket, WSAGetLastError());
			ulRetCode = CXN_ERROR;
			goto CleanupAndExit;
	}

	
	printf("*INFO* | bind() call succeeded\n");
	

	ulRetCode = getsockname(LocalSocket,
		(struct sockaddr *)&SockAddrBthLocal,
		&iAddrLen);
	if ( SOCKET_ERROR == ulRetCode ) {
		printf("=CRITICAL= | getsockname() call failed w/socket = [0x%X]. WSAGetLastError=[%d]\n", LocalSocket, WSAGetLastError());
		ulRetCode = CXN_ERROR;
		goto CleanupAndExit;
	}

	//
	// CSADDR_INFO
	//
	lpCSAddrInfo[0].LocalAddr.iSockaddrLength = sizeof( SOCKADDR_BTH );
	lpCSAddrInfo[0].LocalAddr.lpSockaddr = (LPSOCKADDR)&SockAddrBthLocal;
	lpCSAddrInfo[0].RemoteAddr.iSockaddrLength = sizeof( SOCKADDR_BTH );
	lpCSAddrInfo[0].RemoteAddr.lpSockaddr = (LPSOCKADDR)&SockAddrBthLocal;
	lpCSAddrInfo[0].iSocketType = SOCK_STREAM;
	lpCSAddrInfo[0].iProtocol = BTHPROTO_RFCOMM;

	//
	// If we got an address, go ahead and advertise it.
	//
	ZeroMemory(&wsaQuerySet, sizeof(WSAQUERYSET));
	wsaQuerySet.dwSize = sizeof(WSAQUERYSET);
	wsaQuerySet.lpServiceClassId = (LPGUID) &g_guidServiceClass;

	//
	// Adding a byte to the size to account for the space in the
	// format string in the sprintf call. This will have to change if converted
	// to UNICODE
	//
	res = StringCchLength((LPTSTR)szThisComputerName, sizeof(szThisComputerName), &cbInstanceNameSize);
	if( FAILED(res) ) {
		printf("-FATAL- | ComputerName specified is too large\n");
		ulRetCode = CXN_ERROR;
		goto CleanupAndExit;
	}
	cbInstanceNameSize += sizeof(CXN_INSTANCE_STRING) + 1;
	pszInstanceName = (LPSTR)HeapAlloc(GetProcessHeap(),
		HEAP_ZERO_MEMORY,
		cbInstanceNameSize);
	if ( NULL == pszInstanceName ) {
		printf("-FATAL- | HeapAlloc failed | out of memory | gle = [%d] \n", GetLastError());
		ulRetCode = CXN_ERROR;
		goto CleanupAndExit;
	}

	// StringCchPrintf((LPWSTR)pszInstanceName, cbInstanceNameSize, "%s %s", (LPCWSTR)szThisComputerName, (LPCWSTR)CXN_INSTANCE_STRING);
	StringCchPrintf((LPTSTR)pszInstanceName, cbInstanceNameSize, (LPCTSTR)"%s %s", (LPTSTR)szThisComputerName, (LPTSTR)CXN_INSTANCE_STRING);
	wsaQuerySet.lpszServiceInstanceName = (LPTSTR)pszInstanceName;
	wsaQuerySet.lpszComment = (LPTSTR)"Example Service instance registered in the directory service through RnR";
	wsaQuerySet.dwNameSpace = NS_BTH;
	wsaQuerySet.dwNumberOfCsAddrs = 1;      // Must be 1.
	wsaQuerySet.lpcsaBuffer = lpCSAddrInfo; // Req'd.

	//
	// As long as we use a blocking accept(), we will have a race
	// between advertising the service and actually being ready to
	// accept connections.  If we use non-blocking accept, advertise
	// the service after accept has been called.
	//
	if ( SOCKET_ERROR == WSASetService(&wsaQuerySet, RNRSERVICE_REGISTER, 0) ) {
		printf("=CRITICAL= | WSASetService() call failed. WSAGetLastError=[%d]\n", WSAGetLastError());
		ulRetCode = CXN_ERROR;
		goto CleanupAndExit;
	}

	
    
	//循环接收每一个客户端的连接
	while(true)
	{
		//
		// listen() call indicates winsock2 to listen on a given socket for any incoming connection.
		//
		if ( SOCKET_ERROR == listen(LocalSocket, SOMAXCONN) ) {
			printf("=CRITICAL= | listen() call failed w/socket = [0x%X]. WSAGetLastError=[%d]\n", LocalSocket, WSAGetLastError());
			ulRetCode = CXN_ERROR;
			goto CleanupAndExit;
		}

		printf("*INFO* | 监听成功\n");

		if ( INVALID_SOCKET == ( ClientSocket = accept(LocalSocket, NULL, NULL) ) ) {
			printf("=CRITICAL= | accept() call failed. WSAGetLastError=[%d]\n", WSAGetLastError());
			ulRetCode = CXN_ERROR;
			break;
		}

		//接收文件
		ReciveFile(ClientSocket,path);

        closesocket(ClientSocket);


	}

CleanupAndExit:
	if ( INVALID_SOCKET != ClientSocket ) {
		closesocket(ClientSocket);
		ClientSocket = INVALID_SOCKET;
	}

	if ( INVALID_SOCKET != LocalSocket ) {
		closesocket(LocalSocket);
		LocalSocket = INVALID_SOCKET;
	}

	if ( NULL != lpCSAddrInfo ) {
		HeapFree(GetProcessHeap(), 0, lpCSAddrInfo);
		lpCSAddrInfo = NULL;
	}
	if ( NULL != pszInstanceName ) {
		HeapFree(GetProcessHeap(), 0, pszInstanceName);
		pszInstanceName = NULL;
	}

	if ( NULL != pszDataBuffer ) {
		HeapFree(GetProcessHeap(), 0, pszDataBuffer);
		pszDataBuffer = NULL;
	}

	return(ulRetCode);
}