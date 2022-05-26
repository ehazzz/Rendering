#pragma once
#include "../../Core/System/Memory.h"
#include "../../Core/IO/Path.h"


NAMESPACE_BEGIN(Engine)
class ENGINE_API FileDialog
{
public:
	static Path Open(const WChar* filters = L"(*.*)\0*.*\0", const WChar* initDirectory = L"./", const WChar* title = L"Open File", Handle owner = nullptr);
	static Path Save(const WChar* filters = L"(*.*)\0*.*\0", const WChar* initDirectory = L"./", const WChar* title = L"Save As..", Handle owner = nullptr);
};
NAMESPACE_END(Engine)