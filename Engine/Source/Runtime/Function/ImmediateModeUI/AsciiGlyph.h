#pragma once
#include "../Render/Serface.h"


NAMESPACE_BEGIN(Engine)
class ENGINE_API AsciiGlyph {
public:
	static constexpr Int32 Count = 95;
	static constexpr Int32 Width = 8;
	static constexpr Int32 Height = 16;
	static constexpr Byte Masks[Count][Height] = {
		#include "AsciiLibrary(Converted).inline"
	};


	static Void Render(Serface* serface, const Vector2Int& position, Char character, const ColorF& color);
	static Void Render(Serface* serface, const Vector2Int& position, const Char* text, const ColorF& color = ColorF_White * 0.1f);
};
NAMESPACE_END(Engine)