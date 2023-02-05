#include "SocketAddressFactory.h"
#include "SocketAddress.h"
#include <string>

#ifdef _WIN32
#include <WinSock2.h>
#else
#include <netdb.h>
#endif

BloodSockets::SocketAddressPtr BloodSockets::SocketAddressFactoryWin::CreateIPv4FromString(const std::string& inString)
{
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

BloodSockets::SocketAddressPtr BloodSockets::SocketAddressFactoryLinux::CreateIPv4FromString(const std::string& inString)
{
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

	// Create the sockaddr_in structure
	sockaddr_in address;
	// Zero out the structure
	memset(&address, 0, sizeof(address));
	// Set the family to AF_INET for IPv4
	address.sin_family = AF_INET;
	// Set the port in network byte order
	address.sin_port = htons(std::stoi(service));
	// Convert the host string to an IP address and store in the sockaddr_in structure
	int result = inet_pton(AF_INET, host.c_str(), &address.sin_addr);
	// If the result is not 1 (success)
	if (result != 1) {
		// Return a null pointer
		return nullptr;
	}
	// If the result is 1, create the SocketAddress object and return as a shared pointer
	return std::make_shared<SocketAddress>(reinterpret_cast<sockaddr&>(address));
}
