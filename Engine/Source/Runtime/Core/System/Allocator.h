#pragma once
#include "../Base/Type.h"


NAMESPACE_BEGIN(Engine)
class Allocator
{
public:
	/**
	*	Allocate a contiguous memory block
	* 
	*	Note:
	*		The size in bytes of allocated memory is sizeof(T) * count
	*/
	template<typename T>
	static T* Allocate(SizeType count)
	{ 
		return new T[count];
	}

	/**
	*	Release pointer point to memory block and reset it to nullptr
	*/
	template<typename T> 
	static Void Release(T*& pointer) 
	{ 
		if (pointer) 
		{
			delete[] pointer; 
			pointer = nullptr; 
		} 
	}
};
NAMESPACE_END(Engine)