#include "StdAfx.h"
#include "BlueTooth.h"
#include <stdio.h>
#include <initguid.h>
#include <winsock2.h>
#include <ws2bth.h>
#include <strsafe.h>

namespace BlueToothComm
{

#define CXN_SUCCESS                       0    //success
#define CXN_ERROR                         1    //error

DEFINE_GUID(g_guidServiceClass, 0xb62c4e8d, 0x62cc, 0x404b, 0xbb, 0xbf, 0xbf, 0x3e, 0x3b, 0xbb, 0x13, 0x74);

CBlueTooth::CBlueTooth(void):m_bConnected(false)
{
	m_socket =INVALID_SOCKET;

	WSADATA		WSAData = {0};
	WSAStartup(MAKEWORD(2, 2), &WSAData);
}

CBlueTooth::~CBlueTooth(void)
{
	if(m_bConnected)
	{
		Close();
	}

}

ULONG NameToBthAddr(const char * pszRemoteName, BTH_ADDR * pRemoteBtAddr)
{
	INT				iResult = 0, iRetryCount = 0;
	BOOL			bContinueLookup = FALSE, bRemoteDeviceFound = FALSE;
	ULONG			ulFlags = 0, ulPQSSize = sizeof(WSAQUERYSET);
	
	HANDLE			hLookup = 0;
	PWSAQUERYSET	pWSAQuerySet = NULL;

	//remoteName is null then goto CleanupAndExit
	if ( ( NULL == pszRemoteName ) || ( NULL == pRemoteBtAddr ) ) {
		goto CleanupAndExit;
	}
	//has defined it then allocate the memory
	pWSAQuerySet = (PWSAQUERYSET) HeapAlloc(GetProcessHeap(),
		HEAP_ZERO_MEMORY,
		ulPQSSize);
	//Unable to allocate memory
	if ( NULL == pWSAQuerySet ) {
		printf("!ERROR! | Unable to allocate memory for WSAQUERYSET\n");
		goto CleanupAndExit;
	}

	//
	// Search for the device with the correct name
	//
	for ( iRetryCount = 0;
		!bRemoteDeviceFound && (iRetryCount < 2);
		iRetryCount++ ) {
			//
			// WSALookupService is used for both service search and device inquiry
			// LUP_CONTAINERS is the flag which signals that we're doing a device inquiry.
			//
			//#define LUP_CONTAINERS 0x0002
			ulFlags = LUP_CONTAINERS;

			//
			// Friendly device name (if available) will be returned in lpszServiceInstanceName
			//
			//#define LUP_RETURN_NAME 0x0010
			ulFlags |= LUP_RETURN_NAME;

			//
			// BTH_ADDR will be returned in lpcsaBuffer member of WSAQUERYSET
			//
			//#define LUP_RETURN_ADDR 0x0100
			ulFlags |= LUP_RETURN_ADDR;

			if ( 0 == iRetryCount ) {
				printf("*INFO* | Inquiring device from cache...\n");
			} else {
				//
				// Flush the device cache for all inquiries, except for the first inquiry
				//
				// By setting LUP_FLUSHCACHE flag, we're asking the lookup service to do
				// a fresh lookup instead of pulling the information from device cache.
				//
				//#define LUP_FLUSHCACHE 0x1000
				ulFlags |= LUP_FLUSHCACHE;

				//
				// Pause for some time before all the inquiries after the first inquiry
				//
				// Remote Name requests will arrive after device inquiry has
				// completed.  Without a window to receive IN_RANGE notifications,
				// we don't have a direct mechanism to determine when remote
				// name requests have completed.
				//
				printf("*INFO* | Unable to find device.  Waiting for %d seconds before re-inquiry...\n", 2);
				//等待2秒
				Sleep(2 * 1000);

				printf("*INFO* | Inquiring device ...\n");
			}

			//
			// Start the lookup service
			//
			iResult = 0;
			hLookup = 0;
			bContinueLookup = FALSE;
			//The ZeroMemory macro fills a block of memory with zeros.
			ZeroMemory(pWSAQuerySet, ulPQSSize);
			/*
			void ZeroMemory(
			PVOID Destination,
			SIZE_T Length
			);
			*/
			pWSAQuerySet->dwNameSpace = NS_BTH;
			pWSAQuerySet->dwSize = sizeof(WSAQUERYSET);
			//if exit then return NO_ERROR and then bContinueLookup
			iResult = WSALookupServiceBegin(pWSAQuerySet, ulFlags, &hLookup);
			/*
			The WSALookupServiceBegin function initiates a client query that is constrained by
			the information contained within a WSAQUERYSET structure. WSALookupServiceBegin only
			returns a handle, which should be used by subsequent calls to WSALookupServiceNext to 
			get the actual results.
			// ULONG is equal to DWORD both are unsigned long 
			INT WSALookupServiceBegin(
			LPWSAQUERYSET lpqsRestrictions,
			DWORD dwControlFlags,
			LPHANDLE lphLookup
			);

			*/       


			if ( (NO_ERROR == iResult) && (NULL != hLookup) ) {
				bContinueLookup = TRUE;
			} else if ( 0 < iRetryCount ) {
				printf("=CRITICAL= | WSALookupServiceBegin() failed with error code %d, WSALastError = %d\n", iResult, WSAGetLastError());
				goto CleanupAndExit;
			}

			while ( bContinueLookup ) {
				//
				// Get information about next bluetooth device
				//
				// Note you may pass the same WSAQUERYSET from LookupBegin
				// as long as you don't need to modify any of the pointer
				// members of the structure, etc.
				//
				// ZeroMemory(pWSAQuerySet, ulPQSSize);
				// pWSAQuerySet->dwNameSpace = NS_BTH;
				// pWSAQuerySet->dwSize = sizeof(WSAQUERYSET);
				if ( NO_ERROR == WSALookupServiceNext(hLookup,
					ulFlags,
					&ulPQSSize,
					pWSAQuerySet) ) {
						//
						// Since we're a non-unicode application, the remote
						// name in lpszServiceInstanceName will have been converted
						// from CP_UTF8 to CP_ACP, this may cause the name match
						// to fail unexpectedly.  If the app is to handle this,
						// the app needs to be unicode.
						//
						if ( ( pWSAQuerySet->lpszServiceInstanceName != NULL ) &&
							( 0==_stricmp((char *)pWSAQuerySet->lpszServiceInstanceName, pszRemoteName) ) ) {
								// strcmp lpszServiceInstanceName lpszServiceInstanceName
								// Found a remote bluetooth device with matching name.
								// Get the address of the device and exit the lookup.
								//
								CopyMemory(pRemoteBtAddr,
									&((PSOCKADDR_BTH) pWSAQuerySet->lpcsaBuffer->RemoteAddr.lpSockaddr)->btAddr,
									sizeof(*pRemoteBtAddr));
								bRemoteDeviceFound = TRUE;
								bContinueLookup = FALSE;
						}
				} else {
					//#define WSA_E_NO_MORE 10110L
					if ( WSA_E_NO_MORE == ( iResult = WSAGetLastError() ) ) { //No more data
						//
						// No more devices found.  Exit the lookup.
						//
						bContinueLookup = FALSE;
					} else if ( WSAEFAULT == iResult ) {
						//
						// The buffer for QUERYSET was insufficient.
						// In such case 3rd parameter "ulPQSSize" of function "WSALookupServiceNext()" receives
						// the required size.  So we can use this parameter to reallocate memory for QUERYSET.
						//
						HeapFree(GetProcessHeap(), 0, pWSAQuerySet);
						pWSAQuerySet = (PWSAQUERYSET) HeapAlloc(GetProcessHeap(),
							HEAP_ZERO_MEMORY,
							ulPQSSize);
						if ( NULL == pWSAQuerySet ) {
							printf("!ERROR! | Unable to allocate memory for WSAQERYSET\n");
							bContinueLookup = FALSE;
						}
					} else {
						printf("=CRITICAL= | WSALookupServiceNext() failed with error code %d\n", iResult);
						bContinueLookup = FALSE;
					}
				}
			}

			//
			// End the lookup service
			//
			WSALookupServiceEnd(hLookup);
	}

CleanupAndExit:
	if ( NULL != pWSAQuerySet ) {
		HeapFree(GetProcessHeap(), 0, pWSAQuerySet);
		pWSAQuerySet = NULL;
	}

	if ( bRemoteDeviceFound ) {
		return(CXN_SUCCESS);
	} else {
		return(CXN_ERROR);
	}
}

bool CBlueTooth::Connect(const char *remote)
{
    if(m_bConnected)
	{
		Close();
		m_bConnected =false;
	}

	int iMaxCxnCycles =2;

	ULONGLONG 	ululRemoteBthAddr = 0;
    
	//获取设备地址
	unsigned long ulRetCode = NameToBthAddr(remote, (BTH_ADDR *) &ululRemoteBthAddr);
	if ( CXN_SUCCESS != ulRetCode ) 
	{
		return false;
	}

	int				iCxnCount = 0;
	
	
	SOCKADDR_BTH	SockAddrBthServer = {0};
	HRESULT			res;

	
	//
	// Setting address family to AF_BTH indicates winsock2 to use Bluetooth sockets
	// Port should be set to 0 if ServiceClassId is spesified.
	//
	SockAddrBthServer.addressFamily = AF_BTH;
	SockAddrBthServer.btAddr = (BTH_ADDR) ululRemoteBthAddr;
	SockAddrBthServer.serviceClassId = g_guidServiceClass;
	SockAddrBthServer.port = 0;


	//
	// Run the connection/data-transfer for user specified number of cycles
	//
	for ( iCxnCount = 0;
		(0 == ulRetCode) && (iCxnCount < iMaxCxnCycles || iMaxCxnCycles == 0);
		iCxnCount++ ) 
	{

		

			//
			// Open a bluetooth socket using RFCOMM protocol
			//
			m_socket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
			if ( INVALID_SOCKET == m_socket ) 
			{
				return false;

			}

			
			int retcode =connect(m_socket,
				(struct sockaddr *) &SockAddrBthServer,
				sizeof(SOCKADDR_BTH));
			if ( 0 == retcode ) 
			{
					
				//连接成功
				break;
			}
			else
			{
				closesocket(m_socket);
				m_socket =INVALID_SOCKET;
				return false;
			}


	}	

	m_bConnected =true;
    
	return true;
}

bool CBlueTooth::SendFile(const char *filename)
{
	if(!m_bConnected)
	{
		return false;
	}
	if(m_socket==INVALID_SOCKET)
	{
		return false;
	}
	std::string str ="abcdefg";
	char *pszData =new char[str.length()+1];
	strcpy(pszData,str.c_str());
	pszData[str.length()] =0;

	if ( SOCKET_ERROR == send(m_socket,
		pszData,
		str.length()+1,
		0) ) 
	{
			return false;
	}
	return true;
}

void CBlueTooth::Close()
{
	if(m_socket!=INVALID_SOCKET)
	{
		closesocket(m_socket);
		m_socket =INVALID_SOCKET;
	}
	m_bConnected =false;
}



}
