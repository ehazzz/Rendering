#pragma once
#include "Path.h"


NAMESPACE_BEGIN(Engine)
class FileSystem
{
public:
	using Iterator = std::filesystem::directory_iterator;
	using RecursiveIterator = std::filesystem::recursive_directory_iterator;
	
	using Entry = std::filesystem::directory_entry;
};
NAMESPACE_END(Engine)