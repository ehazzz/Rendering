#include "Texture2D.h"

#include "../../../ThirdParty/lodepng/lodepng.h"


NAMESPACE_BEGIN(Engine)
const Texture2D Texture2D::Black = { new Pixel[1]{ Encode(ColorF_Black, PixelFormat::R8G8B8A8) }, 1, 1 };
const Texture2D Texture2D::White = { new Pixel[1]{ Encode(ColorF_Black, PixelFormat::R8G8B8A8) }, 1, 1 };


Texture2D::Texture2D(Pixel* buffer, UInt32 width, UInt32 height) : buffer(buffer), width(width), height(height)
{
}

Texture2D::~Texture2D()
{
	Allocator::Release(buffer);
}

Void Texture2D::FlipVertical()
{
	auto h2 = height / 2;
	for (auto y = 0; y < h2; y++)
		for (auto x = 0; x < width; x++)
			Swap(&buffer[width * y + x], &buffer[width * (height - 1 - y) + x]);
}

Void Texture2D::FlipHorizontal()
{
	auto w2 = width / 2;
	for (auto y = 0; y < height; y++)
		for (auto x = 0; x < w2; x++)
			Swap(&buffer[width * y + x], &buffer[width * y + (width - 1 - x)]);
}

ColorF Texture2D::Sample(const Vector2F& uv, FilterMode mode) const
{
	switch (mode)
	{
	case FilterMode::Point:
	{
		Int32 x = uv[0] * (width - 1) + 0.5f;
		Int32 y = uv[1] * (height - 1) + 0.5f;;
		return Decode(buffer[width * y + x], PixelFormat::R8G8B8A8);
	}
	default:
		return ColorF_Magenta;
	}
}

Pixel* Texture2D::GetBuffer()
{
	return buffer;
}

UInt32 Texture2D::GetWidth()
{
	return width;
}

UInt32 Texture2D::GetHeight()
{
	return height;
}

Texture2D* Texture2D::Load(const Path& path)
{
	Void* loadedImage = nullptr;
	UInt32 w, h;
	{
		auto fileBuffer = File::ReadAllBytes(path);

		lodepng_decode32((Byte**)&loadedImage, &w, &h, (Byte*)fileBuffer.GetBuffer(), fileBuffer.GetByteCount());
	}
	
	auto count = w * h;
	auto result = new Texture2D[1]{ {Allocator::Allocate<Pixel>(count), w, h} };

	// copy
	{
		auto from = (Pixel*)loadedImage;
		auto to = result->buffer;

		for (auto i = 0; i < count; i++)
#if defined(LINEAR_COLOR_SPACE)
			to[i] = Encode(
				ToLinear( Decode(from[i], PixelFormat::R8G8B8A8) ),
				PixelFormat::R8G8B8A8
			);
#else
			to[i] = from[i];
#endif //
	}
	result->FlipVertical();

	Allocator::Release(loadedImage);

	return result;
}
NAMESPACE_END(Engine)