#include "InputManager.h"

#include "../Windows.h"

#include "../../../Global/RuntimeContext.h"


NAMESPACE_BEGIN(Engine)
InputManager::InputManager()
{
	Memory::Set(keys, InputState::Unknown, KeyCount);
	Memory::Set(buttons, InputState::Unknown, ButtonCount);

	mousePosition		= {};
	mouseScrollWheel	= 0;
}

Void InputManager::Reset()
{
    for (SizeType index = 0; index < KeyCount; index++)
        if ((keys[index] & InputState::Release) == InputState::Release)
            keys[index] = InputState::Unknown;

    for (SizeType index = 0; index < ButtonCount; index++)
        if ((buttons[index] & InputState::Release) == InputState::Release)
            buttons[index] = InputState::Unknown;
}

Void InputManager::Update()
{
    auto& window = runtimeContext.window;

    POINT cursor;
    GetCursorPos(&cursor);
    ScreenToClient((HWND)window.GetHandle(), &cursor);

    mousePosition[0] = cursor.x;
    mousePosition[1] = (window.GetHeight() - 1) - cursor.y;
}

Bool InputManager::EventHandler(UInt32 message, UInt32 wordParam, UInt64 longParam)
{
	Bool isHandled = true;
	switch (message)
	{
	// mouse events
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	{
		// cache index of last mouse button
		static WPARAM lastWordParam = 0;

		// mouse button released
		if (wordParam == 0x00)
			buttons[lastWordParam] |= InputState::Release;
		else
			buttons[wordParam] |= InputState::Press;

		lastWordParam = wordParam;
	}
	break;
	case WM_MOUSEWHEEL:
		mouseScrollWheel += GET_WHEEL_DELTA_WPARAM(wordParam) / WHEEL_DELTA;
		break;
	case WM_MOUSEMOVE:
		break;

	// keyboard events
	case WM_KEYDOWN:
		keys[wordParam] |= InputState::Press;
		break;
	case WM_KEYUP:
		keys[wordParam] |= InputState::Release;
		break;

	default:
		isHandled = false;
		break;
	}

	return isHandled;
}

Bool InputManager::KeyPressed(KeyCode key)
{
    return (keys[(Int32)key] & InputState::Press) == InputState::Press;
}

Bool InputManager::KeyReleased(KeyCode key)
{
    return (keys[(Int32)key] & InputState::Release) == InputState::Release;
}

Bool InputManager::ButtonPressed(MouseButton button)
{
    return (buttons[(Int32)button] & InputState::Press) == InputState::Press;
}

Bool InputManager::ButtonReleased(MouseButton button)
{
    return (buttons[(Int32)button] & InputState::Release) == InputState::Release;
}

const Vector2Int& InputManager::GetMousePosition()
{
    return mousePosition;
}

Int32& InputManager::GetMouseScrollWheel()
{
    return mouseScrollWheel;
}
NAMESPACE_END(Engine)