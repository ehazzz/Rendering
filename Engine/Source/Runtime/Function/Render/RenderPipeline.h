#pragma once
#include "../../Core/Mathematics/Color.h"
#include "../../Core/Mathematics/Matrix4F.h"
#include "../../Core/Base/EnumClass.h"


NAMESPACE_BEGIN(Engine)
struct Attributes;
struct Varyings;


enum class CullMode {
	Disable,
	Back,
	Front
};


enum class FillMode {
	Wireframe	= 0x01,
	Solid		= 0x10,
	All			= Wireframe | Solid,
};
ENABLE_BIT_MASK_OPERATORS(FillMode);


enum class DepthTestMode {
	Disable,
	Less,
	LEqual, // less or equal
	Equal,
	Greater,
	GEqual, // greater or equal
	Always, // pass depth test always
};


enum class DepthWriteMode {
	Disable,
	Enable,
};


enum class BlendMode {
	Disable,
	SrcAlpha_OneMinusSrcAlpha,
};


struct ENGINE_API RenderPipeline
{
	using VertexShader	= Function<Varyings, const Attributes&>;
	using PixelShader	= Function<ColorF, const Varyings&>;

	static CullMode cullMode;
	static FillMode fillMode;
	static DepthTestMode depthTestMode;
	static DepthWriteMode depthWriteMode;
	static BlendMode blendMode;
	// current filled triangle
	static Bool backface;
	// want to discard the pixel?
	static Bool discarded;

	static VertexShader VS;
	static PixelShader PS;
};
NAMESPACE_END(Engine)