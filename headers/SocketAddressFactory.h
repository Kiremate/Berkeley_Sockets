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
		static SocketAddressPtr CreateIPv4FromString(const std::string & inString) {
			auto pos = inString.find_last_of(':');
			std::string host, service;
			if (pos != std::string::npos) {
				host = inString.substr(0, pos);
				service = inString.substr(pos + 1);
			}
			else {
				host = inString;
				// use default port...
				service = "0";
			}
			
			addrinfo hint;
			// Initialize the hint structure to 0
			memset(&hint, 0, sizeof(hint));
			// Set the hint structure to IPv4
			hint.ai_family = AF_INET;
			
			addrinfo* result = nullptr;
			int error = getaddrinfo(host.c_str(), service.c_str(), &hint, &result);
			// If there is an error and the result is not null
			if (error != 0 && result != nullptr) {
				// we release the memory once we copied the desired sockaddr out of the linked list
				freeaddrinfo(result);
				return nullptr;
			}
			// if the address is null from the result we go for the next
			// in the linked list of addresses
			while (!result->ai_addr && result->ai_next) {
				result = result->ai_next; 
			}
			// If the address is null we release the memory and return nullptr
			if (!result->ai_addr) {
				freeaddrinfo(result);
				return nullptr;
			}
			// If the address is not null we create the Socket Address as a shared ptr
			auto toRet = std::make_shared<SocketAddress>(*result->ai_addr);
			// Release the info in result as we have it in the shared ptr
			freeaddrinfo(result);
			return toRet;
		}
	};
}
