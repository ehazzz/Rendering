#include "AsciiGlyph.h"


NAMESPACE_BEGIN(Engine)
Void AsciiGlyph::Render(Serface* serface, const Vector2Int& position, Char character, const ColorF& color)
{
	constexpr Int32 Offset = 32;

	if (character < Offset) return;

	auto mask = Masks[character - Offset];

	for (Int32 y = 0; y < Height; y++)
		for (Int32 x = 0; x < Width; x++)
			if ((mask[y] >> x) & 0x01)
			{
				auto&& row = position[0] + x;
				auto&& column = position[1] + y;

				serface->SetPixel(row, column, Blend(color, serface->GetPixel(row, column)));
			}
}

Void AsciiGlyph::Render(Serface* serface, const Vector2Int& position, const Char* text, const ColorF& color)
{
	SizeType length = 0;

	while (text[length] != 0x00)
		length++;

	// check bound
	{
		// vertical
		if (position[1] < 0 || position[1] + AsciiGlyph::Height >= serface->GetHeight())
			return;

		// horizontal
		if (position[0] < 0 || position[0] + AsciiGlyph::Width * length >= serface->GetWidth())
			return;
	}

	for (SizeType index = 0; index < length; index++)
		AsciiGlyph::Render(serface, position + Vector2Int_Right * index * AsciiGlyph::Width, text[index], color);
}
NAMESPACE_END(Engine)