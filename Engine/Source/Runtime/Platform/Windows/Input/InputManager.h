#pragma once
#include "InputState.h"
#include "Keyboard.h"
#include "Mouse.h"

#include "../../../Core/Mathematics/Vector.h"


NAMESPACE_BEGIN(Engine)
class ENGINE_API InputManager
{
public:
	InputManager();


	/**
	*	Reset input state if needed
	*/
	Void Reset();
	/**
	*	Record mouse position
	*/
	Void Update();

	/**
	*	Handling instrested messages
	*	1. Mouse event
	*	2. Keyboard event
	* 
	*	Note:
	*		This function is invoked auto by Engine
	*/
	Bool EventHandler(UInt32 message, UInt32 wordParam, UInt64 longParam);


	Bool KeyPressed(KeyCode key);
	Bool KeyReleased(KeyCode key);
	Bool ButtonPressed(MouseButton button);
	Bool ButtonReleased(MouseButton button);
	const Vector2Int& GetMousePosition();
	Int32& GetMouseScrollWheel();
private:
	static constexpr SizeType KeyCount = 256;
	static constexpr SizeType ButtonCount = 32;

	InputState keys[KeyCount];
	InputState buttons[ButtonCount];

	Vector2Int mousePosition;
	Int32 mouseScrollWheel;
};
NAMESPACE_END(Engine)