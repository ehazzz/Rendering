#pragma once
#include "../../Core/System/Allocator.h"
#include "../../Core/Mathematics/Color.h"

#include "../../Core/Base/EnumClass.h"


NAMESPACE_BEGIN(Engine)
/* Coordinate System
*	y axis
*	^ [0, height-1]
*	|
*	|
*	|
*	|
*	|
*	+---------------> x axis
*	[0, 0]			[width - 1, 0]
*/


enum class ClearFlag
{
	Disable,

	Color			= 1 << 0,
	Depth			= 1 << 1,
	Stencil			= 1 << 2,
	ColorDepth		= Color | Depth,
	ColorStencil	= Color | Stencil,
	DepthStencil	= Depth | Stencil,
	All				= Color | Depth | Stencil,
};
ENABLE_BIT_MASK_OPERATORS(ClearFlag);


class ENGINE_API Serface
{
public:
	NOT_COPYABLE(Serface);


	/**
	*	Depth value(0.0) of near clip plane
	*/
	static constexpr RealType NearClipPlaneZ = 0.0f;
	/**
	*	Depth value(1.0) of far clip plane
	*/
	static constexpr RealType FarClipPlaneZ = 1.0f;


	Serface();
	~Serface();


	Void Clear(ClearFlag flag = ClearFlag::Color);
	Void ClearColor(const ColorF& color);
	Void ClearDepth(RealType depth);
	Void ClearStencil(Byte stencil);
	Void CopyTo(Void* Target);
	Void Resize(SizeType width, SizeType height);

	
	Void SetPixel(Int32 x, Int32 y, const ColorF& color);
	Void SetDepth(Int32 x, Int32 y, RealType depth);
	Void SetStencil(Int32 x, Int32 y, Byte stencil);
	const ColorF& GetPixel(Int32 x, Int32 y) const;
	const RealType& GetDepth(Int32 x, Int32 y) const;
	const Byte& GetStencil(Int32 x, Int32 y) const;


	ColorF* GetColorBuffer();
	RealType* GetDepthBuffer();
	Byte* GetStencilBuffer();

	SizeType GetWidth() const;
	SizeType GetHeight() const;
	SizeType GetElementCount() const;
	RealType GetAspect() const;
	const ColorF* GetColorBuffer() const;
	const RealType* GetDepthBuffer() const;
	const Byte* GetStencilBuffer() const;
private:
	SizeType width;
	SizeType height;
	SizeType elementCount;
	RealType aspect;
	ColorF* colorBuffer;
	RealType* depthBuffer;
	Byte* stencilBuffer;
};
NAMESPACE_END(Engine)