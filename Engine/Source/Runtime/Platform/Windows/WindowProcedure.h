#pragma once
#include "../../Global/RuntimeContext.h"

#include "Windows.h"


NAMESPACE_BEGIN(Engine)
inline LRESULT CALLBACK WindowProcedure(HWND handle, UINT message, WPARAM wordParam, LPARAM longParam)
{
	Bool isHandled =
		runtimeContext.window.EventHandler(message, wordParam, longParam) ||
		runtimeContext.input.EventHandler(message, wordParam, longParam);

	if (!isHandled)
		return DefWindowProcW(handle, message, wordParam, longParam);

	return LRESULT();
}
NAMESPACE_END(Engine)