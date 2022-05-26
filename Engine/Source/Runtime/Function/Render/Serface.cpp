#include "Serface.h"


NAMESPACE_BEGIN(Engine)
Serface::Serface()
{
	width			= 0;
	height			= 0;
	elementCount	= 0;
	aspect			= 1.0f;
	colorBuffer		= nullptr;
	depthBuffer		= nullptr;
	stencilBuffer	= nullptr;
}

Serface::~Serface()
{
	Allocator::Release(colorBuffer);
	Allocator::Release(depthBuffer);
	Allocator::Release(stencilBuffer);
}

Void Serface::Clear(ClearFlag flag)
{
	if ((flag & ClearFlag::Color) == ClearFlag::Color)
		for (SizeType x = 0; x < width; x++)
			for (SizeType y = 0; y < height; y++)
				colorBuffer[width * y + x] = Lerp<const ColorF&>(
						Lerp<const ColorF&>(ColorF_Yellow, ColorF_Cyan, (RealType)x / (width - 1)),
						Lerp<const ColorF&>(ColorF_Magenta, ColorF_White, (RealType)x / (width - 1)),
						(RealType)y / (height - 1)
					);

	if ((flag & ClearFlag::Depth) == ClearFlag::Depth)
		ClearDepth(FarClipPlaneZ);

	if ((flag & ClearFlag::Stencil) == ClearFlag::Stencil)
		ClearStencil(0);
}

Void Serface::ClearColor(const ColorF& color)
{
	Memory::Set(colorBuffer, color, elementCount);
}

Void Serface::ClearDepth(RealType depth)
{
	Memory::Set(depthBuffer, depth, elementCount);
}

Void Serface::ClearStencil(Byte stencil)
{
	Memory::Set(stencilBuffer, stencil, elementCount);
}

Void Serface::CopyTo(Void* Target)
{
	for (SizeType index = 0; index < elementCount; index++)
		Cast<Pixel*>(Target)[index] = Encode(colorBuffer[index], PixelFormat::B8G8R8A8);
}

Void Serface::Resize(SizeType width, SizeType height)
{
	this->width		= width;
	this->height	= height;
	elementCount	= width * height;

	if (elementCount == 0)
		return;

	aspect = (RealType)width / height;

	Allocator::Release(colorBuffer);
	Allocator::Release(depthBuffer);
	Allocator::Release(stencilBuffer);

	colorBuffer		= Allocator::Allocate<ColorF>(elementCount);
	depthBuffer		= Allocator::Allocate<RealType>(elementCount);
	stencilBuffer	= Allocator::Allocate<Byte>(elementCount);

}

Void Serface::SetPixel(Int32 x, Int32 y, const ColorF& color)
{
	colorBuffer[width * y + x] = color;
}

Void Serface::SetDepth(Int32 x, Int32 y, RealType depth)
{
	depthBuffer[width * y + x] = depth;
}

Void Serface::SetStencil(Int32 x, Int32 y, Byte stencil)
{
	stencilBuffer[width * y + x] = stencil;
}

const ColorF& Serface::GetPixel(Int32 x, Int32 y) const
{
	return colorBuffer[width * y + x];
}

const RealType& Serface::GetDepth(Int32 x, Int32 y) const
{
	return depthBuffer[width * y + x];
}

const Byte& Serface::GetStencil(Int32 x, Int32 y) const
{
	return stencilBuffer[width * y + x];
}

ColorF* Serface::GetColorBuffer()
{
	return colorBuffer;
}

RealType* Serface::GetDepthBuffer()
{
	return depthBuffer;
}

Byte* Serface::GetStencilBuffer()
{
	return stencilBuffer;
}

SizeType Serface::GetWidth() const
{
	return width;
}

SizeType Serface::GetHeight() const
{
	return height;
}

SizeType Serface::GetElementCount() const
{
	return elementCount;
}

RealType Serface::GetAspect() const
{
	return aspect;
}

const ColorF* Serface::GetColorBuffer() const
{
	return colorBuffer;
}

const RealType* Serface::GetDepthBuffer() const
{
	return depthBuffer;
}

const Byte* Serface::GetStencilBuffer() const
{
	return stencilBuffer;
}
NAMESPACE_END(Engine)