#pragma once
#include "Path.h"
#include "../System/Buffer.h"


NAMESPACE_BEGIN(Engine)
class ENGINE_API File
{
public:
	static Bool Delete(const Path& path);
	static Bool Exist(const Path& path);
	/**
	*	Query the size in bytes of file
	*/
	static SizeType GetSize(const Path& path);
	/**
	*	Move/Rename file to other directory entry
	*/
	static Bool Move(const Path& from, const Path& to);

	/**
	*	Read all bytes of file to memory
	*/
	static Void ReadAllBytes(Void** outputBuffer, SizeType* outputByteCount, const Path& path);
	static Buffer ReadAllBytes(const Path& path);
	/**
	*	Write all bytes of memory block to file
	*/
	static Void WriteAllBytes(const Void* buffer, SizeType byteCount, const Path& path);
	static Void WriteAllBytes(const Buffer& buffer, const Path& path);
};
NAMESPACE_END(Engine)