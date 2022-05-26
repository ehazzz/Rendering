#pragma once
#include "../../../Core/Base/Micro.h"


NAMESPACE_BEGIN(Engine)
/**
*	Reference from https://docs.microsoft.com/en-us/windows/win32/learnwin32/keyboard-input#key-codes
*/
enum class KeyCode {
	Undefined = 0x00,

	BackSpace = 0x08,
	Tab = 0x09,
	Enter = 0x0D,
	Shift = 0x10,
	Ctrl = 0x11,
	CapsLock = 0x14,
	ESC = 0x1B,
	Space = 0x20,
	 
	/**
	*	Arrow keys
	*/
	LeftArrow = 0x25,
	UpArrow,
	RightArrow,
	DownArrow,

	/**
	*	0 through 9 keys
	*/
	Alpha0 = 0x30,
	Alpha1,
	Alpha2,
	Alpha3,
	Alpha4,
	Alpha5,
	Alpha6,
	Alpha7,
	Alpha8,
	Alpha9,

	/**
	*	A through Z keys
	*/
	A = 0x41,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,

	//0 through 9 keys(numbers pad)
	NumberPad0 = 0x60,
	NumberPad1,
	NumberPad2,
	NumberPad3,
	NumberPad4,
	NumberPad5,
	NumberPad6,
	NumberPad7,
	NumberPad8,
	NumberPad9,
};
NAMESPACE_END(Engine)