#pragma once
#include <string>
#include "SocketAddress.h"
namespace BloodSockets{
	////// SocketAddressFactory.h
	// This is the implementation of the SocketAddressFactory class
	// This class is used to create SocketAddress objects
	// @author Bloodmask
	// @date 2022
	// @version 1.0
	// @license MIT
	class SocketAddressFactory {
	public:
		// CreateIPv4FromString method
		// This method creates a SocketAddress object using an IPv4 address and port number.
		// The address and port are passed as a string in the format "host:port".
		// @param inString: The string containing the address and port number.
		// @return The created SocketAddress object as a shared pointer.
		// @return nullptr if the address and port information is invalid.
		static SocketAddressPtr CreateIPv4FromString(const std::string & inString) {
			// Find the position of the colon character in the string
			auto pos = inString.find_last_of(':');
			std::string host, service;
			if (pos != std::string::npos) {
				// If the colon is found, the string is split into host and service strings
				host = inString.substr(0, pos);
				service = inString.substr(pos + 1);
			}
			else {
				// If the colon is not found, the whole string is treated as the host
				host = inString;
				// use default port...
				service = "0";
			}
			// Initialize the addrinfo structure
			addrinfo hint;
			// Zero out the hint structure
			memset(&hint, 0, sizeof(hint));
			// Set the hint structure to IPv4
			hint.ai_family = AF_INET;
			
			// Result address information
			addrinfo* result = nullptr;
			// Call the getaddrinfo function to get the address information from the host and service strings
			int error = getaddrinfo(host.c_str(), service.c_str(), &hint, &result);
			// If there is an error and the result is not null
			if (error != 0 && result != nullptr) {
				// Free the memory once the desired sockaddr has been copied out of the linked list
				freeaddrinfo(result);
				return nullptr;
			}
			
			// If the result address is still null, free the memory and return nullptr
			while (!result->ai_addr && result->ai_next) {
				result = result->ai_next; 
			}
			// If the address is null we release the memory and return nullptr
			if (!result->ai_addr) {
				// Free the memory used by the result
				freeaddrinfo(result);
				return nullptr;
			}
			// If the address is not null we create the Socket Address as a shared ptr
			auto toRet = std::make_shared<SocketAddress>(*result->ai_addr);
			// Release the info in result as we have it in the shared ptr
			freeaddrinfo(result);
			// Return the created SocketAddress object as a shared pointer.
			return toRet;
		}
	};
}
