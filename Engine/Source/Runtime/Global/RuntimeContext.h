#pragma once
#include "../Platform/Windows/Window.h"
#include "../Platform/Windows/Input/InputManager.h"


NAMESPACE_BEGIN(Engine)
struct RuntimeContext
{
	/**
	*	Main window of the process(app)
	*/
	Window window;
	InputManager input;
};
extern ENGINE_API RuntimeContext runtimeContext;
NAMESPACE_END(Engine)