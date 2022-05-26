#pragma once
#include "../Base/Type.h"


NAMESPACE_BEGIN(Engine)
class Character
{
public:
#if !defined(PLATFORM_WINDOWS)
	static constexpr Char NewLine = '\n';
	static constexpr Char PreferedPathSeparator = '/';
#else
	static constexpr UInt16 NewLine = '\r\n';
	static constexpr Char PreferedPathSeparator = '\\';
#endif
	static constexpr Char CarriageReturn = '\r';
	static constexpr Char Space = ' ';
	static constexpr Char Dot = '.';

	static constexpr Int32 LowerToUpperCaseOffset = -32;
	static constexpr Int32 UpperToLowerCaseOffset = 32;


	static Bool IsAsciiCode(UInt32 codePoint) { return codePoint <= 127; }
	static Bool IsNumber(Char character) { return character >= '0' && character <= '9'; }
	static Bool IsLetter(Char character) { return character >= 'A' && character <= 'z'; }
	static Bool IsLowerCaseLetter(Char character) { return character >= 'a' && character <= 'z'; }
	static Bool IsUpperCaseLetter(Char character) { return character >= 'A' && character <= 'Z'; }
};
NAMESPACE_END(Engine)