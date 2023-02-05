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
		// This constructor takes in a 32-bit integer representation of an IP address 
		// and a 16-bit integer representation of a port and creates a sockaddr_in structure 
		// with the provided information.
		SocketAddress(uint32_t inAddress, uint16_t inPort) {
			GetAsSockAddrIn()->sin_family = AF_INET;
			GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
			GetAsSockAddrIn()->sin_port = htons(inPort);
		}
		// IPv6 Constructor
		// This constructor takes in an IN6_ADDR structure representation of an IP address 
		// and a 16-bit integer representation of a port and creates a sockaddr_in6 structure 
		// with the provided information.
		SocketAddress(IN6_ADDR inAddress, uint16_t inPort) {
			GetAsSockAddrIn6()->sin6_family = AF_INET6;
			GetAsSockAddrIn6()->sin6_addr = inAddress;
			GetAsSockAddrIn6()->sin6_port = htons(inPort);
		}
		// String constructor
		// This constructor takes in a string representation of an IP address 
		// and a 16-bit integer representation of a port and creates a sockaddr_in structure 
		// with the provided information.
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
		// This constructor takes in a sockaddr structure and creates a new SocketAddress object
		// that contains the same information.
		SocketAddress(const sockaddr& inSockAddr) {
			memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));
		}
		// GetSize()
		// Returns the size of the `sockaddr` structure.
		size_t GetSize() const { return sizeof(sockaddr); }
		// Destructor
		~SocketAddress() = default;

	private:
		sockaddr mSockAddr;
		// GetAsSockAddrIn()
		// Casts the `sockaddr` structure to a `sockaddr_in` structure and returns it
		sockaddr_in* GetAsSockAddrIn() {
			return reinterpret_cast<sockaddr_in*>(&mSockAddr);
		}	
		// GetAsSockAddrIn6()
		// Casts the `sockaddr` structure to a `sockaddr_in6` structure and returns it
		sockaddr_in6* GetAsSockAddrIn6() {
			return reinterpret_cast<sockaddr_in6*>(&mSockAddr);
		}
	};
	// Definition of SocketAddress shared pointer
	// A type alias for a shared pointer of the SocketAddress class.
	typedef std::shared_ptr<SocketAddress> SocketAddressPtr;
}