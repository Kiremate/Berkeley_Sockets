#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")
typedef enum SOCKET_TYPE {IPV4 = AF_INET, IPV6 = AF_INET6, TCP = SOCK_STREAM, UPD = SOCK_DGRAM };

template <typename SOCKET_TYPE>
class BMSocket
{
	/// <summary>
/// 
/// </summary>
/// <param name="af">Address family, indicates the network layer protocol which the socket should employ.
/// Eg. IPv4, IPv6 </param>
/// <param name="type">Indicates the meaning of packets sent and received through the socket. Each
///	transport layer protocol that the socket can use has a corresponding way in which it groups and
/// uses packets.</param>
/// <param name="protocol">Indicates the specific protocol that the socket should use to send
///	data.</param>
/// <returns></returns>
/// 	AF_INET = IPv4, SOCK_STREAM =~ TCP
	/// SOCKET socket(int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);

	private:
		SOCKET mainSocket;

	public:
		BMSocket();
		~BMSocket();

		void CloseThisSocket();



};

