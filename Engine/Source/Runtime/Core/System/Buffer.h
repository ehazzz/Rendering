#pragma once
#include "Memory.h"


NAMESPACE_BEGIN(Engine)
/**
*	Representing A Contiguous Memory Block
*/
class Buffer
{
public:
	NOT_COPYABLE(Buffer);


	Buffer(SizeType allocatedByteCount = 0)
	{
		buffer = Allocator::Allocate<Byte>(allocatedByteCount);
		byteCount = allocatedByteCount;
	}

	Buffer(Void* buffer, SizeType byteCount)
		: buffer(buffer), byteCount(byteCount)
	{

	}

	Buffer(Buffer&& other)
		: buffer(other.buffer), byteCount(other.byteCount)
	{
		other.buffer = nullptr;
	}

	~Buffer()
	{
		Allocator::Release(buffer);
	}


	Void* GetBuffer()
	{
		return buffer;
	}

	const Void* GetBuffer() const
	{
		return buffer;
	}

	SizeType GetByteCount() const
	{
		return byteCount;
	}


	Buffer& operator=(Buffer&& other)
	{
		Swap(&buffer, &other.buffer);
		Swap(&byteCount, &other.byteCount);

		return *this;
	}
private:
	/**
	*	Pointer point to allocated memory block
	*/
	Void* buffer;
	/**
	*	The size in bytes of allocated memory
	*/
	SizeType byteCount;
};
NAMESPACE_END(Engine)