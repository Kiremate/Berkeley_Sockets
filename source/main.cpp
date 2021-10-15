#include <iostream>
#include "../headers/BMSocket.h"

int main() {



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
        return WSAGetLastError();
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
        return WSAGetLastError();
    }
    else
        printf("The Winsock 2.2 dll was found okay\n");


    /* The Winsock DLL is acceptable. Proceed to use it. */

    /* Add network programming using Winsock here */

    /* then call WSACleanup when done using the Winsock dll */


	SOCKET udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKET tcpSocket = socket(AF_INET, SOCK_STREAM, 0);

}