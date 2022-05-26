#pragma once
#include "Allocator.h"


NAMESPACE_BEGIN(Engine)
class Memory
{
public:
	static Void Clear(Void* buffer, SizeType byteCount)
	{
		using T1 = UInt64;
		using T2 = Byte;
		constexpr SizeType size = sizeof(T1);
		SizeType mod = byteCount % size;

		// 8 byte clear
		Set((T1*)buffer, T1(), byteCount / size);

		// 1 byte clear
		Set((T2*)buffer + (byteCount - mod), T2(), mod);
	}

	template<typename T> 
	static Void Copy(const T* from, T* to, SizeType count)
	{ 
		for (SizeType index = 0; index < count; index++)
			to[index] = from[index];
	}

	template<typename T> 
	static Bool Equal(const T* buffer0, const T* buffer1, SizeType count) 
	{ 
		for (SizeType index = 0; index < count; index++)
			if (buffer0[index] != buffer1[index])
				return false;
		
		return true;
	}

	template<typename T> 
	static Void Set(T* buffer, const T& value, SizeType count) 
	{ 
		for (SizeType index = 0; index < count; index++)
			buffer[index] = value;
	}
};
NAMESPACE_END(Engine)