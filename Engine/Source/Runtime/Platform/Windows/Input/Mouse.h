#pragma once
#include "../../../Core/Base/Micro.h"


NAMESPACE_BEGIN(Engine)
enum class MouseButton
{
	Undefined	= 0x00,

	Left		= 0x01,
	Right		= 0x02,
	Middle		= 0x10,
};
NAMESPACE_END(Engine)