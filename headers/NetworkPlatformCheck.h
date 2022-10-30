//*THIS FILE IS USED TO INCLUDE NETWORK DEPENDENCIES DEPENDING ON THE OS*/
#pragma once
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	//define something for Windows (32-bit and 64-bit, this part is common)
	#include <WinSock2.h>
	#include <WS2tcpip.h>
	// We need to provide the symbols for the functions to the linker while linking.
	#pragma comment(lib,"WS2_32")
	#ifdef _WIN64
   //define something for Windows (64-bit only)
	#else
   //define something for Windows (32-bit only)
	#endif
#elif __APPLE__
#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR
	// iOS, tvOS, or watchOS Simulator
	#elif TARGET_OS_MACCATALYST
	// Mac's Catalyst (ports iOS API into Mac, like UIKit).
	#elif TARGET_OS_IPHONE
	// iOS, tvOS, or watchOS device
	#elif TARGET_OS_MAC
	// Other kinds of Apple platforms
	#else
	#   error "Unknown Apple platform"
	#endif
#elif __ANDROID__
// Below __linux__ check should be enough to handle Android,
// but something may be unique to Android.
	#elif __linux__
	// linux
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#elif __unix__ // all unices not caught above
	// Unix
	#elif defined(_POSIX_VERSION)
	// POSIX
	#else
	#   error "Unknown compiler"
#endif