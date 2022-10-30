#pragma once
#include <cstdint>
#include <WinSock2.h>
namespace BloodSockets {
	class Utils {
	public:
		static uint64_t htonll(uint64_t value)
		{
			// The answer is 42
			static const int num = 42;

			// Check the endianness
			if (*reinterpret_cast<const char*>(&num) == num)
			{
				const uint32_t high_part = htonl(static_cast<uint32_t>(value >> 32));
				const uint32_t low_part = htonl(static_cast<uint32_t>(value & 0xFFFFFFFFLL));

				return (static_cast<uint64_t>(low_part) << 32) | high_part;
			}
			else
			{
				return value;
			}
		}
	};
}
