#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <cstdint>
#include <memory>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")


class SocketAddress {
	public:
		SocketAddress(uint32_t inAddress, uint16_t inPort) {
			GetAsSockAddrIn()->sin_family = AF_INET;
			GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
			GetAsSockAddrIn()->sin_port = htons(inPort);
		}
		SocketAddress(const sockaddr& inSockAddr) {
			memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));
		}
		size_t GetSize() const { return sizeof(sockaddr); }


private:
	sockaddr mSockAddr;
	sockaddr_in* GetAsSockAddrIn() {
		return reinterpret_cast<sockaddr_in*>(&mSockAddr);
	}
};

typedef shared_ptr<SocketAddress> SocketAddressPtr;
