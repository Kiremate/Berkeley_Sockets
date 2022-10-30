#include <iostream>
#include "../headers/macros.h"
#include "../headers/SocketAddressFactory.h"
using namespace std;

int main() {
	// This is common in all platforms
	sockaddr_in myAddress;
	// We initialize all to zero to avoid null errors in other platforms
	memset(myAddress.sin_zero, 0, sizeof(myAddress.sin_zero));
	// 192.168.1.129
	myAddress.sin_family = AF_INET;
	// When setting the port and the TCP/IP Suite and the host may use
	// different standards for the ordering of bytes in multi-byte
	// numeric values. The htons() function converts the unsigned short
	// integer hostshort from host byte order to network byte order.
	myAddress.sin_port = htons(8080);
	myAddress.sin_addr.S_un.S_un_b.s_b1 = 192;
	myAddress.sin_addr.S_un.S_un_b.s_b2 = 168;
	myAddress.sin_addr.S_un.S_un_b.s_b3 = 1;
	myAddress.sin_addr.S_un.S_un_b.s_b4 = 129;
	
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	// Eg How to Initialize a Socket
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		/* Tell the user that we could not find a usable */
		/* Winsock DLL.                                  */
		printf("WSAStartup failed with error: %d\n", err);
		return 1;
	}
	/* Confirm that the WinSock DLL supports 2.2.*/
	/* Note that if the DLL supports versions greater    */
	/* than 2.2 in addition to 2.2, it will still return */
	/* 2.2 in wVersion since that is the version we      */
	/* requested.                                        */

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();
		return 1;
	}
	else
		printf("The Winsock 2.2 dll was found okay\n");
	/* The Winsock DLL is acceptable. Proceed to use it. */
	
	///* Add network programming using Winsock here */
	//BloodSockets::SocketAddressPtr bloodBerryConnectionSocket = BloodSockets::SocketAddressFactory::CreateIPv4FromString(
	//	"192.168.1.129:0"
	//);

	/* then call WSACleanup when done using the Winsock dll */
	WSACleanup(); // Shuts down the library
	#endif
		

	
	
	return 0;

}