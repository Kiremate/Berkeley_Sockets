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

		 virtual ~SocketAddressFactory() = default;
		 virtual SocketAddressPtr CreateIPv4FromString(const std::string& inString) = 0;
		 
	
	};
	
	class SocketAddressFactoryWin : public SocketAddressFactory {
	// CreateIPv4FromString method for Windows OS
	// This method creates a SocketAddress object using an IPv4 address and port number.
	// The address and port are passed as a string in the format "host:port".
	// @param inString: The string containing the address and port number.
	// @return The created SocketAddress object as a shared pointer.
	// @return nullptr if the address and port information is invalid.
	// Find the position of the colon character in the string
		 SocketAddressPtr CreateIPv4FromString(const std::string& inString) override;
	};
	class SocketAddressFactoryLinux : public SocketAddressFactory {
	// CreateIPv4FromString method for Linux OS
	// This method creates a SocketAddress object using an IPv4 address and port number.
	// The address and port are passed as a string in the format "host:port".
	// @param inString: The string containing the address and port number.
	// @return The created SocketAddress object as a shared pointer.
	// @return nullptr if the address and port information is invalid.
	// Find the position of the colon character in the string
		 SocketAddressPtr CreateIPv4FromString(const std::string& inString) override;
	};
	

}