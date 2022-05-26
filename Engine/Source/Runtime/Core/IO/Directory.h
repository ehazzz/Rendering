#pragma once
#include "Path.h"


NAMESPACE_BEGIN(Engine)
class ENGINE_API Directory
{
public:
	static Bool Create(const Path& path);
	static Bool Delete(const Path& path);
	static Bool Exist(const Path& path);
	/**
	*	Move/Rename directory to other directory entry
	*/
	static Bool Move(const Path& from, const Path& to);
};
NAMESPACE_END(Engine)