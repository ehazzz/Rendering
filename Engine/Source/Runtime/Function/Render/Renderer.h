#pragma once
#include "../../Core/Mathematics/Triangle.h"

#include "Serface.h"
#include "Mesh.h"
#include "Shader.h"
#include "RenderPipeline.h"


NAMESPACE_BEGIN(Engine)
class ENGINE_API Renderer {
public:
	NOT_COPYABLE(Renderer);


	Renderer() = default;


	Void Draw(const Mesh& mesh);
	Void Draw(const MeshArray& meshArray);

	Serface& GetSerface();
private:
	Void DrawLine(Int32 x0, Int32 y0, Int32 x1, Int32 y1, const ColorF& color);
	Void DrawLine(const Vector2F& A, const Vector2F& B, const ColorF& color);
	Void DrawTriangle(const Triangle& triangle, const ColorF& color = ColorF_White);

	Void TransformVertex(Vertex* from, Varyings* to, Int32 vertexCount);

	Void SetTriangle(Varyings* vertexBuffer, UInt32* indices, UInt32 indexCount);
	Void FillTriangle(const Triangle& triangle, Varyings* varyingsA, Varyings* varyingsB, Varyings* varyingsC);

	Bool CullOp(CullMode mode, const Vector3F& viewDirection, const Vector3F& triangleNormal);
	Bool DepthTestOp(DepthTestMode mode, Int32 x, Int32 y, RealType depth);
	ColorF BlendOp(BlendMode mode, const ColorF& source, const ColorF& destination);

	/**
	*	Calculate axis-aligned bounding box
	* 
	*	Vector4Int[0] - left
	*	Vector4Int[1] - right
	*	Vector4Int[2] - bottom
	*	Vector4Int[3] - top
	*/
	static Vector4Int CalculateAABB(const Triangle& triangle);

	template<typename T> static T InterpolateAttributes(const T& a, const T& b, const T& c, RealType alpha, RealType beta, RealType gamma, RealType weight);
	template<typename T> static T InterpolateAttributes(const T& a, const T& b, const T& c, const Vector4F& params);
private:
	Serface serface;
};


template<typename T>
inline T Renderer::InterpolateAttributes(const T& a, const T& b, const T& c, RealType alpha, RealType beta, RealType gamma, RealType weight)
{
	return (a * alpha + b * beta + c * gamma) * weight;
}

template<typename T>
inline T Renderer::InterpolateAttributes(const T& a, const T& b, const T& c, const Vector4F& params)
{
	return InterpolateAttributes(a, b, c, params[0], params[1], params[2], params[3]);
}
NAMESPACE_END(Engine)