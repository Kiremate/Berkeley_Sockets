#pragma once
#include <cstdint>
#include <memory>
#include "NetworkPlatformCheck.h"
#include "utils.h"
namespace BloodSockets {
	////// SocketAddress.h
	// This is the implementation of the SocketAddress class
	// This class is used to wrap the address of a socket
    // @author Bloodmask
	// @date 2022
	// @version 1.0
	// @license MIT
	class SocketAddress {
	public:
		// IPv4 Constructor
		SocketAddress(uint32_t inAddress, uint16_t inPort) {
			GetAsSockAddrIn()->sin_family = AF_INET;
			GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
			GetAsSockAddrIn()->sin_port = htons(inPort);
		}
		// IPv6 Constructor
		SocketAddress(IN6_ADDR inAddress, uint16_t inPort) {
			GetAsSockAddrIn6()->sin6_family = AF_INET6;
			GetAsSockAddrIn6()->sin6_addr = inAddress;
			GetAsSockAddrIn6()->sin6_port = htons(inPort);
		}
		// String constructor
		SocketAddress(PCTSTR inAddress, uint16_t inPort) {
			GetAsSockAddrIn()->sin_family = AF_INET;
			GetAsSockAddrIn()->sin_port = htons(inPort);
		#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
			InetPton(AF_INET, inAddress, &GetAsSockAddrIn()->sin_addr);
		#elif __linux__
			inet_pton(AF_INET, inAddress, &GetAsSockAddrIn()->sin_addr);
		#endif
			
		}
		// Copy Constructor
		SocketAddress(const sockaddr& inSockAddr) {
			memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));
		}
		size_t GetSize() const { return sizeof(sockaddr); }
		
	private:
		sockaddr mSockAddr;
		
		sockaddr_in* GetAsSockAddrIn() {
			return reinterpret_cast<sockaddr_in*>(&mSockAddr);
		}	
		sockaddr_in6* GetAsSockAddrIn6() {
			return reinterpret_cast<sockaddr_in6*>(&mSockAddr);
		}
	};
	// Definition of Socket address shared pointer
	typedef std::shared_ptr<SocketAddress> SocketAddressPtr;
}