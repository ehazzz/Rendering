#pragma once
#include "../../../Core/Base/EnumClass.h"


NAMESPACE_BEGIN(Engine)
enum class InputState
{
	Unknown	= 0,
	Press	= 1 << 0,
	Release	= 1 << 1,
};
ENABLE_BIT_MASK_OPERATORS(InputState);

NAMESPACE_END(Engine)